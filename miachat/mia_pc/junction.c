/**
  * The MiaChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the AIM protocol.
  *
  *  Copyright 2004 by Gregory Smith
  *  (greg@alcorgrp.com)
  *
  *  This program is free software; you can redistribute it and/or
  *  modify it under the terms of the GNU General Public License
  *  as published by the Free Software Foundation; either version 2
  *  of the License, or (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  *
  * @author Gregory Smith (http://www.greg-smith.com, Greg@AlcorGrp.com)
  * @version 1.0
  */
#include "../libfaim/aim.h"
#include <windows.h>
#include <stdio.h>
#include "miachat.h"

char g_fontname[64] = "Arial";
char g_fontsize[64] = "0";
char g_fontbgcolor[64] = "White";
char g_fontfgcolor[64] = "Black";
// stubs //

/* Hrmph. I don't know how to make this look better. --mid */
static int my_handle_redirect(struct aim_session_t *sess, struct command_rx_struct *fr, ...) {
	va_list ap;
	fu16_t serviceid;
	char *ip;
	fu8_t *cookie;
//	struct gaim_connection *gc = sess->aux_data;
//	struct aim_user *user = gc->user;
	struct aim_conn_t *tstconn;
	int i;
	char *host;
	int port;

	printf("my_handle_redirect\n");

//	port = user->proto_opt[USEROPT_AUTHPORT][0] ?
//		atoi(user->proto_opt[USEROPT_AUTHPORT]) : FAIM_LOGIN_PORT,

	va_start(ap, fr);
	serviceid = (fu16_t)va_arg(ap, unsigned int);
	ip = va_arg(ap, char *);
	cookie = (fu8_t *)va_arg(ap, unsigned char *);

//	for (i = 0; i < (int)strlen(ip); i++) {
//		if (ip[i] == ':') {
//			port = atoi(&(ip[i+1]));
//			break;
//		}
//	}
//	host = strdup(ip);

	switch(serviceid) {
	case 0x7: /* Authorizer */
		printf("Reconnecting with authorizor...\n");
//		tstconn = aim_newconn(sess, AIM_CONN_TYPE_AUTH, NULL);
//		if (tstconn == NULL) {
//			printf("unable to reconnect with authorizer\n");
//			free(host);
//			return 1;
//		}
//		aim_conn_addhandler(sess, tstconn, 0x0001, 0x0003, server_ready_auth, 0);
//		aim_conn_addhandler(sess, tstconn, 0x0001, 0x0007, rateresp_auth, 0);
//		aim_conn_addhandler(sess, tstconn, 0x0007, 0x0003, my_info_change, 0);
//		aim_conn_addhandler(sess, tstconn, 0x0007, 0x0005, my_info_change, 0);
//		aim_conn_addhandler(sess, tstconn, 0x0007, 0x0007, my_account_confirm, 0);

//		tstconn->status |= AIM_CONN_STATUS_INPROGRESS;
//		tstconn->fd = proxy_connect(host, port, oscar_auth_connect, gc);
//		if (tstconn->fd < 0) {
//			aim_conn_kill(sess, &tstconn);
//			debug_printf("unable to reconnect with authorizer\n");
//			g_free(host);
//			return 1;
//		}
//		aim_auth_sendcookie(sess, tstconn, cookie);
		break;
	case 0xd: /* ChatNav */
		printf("ChatNav\n");
//		tstconn = aim_newconn(sess, AIM_CONN_TYPE_CHATNAV, NULL);
//		if (tstconn == NULL) {
//			debug_printf("unable to connect to chatnav server\n");
//			g_free(host);
//			return 1;
//		}
//		aim_conn_addhandler(sess, tstconn, 0x0001, 0x0003, server_ready_chatnav, 0);

//		tstconn->status |= AIM_CONN_STATUS_INPROGRESS;
//		tstconn->fd = proxy_connect(host, port, oscar_chatnav_connect, gc);
//		if (tstconn->fd < 0) {
//			aim_conn_kill(sess, &tstconn);
//			debug_printf("unable to connect to chatnav server\n");
//			g_free(host);
//			return 1;
//		}
//		aim_auth_sendcookie(sess, tstconn, cookie);
		break;
	case 0xe: /* Chat */
		printf("Chat\n");
//		{
//		char *roomname;
//		fu16_t exchange;
//		struct chat_connection *ccon;

//		roomname = va_arg(ap, char *);
//		exchange = (fu16_t)va_arg(ap, unsigned int);

//		tstconn = aim_newconn(sess, AIM_CONN_TYPE_CHAT, NULL);
//		if (tstconn == NULL) {
//			debug_printf("unable to connect to chat server\n");
//			g_free(host);
//			return 1;
//		}

//		aim_conn_addhandler(sess, tstconn, 0x0001, 0x0003, server_ready_chat, 0);
//		ccon = g_new0(struct chat_connection, 1);
//		ccon->conn = tstconn;
//		ccon->gc = gc;
//		ccon->fd = -1;
//		ccon->name = g_strdup(roomname);
//		ccon->exchange = exchange;
//		ccon->show = extract_name(roomname);
		
//		ccon->conn->status |= AIM_CONN_STATUS_INPROGRESS;
//		ccon->conn->fd = proxy_connect(host, port, oscar_chat_connect, ccon);
//		if (ccon->conn->fd < 0) {
//			aim_conn_kill(sess, &tstconn);
//			debug_printf("unable to connect to chat server\n");
//			g_free(host);
//			g_free(ccon->show);
//			g_free(ccon->name);
//			g_free(ccon);
//			return 1;
//		}
//		aim_auth_sendcookie(sess, tstconn, cookie);
//		debug_printf("Connected to chat room %s exchange %d\n", roomname, exchange);
//		}
		break;
	default: /* huh? */
		printf("got redirect for unknown service 0x%04x\n", serviceid);
		break;
	}

	va_end(ap);

//	g_free(host);
	return 1;
}

