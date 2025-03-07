/*
 *  aim_txqueue.c
 *
 * Herein lies all the mangement routines for the transmit (Tx) queue.
 *
 */

#define FAIM_INTERNAL
#include <aim.h>

#ifndef _WIN32
#include <sys/socket.h>
#endif

/*
 * Allocate a new tx frame.
 *
 * This is more for looks than anything else.
 *
 * Right now, that is.  If/when we implement a pool of transmit
 * frames, this will become the request-an-unused-frame part.
 *
 * framing = AIM_FRAMETYPE_OFT/OSCAR
 * chan = channel for OSCAR, hdrtype for OFT
 *
 */
faim_internal struct command_tx_struct *aim_tx_new(struct aim_session_t *sess, 
						   struct aim_conn_t *conn, 
						   unsigned char framing, 
						   int chan, 
						   int datalen)
{
  struct command_tx_struct *newtx;

  if (!conn) {
    faimdprintf(sess, 0, "aim_tx_new: ERROR: no connection specified\n");
    return NULL;
  }

  /* For sanity... */
  if ((conn->type == AIM_CONN_TYPE_RENDEZVOUS) || (conn->type == AIM_CONN_TYPE_RENDEZVOUS_OUT)) {
    if (framing != AIM_FRAMETYPE_OFT) {
      faimdprintf(sess, 0, "aim_tx_new: attempted to allocate inappropriate frame type for rendezvous connection\n");
      return NULL;
    }
  } else {
    if (framing != AIM_FRAMETYPE_OSCAR) {
      faimdprintf(sess, 0, "aim_tx_new: attempted to allocate inappropriate frame type for FLAP connection\n");
      return NULL;
    }
  }

  newtx = (struct command_tx_struct *)malloc(sizeof(struct command_tx_struct));
  if (!newtx)
    return NULL;
  memset(newtx, 0, sizeof(struct command_tx_struct));

  newtx->conn = conn; 

  if(datalen) {
    newtx->data = (unsigned char *)malloc(datalen);
    newtx->commandlen = datalen;
  } else
    newtx->data = NULL;

  newtx->hdrtype = framing;
  if (newtx->hdrtype == AIM_FRAMETYPE_OSCAR) {
    newtx->hdr.oscar.type = chan;
  } else if (newtx->hdrtype == AIM_FRAMETYPE_OFT) {
    newtx->hdr.oft.type = chan;
    newtx->hdr.oft.hdr2len = 0; /* this will get setup by caller */
  } else { 
    faimdprintf(sess, 0, "tx_new: unknown framing\n");
  }

  return newtx;
}

/*
 * aim_tx_enqeue__queuebased()
 *
 * The overall purpose here is to enqueue the passed in command struct
 * into the outgoing (tx) queue.  Basically...
 *   1) Make a scope-irrelevent copy of the struct
 *   2) Lock the struct
 *   3) Mark as not-sent-yet
 *   4) Enqueue the struct into the list
 *   5) Unlock the struct once it's linked in
 *   6) Return
 *
 * Note that this is only used when doing queue-based transmitting;
 * that is, when sess->tx_enqueue is set to &aim_tx_enqueue__queuebased.
 *
 */
static int aim_tx_enqueue__queuebased(struct aim_session_t *sess, struct command_tx_struct *newpacket)
{
  struct command_tx_struct *cur;

  if (newpacket->conn == NULL) {
      faimdprintf(sess, 1, "aim_tx_enqueue: WARNING: enqueueing packet with no connecetion\n");
      newpacket->conn = aim_getconn_type(sess, AIM_CONN_TYPE_BOS);
  }
 
  if (newpacket->hdrtype == AIM_FRAMETYPE_OSCAR) {
    /* assign seqnum */
    newpacket->hdr.oscar.seqnum = aim_get_next_txseqnum(newpacket->conn);
  }
  /* set some more fields */
  newpacket->lock = 1; /* lock */
  newpacket->sent = 0; /* not sent yet */
  newpacket->next = NULL; /* always last */

  /* see overhead note in aim_rxqueue counterpart */
  if (sess->queue_outgoing == NULL) {
    sess->queue_outgoing = newpacket;
  } else {
    for (cur = sess->queue_outgoing;
	 cur->next;
	 cur = cur->next)
      ;
    cur->next = newpacket;
  }

  newpacket->lock = 0; /* unlock so it can be sent */

  return 0;
}

