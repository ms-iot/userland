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

#ifndef _DIRENT_H_
#define _DIRENT_H_

#include <features.h>

#include <sys/types.h>	/* for size_t, ino_t, wchar_t, ... */
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

struct dirent {
    char d_name[NAME_MAX+1];
    ino_t d_ino;
    size_t d_namlen;
    long reserved[16];
};

#if !defined(_PSX_KERNEL) && !defined(_PSX_LIB)
/*
 * *** WARNING - WARNING ***
 *  _DIR (and DIR) are system specific reserved OPAQUE structures.
 *  DO NOT make use of these structures in any way except indirectly 
 *  as pointers.  (eg.  as DIR* arguments to opendir(), readdir() ...)
 *  The size and contents are not guaranteed to be backward compatible 
 *  between different releases of Interix.
 *
 *  The only reason this is here is to satisfy an improperly/incorrectly
 *  written test case in the PCTS.
 *
 */
struct _DIR {
      char reserved[sizeof(struct dirent)+(23*sizeof(long))];
};
#endif


typedef struct _DIR DIR;

extern DIR* 	__cdecl        opendir(const char *);
extern void 	__cdecl        rewinddir(DIR *);
extern int 	__cdecl        closedir(DIR *);
extern struct dirent * __cdecl readdir(DIR *);
#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
extern int __cdecl readdir_r(DIR *, struct dirent *, 
    struct dirent **);
#endif

/*
 * seekdir() and telldir() are XPG4 extensions.
 */
#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) || (__STDC__ - 0 == 0)

extern void     __cdecl seekdir (DIR *, long int);
extern long int __cdecl telldir (DIR *);

#endif /* defined(_ALL_SOURCE) || ... */

#if defined(_ALL_SOURCE)
extern int  __cdecl     dirfd(DIR *);
extern DIR* __cdecl	wcs_opendir(const wchar_t * );

/* scandir() and alphasort() are 4.3 bsd extensions 
 * that are becoming quite popular. 
 */
extern int scandir(const char *, struct dirent **[], 
		    int (*)(struct dirent *), 
		    int (*)(const void *, const void *)); 

extern int alphasort(const void *, const void *);
#endif /* defined(_ALL_SOURCE) */

#ifdef __cplusplus
}
#endif

#endif /* _DIRENT_H_ */