/* XXX this is frivelous... do you really want to know this info? */
static int my_parse_buddyrights(struct aim_session_t *sess, struct command_rx_struct *fr, ...) {
	va_list ap;
	fu16_t maxbuddies, maxwatchers;

	va_start(ap, fr);
	maxbuddies = (fu16_t)va_arg(ap, unsigned int);
	maxwatchers = (fu16_t)va_arg(ap, unsigned int);
	va_end(ap);

	printf("buddy list rights: Max buddies = %d / Max watchers = %d\n", maxbuddies, maxwatchers);

	return 1;
}

my_parse_locerr()
{
	printf("my_parse_locerr\n");
}
my_parse_misses()
{
	printf("my_parse_misses\n");
}
my_parse_ratechange()
{
	printf("my_parse_ratechange\n");
}
my_parse_evilnotify()
{
	printf("my_parse_evilnotify\n");
}
my_parse_searcherror()
{
	printf("my_parse_searcherror\n");
}
my_parse_searchreply()
{
	printf("my_parse_searchreply\n");
}
my_parse_msgerr()
{
	printf("my_parse_msgerr\n");
	sprintf(msgbuf, "user_offline|unknown");
	serial_send(tty, msgbuf);
}
my_parse_user_info()
{
	printf("my_parse_user_info\n");
}
my_parse_msgack()
{
	printf("my_parse_msgack\n");
}

