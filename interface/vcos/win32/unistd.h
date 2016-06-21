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
 *  Rcsid = $Header: /E/interix/include/unistd.h,v 1.47 2000/03/14 23:03:58 jeffcope Exp $
 */

#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <features.h>
#include <sys/types.h>	/* for ssize_t and ... */
#include <sys/unistd.h>


#ifdef __cplusplus
extern "C" {
#endif


#ifndef NULL
# ifdef __cplusplus
#    define NULL        0
# else
#    define NULL        ((void *)0)
# endif /*__cplusplus*/
#endif /*NULL*/


/*
 * POSIX.1-1990 Section 2.9.1  (symbolic constants for access())
 */
#define  F_OK  00
#define  X_OK  01
#define  W_OK  02
#define  R_OK  04

#if defined(_ALL_SOURCE)
/*
 * Non-standard symbolic constants for access().
 * EFF_ONLY_OK and EX_OK come from UnixWare/System V.
 * If you or in a S_IF* file type constant from <sys/stat.h>,
 * then the file is constrained to be of that type:
 * this is an Interix extension.
 */
#define EFF_ONLY_OK	0x0008	/* test using effective ids */
#define SYMLINK_OK	0x0010	/* operate directly on a symlink */
#define EX_OK		0x8001	/* test for regular executable */
#endif

/*
 * POSIX.1-1990 Section 2.9.2  (symbolic constants for lseek())
 */
#define  SEEK_SET 0
#define  SEEK_CUR 1
#define  SEEK_END 2

#if defined(_ALL_SOURCE)
/* Historical symbolic constants for lseek() */
#define L_SET	SEEK_SET
#define L_INCR	SEEK_CUR
#define L_XTND	SEEK_END
#endif /* ALL_SOURCE */

/*
 * POSIX.1-1990 Section 2.9.3  (symbolic constants for Portability Specs)
 */
#define _POSIX_JOB_CONTROL			1
#define _POSIX_VERSION				199009L
#define _POSIX_SAVED_IDS			1
#define _POSIX_SPIN_LOCKS			1
#define _POSIX_READER_WRITER_LOCKS		1
#define _POSIX_SEMAPHORES			1
#define _POSIX_THREADS				1

#define _POSIX_THREAD_PRIORITY_SCHEDULING       1
#define _POSIX_THREAD_ATTR_STACKADDR            1
#define _POSIX_THREAD_ATTR_STACKSIZE            1
#define _POSIX_THREAD_SAFE_FUNCTIONS            1

/*
 * POSIX.1-1990 Section 2.9.4
 */
#define _POSIX_CHOWN_RESTRICTED 1
#define _POSIX_NO_TRUNC	 1
#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE	 0
#endif


/*
 * POSIX.1-1990 Section 5.7.1 : 'name' values for pathconf/fpathconf
 */
#define _PC_LINK_MAX		1
#define _PC_MAX_CANON 		2
#define _PC_MAX_INPUT		3
#define _PC_NAME_MAX		4
#define _PC_PATH_MAX		5
#define _PC_PIPE_BUF		6
#define _PC_CHOWN_RESTRICTED	7
#define _PC_NO_TRUNC		8
#define _PC_VDISABLE		9

/*
 * POSIX.1-1990 Section 8.2.1.2  (symbolic constants for streams)
 */
#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2


#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) || (_POSIX_C_SOURCE>=2)
/*
 * POSIX.2-1992 compile time symbolic constants - B.2.2 Table B-4
 */
#define _POSIX2_C_VERSION	199209L

/*
 * POSIX.2-1992 execution time symbolic constants - B.2.3 Table B-5
 */
#define _POSIX2_C_DEV		 1
#define _POSIX2_C_BIND		 1
#define _POSIX2_CHAR_TERM	 1
#define _POSIX2_FORT_DEV	-1
#define _POSIX2_FORT_RUN	-1
#define _POSIX2_LOCALEDEF	 1
#define _POSIX2_SW_DEV		 1
#define _POSIX2_UPE		-1

#define _POSIX2_VERSION	        199209L
#endif /*defined(_ALL_SOURCE) .. */


#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)
#define _XOPEN_VERSION		4
#define _XOPEN_XCU_VERSION	4	
#define _XOPEN_XPG4		1
#undef _XOPEN_XPG2
#undef _XOPEN_XPG3

#   define _XOPEN_UNIX		1
#   define _XOPEN_SHM		1

#endif /*defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)*/


/*
 * Function Prototypes
 */
extern int   __cdecl	access(const char *, int);
extern unsigned int __cdecl	alarm(unsigned int);
extern int   __cdecl	chdir(const char *);
extern int   __cdecl	chown(const char *, uid_t, gid_t);
extern int   __cdecl	close(int);
extern char *__cdecl	ctermid(char *);
extern int   __cdecl	dup(int);
extern int   __cdecl	dup2(int, int);
extern int   __cdecl	execl(const char *, const char *, ...);
extern int   __cdecl	execle(const char *, const char *, ...);
extern int   __cdecl	execlp(const char *, const char *, ...);
extern int   __cdecl	execv(const char *, char * const []);
extern int   __cdecl	execve(const char *, char * const [], char * const []);
extern int   __cdecl	execvp(const char *, char * const []);
// Userland MOD
//extern void  __cdecl	_exit(int);
extern pid_t __cdecl	fork(void);
extern long  __cdecl	fpathconf(int, int);
extern char *__cdecl	getcwd(char *, size_t);
extern uid_t __cdecl	geteuid(void);
extern gid_t __cdecl	getegid(void);
extern gid_t __cdecl	getgid(void);
extern int   __cdecl	getgroups(int, gid_t []);
extern char *__cdecl	getlogin(void);
extern pid_t __cdecl	getpgrp(void);
extern pid_t __cdecl	getpid(void);
extern pid_t __cdecl	getppid(void);
extern uid_t __cdecl	getuid(void);
extern int   __cdecl	isatty(int);
extern int   __cdecl	link(const char *, const char *);
extern off_t __cdecl	lseek(int, off_t, int);
extern long  __cdecl	pathconf(const char *, int);
extern int   __cdecl	pause(void);
extern int   __cdecl	pipe(int *);
extern ssize_t __cdecl  pread(int, void *, size_t, off_t);
extern ssize_t __cdecl  pwrite(int, const void *, size_t, off_t);
extern ssize_t __cdecl	read(int, void *, size_t);
extern int   __cdecl	rmdir(const char *);
extern int   __cdecl	setuid(uid_t);
extern int   __cdecl	setgid(gid_t);
extern int   __cdecl	setpgid(pid_t, pid_t);
extern pid_t __cdecl	setsid(void);
extern unsigned int __cdecl	sleep(unsigned int);
extern long  __cdecl	sysconf(int);
extern pid_t __cdecl	tcgetpgrp(int);
extern int   __cdecl	tcsetpgrp(int, pid_t);
extern char *__cdecl	ttyname(int);
// Userland MOD
//extern int   __cdecl	unlink(const char *);
extern ssize_t __cdecl	write(int, const void *, size_t);
extern int __cdecl	pthread_atfork(void (*)(void), void (*)(void),
							void (*)(void));

#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
extern int   __cdecl 	getlogin_r(char *, size_t);
extern int   __cdecl 	ttyname_r(int, char *, size_t);
#endif

#if defined(_ALL_SOURCE) || (_POSIX_C_SOURCE>=2) || defined(_XOPEN_SOURCE)
/*
 * constants for confstr() : POSIX.2-1992
 */
#define _CS_PATH		1
#define _CS_SHELL       	2
#define _CS_INSTALLEDDIR        3
#define _CS_TMPDIR      	4
#define _CS_ETCDIR      	5
#define _CS_BINDIR      	6
#define _CS_INCLUDEDIR  	7
#define _CS_LIBDIR      	8
#define _CS_USRDIR      	9
#define _CS_PUBSDIR     	10

extern size_t  __cdecl	confstr(int, char *, size_t);
extern int     __cdecl	getopt(int, char * const [], const char *);

/*
 * External variables for getopt()
 */
extern char *optarg;
extern int   optind, opterr, optopt;

#endif /* defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) ... */


#if defined(_ALL_SOURCE) || defined(_XPG4_UNIX)

/* Single Unix Spec. compatibility */

/* operation codes for lockf() */
#define F_ULOCK         0       /* unlock */
#define F_LOCK          1       /* lock for exclusive use */
#define F_TLOCK         2       /* test and lock for exclusive use */
#define F_TEST          3       /* test a section for locks */

extern int    __cdecl brk(void*);
extern void   __cdecl encrypt(char[64], int);
extern int    __cdecl fchdir(int);
extern int    __cdecl fchown(int, uid_t, gid_t);
extern int    __cdecl ftruncate(int, off_t);
extern int    __cdecl getdtablesize(void);
extern int    __cdecl getpagesize(void);
extern char * __cdecl getwd(char *);
extern int    __cdecl lockf(int, int, off_t);
extern int    __cdecl lchown(const char *, uid_t , gid_t );
extern int    __cdecl readlink(const char *, char *, size_t );
extern void*  __cdecl sbrk(int);
extern int    __cdecl setregid(gid_t , gid_t);
extern int    __cdecl setreuid(uid_t , uid_t);
extern int    __cdecl symlink(const char *, const char *);
extern int    __cdecl truncate(const char *, off_t);
extern useconds_t __cdecl ualarm(useconds_t, useconds_t);
extern int    __cdecl usleep(useconds_t);
extern pid_t  __cdecl vfork(void);

#if !defined(_PSX_KERNEL)
/* expose this prototype when not building the subsystem. 
 * Some header files used in subsystem build cause a clash here.
 */
extern int __cdecl gethostname(char *, size_t);
#endif /* _PSX_KERNEL */

#endif /* _ALL_SOURCE || defined(_XPG4_UNIX) */


#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)
extern int    __cdecl chroot(const char *);
extern char * __cdecl cuserid(char *);
extern char * __cdecl getpass(const char *);
extern void   __cdecl swab(const void*, void*, ssize_t);
extern int    __cdecl fsync(int);
extern int    __cdecl nice(int);
#endif /* defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) */

#if defined(_ALL_SOURCE)  && !defined(_PSX_KERNEL)
/* BSD 4.x compat */
extern mode_t __cdecl getmode (const void *, mode_t );
extern void * __cdecl setmode (const char * /*mode_str*/);

/* widechar functions */
extern int   __cdecl wcs_access(const wchar_t *, int);
extern int   __cdecl wcs_chdir(const wchar_t *);
extern int   __cdecl wcs_chown(const wchar_t *, uid_t, gid_t);
extern int   __cdecl wcs_chroot(const wchar_t *);
extern int   __cdecl wcs_lchown(const wchar_t *, uid_t , gid_t );
extern int   __cdecl wcs_link(const wchar_t *, const wchar_t *);
extern long  __cdecl wcs_pathconf(const wchar_t *, int);
extern int   __cdecl wcs_readlink(const wchar_t *, wchar_t *, size_t );
extern int   __cdecl wcs_rmdir(const wchar_t *);
extern int   __cdecl wcs_unlink(const wchar_t *);
extern int   __cdecl wcs_symlink(const wchar_t *, const wchar_t *);
#endif /* defined(_ALL_SOURCE) && ...*/

#ifdef __cplusplus
}
#endif

#endif /* _UNISTD_ */
