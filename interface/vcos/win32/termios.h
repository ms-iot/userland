/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * Rcsid = $Header: /E/interix/include/termios.h,v 1.25 1999/02/05 20:59:14 rodney Exp $
 */ 

/*++
Module Name:
   termios.h
Abstract:
   This module contains the primitive system data types described in section 
   7.1.2.1 of IEEE P1003.1-1990
--*/

#ifndef _TERMIOS_H_
#define _TERMIOS_H_

#include <features.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Input modes, for c_iflag member
 */

#define BRKINT	0x00000001	/* signal interrupt on break		*/
#define ICRNL	0x00000002	/* map CR to NL on input		*/
#define IGNBRK	0x00000004	/* ignore break condition		*/
#define IGNCR	0x00000008	/* ignore CR				*/
#define IGNPAR	0x00000010	/* ignore characters with parity errors	*/
#define INLCR	0x00000020	/* map NL to CR on input		*/
#define INPCK	0x00000040	/* Enable input parity check		*/
#define ISTRIP	0x00000080	/* strip character			*/
#define IXOFF	0x00000100	/* enable start/stop input control	*/
#define IXON	0x00000200	/* enable start/stop output control	*/
#define PARMRK	0x00000400	/* mark parity errors			*/
#define IMAXBEL	0x00000800	/* bell when MAX_{INPUT,CANON} met	*/
#define IXANY	0x00001000	/* enable all keys to act like VSTART	*/

/*
 * Output modes, for c_oflag member
 */

#define OPOST	0x00000001	/* perform output processing		*/
#define ONLCR	0x00000002	/* map NL to ASCII CR-NL on output	*/
#define ONLRET	0x00000004	/* NL performs ASCII CR function	*/
#define OCRNL	0x00000008	/* map ASCII CR to NL on output		*/
#define ONOCR	0x00000010	/* No ASCII CR output at column 0.	*/

/*
 * Control modes, for c_cflag member
 */
#define CLOCAL	0x00000001	/* ignore modem status lines		*/
#define CREAD	0x00000002	/* enable receiver			*/
#define CSIZE	0x000000F0	/* number of bits per byte		*/
#define    CS5	0x00000010	/* 	5 bits				*/
#define    CS6	0x00000020	/*	6 bits				*/
#define	   CS7	0x00000040	/* 	7 bits				*/
#define	   CS8	0x00000080	/*	8 bits				*/
#define CSTOPB	0x00000100	/* send two stop bits, else one		*/
#define HUPCL	0x00000200	/* hang up on last close		*/
#define PARENB	0x00000400	/* parity enable			*/
#define PARODD	0x00000800	/* odd parity, else even		*/

/*
 * Local modes, for c_lflag member
 */
#define ECHO	0x00000001	/* enable echo				*/
#define ECHOE	0x00000002	/* echo ERASE as an error-correcting backspace	*/
#define ECHOK	0x00000004	/* echo KILL				*/
#define ECHONL	0x00000008	/* echo '\n'				*/
#define ICANON	0x00000010	/* canonical input (erase and kill processing)	*/
#define IEXTEN	0x00000020	/* enable extended functions		*/
#define ISIG	0x00000040	/* enable signals			*/
#define NOFLSH	0x00000080	/* disable flush after intr, quit, or suspend	*/
#define TOSTOP	0x00000100	/* send SIGTTOU for background output	*/
#define EXTPROC	0x00000200	/* external processing */
#define ECHOCTL	0x00000400	/* human readable control characters (^X) */
#define IMELINE	0x00000800	/* input; leave a blank line for Window's IME */
#define IAIM	IMELINE		/* backward compat - synonym for IMELINE */
#define IME_RECOMMENDED 0x00001000  /*This will specify if IMELINE should be ON/OFF for "stty sane"*/

/*
 * Indices into c_cc array
 */
