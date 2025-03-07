/*
 * aim_chat.c
 *
 * Routines for the Chat service.
 *
 */

#define FAIM_INTERNAL
#include <aim.h> 

faim_export char *aim_chat_getname(struct aim_conn_t *conn)
{
  if (!conn)
    return NULL;
  if (conn->type != AIM_CONN_TYPE_CHAT)
    return NULL;

  return (char *)conn->priv; /* yuck ! */
}

faim_export struct aim_conn_t *aim_chat_getconn(struct aim_session_t *sess, char *name)
{
  struct aim_conn_t *cur;
  
  faim_mutex_lock(&sess->connlistlock);
  for (cur = sess->connlist; cur; cur = cur->next) {
    if (cur->type != AIM_CONN_TYPE_CHAT)
      continue;
    if (!cur->priv) {
      faimdprintf(sess, 0, "faim: chat: chat connection with no name! (fd = %d)\n", cur->fd);
      continue;
    }
    if (strcmp((char *)cur->priv, name) == 0)
      break;
  }
  faim_mutex_unlock(&sess->connlistlock);

  return cur;
}

faim_export int aim_chat_attachname(struct aim_conn_t *conn, char *roomname)
{
  if (!conn || !roomname)
    return -1;

  if (conn->priv)
    free(conn->priv);

  conn->priv = strdup(roomname);

  return 0;
}

/*
 * Send a Chat Message.
 *
 * Possible flags:
 *   AIM_CHATFLAGS_NOREFLECT   --  Unset the flag that requests messages
 *                                 should be sent to their sender.
 *   AIM_CHATFLAGS_AWAY        --  Mark the message as an autoresponse
 *                                 (Note that WinAIM does not honor this,
 *                                 and displays the message as normal.)
 *
 * XXX convert this to use tlvchains 
 */
faim_export unsigned long aim_chat_send_im(struct aim_session_t *sess,
					   struct aim_conn_t *conn, 
					   unsigned short flags,
					   const char *msg,
					   int msglen)
{   

  int curbyte,i;
  struct command_tx_struct *newpacket;
  struct aim_msgcookie_t *cookie;

  if (!sess || !conn || !msg || (msglen <= 0))
    return 0;
  
  if (!(newpacket = aim_tx_new(sess, conn, AIM_FRAMETYPE_OSCAR, 0x0002, 1152)))
    return -1;

  newpacket->lock = 1; /* lock struct */

  curbyte  = 0;
  curbyte += aim_putsnac(newpacket->data+curbyte, 
			 0x000e, 0x0005, 0x0000, sess->snac_nextid);

  /* 
   * Generate a random message cookie 
   */
  for (i=0;i<8;i++)
    curbyte += aimutil_put8(newpacket->data+curbyte, (u_char) rand());

  cookie = aim_mkcookie(newpacket->data+curbyte-8, AIM_COOKIETYPE_CHAT, NULL);
  cookie->data = strdup(conn->priv); /* chat hack dependent */

  aim_cachecookie(sess, cookie);

  /*
   * Channel ID. 
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0003);

  /*
   * Type 1: Flag meaning this message is destined to the room.
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0001);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0000);
  
  /*
   * Type 6: Reflect
   */
  if (!(flags & AIM_CHATFLAGS_NOREFLECT)) {
    curbyte += aimutil_put16(newpacket->data+curbyte, 0x0006);
    curbyte += aimutil_put16(newpacket->data+curbyte, 0x0000);
  }

  /*
   * Type 7: Autoresponse
   */
  if (flags & AIM_CHATFLAGS_AWAY) {
    curbyte += aimutil_put16(newpacket->data+curbyte, 0x0007);
    curbyte += aimutil_put16(newpacket->data+curbyte, 0x0000);
  }

  /*
   * Type 5: Message block.  Contains more TLVs.
   *
   * This could include other information... We just
   * put in a message TLV however.  
   * 
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0005);
  curbyte += aimutil_put16(newpacket->data+curbyte, strlen(msg)+4);

  /*
   * SubTLV: Type 1: Message
   */
  curbyte += aim_puttlv_str(newpacket->data+curbyte, 0x0001, strlen(msg), msg);
  
  newpacket->commandlen = curbyte;

  newpacket->lock = 0;
  aim_tx_enqueue(sess, newpacket);

  return (sess->snac_nextid++);
}

