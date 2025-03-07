/*
 * aim_internal.h -- prototypes/structs for the guts of libfaim
 *
 */

#ifdef FAIM_INTERNAL
#ifndef __AIM_INTERNAL_H__
#define __AIM_INTERNAL_H__ 1

typedef struct {
  unsigned short family;
  unsigned short subtype;
  unsigned short flags;
  unsigned long id;
} aim_modsnac_t;

#define AIM_MODULENAME_MAXLEN 16
#define AIM_MODFLAG_MULTIFAMILY 0x0001
typedef struct aim_module_s {
  unsigned short family;
  unsigned short flags;
  unsigned short version;
  char name[AIM_MODULENAME_MAXLEN+1];
  int (*snachandler)(struct aim_session_t *sess, struct aim_module_s *mod, struct command_rx_struct *rx, aim_modsnac_t *snac, unsigned char *data, int datalen);
  void (*shutdown)(struct aim_session_t *sess, struct aim_module_s *mod);
  void *priv;
  struct aim_module_s *next;
} aim_module_t;

faim_internal int aim__registermodule(struct aim_session_t *sess, int (*modfirst)(struct aim_session_t *, aim_module_t *));
faim_internal void aim__shutdownmodules(struct aim_session_t *sess);


faim_internal int buddylist_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int admin_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int bos_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int search_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int stats_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int auth_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int msg_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int misc_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int chatnav_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int chat_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int locate_modfirst(struct aim_session_t *sess, aim_module_t *mod);
faim_internal int general_modfirst(struct aim_session_t *sess, aim_module_t *mod);

faim_internal unsigned long aim_genericreq_n(struct aim_session_t *, struct aim_conn_t *conn, u_short family, u_short subtype);
faim_internal unsigned long aim_genericreq_n_snacid(struct aim_session_t *, struct aim_conn_t *conn, u_short family, u_short subtype);
faim_internal unsigned long aim_genericreq_l(struct aim_session_t *, struct aim_conn_t *conn, u_short family, u_short subtype, u_long *);
faim_internal unsigned long aim_genericreq_s(struct aim_session_t *, struct aim_conn_t *conn, u_short family, u_short subtype, u_short *);

faim_internal void aim_rxqueue_cleanbyconn(struct aim_session_t *sess, struct aim_conn_t *conn);
faim_internal int aim_recv(int fd, void *buf, size_t count);

faim_internal int aim_get_command_rendezvous(struct aim_session_t *sess, struct aim_conn_t *conn);

faim_internal int aim_tx_sendframe(struct aim_session_t *sess, struct command_tx_struct *cur);
faim_internal unsigned int aim_get_next_txseqnum(struct aim_conn_t *);
faim_internal struct command_tx_struct *aim_tx_new(struct aim_session_t *sess, struct aim_conn_t *conn, unsigned char framing, int chan, int datalen);
faim_internal int aim_tx_enqueue(struct aim_session_t *, struct command_tx_struct *);
faim_internal int aim_tx_printqueue(struct aim_session_t *);
faim_internal int aim_tx_cleanqueue(struct aim_session_t *, struct aim_conn_t *);

faim_internal aim_rxcallback_t aim_callhandler(struct aim_session_t *sess, struct aim_conn_t *conn, u_short family, u_short type);
faim_internal int aim_callhandler_noparam(struct aim_session_t *sess, struct aim_conn_t *conn, u_short family, u_short type, struct command_rx_struct *ptr);

/*
 * Generic SNAC structure.  Rarely if ever used.
 */
struct aim_snac_t {
  u_long id;
  u_short family;
  u_short type;
  u_short flags;
  void *data;
  time_t issuetime;
  struct aim_snac_t *next;
};
faim_internal void aim_initsnachash(struct aim_session_t *sess);
faim_internal unsigned long aim_newsnac(struct aim_session_t *, struct aim_snac_t *newsnac);
faim_internal unsigned long aim_cachesnac(struct aim_session_t *sess, const unsigned short family, const unsigned short type, const unsigned short flags, const void *data, const int datalen);
faim_internal struct aim_snac_t *aim_remsnac(struct aim_session_t *, u_long id);
faim_internal int aim_cleansnacs(struct aim_session_t *, int maxage);
faim_internal int aim_putsnac(u_char *, int, int, int, u_long);

faim_internal struct aim_conn_t *aim_cloneconn(struct aim_session_t *sess, struct aim_conn_t *src);

faim_internal int aim_oft_buildheader(unsigned char *,struct aim_fileheader_t *);
faim_internal int aim_listenestablish(u_short);
faim_internal int aim_tx_destroy(struct command_tx_struct *);

faim_internal int aim_parse_unknown(struct aim_session_t *, struct command_rx_struct *, ...);

/* these are used by aim_*_clientready */
#define AIM_TOOL_JAVA   0x0001
#define AIM_TOOL_MAC    0x0002
#define AIM_TOOL_WIN16  0x0003
#define AIM_TOOL_WIN32  0x0004
#define AIM_TOOL_MAC68K 0x0005
#define AIM_TOOL_MACPPC 0x0006
#define AIM_TOOL_NEWWIN 0x0010
struct aim_tool_version {
  unsigned short group;
  unsigned short version;
  unsigned short tool;
  unsigned short toolversion;
};

faim_internal int aim_negchan_middle(struct aim_session_t *sess, struct command_rx_struct *command);

faim_internal unsigned short aim_getcap(struct aim_session_t *sess, unsigned char *capblock, int buflen);
faim_internal int aim_putcap(unsigned char *capblock, int buflen, unsigned short caps);

faim_internal int aim_cachecookie(struct aim_session_t *sess, struct aim_msgcookie_t *cookie);
faim_internal struct aim_msgcookie_t *aim_uncachecookie(struct aim_session_t *sess, unsigned char *cookie, int type);
faim_internal struct aim_msgcookie_t *aim_mkcookie(unsigned char *, int, void *);
faim_internal struct aim_msgcookie_t *aim_checkcookie(struct aim_session_t *, const unsigned char *, const int);
faim_internal int aim_freecookie(struct aim_session_t *sess, struct aim_msgcookie_t *cookie);
faim_internal int aim_msgcookie_gettype(int reqclass);
faim_internal int aim_cookie_free(struct aim_session_t *sess, struct aim_msgcookie_t *cookie);

faim_internal int aim_extractuserinfo(struct aim_session_t *sess, unsigned char *, struct aim_userinfo_s *);
faim_internal int aim_putuserinfo(u_char *buf, int buflen, struct aim_userinfo_s *info);

faim_internal int aim_chat_readroominfo(u_char *buf, struct aim_chat_roominfo *outinfo);

faim_internal void faimdprintf(struct aim_session_t *sess, int dlevel, const char *format, ...);

#ifndef FAIM_INTERNAL_INSANE
/* why the hell wont cpp let you use #error inside #define's? */
/* isn't it single-pass? so the #error would get passed to the compiler --jbm */
#define printf() printf called inside libfaim
#define sprintf() unbounded sprintf used inside libfaim
#endif

#endif /* __AIM_INTERNAL_H__ */
#endif /* FAIM_INTERNAL */
