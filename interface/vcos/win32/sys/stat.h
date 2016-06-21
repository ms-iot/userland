/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * All rights reserved.
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
 * RCSID = $Header: /E/interix/include/sys/stat.h,v 1.24 1999/07/22 06:04:18 rodney Exp $
 *
 */

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>
#include <sys/types.h> 	/* for time_t, wchar_t, uid_t, off_t, .... */

struct stat {
    mode_t st_mode;
    ino_t st_ino;
    dev_t st_dev;
    dev_t st_rdev;
    nlink_t st_nlink;
    uid_t st_uid;
    gid_t st_gid;
    off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
    long st_blksize;
    long st_blocks;	/* num of S_BLOCK_SIZE byte blocks allocated */
    int st_attrs;	/* DOS file attributes */
    int st_info;	/* Interix-specific flags */
    long st_reserved[18];
};

/*
 * File type bits (used in st_mode)
 */
#define S_IFMT		0x3F000		/* type of file - mask */
#define S_IFIFO		0x01000		/* fifo file */
#define S_IFCHR		0x02000		/* character special */
#define S_IFDIR		0x04000		/* directory */
#define S_IFBLK		0x06000		/* block special */
#define S_IFREG		0x08000		/* regular */
#define S_IFLNK		0x0A000		/* symbolic link */
#define S_IFSOCK	0x0C000		/* socket */

/*
 * Special read-only bit which indicates that additional ACE(s) 
 * are present in the NT ACL 
 * - beyond those used below to represent the UNIX permissions below
 */
#define S_ADDACE	0x80000000

#define S_ISUID     0x800   /* set user id on execution */
#define S_ISGID     0x400   /* set group id on execution */
#define S_ISVTX	    0x200   /* for a directory, only owner can unlink child */

/*
 * File permission bits
 */
#define _S_PROT     0777
#define S_IRWXU     0700
#define S_IRUSR     0400
#define S_IWUSR     0200
#define S_IXUSR     0100

#define S_IRWXG     0070
#define S_IRGRP     0040
#define S_IWGRP     0020
#define S_IXGRP     0010

#define S_IRWXO     0007
#define S_IROTH     0004
#define S_IWOTH     0002
#define S_IXOTH     0001

/* 
 * macros for determining file types
 */
#define S_ISDIR(m) ( ((m) & S_IFMT) == S_IFDIR )
#define S_ISBLK(m) ( ((m) & S_IFMT) == S_IFBLK )
#define S_ISREG(m) ( ((m) & S_IFMT) == S_IFREG )
#define S_ISSOCK(m) ( ((m) & S_IFMT) == S_IFSOCK )
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISLNK(m) ( ((m) & S_IFMT) == S_IFLNK )
/*
 * note: using POSIX.1gD6.5 definition 
 *       (eg. one or both S_ISFIFO or S_ISCHR should return TRUE for a socket)
 */
#define S_ISCHR(m) (  (((m) & S_IFMT) == S_IFCHR)	\
		    || (((m) & S_IFMT) == S_IFSOCK) )


/*
 * function prototypes
 */
extern mode_t __cdecl umask(mode_t);
extern int __cdecl mkdir(const char *, mode_t);
extern int __cdecl mkfifo(const char *, mode_t);
extern int __cdecl stat(const char *, struct stat *);
extern int __cdecl fstat(int, struct stat *);
extern int __cdecl chmod(const char *, mode_t);
extern int __cdecl mknod(const char *, mode_t, dev_t);
extern int __cdecl lstat(const char *, struct stat *);
extern int __cdecl fchmod(int, mode_t);


#if (!defined(_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE)) \
	 || defined(_ALL_SOURCE)
/*
 * SYMBOLIC CONSTANTS
 *
 * DEFFILEMODE from 4.4BSD-Lite sys/stat.h   jdz 951012
 */
#define DEFFILEMODE     (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

/*
 * 4.4BSD sys/stat.h defines several non-POSIX abbreviations for some stat
 * bits. Pretty dumb, but lots of code uses these.
 */
#define S_IREAD         S_IRUSR
#define S_IWRITE        S_IWUSR
#define S_IEXEC         S_IXUSR

/*
 * DOS file attributes, for the st_attrs member of struct stat.
 */
#define S_READONLY      0x00000001
#define S_HIDDEN        0x00000002
#define S_SYSTEM        0x00000004
#define S_DIRECTORY     0x00000010
#define S_ARCHIVE       0x00000020
#define S_TEMPORARY     0x00000100
#define S_COMPRESSED    0x00000800
#define S_OFFLINE       0x00001000

/*
 * Interix-specific flags, for the st_info member of struct stat.
 */
#define S_INO_RELIABLE	0x0001	/* st_ino can be trusted */
#define S_BLOCK_SIZE	512	/* units used in st_blocks */


/* Interix specific wide char routines */
extern int __cdecl wcs_chmod(const wchar_t *, mode_t);
extern int __cdecl wcs_lstat(const wchar_t *, struct stat *);
extern int __cdecl wcs_mkdir(const wchar_t *, mode_t);
extern int __cdecl wcs_mkfifo(const wchar_t *, mode_t);
extern int __cdecl wcs_mknod(const wchar_t *, mode_t, dev_t);
extern int __cdecl wcs_stat(const wchar_t *, struct stat *);

#endif /* !defined(_POSIX_SOURCE) || defined(_ALL_SOURCE) */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_STAT_H_ */