static int my_parse_motd(struct aim_session_t *sess, struct command_rx_struct *fr, ...) {
	char *msg;
	fu16_t id;
	va_list ap;
	char buildbuf[150];

	va_start(ap, fr);
	id  = (fu16_t)va_arg(ap, unsigned int);
	msg = va_arg(ap, char *);
	va_end(ap);

	aim_getbuildstring(buildbuf, sizeof(buildbuf));

	printf("MOTD: %s (%d)\n", msg ? msg : "Unknown", id);
	printf("MiaChat %s / libfaim %s\n", VERSION, buildbuf);
	if (id < 4)
		printf("Your connection may be lost. AOL error");

	return 1;
}
static int my_icbm_param_info(struct aim_session_t *sess, struct command_rx_struct *fr, ...) {
//	struct aim_icbmparameters *params;
	va_list ap;

	va_start(ap, fr);
//	params = va_arg(ap, struct aim_icbmparameters *);
	va_end(ap);

	/* evidently this crashes on solaris. i have no clue why
	debug_printf("ICBM Parameters: maxchannel = %d, default flags = 0x%08lx, max msg len = %d, "
			"max sender evil = %f, max receiver evil = %f, min msg interval = %ld\n",
			params->maxchan, params->flags, params->maxmsglen,
			((float)params->maxsenderwarn)/10.0, ((float)params->maxrecverwarn)/10.0,
			params->minmsginterval);
	*/

	/* Maybe senderwarn and recverwarn should be user preferences... */
//	params->maxmsglen = 8000;
//	params->minmsginterval = 0;

//	aim_seticbmparam(sess, fr->conn, params);
	aim_seticbmparam(sess, fr->conn);

	return 1;
}

my_parse_genericerr()
{
	printf("my_parse_genericerr\n");
}
int my_memrequest(struct aim_session_t *sess, struct command_rx_struct *fr, ...) {
	va_list ap;
	struct pieceofcrap *pos;
	fu32_t offset, len;
	char *modname;
	int fd;

	va_start(ap, fr);
	offset = (fu32_t)va_arg(ap, unsigned long);
	len = (fu32_t)va_arg(ap, unsigned long);
	modname = va_arg(ap, char *);
	va_end(ap);

	printf("offset: %d, len: %d, file: %s\n", offset, len, modname ? modname : "aim.exe");
	if (len == 0) {
		printf("len is 0, hashing NULL\n");
		aim_sendmemblock(sess, fr->conn, offset, len, NULL,
				AIM_SENDMEMBLOCK_FLAG_ISREQUEST);
		return 1;
	}
	/* uncomment this when you're convinced it's right. remember, it's been wrong before.*/
	if (offset > AIM_MAX_FILE_SIZE || len > AIM_MAX_FILE_SIZE) {
		char *buf;
		int i = 8;
		if (modname)
			i += strlen(modname);
		buf = malloc(i);
		i = 0;
		if (modname) {
			memcpy(buf, modname, strlen(modname));
			i += strlen(modname);
		}
		buf[i++] = offset & 0xff;
		buf[i++] = (offset >> 8) & 0xff;
		buf[i++] = (offset >> 16) & 0xff;
		buf[i++] = (offset >> 24) & 0xff;
		buf[i++] = len & 0xff;
		buf[i++] = (len >> 8) & 0xff;
		buf[i++] = (len >> 16) & 0xff;
		buf[i++] = (len >> 24) & 0xff;
		printf("len + offset is invalid, hashing request\n");
		aim_sendmemblock(sess, fr->conn, offset, i, buf, AIM_SENDMEMBLOCK_FLAG_ISREQUEST);
		free(buf);
		return 1;
	}
	

/*	pos = calloc(sizeof(struct pieceofcrap), 1);
	pos->gc = sess->aux_data;
	pos->conn = fr->conn;

	pos->offset = offset;
	pos->len = len;
	pos->modname = modname ? g_strdup(modname) : NULL;

	fd = proxy_connect("gaim.sourceforge.net", 80, straight_to_hell, pos);
	if (fd < 0) {
		if (pos->modname)
			g_free(pos->modname);
		g_free(pos);
		do_error_dialog("Gaim was unable to get a valid hash for logging into AIM."
				" You may be disconnected shortly.", "Login Error");
	}
	pos->fd = fd;
*/
		printf("MiaChat was unable to get a valid hash for logging into AIM."
				" You may be disconnected shortly.\n");

	return 1;
}