#define VEOF		0	/* EOF character			*/
#define VEOL		1	/* EOL character			*/
#define VERASE		2	/* ERASE character			*/
#define VINTR		3	/* INTR character			*/
#define VKILL		4	/* KILL character			*/
#define VMIN		5	/* MIN value				*/
#define VQUIT		6	/* QUIT character			*/
#define VSUSP		7	/* SUSP character			*/
#define VTIME		8	/* TIME value				*/
#define VSTART		9	/* START character			*/
#define VSTOP		10	/* STOP character			*/
#define VBELTIME	11	/* BELTIME value			*/
#define VREPRINT	12	/* REPRINT character			*/
#define VWERASE		13	/* WERASE character			*/
#define VEOL2		14	/* EOL2 character			*/
#define VLNEXT		15	/* LNEXT character			*/

/* TODO: increase NCCS to 22 - for eventual support of:
 *    VDISCARD
 *    VDSUSP
 *    <5 spares>
 */

#define NCCS 22

/*
 * Values for speed_t's
 */

#define B0	0
#define B50	1
#define B75	2
#define B110	3
#define B134	4
#define B150	5
#define B200	6
#define B300	7
#define B600	8
#define B1200	9
#define B1800	10
#define B2400	11
#define B4800	12
#define B9600	13
#define B19200	14
#define B38400	15
#define B7200	16
#define B14400	17
#define B28800	18
#define B57600	19
#define B76800	20
#define B115200	21
#define B153600	22
#define B230400	23
#define B307200	24
#define B460800	25
#define EXTA	B19200
#define EXTB	B38400

/*
 * Optional actions for tcsetattr()
 */
#define TCSANOW		1
#define TCSADRAIN	2
#define TCSAFLUSH	3
#define TCSAIFLUSH	4

/*
 * Queue selectors for tcflush()
 */

#define TCIFLUSH 	0
#define TCOFLUSH	1
#define TCIOFLUSH	2

/*
 * Actions for tcflow()
 */

#define TCOOFF 		0
#define TCOON		1
#define TCIOFF		2
#define TCION		3


typedef unsigned long cc_t;
typedef unsigned long speed_t;
typedef unsigned long tcflag_t;

struct termios {
    tcflag_t c_iflag;		/* input modes 				*/
    tcflag_t c_oflag;		/* output modes				*/
    tcflag_t c_cflag;		/* control modes			*/
    tcflag_t c_lflag;		/* local modes				*/
    speed_t c_ispeed;		/* input speed				*/
    speed_t c_ospeed;		/* output speed				*/
    cc_t c_cc[NCCS];		/* control characters			*/
};

/*
 * For ease of flag validations
 */
#define TTYALL_CFLAG (CLOCAL|CREAD|CSIZE|CSTOPB|HUPCL|PARENB|PARODD)
#define TTYALL_IFLAG (BRKINT|ICRNL|IGNBRK|IGNCR|IGNPAR|INLCR|INPCK|ISTRIP|IXOFF|IXON|PARMRK|IMAXBEL|IXANY)
#define TTYALL_LFLAG (ECHO|ECHOE|ECHOK|ECHONL|ICANON|IEXTEN|ISIG|NOFLSH|TOSTOP|EXTPROC|ECHOCTL|IAIM|IME_RECOMMENDED)
#define TTYALL_OFLAG (OPOST|ONLCR|ONLRET|OCRNL|ONOCR)

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE 0
#endif
/*
 * Default terminal starting values.
 */
