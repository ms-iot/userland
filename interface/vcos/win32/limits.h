/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * This Software Source is the unpublished, valuable, confidential property
 * of Microsoft Corporation.  Use is authorised only under the terms and
 * conditions set out in the source code licence agreement protecting this
 * Software Source.  Any unauthorised use or disclosure of this Software 
 * Source is prohibited.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' BY MICROSOFT CORPORATION AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 */ 

/*
 * RCSid = $Header: /E/interix/include/limits.h,v 1.29 1999/06/07 14:05:14 mark Exp $
 */

#ifndef _LIMITS_H_
#define _LIMITS_H_

#include <features.h>
#include <sys/types.h>   /* for size_t */
#include <sys/unistd.h>  /* for sysconf() variables */

#if defined(__cplusplus)
extern "C" {
#endif

#define CHAR_BIT	  8		/* number of bits in a char */
#define	MB_LEN_MAX	  2		/* max. # bytes in multibyte char */

#define SCHAR_MIN	(-128)		/* min value for a signed char */
#define SCHAR_MAX	  127		/* max value for a signed char */
#define UCHAR_MAX	 0xff		/* max value for a unsigned char */

#if defined(_CHAR_UNSIGNED) || defined(__CHAR_UNSIGNED__)
#define CHAR_MIN	0
#define CHAR_MAX	UCHAR_MAX
#else
#define CHAR_MIN	SCHAR_MIN	/* mim value for a char */
#define CHAR_MAX	SCHAR_MAX	/* max value for a char */
#endif	/* _CHAR_UNSIGNED */


#define SHRT_MIN	(-32768)	/* min value for (signed) short */
#define SHRT_MAX	  32767 	/* max value for (signed) short */
#define USHRT_MAX	 0xffff	        /* max value for unsigned short */

#define INT_MIN 	(-2147483647-1) /* min value for (signed) int */
#define INT_MAX 	  2147483647	/* max value for (signed) int */
#define UINT_MAX	  0xffffffff	/* max value for unsigned int */

#define LONG_MIN	(-2147483647L-1) /* minimum (signed) long */
#define LONG_MAX	  2147483647L	/* maximum (signed) long */
#define ULONG_MAX	  0xffffffffUL	/* maximum unsigned long */

#if defined(_ALL_SOURCE) \
	|| (__STDC__ - 0 == 0) && !defined(_POSIX_C_SOURCE)  \
			       && !defined(_XOPEN_SOURCE)
/*
 * Minimum and maximum values for 64-bit types
 * Define all the various well-known flavors of symbols
 * 
 */
#define ULLONG_MAX       ((u_quad_t)0-1)	    /* 0xffffffffffffffff */
#define LLONG_MAX        ((quad_t)(ULLONG_MAX>>1))  /* 0x7fffffffffffffff */
#define LLONG_MIN        ((quad_t)((-LLONG_MAX)-1)) /* 0x8000000000000000 */


#define  LONG_LONG_MIN	 LLONG_MIN
#define  LONG_LONG_MAX	 LLONG_MAX
#define ULONG_LONG_MAX	 ULLONG_MAX


#define QUAD_MIN 	LLONG_MIN
#define QUAD_MAX 	LLONG_MAX
#define UQUAD_MAX 	ULLONG_MAX

#endif /* defined(_ALL_SOURCE) ... */

#define _POSIX_ARG_MAX          4096
#define _POSIX_CHILD_MAX        6
#define _POSIX_LINK_MAX         8
#define _POSIX_MAX_CANON        255
#define _POSIX_MAX_INPUT        255
#define _POSIX_NAME_MAX         14
#define _POSIX_NGROUPS_MAX      0
#define _POSIX_OPEN_MAX         16
#define _POSIX_PATH_MAX         255
#define _POSIX_PIPE_BUF         512
#define _POSIX_SSIZE_MAX	32767
#define _POSIX_STREAM_MAX	8
#define _POSIX_TZNAME_MAX	3
#define _POSIX_SEM_NSEMS_MAX	256
#define _POSIX_SEM_VALUE_MAX	32767

#define _POSIX_THREAD_KEYS_MAX			128
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS	4
#define _POSIX_THREAD_THREADS_MAX		64

#define _POSIX_LOGIN_NAME_MAX       9
#define _POSIX_TTY_NAME_MAX         9

#define     SEM_NSEMS_MAX          INT_MAX


#if defined(_ALL_SOURCE) \
	|| (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L))