static int my_selfinfo(struct aim_session_t *sess, struct command_rx_struct *fr, ...) {
	va_list ap;
//	struct aim_userinfo_t *info;
//	struct gaim_connection *gc = sess->aux_data;

	printf("my_selfinfo\n");
	va_start(ap, fr);
//	info = va_arg(ap, struct aim_userinfo_t *);
	va_end(ap);

//	printf("warning=%d\n", info->warnlevel);
//	gc->evil = info->warnlevel/10;
//	printf("onlinesince = %d\n", info->onlinesince);
//	gc->correction_time = (info->onlinesince - gc->login_time);

	return 1;
}

//
// windows socket stuff
//
void my_socket_init()
{
	WSADATA wsaData;
	int rc;

	if((rc=WSAStartup( MAKEWORD(2,0), &wsaData )))
	{
		perror("Sorry, can't initialize Windows Sockets...");
		DBG("Error code=%d", rc);
		exit(1);
	}
}

#define SEPARATOR "|"

static void oscar_debug(struct aim_session_t *sess, int level, const char *format, va_list va, ...) 
{
	char buf[256];
	vsprintf(buf, format, va);
	//printf("oscar_debug %s\n", buf);
}

struct client_info_s client_info = AIM_CLIENTINFO_KNOWNGOOD_4_7_2480;

static int my_parse_login(struct aim_session_t *sess, struct command_rx_struct *rx, ...) {
	char *key;
	va_list ap;
	

	va_start(ap, rx);
	key = va_arg(ap, char *);
	va_end(ap);

	printf("parse_login...\n");
	DBG("\nmy_parse_login ... key=%s\n", key);

	aim_send_login(sess, rx->conn, global_sn, global_passwd, &client_info, key);

	return 1;
}

static int my_bosrights(struct aim_session_t *sess, struct command_rx_struct *rx, ...) {
	fu16_t maxpermits, maxdenies;
	va_list ap;

	va_start(ap, rx->conn);
	maxpermits = (fu16_t)va_arg(ap, unsigned int);
	maxdenies = (fu16_t)va_arg(ap, unsigned int);
	va_end(ap);

	DBG("BOS rights: Max permit = %d / Max deny = %d\n", maxpermits, maxdenies);

	serial_send(tty, "connected");

	aim_bos_clientready(sess, rx->conn);

	aim_bos_reqservice(sess, rx->conn, AIM_CONN_TYPE_CHATNAV);

	return 1;
}

static int rateresp_bos(struct aim_session_t *sess, struct command_rx_struct *rx, ...) {

	DBG("rateresp_bos\n");
	aim_bos_ackrateresp(sess, rx->conn);
	aim_bos_reqpersonalinfo(sess, rx->conn);
	aim_bos_reqlocaterights(sess, rx->conn);
//	aim_bos_setprofile(sess, rx->conn, gc->user->user_info, NULL, gaim_caps);
	aim_bos_reqbuddyrights(sess, rx->conn);

//	aim_reqicbmparams(sess, rx->conn);
	aim_bos_reqicbmparaminfo(sess, rx->conn);

	aim_bos_reqrights(sess, rx->conn);
	aim_bos_setgroupperm(sess, rx->conn, AIM_FLAG_ALLUSERS);
	aim_bos_setprivacyflags(sess, rx->conn, AIM_PRIVFLAGS_ALLOWIDLE | AIM_PRIVFLAGS_ALLOWMEMBERSINCE);

	return 1;
}

static int server_ready_bos(struct aim_session_t *sess, struct command_rx_struct *rx, ...) {
	aim_setversions(sess, rx->conn);
	aim_bos_reqrate(sess, rx->conn); /* request rate info */
	DBG("done with BOS ServerReady\n");

	return 1;
}

static char *strip_html(char *s)
{
	static char buf[BUF_LONG];
	int i;
	char *x;
//printf("%s\n", s);
	strcpy(buf, s);
	for(i=0; buf[i]; i++)
	{
		while (buf[i] == '<')
		{
			x = strchr(buf, '>');
			if (x) 
			{
				strcpy(&buf[i], x+1);
			}
			else
			{
				break;
			}
		}
	}
	return buf;
}

