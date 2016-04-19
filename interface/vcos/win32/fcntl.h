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
 * Rcsid = $Header: /E/interix/include/fcntl.h,v 1.16 1999/04/23 02:38:02 SSI_DEV+mark Exp $
 */

/*++
Copyright (c) 1989  Microsoft Corporation
Module Name:
   fcntl.h
Abstract:
   This module contains the required contents of fcntl
--*/

#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <features.h>

#include <sys/types.h>
#include <unistd.h>	/* to get defns for SEEK, SEEK_END .. (XPG4) */
#include <sys/stat.h>	/* to get defns for S_IRGRP, S_IXGRP, ... (XPG4) */
#ifdef __cplusplus
extern "C" {
#endif

#define O_RDONLY    0x00000000	/* Open read-only */
#define O_WRONLY    0x00000001	/* Open write-only */
#define O_RDWR      0x00000002	/* Reading and writing */
#define O_ACCMODE   0x00000007	/* Mask for file mode */

#if defined(_PSX_KERNEL) || defined(_PSX_LIB)
#define O_READ	    0x00000001	/* Open for read, in kernel */
#define O_WRITE	    0x00000002	/* Open for write, in kernel */
#define O_ACCESS    0x00000004	/* For file access only */
#endif /*_PSX_KERNEL*/

#define O_APPEND    0x00000008	/* Set file for append */

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)
#define O_SYNC      0x00000010	/* Synchronous write option */
#endif /*defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)*/

#define O_CREAT     0x00000100	/* Create file if it doesn't exist already */
#define O_TRUNC     0x00000200	/* Truncate file to length of zero */
#define O_EXCL      0x00000400	/* Error if create and file exists */
#define O_NOCTTY    0x00000800	/* Do not assign controlling terminal */

#define O_NONBLOCK  0x00001000	/* Do not block on open */
#define O_ASYNC     0x00002000	/* SIGIO to pgrp when data ready */

#define O_NDELAY    O_NONBLOCK  /* defining O_NDELAY to be NONBLOCK */

/* fcntl F_SETFL options - backward compatibility with other UNIXs */
#define FNDELAY		O_NONBLOCK
#define FNONBLOCK	O_NONBLOCK
#define FAPPEND		O_APPEND
#define FASYNC		O_ASYNC

/*
 * Control operations on files, 1003.1-88 (6.5.2.2).  Use as 'command'
 * argument to fcntl().
 */

#define F_DUPFD		0	/* Duplicate file descriptor */
#define F_GETFD		1	/* Get file descriptor flags */
#define F_GETLK		2	/* Get record locking information */
#define F_SETFD		3	/* Set file descriptor flags */
#define F_GETFL		4	/* Get file status flags */
#define F_SETFL		5	/* Set file status flags */
#define F_SETLK		6	/* Set record locking information */
#define F_SETLKW	7	/* wait if blocked */
#define F_GETNREAD	8	/* FIONREAD ioctl */
#define F_GETOWN	9	/* Get SIGURG/SIGIO process/pgrp */
#define F_SETOWN	10	/* Set SIGURG/SIGIO process/pgrp */

/*
 * File descriptor flags, 1003.1-90 (6-2).  Used as argument to F_SETFD
 * command.
 */

#define FD_CLOEXEC	0x1

struct flock {
	short l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK		*/
	short l_whence;		/* flag for starting offset		*/
	off_t l_start;		/* relative offset in bytes		*/
	off_t l_len;		/* size; if 0 then until EOF		*/
	pid_t l_pid;		/* pid of process holding the lock	*/
};

/*
 * Values for the l_type field.
 */

#define F_RDLCK	1
#define F_UNLCK 2
#define F_WRLCK 3

extern int __cdecl open(const char *, int,...);
extern int __cdecl creat(const char *, mode_t);
extern int __cdecl fcntl(int, int, ...);

#if defined(_ALL_SOURCE)
/*
 * 4.2 BSD flock() support
 */
#define LOCK_SH	1
#define LOCK_EX	2
#define LOCK_NB	4
#define LOCK_UN	8
extern int __cdecl flock(int fd, int operation);

/* widechar version of open() */
extern int __cdecl wcs_open(const wchar_t *, int, ...);
#endif /*_ALL_SOURCE*/


#ifdef __cplusplus
}
#endif

#endif /* _FCNTL_H_ */