extern long __cdecl _sysconf(int); /* private interface */
        
/*
 * POSIX.1c pthread constants
 */
 
#define PTHREAD_STACK_MIN       ((size_t)_sysconf(_SC_THREAD_STACK_MIN))
#define PTHREAD_KEYS_MAX 	_POSIX_THREAD_KEYS_MAX

#endif // defined(_ALL_SOURCE) || ... (POSIX_C_SOURCE >= 199506L)

#define LINK_MAX     		1024
#define MAX_INPUT		512
#define MAX_CANON		512
#define NGROUPS_MAX             16
#define NAME_MAX		255
#define SEM_VALUE_MAX 		INT_MAX
#define PATH_MAX                512   /* must be >= FILENAME_MAX <stdio.h> */
#define PIPE_BUF                5120
#define SSIZE_MAX		INT_MAX
#define TZNAME_MAX		10

#define TTY_NAME_MAX 		PATH_MAX +1
#define LOGIN_NAME_MAX  	298

#if defined (_ALL_SOURCE)
#define SID_NAME_MAX   512 /* for buffers that contain SID's as ASCII chars*/
#endif // defined (_ALL_SOURCE)

#if defined(_PSX_KERNEL) || defined(_PSX_LIB)
#define ARG_MAX                 1048576	 /* 1MB */
#else
/* backward compat with 2.2 for utils and libaries for now */
#define ARG_MAX                 14500  	 
#endif

#if !defined(_POSIX_C_SOURCE)  && !defined(_XOPEN_SOURCE)
/* july, 2000
 * Use sysconf(_SC_OPEN_MAX) instead.
 * OPEN_MAX changes based on value of rlim_cur of getrlimit(RLIMIT_NOFILE).
 * We define it here (a default value) for backward compatibility
 */
#define OPEN_MAX                1024

/* july, 2000
 * STREAM_MAX has been removed - must use sysconf(_SC_STREAM_MAX) instead.
 *  The value changes depending on rlim_cur of getrlimit(RLIMIT_NOFILE)
 */
#endif


#if defined(_ALL_SOURCE) || ((__STDC__ - 0 == 0) && !defined(_POSIX_SOURCE))  \
        || defined(_XOPEN_SOURCE)

#define LONG_BIT	32
#define WORD_BIT	16

#ifndef FLT_DIG
   #define FLT_DIG              6               /* floor((p-1)*log10(b))+(b == 10) */
#endif /* FLT_DIG */
#ifndef FLT_MAX
   #define FLT_MAX              3.40282347E+38F /* (1-b**(-p))*b**emax */
#endif /* FLT_MAX */

#ifndef DBL_DIG
   #define DBL_DIG              15
#endif /* DBL_DIG */
#ifndef DBL_MAX
   #define DBL_MAX              1.7976931348623157E+308
#endif /* DBL_MAX */
#endif /* defined(_ALL_SOURCE) || ((__STDC__ - 0 == 0) ... */


#if defined(_ALL_SOURCE) || (__STDC__ - 0 == 0) || \
        defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
/*
 * POSIX2 SYMBOLIC CONSTANTS
 *
 * POSIX 1003.2-1992 table 2-17
 */

#define	_POSIX2_BC_BASE_MAX		99
#define	_POSIX2_BC_DIM_MAX		2048
#define	_POSIX2_BC_SCALE_MAX		99
#define	_POSIX2_BC_STRING_MAX		1000
#define	_POSIX2_COLL_WEIGHTS_MAX	2
#define	_POSIX2_EXPR_NEST_MAX		32
#define	_POSIX2_LINE_MAX		2048
#define	_POSIX2_RE_DUP_MAX		255
#define _POSIX2_VERSION			199209L

#define	COLL_WEIGHTS_MAX	4
#define	EXPR_NEST_MAX		32
#define	LINE_MAX		2048
#define	RE_DUP_MAX		255