static int incomingim_chan1(struct aim_session_t *sess, struct aim_conn_t *conn, struct aim_userinfo_s *userinfo, struct aim_incomingim_ch1_args *args) {
	char *tmp = malloc(BUF_LONG);
	int flags = 0;

	if (args->icbmflags & AIM_IMFLAGS_UNICODE) {
		int i;
		
		for (i = 0, tmp[0] = '\0'; i < args->msglen; i += 2) {
			unsigned short uni;
			
			uni = ((args->msg[i] & 0xff) << 8) | (args->msg[i+1] & 0xff);

			if ((uni < 128) || ((uni >= 160) && (uni <= 255))) { /* ISO 8859-1 */
				
				sprintf(tmp+strlen(tmp), "%c", uni);
				
			} else { /* something else, do UNICODE entity */
				sprintf(tmp+strlen(tmp), "&#%04x;", uni);
			}
		}
	} else
		sprintf(tmp, "%s", args->msg);

	DBG("!!!%s", strip_html(tmp));
	sprintf(msgbuf, "recv_msg|%s|%s", userinfo->sn, strip_html(tmp));
	serial_send(tty, msgbuf);

	free(tmp);

	return 1;
}

static int incomingim_chan2(struct aim_session_t *sess, struct aim_conn_t *conn, struct aim_userinfo_t *userinfo, struct aim_incomingim_ch2_args *args) {
	DBG("??? Chat room message ???\n");
	return 1;
}

static int my_parse_incoming_im(struct aim_session_t *sess, struct command_rx_struct *rx, ...) {
	int channel, ret = 0;
	struct aim_userinfo_t *userinfo;
	va_list ap;

	va_start(ap, rx);
	channel = va_arg(ap, int);
	userinfo = va_arg(ap, struct aim_userinfo_t *);

	printf("parse_incoming_im\n");
	/* channel 1: standard message */
	if (channel == 1) {
		struct aim_incomingim_ch1_args *args;

		args = va_arg(ap, struct aim_incomingim_ch1_args *);

		ret = incomingim_chan1(sess, rx->conn, userinfo, args);

	} else if (channel == 2) {
		struct aim_incomingim_ch2_args *args;

		args = va_arg(ap, struct aim_incomingim_ch2_args *);

		ret = incomingim_chan2(sess, rx->conn, userinfo, args);
	}

	va_end(ap);

	return ret;
}

static int my_parse_oncoming(struct aim_session_t *sess, struct command_rx_struct *rx, ...) {
	struct aim_userinfo_s *info;
//	time_t time_idle;
//	int type = 0;
//	char *tmp;

	va_list ap;
	va_start(ap, rx);
	info = va_arg(ap, struct aim_userinfo_t *);
	va_end(ap);
	printf("parse_oncoming...\n");
//	if (!od->icq) {
//		if (info->flags & AIM_FLAG_ACTIVEBUDDY)
//			type |= UC_AB;
//		if (info->flags & AIM_FLAG_UNCONFIRMED)
//			type |= UC_UNCONFIRMED;
//		if (info->flags & AIM_FLAG_ADMINISTRATOR)
//			type |= UC_ADMIN;
//		if (info->flags & AIM_FLAG_AOL)
//			type |= UC_AOL;
//		if (info->flags & AIM_FLAG_FREE)
//			type |= UC_NORMAL;
//		if (info->flags & AIM_FLAG_AWAY)
//			type |= UC_UNAVAILABLE;
//	} else {
//		if (info->icqinfo.status) {
//			type = (info->icqinfo.status << 6);
//			if (!(info->icqinfo.status & AIM_ICQ_STATE_CHAT))
//				type |= UC_UNAVAILABLE;
//		}
//		printf("icq status: %d\n", info->icqinfo.status);
//	}

//	if (info->idletime) {
//		time(&time_idle);
//		time_idle -= info->idletime*60;
//	} else
//		time_idle = 0;

//	tmp = g_strdup(normalize(gc->username));
//	if (!strcmp(tmp, normalize(info->sn)))
//		g_snprintf(gc->displayname, sizeof(gc->displayname), "%s", info->sn);
//	g_free(tmp);

//	serv_got_update(gc, info->sn, 1, info->warnlevel/10, info->onlinesince,
//			time_idle, type, info->capabilities);
	sprintf(msgbuf, "user_online|%s", info->sn);
	serial_send(tty, msgbuf);
	DBG("BUDDY ONLINE %s\n", info->sn);
	return 1;
}