#define TTYDEF_CFLAG	(CREAD | CS8 | HUPCL)
#define TTYDEF_IFLAG	(BRKINT | ICRNL | IMAXBEL | IXON | IXANY)
#define TTYDEF_LFLAG	(ECHO | ICANON | ISIG | ECHOK | ECHOE | ECHOCTL)
#define TTYDEF_OFLAG	(OPOST | ONLCR)
#define TTYDEF_SPEED	(B9600)
#define CCEQ(val, memb)	(val == memb ? val != _POSIX_VDISABLE : 0)
#define CTRL(x)		((x) & 037)
#define CEOF		CTRL('D')
#define CEOF2		CTRL('D')
#define CEOL		(_POSIX_VDISABLE)
#define CBRK		CEOL
#define CERASE		CTRL('H')
#define CINTR		CTRL('C')
#define CKILL		CTRL('U')
#define CQUIT		CTRL('\\')
#define CSUSP		CTRL('Z')
#define CSTOP		CTRL('S')
#define CSTART		CTRL('Q')
#define CMIN		(1)
#define CTIME		(0)
#define CBELTIME	(3)
#define CREPRINT	CTRL('R')
#define CRPRNT		CREPRINT
#define CWERASE		CTRL('W')
#define CEOL2		(_POSIX_VDISABLE)
#define CLNEXT		CTRL('V')

#define TTYDEF_CCARRAY	{ CEOF, CEOL, CERASE, CINTR, CKILL, CMIN, \
    CQUIT, CSUSP, CTIME, CSTART, CSTOP, CBELTIME, CREPRINT, CWERASE, \
    CEOL2, CLNEXT }

#ifdef TTYDEFCHARS
cc_t ttydefchars[NCCS] = TTYDEF_CCARRAY;
#undef TTYDEFCHARS
#endif /* TTYDEFCHARS */

#ifdef TTYDEFTERMIOS
/*
 * A struct termios pre-initialized to default values
 */
struct termios ttydeftermios = {
	TTYDEF_IFLAG,
	TTYDEF_OFLAG,
	TTYDEF_CFLAG,
	TTYDEF_LFLAG,
	TTYDEF_SPEED,
	TTYDEF_SPEED,
	TTYDEF_CCARRAY
};
#undef TTYDEFTERMIOS
#endif /* TTYDEFTERMIOS */

/*
 * Macros for testing parts of a struct termios
 */
#define ISSET_IFLAG(m, b) ((m).c_iflag & (b))
#define ISSET_OFLAG(m, b) ((m).c_oflag & (b))
#define ISSET_CFLAG(m, b) ((m).c_cflag & (b))
#define ISSET_LFLAG(m, b) ((m).c_lflag & (b))

/*
 * Macros for setting parts of a struct termios
 */
#define SET_IFLAG(m, b) ((m).c_iflag |= (b))
#define SET_OFLAG(m, b) ((m).c_oflag |= (b))
#define SET_CFLAG(m, b) ((m).c_cflag |= (b))
#define SET_LFLAG(m, b) ((m).c_lflag |= (b))

/*
 * Macros for clearing parts of a struct termios
 */
#define CLR_IFLAG(m, b) ((m).c_iflag &= (~((unsigned)(b)))
#define CLR_OFLAG(m, b) ((m).c_oflag &= (~((unsigned)(b)))
#define CLR_CFLAG(m, b) ((m).c_cflag &= (~((unsigned)(b)))
#define CLR_LFLAG(m, b) ((m).c_lflag &= (~((unsigned)(b)))

int _CRTAPI1 tcgetattr(int, struct termios *);
int _CRTAPI1 tcsetattr(int, int, const struct termios *);
int _CRTAPI1 tcsendbreak(int, int);
int _CRTAPI1 tcdrain(int);
int _CRTAPI1 tcflush(int, int);
int _CRTAPI1 tcflow(int, int);

speed_t _CRTAPI1 cfgetospeed(const struct termios *);
int     _CRTAPI1 cfsetospeed(struct termios *, speed_t);
speed_t _CRTAPI1 cfgetispeed(const struct termios *);
int     _CRTAPI1 cfsetispeed(struct termios *, speed_t);
#define cfsetspeed(t, s)	\
		(cfsetospeed((t), (s)) | cfsetispeed((t), (s)))

#ifdef __cplusplus
}
#endif

#endif /* _TERMIOS_H_ */