/*
 * Join a room of name roomname.  This is the first
 * step to joining an already created room.  It's 
 * basically a Service Request for family 0x000e, 
 * with a little added on to specify the exchange
 * and room name.
 *
 */
faim_export unsigned long aim_chat_join(struct aim_session_t *sess,
					struct aim_conn_t *conn, 
					u_short exchange,
					const char *roomname)
{
  struct command_tx_struct *newpacket;
  int i;

  if (!sess || !conn || !roomname)
    return 0;
  
  if (!(newpacket = aim_tx_new(sess, conn, AIM_FRAMETYPE_OSCAR, 0x0002, 10+9+strlen(roomname)+2)))
    return -1;

  newpacket->lock = 1;
  
  i = aim_putsnac(newpacket->data, 0x0001, 0x0004, 0x0000, sess->snac_nextid);

  i+= aimutil_put16(newpacket->data+i, 0x000e);

  /* 
   * this is techinally a TLV, but we can't use normal functions
   * because we need the extraneous nulls and other weird things.
   */
  i+= aimutil_put16(newpacket->data+i, 0x0001);
  i+= aimutil_put16(newpacket->data+i, 2+1+strlen(roomname)+2);
  i+= aimutil_put16(newpacket->data+i, exchange);
  i+= aimutil_put8(newpacket->data+i, strlen(roomname));
  i+= aimutil_putstr(newpacket->data+i, roomname, strlen(roomname));
  i+= aimutil_put16(newpacket->data+i, 0x0000); /* instance? */

  /*
   * Chat hack.
   *
   * XXX: A problem occurs here if we request a channel
   *      join but it fails....pendingjoin will be nonnull
   *      even though the channel is never going to get a
   *      redirect!
   *
   */
  sess->pendingjoin = strdup(roomname);
  sess->pendingjoinexchange = exchange;

  newpacket->lock = 0;
  aim_tx_enqueue(sess, newpacket);

  aim_cachesnac(sess, 0x0001, 0x0004, 0x0000, roomname, strlen(roomname)+1);

  return sess->snac_nextid;
}

faim_internal int aim_chat_readroominfo(u_char *buf, struct aim_chat_roominfo *outinfo)
{
  int namelen = 0;
  int i = 0;

  if (!buf || !outinfo)
    return 0;

  outinfo->exchange = aimutil_get16(buf+i);
  i += 2;

  namelen = aimutil_get8(buf+i);
  i += 1;

  outinfo->name = (char *)malloc(namelen+1);
  memcpy(outinfo->name, buf+i, namelen);
  outinfo->name[namelen] = '\0';
  i += namelen;

  outinfo->instance = aimutil_get16(buf+i);
  i += 2;
  
  return i;
}

faim_export unsigned long aim_chat_clientready(struct aim_session_t *sess,
					       struct aim_conn_t *conn)
{
  struct command_tx_struct *newpacket;
  int i;

  if (!(newpacket = aim_tx_new(sess, conn, AIM_FRAMETYPE_OSCAR, 0x0002, 0x20)))
    return -1;

  newpacket->lock = 1;

  i = aim_putsnac(newpacket->data, 0x0001, 0x0002, 0x0000, sess->snac_nextid);

  i+= aimutil_put16(newpacket->data+i, 0x000e);
  i+= aimutil_put16(newpacket->data+i, 0x0001);

  i+= aimutil_put16(newpacket->data+i, 0x0004);
  i+= aimutil_put16(newpacket->data+i, 0x0001);

  i+= aimutil_put16(newpacket->data+i, 0x0001);
  i+= aimutil_put16(newpacket->data+i, 0x0003);

  i+= aimutil_put16(newpacket->data+i, 0x0004);
  i+= aimutil_put16(newpacket->data+i, 0x0686);

  newpacket->lock = 0;
  aim_tx_enqueue(sess, newpacket);

  return (sess->snac_nextid++);
}

faim_export int aim_chat_leaveroom(struct aim_session_t *sess, char *name)
{
  struct aim_conn_t *conn;

  if ((conn = aim_chat_getconn(sess, name)))
    aim_conn_close(conn);

  if (!conn)
    return -1;
  return 0;
}

/*
 * conn must be a BOS connection!
 */