static int my_parse_offgoing(struct aim_session_t *sess, struct command_rx_struct *rx, ...) {
	struct aim_userinfo_s *info;
	va_list ap;
//	struct gaim_connection *gc = sess->aux_data;

	va_start(ap, rx);
	info = va_arg(ap, struct aim_userinfo_s *);
	va_end(ap);
    printf("parse_offgoing\n");
//	serv_got_update(gc, info->sn, 0, 0, 0, 0, 0, 0);
	sprintf(msgbuf, "user_offline|%s", info->sn);
	serial_send(tty, msgbuf);
	DBG("BUDDY OFFLINE %s\n", info->sn);
	return 1;
}

static int my_parse_auth_resp(struct aim_session_t *sess, struct aim_conn_t *fr, ...) {
	va_list ap;
	struct aim_conn_t *bosconn = NULL;
	char *sn = NULL, *bosip = NULL, *errurl = NULL, *email = NULL;
	fu8_t *cookie = NULL;
//	unsigned char *cookie = NULL;
	int errorcode = 0, regstatus = 0;
	int latestbuild = 0, latestbetabuild = 0;
	char *latestrelease = NULL, *latestbeta = NULL;
	char *latestreleaseurl = NULL, *latestbetaurl = NULL;
	char *latestreleaseinfo = NULL, *latestbetainfo = NULL;
//	int i; 
//	char *host; int port;
//	struct aim_user *user;

	va_start(ap, fr);
	sn = va_arg(ap, char *);
	errorcode = va_arg(ap, int);
	errurl = va_arg(ap, char *);
	regstatus = va_arg(ap, int);
	email = va_arg(ap, char *);
	bosip = va_arg(ap, char *);
	cookie = va_arg(ap, unsigned char *);

	latestrelease = va_arg(ap, char *);
	latestbuild = va_arg(ap, int);
	latestreleaseurl = va_arg(ap, char *);
	latestreleaseinfo = va_arg(ap, char *);

	latestbeta = va_arg(ap, char *);
	latestbetabuild = va_arg(ap, int);
	latestbetaurl = va_arg(ap, char *);
	latestbetainfo = va_arg(ap, char *);

	va_end(ap);

	printf("auth_resp...\n");
	DBG("inside auth_resp (Screen name: %s)\n", sn);

	if (errorcode || !bosip || !cookie) {
		switch (errorcode) {
		case 0x05:
			/* Incorrect nick/password */
			serial_send(tty, "bad_password");
			printf("Incorrect nickname or password\n");
			break;
		case 0x11:
			/* Suspended account */
			printf("Your account is currently suspended\n");
			break;
		case 0x18:
			/* connecting too frequently */
			printf("You have been connecting and disconnecting too frequently. Wait ten minutes and try again. If you continue to try, you will need to wait even longer\n");
			break;
		case 0x1c:
			/* client too old */
			printf("The client version you are using is too old. Please upgrade \n");
			break;
		default:
			printf("Authentication Failed\n");
			break;
		}
		printf("Login Error Code 0x%04x\n", errorcode);
		printf("Error URL: %s\n", errurl);
		return 1;
	}


	DBG("Reg status: %2d\n", regstatus);
	if (email) {
		DBG("Email: %s\n", email);
	} else {
		DBG("Email is NULL\n");
	}
	DBG("BOSIP: %s\n", bosip);
	if (latestbeta)
		printf("Latest WinAIM beta version %s, build %d, at %s (%s)\n",
				latestbeta, latestbetabuild, latestbetaurl, latestbetainfo);
	if (latestrelease)
		printf("Latest WinAIM released version %s, build %d, at %s (%s)\n",
				latestrelease, latestbuild, latestreleaseurl, latestreleaseinfo);
	DBG("Closing auth connection...\n");
	aim_conn_kill(sess, &conn);

	bosconn = aim_newconn(sess, AIM_CONN_TYPE_BOS, bosip);
	if (bosconn == NULL) {
		printf("Internal Error");
		return 0;
	}
	conn = bosconn;

	aim_conn_addhandler(sess, bosconn, 0x0009, 0x0003, my_bosrights, 0);
	aim_conn_addhandler(sess, bosconn, 0x0001, 0x0007, rateresp_bos, 0); // rate info
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_ACK, AIM_CB_ACK_ACK, NULL, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_GEN, AIM_CB_GEN_SERVERREADY, server_ready_bos, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_GEN, AIM_CB_GEN_RATEINFO, NULL, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_GEN, AIM_CB_GEN_REDIRECT, my_handle_redirect, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_BUD, AIM_CB_BUD_RIGHTSINFO, my_parse_buddyrights, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_BUD, AIM_CB_BUD_ONCOMING, my_parse_oncoming, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_BUD, AIM_CB_BUD_OFFGOING, my_parse_offgoing, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_MSG, AIM_CB_MSG_INCOMING, my_parse_incoming_im, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_LOC, AIM_CB_LOC_ERROR, my_parse_locerr, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_MSG, AIM_CB_MSG_MISSEDCALL, my_parse_misses, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_GEN, AIM_CB_GEN_RATECHANGE, my_parse_ratechange, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_GEN, AIM_CB_GEN_EVIL, my_parse_evilnotify, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_LOK, AIM_CB_LOK_ERROR, my_parse_searcherror, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_LOK, 0x0003, my_parse_searchreply, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_MSG, AIM_CB_MSG_ERROR, my_parse_msgerr, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_LOC, AIM_CB_LOC_USERINFO, my_parse_user_info, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_MSG, AIM_CB_MSG_ACK, my_parse_msgack, 0);
	aim_conn_addhandler(sess, bosconn, AIM_CB_FAM_GEN, AIM_CB_GEN_MOTD, my_parse_motd, 0);
	aim_conn_addhandler(sess, bosconn, 0x0004, 0x0005, my_icbm_param_info, 0);
	aim_conn_addhandler(sess, bosconn, 0x0001, 0x0001, my_parse_genericerr, 0);
	aim_conn_addhandler(sess, bosconn, 0x0003, 0x0001, my_parse_genericerr, 0);
	aim_conn_addhandler(sess, bosconn, 0x0009, 0x0001, my_parse_genericerr, 0);
	aim_conn_addhandler(sess, bosconn, 0x0001, 0x001f, my_memrequest, 0);
	aim_conn_addhandler(sess, bosconn, 0x0001, 0x000f, my_selfinfo, 0);