/*
 * aim_tx_enqueue__immediate()
 *
 * Parallel to aim_tx_enqueue__queuebased, however, this bypasses
 * the whole queue mess when you want immediate writes to happen.
 *
 * Basically the same as its __queuebased couterpart, however
 * instead of doing a list append, it just calls aim_tx_sendframe()
 * right here. 
 * 
 */
static int aim_tx_enqueue__immediate(struct aim_session_t *sess, struct command_tx_struct *newpacket)
{
  if (newpacket->conn == NULL) {
    faimdprintf(sess, 1, "aim_tx_enqueue: ERROR: packet has no connection\n");
    if (newpacket->data)
      free(newpacket->data);
    free(newpacket);
    return -1;
  }

  if (newpacket->hdrtype == AIM_FRAMETYPE_OSCAR)
    newpacket->hdr.oscar.seqnum = aim_get_next_txseqnum(newpacket->conn);

  newpacket->lock = 1; /* lock */
  newpacket->sent = 0; /* not sent yet */

  aim_tx_sendframe(sess, newpacket);

  if (newpacket->data)
    free(newpacket->data);
  free(newpacket);

  return 0;
}

faim_export int aim_tx_setenqueue(struct aim_session_t *sess, 
				  int what,  
				  int (*func)(struct aim_session_t *, struct command_tx_struct *))
{
  if (!sess)
    return -1;

  if (what == AIM_TX_QUEUED)
    sess->tx_enqueue = &aim_tx_enqueue__queuebased;
  else if (what == AIM_TX_IMMEDIATE) 
    sess->tx_enqueue = &aim_tx_enqueue__immediate;
  else if (what == AIM_TX_USER) {
    if (!func)
      return -1;
    sess->tx_enqueue = func;
  } else
    return -1; /* unknown action */

  return 0;
}

faim_internal int aim_tx_enqueue(struct aim_session_t *sess, struct command_tx_struct *command)
{
  /*
   * If we want to send a connection thats inprogress, we have to force
   * them to use the queue based version. Otherwise, use whatever they
   * want.
   */
  if (command && command->conn && (command->conn->status & AIM_CONN_STATUS_INPROGRESS)) {
    return aim_tx_enqueue__queuebased(sess, command);
  }
  return (*sess->tx_enqueue)(sess, command);
}

/* 
 *  aim_get_next_txseqnum()
 *
 *   This increments the tx command count, and returns the seqnum
 *   that should be stamped on the next FLAP packet sent.  This is
 *   normally called during the final step of packet preparation
 *   before enqueuement (in aim_tx_enqueue()).
 *
 */
faim_internal unsigned int aim_get_next_txseqnum(struct aim_conn_t *conn)
{
  u_int ret;
  
  faim_mutex_lock(&conn->seqnum_lock);
  ret = ++conn->seqnum;
  faim_mutex_unlock(&conn->seqnum_lock);
  return ret;
}

/*
 *  aim_tx_flushqueue()
 *
 *  This the function is responsable for putting the queued commands
 *  onto the wire.  This function is critical to the operation of 
 *  the queue and therefore is the most prone to brokenness.  It
 *  seems to be working quite well at this point.
 *
 *  Procedure:
 *    1) Traverse the list, only operate on commands that are unlocked
 *       and haven't been sent yet.
 *    2) Lock the struct
 *    3) Allocate a temporary buffer to store the finished, fully
 *       processed packet in.
 *    4) Build the packet from the command_tx_struct data.
 *    5) Write the packet to the socket.
 *    6) If success, mark the packet sent, if fail report failure, do NOT
 *       mark the packet sent (so it will not get purged and therefore
 *       be attempted again on next call).
 *    7) Unlock the struct.
 *    8) Free the temp buffer
 *    9) Step to next struct in list and go back to 1.
 *
 */