/*
 * additional XPG 4.2 symbolic constants
 *
 * (System Interfaces and Headers, issue 4, rev 2, pg 776)
 */
#define CHARCLASS_NAME_MAX	32
#define NL_LANGMAX		32
#define NL_NMAX			16
#define NL_MSGMAX		32767
#define NL_SETMAX		255
#define NL_TEXTMAX		_POSIX2_LINE_MAX
#define NL_ARGMAX		30


/*
 * POSIX 1003.2-1992 Section B.2.1 Table B-3
 */
#define BC_BASE_MAX		LINE_MAX
#define BC_DIM_MAX		65535
#define BC_SCALE_MAX		LINE_MAX
#define	BC_STRING_MAX		LINE_MAX

#endif /* defined(_ALL_SOURCE) ... */

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)
#define _XOPEN_IOV_MAX         INT_MAX

#endif /*defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)*/

/*
 * some other useful constants
 */
// Userland MOD
#if 0
#ifndef __min
#define	__min(a,b) (((a)<(b))?(a):(b))
#endif /*__min*/
#ifndef __max
#define	__max(a,b) (((a)>(b))?(a):(b))
#endif /*__max*/
#endif

#ifndef __howmany
#define __howmany(x, y) ( ( (x) + ((y)-1) ) / (y) )
#endif /*__howmany*/

#if defined(_ALL_SOURCE) || defined(_XPG4_UNIX)
/*
 * size of page alignment for memory mapped files
 * Must be 64K on WindowsNT
 */
#define PAGESIZE                0x10000
#define PAGE_SIZE               0x10000
#define ATEXIT_MAX		INT_MAX
#endif /*defined(_ALL_SOURCE) || defined(_XPG4_UNIX) ... */

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)

#ifndef TMP_MAX
#define TMP_MAX		17576    /* from <stdio.h> */
#endif

#define NZERO     20 	/* process' default nice value */

#endif /* defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)  */


#if defined(_ALL_SOURCE)

/* numeric limit for size_t type  */
#define SIZE_T_MAX	4294967295UL

/*
 * SYMBOLIC CONSTANTS
 *
 * From /4_4bsd_l/usr/src/sys/sys/param.h
 *
 * File system parameters and macros.
 *
 * BSD assumed that:
 *   the file system is made out of blocks of at 
 *   most MAXBSIZE units. MAXBSIZE primarily determines the size of 
 *   buffers in the buffer pool.  It may be
 *   made larger without any effect on existing file systems; however making
 *   it smaller make make some file systems unmountable.
 *
 * This assumption is not true on NT. But we still want some indication
 * of what buffer size we can choose.
 *
 */
#define	MAXBSIZE	(4 * 1024)

#define  NBBY    _NBBY               /* number of bits in a byte */
#define	MIN(a,b) __min(a,b)
#define	MAX(a,b) __max(a,b)

/*
 *
 * MAXPATHLEN defines the longest permissable path length after expanding
 * symbolic links. 
 * In BSD systems it is used to allocate a temporary buffer from the buffer
 * pool in which to do the name expansion, hence should be a power of two,
 * and must be less than or equal to MAXBSIZE.
 *
 * MAXSYMLINKS defines the
 * maximum number of symbolic links that may be expanded in a path name.
 * It should be set high enough to allow all legitimate uses, but halt
 * infinite loops reasonably quickly.
 *
 * NOFILE appears to be a synonym for OPEN_MAX.
 *
 */
#define	MAXPATHLEN	PATH_MAX
#define MAXSYMLINKS	8
#define	NOFILE		64	/* OBSOLETE : max open files per process */
#define MAXHOSTNAMELEN	256	/* max hostname size */
#define MAXNAMLEN	NAME_MAX	/* max filename component size */


/*
 *  ALIGNBYTES was originally setup in BSD machine/param.h via
 *  sys/param.h.  I can't believe we need ALL that to get here....
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
 */
#define	ALIGNBYTES	3
#define	ALIGN(p)	(((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)

#endif /* defined(_ALL_SOURCE) */


#if defined(__cplusplus)
}
#endif

#endif /* _LIMITS_H_ */