faim_export unsigned long aim_chat_invite(struct aim_session_t *sess,
					  struct aim_conn_t *conn,
					  char *sn,
					  char *msg,
					  u_short exchange,
					  char *roomname,
					  u_short instance)
{
  struct command_tx_struct *newpacket;
  int i,curbyte=0;
  struct aim_msgcookie_t *cookie;
  struct aim_invite_priv *priv;

  if (!sess || !conn || !sn || !msg || !roomname)
    return -1;

  if (conn->type != AIM_CONN_TYPE_BOS)
    return -1;

  if (!(newpacket = aim_tx_new(sess, conn, AIM_FRAMETYPE_OSCAR, 0x0002, 1152+strlen(sn)+strlen(roomname)+strlen(msg))))
    return -1;

  newpacket->lock = 1;

  curbyte = aim_putsnac(newpacket->data, 0x0004, 0x0006, 0x0000, sess->snac_nextid);

  /*
   * Cookie
   */
  for (i=0;i<8;i++)
    curbyte += aimutil_put8(newpacket->data+curbyte, (u_char)rand());

  /* XXX this should get uncached by the unwritten 'invite accept' handler */
  if(!(priv = calloc(sizeof(struct aim_invite_priv), 1)))
    return -1;
  priv->sn = strdup(sn);
  priv->roomname = strdup(roomname);
  priv->exchange = exchange;
  priv->instance = instance;

  if(!(cookie = aim_mkcookie(newpacket->data+curbyte-8, AIM_COOKIETYPE_INVITE, priv)))
    return -1;
  aim_cachecookie(sess, cookie);

  /*
   * Channel (2)
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0002);

  /*
   * Dest sn
   */
  curbyte += aimutil_put8(newpacket->data+curbyte, strlen(sn));
  curbyte += aimutil_putstr(newpacket->data+curbyte, sn, strlen(sn));

  /*
   * TLV t(0005)
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0005);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x28+strlen(msg)+0x04+0x03+strlen(roomname)+0x02);
  
  /* 
   * Unknown info
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0000);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x3131);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x3538);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x3446);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x4100);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x748f);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x2420);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x6287);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x11d1);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x8222);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x4445);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x5354);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0000);
  
  /*
   * TLV t(000a) -- Unknown
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x000a);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0002);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0001);
  
  /*
   * TLV t(000f) -- Unknown
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x000f);
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x0000);
  
  /*
   * TLV t(000c) -- Invitation message
   */
  curbyte += aim_puttlv_str(newpacket->data+curbyte, 0x000c, strlen(msg), msg);

  /*
   * TLV t(2711) -- Container for room information 
   */
  curbyte += aimutil_put16(newpacket->data+curbyte, 0x2711);
  curbyte += aimutil_put16(newpacket->data+curbyte, 3+strlen(roomname)+2);
  curbyte += aimutil_put16(newpacket->data+curbyte, exchange);
  curbyte += aimutil_put8(newpacket->data+curbyte, strlen(roomname));
  curbyte += aimutil_putstr(newpacket->data+curbyte, roomname, strlen(roomname));
  curbyte += aimutil_put16(newpacket->data+curbyte, instance);

  newpacket->commandlen = curbyte;
  newpacket->lock = 0;
  aim_tx_enqueue(sess, newpacket);

  return (sess->snac_nextid++);
}

/*
 * General room information.  Lots of stuff.
 *
 * Values I know are in here but I havent attached
 * them to any of the 'Unknown's:
 *	- Language (English)
 *
 * SNAC 000e/0002
 */