faim_internal int aim_tx_sendframe(struct aim_session_t *sess, struct command_tx_struct *cur)
{
  int buflen = 0;
  unsigned char *curPacket;

  if (!cur)
    return -1; /* fatal */

  cur->lock = 1; /* lock the struct */

  if (cur->hdrtype == AIM_FRAMETYPE_OSCAR)
    buflen = cur->commandlen + 6;
  else if (cur->hdrtype == AIM_FRAMETYPE_OFT)
    buflen = cur->hdr.oft.hdr2len + 8;
  else {
    cur->lock = 0;
    return -1;
  }

  /* allocate full-packet buffer */
  if (!(curPacket = (unsigned char *) malloc(buflen))) {
    cur->lock = 0;
    return -1;
  }
      
  if (cur->hdrtype == AIM_FRAMETYPE_OSCAR) {
    /* command byte */
    curPacket[0] = 0x2a;
      
    /* type/family byte */
    curPacket[1] = cur->hdr.oscar.type;
      
    /* bytes 3+4: word: FLAP sequence number */
    aimutil_put16(curPacket+2, cur->hdr.oscar.seqnum);

    /* bytes 5+6: word: SNAC len */
    aimutil_put16(curPacket+4, cur->commandlen);
      
    /* bytes 7 and on: raw: SNAC data */  /* XXX: ye gods! get rid of this! */
    memcpy(&(curPacket[6]), cur->data, cur->commandlen);

  } else if (cur->hdrtype == AIM_FRAMETYPE_OFT) {
    int z = 0;

    z += aimutil_put8(curPacket+z, cur->hdr.oft.magic[0]);
    z += aimutil_put8(curPacket+z, cur->hdr.oft.magic[1]);
    z += aimutil_put8(curPacket+z, cur->hdr.oft.magic[2]);
    z += aimutil_put8(curPacket+z, cur->hdr.oft.magic[3]);

    z += aimutil_put16(curPacket+z, cur->hdr.oft.hdr2len + 8);
    z += aimutil_put16(curPacket+z, cur->hdr.oft.type);

    memcpy(curPacket+z, cur->hdr.oft.hdr2, cur->hdr.oft.hdr2len);
  }

  /* 
   * For OSCAR, a full image of the raw packet data now in curPacket.
   * For OFT, an image of just the bloated header is in curPacket, 
   * since OFT allows us to do the data in a different write (yay!).
   */
  faim_mutex_lock(&cur->conn->active);
  if (send(cur->conn->fd, curPacket, buflen, 0) != buflen) {
    faim_mutex_unlock(&cur->conn->active);
    cur->sent = 1;
    aim_conn_close(cur->conn);
    return 0; /* bail out */
  }

  if ((cur->hdrtype == AIM_FRAMETYPE_OFT) && cur->commandlen) {
    int curposi;
    for(curposi = 0; curposi < cur->commandlen; curposi++)
      faimdprintf(sess, 0, "%02x ", cur->data[curposi]);

    if (send(cur->conn->fd, cur->data, cur->commandlen, 0) != (int)cur->commandlen) {
      /* 
       * Theres nothing we can do about this since we've already sent the 
       * header!  The connection is unstable.
       */
      faim_mutex_unlock(&cur->conn->active);
      cur->sent = 1;
      aim_conn_close(cur->conn);
      return 0; /* bail out */
    }

  }

  cur->sent = 1; /* mark the struct as sent */
  cur->conn->lastactivity = time(NULL);

  faim_mutex_unlock(&cur->conn->active);

  if (sess->debug >= 2) {
    int i;

    faimdprintf(sess, 2, "\nOutgoing packet: (only valid for OSCAR)");
    for (i = 0; i < buflen; i++) {
      if (!(i % 8)) 
	faimdprintf(sess, 2, "\n\t");
      faimdprintf(sess, 2, "0x%02x ", curPacket[i]);
    }
    faimdprintf(sess, 2, "\n");
  }

  cur->lock = 0; /* unlock the struct */

  free(curPacket); /* free up full-packet buffer */

  return 1; /* success */
}

