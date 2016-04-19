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
 *  RCSID = $Header: /E/interix/include/va_list.h,v 1.1 1997/07/09 01:10:38 SSI_DEV+mark Exp $
 *
 */

#ifndef _HIDDEN_VA_LIST_DEFINED
#define _HIDDEN_VA_LIST_DEFINED

#ifdef	_MSC_VER 		/* Microsoft compiler support */
#ifdef	_M_ALPHA
typedef struct {
	char *a0;	/* Pointer to first integer argument */
	int offset;	/* Byte offset of next argument */
} __va_list;
#else
typedef char *	__va_list;
#endif /* _M_ALPHA */

#elif defined (__GNUC__)	/* GNU C compiler */

#if __GNUC__ >= 3
/* Use the gcc stdarg.h (gcc default search paths get us the right file) */
#define __need___va_list        /* Tell stdarg we're after JUST va_list */
#include <stdarg.h>             /* Get the gnuc stdarg.h */
typedef __builtin_va_list __va_list;
#else
#  ifdef _M_ALPHA
typedef struct {
  char *__base;         /* Pointer to first integer register. */
  int __offset;         /* Byte offset of args so far. */
} __va_list;
#  else /*! _M_ALPHA*/
typedef void *__va_list;
#  endif /*_M_ALPHA*/

#endif /*__GNUC__*/

#else /*! _MSC_VER */

/* default definition for other compilers */
typedef char *	__va_list;

#endif /* MSC_VER */

#endif /*_HIDDEN_VA_LIST_DEFINED*/


#if !defined(_HIDDEN_VA_LIST) && !defined(_VA_LIST_DEFINED)
/*
 * define va_list unless its requested to remain hidden
 */
typedef __va_list  va_list;
#define _VA_LIST_DEFINED

#endif /* !defined(_HIDDEN_VA_LIST) ... */
#undef _HIDDEN_VA_LIST