static int infoupdate(struct aim_session_t *sess, aim_module_t *mod, struct command_rx_struct *rx, aim_modsnac_t *snac, unsigned char *data, int datalen)
{
  struct aim_userinfo_s *userinfo = NULL;
  aim_rxcallback_t userfunc=NULL;	
  int ret = 0, i = 0;
  int usercount = 0;
  unsigned char detaillevel = 0;
  char *roomname = NULL;
  struct aim_chat_roominfo roominfo;
  unsigned short tlvcount = 0;
  struct aim_tlvlist_t *tlvlist;
  char *roomdesc = NULL;
  unsigned short unknown_c9 = 0;
  unsigned long creationtime = 0;
  unsigned short maxmsglen = 0;
  unsigned short unknown_d2 = 0, unknown_d5 = 0;

  i += aim_chat_readroominfo(data+i, &roominfo);
  
  detaillevel = aimutil_get8(data+i);
  i++;

  if (detaillevel != 0x02) {
    if (detaillevel == 0x01)
      faimdprintf(sess, 0, "faim: chat_roomupdateinfo: detail level 1 not supported\n");
    else
      faimdprintf(sess, 0, "faim: chat_roomupdateinfo: unknown detail level %d\n", detaillevel);
    return 1;
  }
  
  tlvcount = aimutil_get16(data+i);
  i += 2;

  /*
   * Everything else are TLVs.
   */ 
  tlvlist = aim_readtlvchain(data+i, datalen-i);
  
  /*
   * TLV type 0x006a is the room name in Human Readable Form.
   */
  if (aim_gettlv(tlvlist, 0x006a, 1))
    roomname = aim_gettlv_str(tlvlist, 0x006a, 1);

  /*
   * Type 0x006f: Number of occupants.
   */
  if (aim_gettlv(tlvlist, 0x006f, 1))
    usercount = aim_gettlv16(tlvlist, 0x006f, 1);

  /*
   * Type 0x0073:  Occupant list.
   */
  if (aim_gettlv(tlvlist, 0x0073, 1)) {	
    int curoccupant = 0;
    struct aim_tlv_t *tmptlv;
    
    tmptlv = aim_gettlv(tlvlist, 0x0073, 1);

    /* Allocate enough userinfo structs for all occupants */
    userinfo = calloc(usercount, sizeof(struct aim_userinfo_s));
    
    i = 0;
    while (curoccupant < usercount)
      i += aim_extractuserinfo(sess, tmptlv->value+i, &userinfo[curoccupant++]);
  }
  
  /* 
   * Type 0x00c9: Unknown. (2 bytes)
   */
  if (aim_gettlv(tlvlist, 0x00c9, 1))
    unknown_c9 = aim_gettlv16(tlvlist, 0x00c9, 1);
  
  /* 
   * Type 0x00ca: Creation time (4 bytes)
   */
  if (aim_gettlv(tlvlist, 0x00ca, 1))
    creationtime = aim_gettlv32(tlvlist, 0x00ca, 1);

  /* 
   * Type 0x00d1: Maximum Message Length
   */
  if (aim_gettlv(tlvlist, 0x00d1, 1))
    maxmsglen = aim_gettlv16(tlvlist, 0x00d1, 1);

  /* 
   * Type 0x00d2: Unknown. (2 bytes)
   */
  if (aim_gettlv(tlvlist, 0x00d2, 1))
    unknown_d2 = aim_gettlv16(tlvlist, 0x00d2, 1);

  /* 
   * Type 0x00d3: Room Description
   */
  if (aim_gettlv(tlvlist, 0x00d3, 1))
    roomdesc = aim_gettlv_str(tlvlist, 0x00d3, 1);

  /* 
   * Type 0x00d5: Unknown. (1 byte)
   */
  if (aim_gettlv(tlvlist, 0x00d5, 1))
    unknown_d5 = aim_gettlv8(tlvlist, 0x00d5, 1);


  if ((userfunc = aim_callhandler(sess, rx->conn, snac->family, snac->subtype))) {
    ret = userfunc(sess,
		   rx, 
		   &roominfo,
		   roomname,
		   usercount,
		   userinfo,	
		   roomdesc,
		   unknown_c9,
		   creationtime,
		   maxmsglen,
		   unknown_d2,
		   unknown_d5);
  }

  free(roominfo.name);
  free(userinfo);
  free(roomname);
  free(roomdesc);
  aim_freetlvchain(&tlvlist);
 
  return ret;
}

static int userlistchange(struct aim_session_t *sess, aim_module_t *mod, struct command_rx_struct *rx, aim_modsnac_t *snac, unsigned char *data, int datalen)
{
  struct aim_userinfo_s *userinfo = NULL;
  aim_rxcallback_t userfunc;
  int i = 0, curcount = 0, ret = 0;

  while (i < datalen) {
    curcount++;
    userinfo = realloc(userinfo, curcount * sizeof(struct aim_userinfo_s));
    i += aim_extractuserinfo(sess, data+i, &userinfo[curcount-1]);
  }

  if ((userfunc = aim_callhandler(sess, rx->conn, snac->family, snac->subtype)))
    ret = userfunc(sess, rx, curcount, userinfo);

  free(userinfo);

  return ret;
}

