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
 *  RCSID = $Header: /E/interix/include/stdarg.h,v 1.12 1999/08/24 20:53:42 mark Exp $
 *
 */

#ifndef _STDARG_H_
#define _STDARG_H_

#include <features.h>

#ifdef _VARARGS_H_

#ifdef _MSC_VER		/* Microsoft compiler */
#pragma message("stdarg.h: included after after <varargs.h>. Removing <varargs.h> definitions")
#elif defined (__GNUC__)
#warning "<stdarg.h> included after after <varargs.h>. Removing <varargs.h> definitions"
#endif


/* clear all references to <stdarg.h> */
#undef _VARARGS_H_
#undef va_dcl
#undef va_start
#undef va_arg
#undef va_end

#endif /* _VARARGS_H_ */


/*
 * get definition of va_list
 */
#include <va_list.h>


#ifdef _MSC_VER		/* Microsoft compiler */

#ifdef	_M_IX86
#define _INTSIZEOF(n)	( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)	( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)	( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)	( ap = (va_list)0 )

#elif	defined(_M_ALPHA)

/* Use these types and definitions if generating code for ALPHA */

/*
 * The Alpha compiler supports two builtin functions that are used to
 * implement stdarg/varargs.  The __builtin_va_start function is used
 * by va_start to initialize the data structure that locates the next
 * argument.  The __builtin_isfloat function is used by va_arg to pick
 * which part of the home area a given register argument is stored in.
 * The home area is where up to six integer and/or six floating point
 * register arguments are stored down (so they can also be referenced
 * by a pointer like any arguments passed on the stack).
 */

#ifdef __cplusplus
extern "C" {
#endif

extern void * __builtin_va_start(va_list, ...);

#ifdef __cplusplus
}
#endif

#define va_start(list, v) __builtin_va_start(list, v, 1)
#define va_end(list)
#define va_arg(list, mode) \
    ( *(        ((list).offset += ((int)sizeof(mode) + 7) & -8) , \
        (mode *)((list).a0 + (list).offset - \
                    ((__builtin_isfloat(mode) && (list).offset <= (6 * 8)) ? \
                        (6 * 8) + 8 : ((int)sizeof(mode) + 7) & -8) \
                ) \
       ) \
    )

#else
/* A guess at the proper definitions for other platforms */
#define _INTSIZEOF(n)	( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)	( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)	( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)	( ap = (va_list)0 )

#endif /* _M_IX86 || _M_ALPHA ... */

#elif defined (__GNUC__)
/*
 * gcc compiler
 */

#if __GNUC__ >= 3
/* Use the gcc stdarg.h (gcc default search paths get us the right file) */
#include <stdarg.h>             /* Get the gnuc stdarg.h */   
#else
#ifdef  _M_ALPHA
#include <gnu/va-alpha.h>
#else
#include <gnu/va-intel.h>
#endif /* _M_ALPHA */
#endif /* __GNUC__ >= 3 */
#endif /* MSC_VER */

#endif	/* _STDARG_H_ */
