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
 *  RCSID - $Header: /E/interix/include/features.h,v 1.14 1999/04/23 02:38:02 SSI_DEV+mark Exp $
 */ 


#ifndef _FEATURES_H_
#define _FEATURES_H_


/* Note:
 *  According to POSIX.1, if we follow the
 *  "C Standard Language Dependent Support"
 *  then only ANSI-C symbols are allowed to be present when no
 *  other feature test macros are defined
 */

/* look at the several high level feature test macros and 
 * ensure that the lower level features are enabled
 */

#if defined(_XOPEN_SOURCE) && !defined(_POSIX_C_SOURCE)  \
			   && !defined(_POSIX_SOURCE)
#  define _POSIX_C_SOURCE 2
#endif /* _XOPEN_SOURCE */

#if defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#  define _POSIX_C_SOURCE 1
#endif


/*  
 * NOTE: _XPG4_UNIX is an implementation defined special macro.
 *       Users wishing to interfaces defined by X/Open's XPG4 UNIX 
 *       specification should define _XOPEN_SOURCE and _XOPEN_SOURCE_EXTENDED
 *       Using _XPG_UNIX directly could result in unexpected results
 */
#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED==1)
#  define _XPG4_UNIX	1
#endif


/* 
 * For XPG5 (UNIX 98), this includes UNIX 95 functionality.
 * To use UNIX98 functionality, _XOPEN_SOURCE must be set by
 * the user to 500.  This enables UNIX98, UNIX95 and 
 * POSIX Realtime and Threads.
 */
#if (_XOPEN_SOURCE - 0 == 500)
#  define _XPG5_UNIX	1
#  define _XPG4_2_UNIX	1

#  undef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE		199506L
#  define _POSIX_PTHREAD_SEMANTICS	1
#endif //(_XOPEN_SOURCE - 0 == 500)

/* -------- compiler Specific setup ----------- */
/*
 **** GCC and MSVC 4.0+ compilers
 */
/*
 *  Define _CRTAPI1 (for compatibility with the NT SDK)
 */
#ifndef _CRTAPI1
#  ifdef  _M_IX86
#    define _CRTAPI1 __cdecl
#  else
#    define _CRTAPI1
#  endif /*_MSC_VER ... */
#endif /*_CRTAPI1*/

/*
 *  Define _CRTAPI2 (for compatibility with the NT SDK)
 */
#ifndef _CRTAPI2
#  ifdef _M_IX86
#    define _CRTAPI2 __cdecl
#  else
#    define _CRTAPI2
#  endif
#endif /*_CRTAPI2*/


#if defined(__GNUC__) && defined(__cplusplus)
#  undef _CRTAPI1
#  undef _CRTAPI2
#  undef __cdecl
#  define _CRTAPI1
#  define _CRTAPI2
#  define __cdecl
#endif /*defined(__GNUC__)*/


#if !defined(_MSC_VER) && !defined(__cdecl)
#    define __cdecl
#endif


#endif /* _FEATURES_H_ */