//	for (i = 0; i < (int)strlen(bosip); i++) {
//		if (bosip[i] == ':') {
//			port = atoi(&(bosip[i+1]));
//			break;
//		}
//	}
//	printf("%s\n", bosip);
//	host = strndup(bosip, i);
//	bosconn->status |= AIM_CONN_STATUS_INPROGRESS;
//	bosconn->fd = proxy_connect(host, port, oscar_bos_connect, gc);
//	free(host);
//	if (bosconn->fd < 0) {
//		errexit("Could Not Connect");
//		return 0;
//	}
	aim_auth_sendcookie(sess, bosconn, cookie);
	return 1;
}

char *fontnames[] = {"Arial", "Times New Roman", "Arial", "Courier", 0};
char *sizes[] = {"0", "1" , "2", "3", "4", "5", "6", "7", 0};
char *bgcolors[] = {"White", "Black", "White", "Red", "Orange", "Yellow", "Green", "Blue", "Teal", "Violet", 0};
char *fgcolors[] = {"Black", "Black", "White", "Red", "Orange", "Yellow", "Green", "Blue", "Teal", "Violet", 0};

void junction_dispatch(HANDLE tty, char *buf)
{
	char *cmd;
	char *tmp;
	int rc;

	DBG(">junction_dispatch\n");
	DBG("...recv %s\n", buf);

	cmd = strtok(buf, SEPARATOR);
	DBG("...cmd=%s\n", cmd);
	if (cmd == 0) goto EARLY_EXIT;

	if (SAME(cmd, "connect"))
	{
		char *sn;
		char *passwd;
		char *server;
		int port;
		char login_addr[64];

		printf("connect...\n");
		sn = strtok(NULL, SEPARATOR);
		if (!sn)
		{
			printf("ERROR: Missing Screen Name\n");
			return 0;
		}
		strcpy(global_sn, sn);

		passwd = strtok(NULL, SEPARATOR);
		if (!passwd)
		{
			printf("ERROR: Missing Password\n");
			return 0;
		}
		strcpy(global_passwd, passwd);

		server=strtok(NULL, SEPARATOR);
		if (!server)
		{
			printf("ERROR: Missing Server\n");
			return 0;
		}
		tmp = strtok(NULL, SEPARATOR);
		if (!tmp)
		{
			printf("ERROR: Missing Port\n");
			return 0;
		}
		port = atoi(tmp);

		DBG("sn=%ld, passwd=%s\n", sn, passwd);
		DBG("server=%s port=%d\n", server, port);

		my_socket_init(); // init the windows sockets

		aim_session_init(&session, AIM_SESS_FLAGS_NONBLOCKCONNECT, 0);
		//aim_setdebuggingcb(&session, oscar_debug);
		aim_tx_setenqueue(&session, AIM_TX_IMMEDIATE, NULL);
		
		sprintf(login_addr, "%s:%d", server, port);
		conn = aim_newconn(&session, AIM_CONN_TYPE_AUTH, "login.oscar.aol.com:5190");
		if (conn == NULL) errexit("ERROR: aim_newconn\n");
		DBG("conn->fd=%d\n", conn->fd);

		aim_conn_addhandler(&session, conn, AIM_CB_FAM_ATH, AIM_CB_ATH_AUTHRESPONSE, my_parse_login, 0);
		aim_conn_addhandler(&session, conn, AIM_CB_FAM_ATH, AIM_CB_ATH_LOGINRESPONSE, my_parse_auth_resp, 0);

		rc = aim_request_login(&session, conn, sn);
		if (rc) errexit("ERROR: aim_request_login\n");
	}
	else if (SAME(cmd, "logout"))
	{
		printf("Logging Out...\n");
		if (conn) aim_conn_close(conn);
		conn = NULL;
		//exit(0);
	}
	else if (SAME(cmd, "contact_add"))
	{
		char *sn = strtok(NULL, SEPARATOR);
		printf("connect_add...\n");
		aim_add_buddy(&session, conn, sn);
	}
	else if (SAME(cmd, "send_msg"))
	{
		char *sn=strtok(NULL, SEPARATOR);
		char msg[512];
		printf("send_msg...\n");
		tmp=strtok(NULL, SEPARATOR);
		sprintf(msg, "<HTML><BODY BGCOLOR=white><FONT FACE=\"%s\" SIZE=%s COLOR=%s BACK=%s>%s</FONT></BODY></HTML>",
				g_fontname, g_fontsize, g_fontfgcolor, g_fontbgcolor, tmp);
		aim_send_im(&session, conn, sn, 0, msg);
//printf("CYBIKO: %s\n", msg);
	}
	else if (SAME(cmd, "font"))
	{
		int font = atoi(strtok(NULL, SEPARATOR));
		int size = atoi(strtok(NULL, SEPARATOR))+2;
		int bgcolor = atoi(strtok(NULL, SEPARATOR));
		int fgcolor = atoi(strtok(NULL, SEPARATOR));

		printf("font...\n");
		strcpy(g_fontname, fontnames[font]);
		strcpy(g_fontsize, sizes[size]);
		strcpy(g_fontbgcolor, bgcolors[bgcolor]);
		strcpy(g_fontfgcolor, fgcolors[fgcolor]);
	}
EARLY_EXIT:
	return;
}
