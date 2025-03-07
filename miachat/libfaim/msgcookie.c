/*
 * Cookie Caching stuff. Adam wrote this, apparently just some
 * derivatives of n's SNAC work. I cleaned it up, added comments.
 * 
 */

/*
 * I'm assuming that cookies are type-specific. that is, we can have
 * "1234578" for type 1 and type 2 concurrently. if i'm wrong, then we
 * lose some error checking. if we assume cookies are not type-specific and are
 * wrong, we get quirky behavior when cookies step on each others' toes.
 */

#define FAIM_INTERNAL
#include <aim.h>

/**
 * aim_cachecookie - appends a cookie to the cookie list
 * @sess: session to add to
 * @cookie: pointer to struct to append
 *
 * if cookie->cookie for type cookie->type is found, updates the
 * ->addtime of the found structure; otherwise adds the given cookie
 * to the cache
 *
 * returns -1 on error, 0 on append, 1 on update.  the cookie you pass
 * in may be free'd, so don't count on its value after calling this!
 * 
 */
faim_internal int aim_cachecookie(struct aim_session_t *sess,
				  struct aim_msgcookie_t *cookie)
{
  struct aim_msgcookie_t *newcook;

  if (!sess || !cookie)
    return -1;

  if( (newcook = aim_checkcookie(sess, cookie->cookie, cookie->type)) ) {
    if(newcook != cookie) {
      aim_cookie_free(sess, newcook);
    } else {
      newcook->addtime = time(NULL);
      return 1;
    }
  }

  cookie->addtime = time(NULL);  

  cookie->next = sess->msgcookies;
  sess->msgcookies = cookie;

  return 0;
}

/**
 * aim_uncachecookie - grabs a cookie from the cookie cache (removes it from the list)
 * @sess: session to grab cookie from
 * @cookie: cookie string to look for
 * @type: cookie type to look for
 *
 * takes a cookie string and a cookie type and finds the cookie struct associated with that duple, removing it from the cookie list ikn the process.
 *
 * if found, returns the struct; if none found (or on error), returns NULL:
 */
faim_internal struct aim_msgcookie_t *aim_uncachecookie(struct aim_session_t *sess, unsigned char *cookie, int type)
{
  struct aim_msgcookie_t *cur, **prev;

  if (!cookie || !sess->msgcookies)
    return NULL;

  for (prev = &sess->msgcookies; (cur = *prev); ) {
    if ((cur->type == type) && 
	(memcmp(cur->cookie, cookie, 8) == 0)) {
      *prev = cur->next;
      return cur;
    }
    prev = &cur->next;
  }

  return NULL;
}

/**
 * aim_mkcookie - generate an aim_msgcookie_t *struct from a cookie string, a type, and a data pointer.
 * @c: pointer to the cookie string array
 * @type: cookie type to use
 * @data: data to be cached with the cookie
 *
 * returns NULL on error, a pointer to the newly-allocated cookie on
 * success.
 *
 */
faim_internal struct aim_msgcookie_t *aim_mkcookie(unsigned char *c, int type, void *data) 
{
  struct aim_msgcookie_t *cookie;

  if (!c)
    return NULL;

  if (!(cookie = calloc(1, sizeof(struct aim_msgcookie_t))))
    return NULL;
  
  cookie->data = data;
  cookie->type = type;
  memcpy(cookie->cookie, c, 8);
  
  return cookie;
}

/**
 * aim_checkcookie - check to see if a cookietuple has been cached
 * @sess: session to check for the cookie in
 * @cookie: pointer to the cookie string array
 * @type: type of the cookie to look for
 *
 * this returns a pointer to the cookie struct (still in the list) on
 * success; returns NULL on error/not found
 *
 */

faim_internal struct aim_msgcookie_t *aim_checkcookie(struct aim_session_t *sess, 
						      const unsigned char *cookie, 
						      const int type)
{
  struct aim_msgcookie_t *cur;

  for (cur = sess->msgcookies; cur; cur = cur->next) {
    if ((cur->type == type) && 
	(memcmp(cur->cookie, cookie, 8) == 0))
      return cur;   
  }

  return NULL;
}

#if 0 /* debugging feature */
faim_internal int aim_dumpcookie(struct aim_msgcookie_t *cookie) 
{
  if(!cookie)
    return -1;
  printf("\tCookie at %p: %d/%s with %p, next %p\n", cookie, cookie->type, cookie->cookie, cookie->data, cookie->next);
  return 0;
}
#endif

/**
 * aim_cookie_free - free an aim_msgcookie_t struct
 * @sess: session to remove the cookie from
 * @cookiep: the address of a pointer to the cookie struct to remove
 *
 * this function removes the cookie *cookie from teh list of cookies
 * in sess, and then frees all memory associated with it. including
 * its data! if you want to use the private data after calling this,
 * make sure you copy it first.
 *
 * returns -1 on error, 0 on success.
 *
 */

faim_internal int aim_cookie_free(struct aim_session_t *sess, 
				  struct aim_msgcookie_t *cookie) 
{
  struct aim_msgcookie_t *cur, **prev;

  if (!sess || !cookie)
    return -1;

  if(!cookie)
    return 0;

  for (prev = &sess->msgcookies; (cur = *prev); ) {
    if (cur == cookie) {
      *prev = cur->next;
    } else
      prev = &cur->next;
  }

  if(cookie->data)
    free(cookie->data);

  free(cookie);

  return 0;
} 

faim_internal int aim_msgcookie_gettype(int reqclass) {
  /* XXX: hokey-assed. needs fixed. */
  switch(reqclass) {
  case AIM_CAPS_BUDDYICON:
    return AIM_COOKIETYPE_OFTICON;
    break;
  case AIM_CAPS_VOICE:
    return AIM_COOKIETYPE_OFTVOICE;
    break;
  case AIM_CAPS_IMIMAGE:
    return AIM_COOKIETYPE_OFTIMAGE;
    break;
  case AIM_CAPS_CHAT:
    return AIM_COOKIETYPE_CHAT;
    break;
  case AIM_CAPS_GETFILE:
    return AIM_COOKIETYPE_OFTGET;
    break;
  case AIM_CAPS_SENDFILE:
    return AIM_COOKIETYPE_OFTSEND;
    break;
  default:
    return AIM_COOKIETYPE_UNKNOWN;
    break;
  }           
}
