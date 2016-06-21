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

#ifndef _SYS_STATVFS_H_
#define _SYS_STATVFS_H_

#include <features.h>


#include<sys/types.h>	/* for wchar_t */

#ifdef __cplusplus
extern "C" {
#endif

#define MNAMELEN 128

struct statvfs {
	unsigned long f_bsize;
	unsigned long f_frsize;
	unsigned long f_blocks;
	unsigned long f_bfree;
	unsigned long f_bavail;
	unsigned long f_files;
	unsigned long f_ffree;
	unsigned long f_favail;
	unsigned long f_fsid;
	unsigned long f_flag;
	unsigned long f_namemax;
	unsigned long f_type;
	unsigned long f_iosize;
	char f_mntonname[MNAMELEN+1];
	char f_mntfromname[MNAMELEN+1];
	unsigned long f_spare[8];
	char f_fstypename[MNAMELEN+1];
	char f_spare3[MNAMELEN+1];
};

/* for use with f_flag */
#define ST_CLEAR	0x0
#define ST_RDONLY	0x1
#define ST_NOSUID	0x2
#define ST_INO_RELIABLE 0x4

/* file system types */
#define ST_FSTYPE_UNKNOWN	0	/* unknown */
#define ST_FSTYPE_NTFS		1	/* NTFS */
#define ST_FSTYPE_OFS		2	/* OFS - NT's object FS */
#define ST_FSTYPE_CDFS		3
#define ST_FSTYPE_CDROM		ST_FSTYPE_CDFS
#define ST_FSTYPE_ISO9660	ST_FSTYPE_CDFS
#define ST_FSTYPE_FATFS		4	/* MS-DOS FAT FS */
#define ST_FSTYPE_MSDOS		ST_FSTYPE_FATFS
#define ST_FSTYPE_HPFS		5	/* OS2 HPFS */
#define ST_FSTYPE_SAMBA		6	/* Samba FS */
#define ST_FSTYPE_NFS		8	/* NFS */
#define ST_FSTYPE_MAX		8	/* for now */

#ifndef __INTERIX
/* the file system types below here are not supported */
#define ST_FSTYPE_UFS		7	/* BSD FFS */
#endif /*__INTERIX*/

extern int __cdecl statvfs(const char *, struct statvfs *);
extern int __cdecl fstatvfs(int, struct statvfs *);


#if  defined(_ALL_SOURCE) \
     || ( !defined(_XOPEN_SOURCE) && (__STDC__ - 0 == 0) \
                                  && !defined(_POSIX_C_SOURCE) )
struct wstatvfs {
	unsigned long f_bsize;
	unsigned long f_frsize;
	unsigned long f_blocks;
	unsigned long f_bfree;
	unsigned long f_bavail;
	unsigned long f_files;
	unsigned long f_ffree;
	unsigned long f_favail;
	unsigned long f_fsid;
	unsigned long f_flag;
	unsigned long f_namemax;
	unsigned long f_type;
	unsigned long f_iosize;
	wchar_t f_mntonname[MNAMELEN+1];
	wchar_t f_mntfromname[MNAMELEN+1];
	wchar_t f_fstypename[MNAMELEN+1];
	wchar_t f_spare3[MNAMELEN+1];
	unsigned long f_spare[8];
};

extern int __cdecl wcs_statvfs(const wchar_t *, struct wstatvfs *);

#endif /*_ALL_SOURCE ... */



#ifdef __cplusplus
}
#endif

#endif /* _SYS_STATVFS_H_ */