faim_export int aim_tx_flushqueue(struct aim_session_t *sess)
{
  struct command_tx_struct *cur;
   
  if (sess->queue_outgoing == NULL)
    return 0;

  faimdprintf(sess, 2, "beginning txflush...\n");
  for (cur = sess->queue_outgoing; cur; cur = cur->next) {
    /* only process if its unlocked and unsent */
    if (!cur->lock && !cur->sent) {

      if (cur->conn && (cur->conn->status & AIM_CONN_STATUS_INPROGRESS))
	continue;

      /*
       * And now for the meager attempt to force transmit
       * latency and avoid missed messages.
       */
      if ((cur->conn->lastactivity + cur->conn->forcedlatency) >= time(NULL)) {
	/* FIXME FIXME -- should be a break! we dont want to block the upper layers */
	sleep((cur->conn->lastactivity + cur->conn->forcedlatency) - time(NULL));
      }

      /* XXX XXX XXX this should call the custom "queuing" function!! */
      if (aim_tx_sendframe(sess, cur) == -1)
	break;
    }
  }

  /* purge sent commands from queue */
  aim_tx_purgequeue(sess);

  return 0;
}

/*
 *  aim_tx_purgequeue()
 *  
 *  This is responsable for removing sent commands from the transmit 
 *  queue. This is not a required operation, but it of course helps
 *  reduce memory footprint at run time!  
 *
 */
faim_export void aim_tx_purgequeue(struct aim_session_t *sess)
{
  struct command_tx_struct *cur = NULL;
  struct command_tx_struct *tmp;

  if (sess->queue_outgoing == NULL)
    return;
  
  if (sess->queue_outgoing->next == NULL) {
    if (!sess->queue_outgoing->lock && sess->queue_outgoing->sent) {
      tmp = sess->queue_outgoing;
      sess->queue_outgoing = NULL;
      if (tmp->hdrtype == AIM_FRAMETYPE_OFT)
	free(tmp->hdr.oft.hdr2);
      free(tmp->data);
      free(tmp);
    }
    return;
  }

  for(cur = sess->queue_outgoing; cur->next != NULL; ) {
    if (!cur->next->lock && cur->next->sent) {
      tmp = cur->next;
      cur->next = tmp->next;
      if (tmp->hdrtype == AIM_FRAMETYPE_OFT)
	free(tmp->hdr.oft.hdr2);
      free(tmp->data);
      free(tmp);
    }	
    cur = cur->next;

    /* 
     * Be careful here.  Because of the way we just
     * manipulated the pointer, cur may be NULL and 
     * the for() will segfault doing the check unless
     * we find this case first.
     */
    if (cur == NULL)	
      break;
  }
  return;
}

/**
 * aim_tx_cleanqueue - get rid of packets waiting for tx on a dying conn
 * @sess: session
 * @conn: connection that's dying
 *
 * for now this simply marks all packets as sent and lets them
 * disappear without warning.
 *
 * doesn't respect command_tx_struct locks.
 */

faim_export int aim_tx_cleanqueue(struct aim_session_t *sess, struct aim_conn_t *conn)
{
  struct command_tx_struct *cur = NULL;

  if(!sess || !conn)
    return -1;

  /* we don't respect locks here */
  for(cur = sess->queue_outgoing; cur; cur = cur->next)
    if(cur->conn == conn)
      cur->sent = 1;
  
  return 0;
}
    
      
