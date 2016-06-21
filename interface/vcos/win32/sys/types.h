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
 *
 * RCSID = $Header: /E/interix/include/sys/types.h,v 1.18 2000/03/15 20:23:30 NORTHAMERICA+markfunk Exp $
 *
 */


#ifndef _SYS_TYPES_
#define _SYS_TYPES_

#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/endian.h>		/* for BSD4.x compat */

/*
 *   POSIX data types
 */

#ifndef _MODE_T_DEFINED
#define _MODE_T_DEFINED
typedef unsigned long mode_t;
#endif  /*_MODE_T_DEFINED*/

#ifndef _NLINK_T_DEFINED
#define _NLINK_T_DEFINED
typedef unsigned long nlink_t;
#endif /* _NLINK_T_DEFINED*/

#ifndef _PID_T_DEFINED
#define _PID_T_DEFINED
typedef          long pid_t;
#endif /* _PID_T_DEFINED*/

#ifndef _GID_T_DEFINED
#define _GID_T_DEFINED
typedef unsigned long gid_t;
#endif /* _GID_T_DEFINED*/

#ifndef _UID_T_DEFINED
#define _UID_T_DEFINED
typedef unsigned long uid_t;
#endif /* _UID_T_DEFINED*/

#ifndef _OFF_T_DEFINED
typedef 	 long off_t;
#define _OFF_T_DEFINED
#endif

#ifndef _DEV_T_DEFINED
typedef unsigned long dev_t;
#define _DEV_T_DEFINED
#endif

#ifndef _INO_T_DEFINED
typedef unsigned long ino_t;
#define _INO_T_DEFINED
#endif

#ifndef _TIME_T_DEFINED
typedef long time_t;
#define _TIME_T_DEFINED
#endif

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

#ifndef _SSIZE_T_DEFINED
typedef signed int ssize_t;
#define _SSIZE_T_DEFINED
#endif

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#ifndef _WCTYPE_T_DEFINED
typedef wchar_t wctype_t;
// Userland MOD
// typedef int wint_t;
#define _WCTYPE_T_DEFINED
#endif /* _WCTYPE_T_DEFINED */

#ifndef _SA_FAMILY_T
#define _SA_FAMILY_T
typedef unsigned short  sa_family_t;
#endif /* !_SA_FAMILY_T */

/*
 * additional symbols not defined in POSIX.1 but are permitted
 */

/*
 * symbols in XPG4
 */
#ifndef _CLOCK_T_DEFINED
typedef long clock_t;
#define _CLOCK_T_DEFINED
#endif

#ifndef _USECONDS_T_DEFINED
typedef unsigned long useconds_t;
#define _USECONDS_T_DEFINED
#endif

#ifndef _ID_T_DEFINED
typedef unsigned long id_t;
#define _ID_T_DEFINED
#endif /* _ID_T_DEFINED */

/* types for Networking headers */
typedef char            *caddr_t;

/* types for IPC */
typedef int             key_t;

/* types from SVR4 */
typedef unsigned char uchar_t;
typedef unsigned int uint_t;
typedef unsigned short ushort_t;
typedef unsigned long ulong_t;

/* types for compat. with various BSD and other library sources */
typedef signed char      int8_t;
typedef unsigned char  u_int8_t;
typedef short            int16_t;
typedef unsigned short u_int16_t;
typedef int              int32_t;
typedef unsigned int   u_int32_t;

/* types for compat. with Solaris 7 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

/*
 * 64bit type for BSD compatability
 */
#ifdef __GNUC__
typedef long long int 		  quad_t;
typedef unsigned long long int	u_quad_t;
typedef long long int             int64_t;
typedef unsigned long long int  u_int64_t;
#elif _MSC_VER
typedef __int64 		  quad_t;
typedef unsigned __int64 	u_quad_t;
typedef __int64 		  int64_t;
typedef unsigned __int64 	u_int64_t;
#endif /*__GNUC__*/

typedef struct {
        void *_current_table;
        long _state;
        long _fill[7];
        long _policy;
} __mbstate_t;


#if defined(_ALL_SOURCE) \
     || (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) \
     || (__STDC__ -0 == 0)


/*
 * Additional types for sockets and streams
 */
typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned short	ushort;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

typedef unsigned int    uint;
typedef unsigned long   ulong;
typedef unsigned char   unchar;

#endif	/* _ALL_SOURCE */

/*
 * pthread definitions
 */
typedef  long pthread_t; 

/*
 * attributes for threads, dynamically allocated by library
 */
typedef  void* pthread_attr_t;

/*
 * mutex, cond variables and their attributes
 */
typedef void*   pthread_mutex_t;
typedef void*   pthread_cond_t;
typedef void*   pthread_mutexattr_t;
typedef void*   pthread_condattr_t;

/*
 * pthread once, keys
 */
typedef struct {
    void* _once_value ;
    pthread_mutex_t _once_mutex ;
    int _reserved[6];
} pthread_once_t ;

typedef unsigned int pthread_key_t;

/*
 * spinlock, rwlock and attributes for rwlock
 */
typedef void*   pthread_spinlock_t;
typedef void*   pthread_rwlock_t;
typedef void*   pthread_rwlockattr_t;

#ifdef __cplusplus
}
#endif

#endif  /* _SYS_TYPES_ */
