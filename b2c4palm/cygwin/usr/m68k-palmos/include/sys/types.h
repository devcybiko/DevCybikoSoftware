#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H

/*
 * This allows for 256 file descriptors: if NR_OPEN is ever grown beyond that
 * you'll have to change this too. But 256 fd's seem to be enough even for such
 * "real" unices like SunOS, so hopefully this is one limit that doesn't have
 * to be changed.
 *
 * Note that POSIX wants the FD_CLEAR(fd,fdsetp) defines to be in <sys/time.h>
 * (and thus <linux/time.h>) - but this is a more logical place for them. Solved
 * by having dummy defines in <sys/time.h>.
 */

/*
 * Those macros may have been defined in <gnu/types.h>. But we always
 * use the ones here. 
 */

#ifndef NULL
#define NULL ((void *) 0)
#endif

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define _LOFF_T
typedef long long loff_t;
#endif

/* bsd */
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

/* sysv */
typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef char *caddr_t;

typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
typedef unsigned long size_t;
#endif

#endif