/*
 * We could probably include this in the normal ICBM parsing 
 * code as channel 0x0003, however, since only the start
 * would be the same, we might as well do it here.
 *
 * General outline of this SNAC:
 *   snac
 *   cookie
 *   channel id
 *   tlvlist
 *     unknown
 *     source user info
 *       name
 *       evility
 *       userinfo tlvs
 *         online time
 *         etc
 *     message metatlv
 *       message tlv
 *         message string
 *       possibly others
 *  
 */
static int incomingmsg(struct aim_session_t *sess, aim_module_t *mod, struct command_rx_struct *rx, aim_modsnac_t *snac, unsigned char *data, int datalen)
{
  struct aim_userinfo_s userinfo;
  aim_rxcallback_t userfunc=NULL;	
  int ret = 0, i = 0;
  unsigned char cookie[8];
  int channel;
  struct aim_tlvlist_t *outerlist;
  char *msg = NULL;
  struct aim_msgcookie_t *ck;

  memset(&userinfo, 0x00, sizeof(struct aim_userinfo_s));

  /*
   * ICBM Cookie.  Cache it.
   */ 
  memcpy(cookie, data, 8);
  i += 8;

  if ((ck = aim_uncachecookie(sess, cookie, AIM_COOKIETYPE_CHAT))) {
    if (ck->data)
      free(ck->data);
    free(ck);
  }

  /*
   * Channel ID
   *
   * Channels 1 and 2 are implemented in the normal ICBM
   * parser.
   *
   * We only do channel 3 here.
   *
   */
  channel = aimutil_get16(data+i);
  i += 2;

  if (channel != 0x0003) {
    faimdprintf(sess, 0, "faim: chat_incoming: unknown channel! (0x%04x)\n", channel);
    return 0;
  }

  /*
   * Start parsing TLVs right away. 
   */
  outerlist = aim_readtlvchain(data+8+2, datalen-8-2);
  
  /*
   * Type 0x0003: Source User Information
   */
  if (aim_gettlv(outerlist, 0x0003, 1)) {
    struct aim_tlv_t *userinfotlv;
    
    userinfotlv = aim_gettlv(outerlist, 0x0003, 1);
    aim_extractuserinfo(sess, userinfotlv->value, &userinfo);
  }

  /*
   * Type 0x0001: Unknown.
   */
  if (aim_gettlv(outerlist, 0x0001, 1))
    ;

  /*
   * Type 0x0005: Message Block.  Conains more TLVs.
   */
  if (aim_gettlv(outerlist, 0x0005, 1)) {
    struct aim_tlvlist_t *innerlist;
    struct aim_tlv_t *msgblock;

    msgblock = aim_gettlv(outerlist, 0x0005, 1);
    innerlist = aim_readtlvchain(msgblock->value, msgblock->length);
      
    /* 
     * Type 0x0001: Message.
     */	
    if (aim_gettlv(innerlist, 0x0001, 1))
      msg = aim_gettlv_str(innerlist, 0x0001, 1);

    aim_freetlvchain(&innerlist); 
  }

  if ((userfunc = aim_callhandler(sess, rx->conn, snac->family, snac->subtype)))
    ret = userfunc(sess, rx, &userinfo, msg);

  free(msg);
  aim_freetlvchain(&outerlist);

  return ret;
}

static int snachandler(struct aim_session_t *sess, aim_module_t *mod, struct command_rx_struct *rx, aim_modsnac_t *snac, unsigned char *data, int datalen)
{

  if (snac->subtype == 0x0002)
    return infoupdate(sess, mod, rx, snac, data, datalen);
  else if ((snac->subtype == 0x0003) || (snac->subtype == 0x0004))
    return userlistchange(sess, mod, rx, snac, data, datalen);
  else if (snac->subtype == 0x0006)
    return incomingmsg(sess, mod, rx, snac, data, datalen);

  return 0;
}

faim_internal int chat_modfirst(struct aim_session_t *sess, aim_module_t *mod)
{

  mod->family = 0x000e;
  mod->version = 0x0000;
  mod->flags = 0;
  strncpy(mod->name, "chat", sizeof(mod->name));
  mod->snachandler = snachandler;

  return 0;
}
