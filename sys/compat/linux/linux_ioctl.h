/*
 * Copyright (c) 1999 Marcel Moolenaar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer 
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _LINUX_IOCTL_H_
#define	_LINUX_IOCTL_H_

/*
 * disk
 */
#define	LINUX_BLKROSET		0x125d
#define	LINUX_BLKROGET		0x125e
#define	LINUX_BLKRRPART		0x125f
#define	LINUX_BLKGETSIZE	0x1260
#define	LINUX_BLKFLSBUF		0x1261
#define	LINUX_BLKRASET		0x1262
#define	LINUX_BLKRAGET		0x1263
#define	LINUX_BLKFRASET		0x1264
#define	LINUX_BLKFRAGET		0x1265
#define	LINUX_BLKSECTSET	0x1266
#define	LINUX_BLKSECTGET	0x1267
#define	LINUX_BLKSSZGET		0x1268

#define LINUX_IOCTL_DISK_MIN    LINUX_BLKROSET
#define LINUX_IOCTL_DISK_MAX    LINUX_BLKSSZGET

/*
 * hdio
 */
#define LINUX_HDIO_GET_GEO	0x0301
#define LINUX_HDIO_GET_IDENTITY	0x030D	/* not yet implemented */
#define LINUX_HDIO_GET_GEO_BIG	0x0330

#define LINUX_IOCTL_HDIO_MIN	LINUX_HDIO_GET_GEO
#define LINUX_IOCTL_HDIO_MAX	LINUX_HDIO_GET_GEO_BIG

/*
 * cdrom
 */
#define	LINUX_CDROMPAUSE		0x5301
#define	LINUX_CDROMRESUME		0x5302
#define	LINUX_CDROMPLAYMSF		0x5303
#define	LINUX_CDROMPLAYTRKIND		0x5304
#define	LINUX_CDROMREADTOCHDR		0x5305
#define	LINUX_CDROMREADTOCENTRY		0x5306
#define	LINUX_CDROMSTOP			0x5307
#define	LINUX_CDROMSTART		0x5308
#define	LINUX_CDROMEJECT		0x5309
#define	LINUX_CDROMVOLCTRL		0x530a
#define	LINUX_CDROMSUBCHNL		0x530b
#define	LINUX_CDROMREADMODE2		0x530c
#define	LINUX_CDROMREADMODE1		0x530d
#define	LINUX_CDROMREADAUDIO		0x530e
#define	LINUX_CDROMEJECT_SW		0x530f
#define	LINUX_CDROMMULTISESSION		0x5310
#define	LINUX_CDROM_GET_UPC		0x5311
#define	LINUX_CDROMRESET		0x5312
#define	LINUX_CDROMVOLREAD		0x5313
#define	LINUX_CDROMREADRAW		0x5314
#define	LINUX_CDROMREADCOOKED		0x5315
#define	LINUX_CDROMSEEK			0x5316
#define	LINUX_CDROMPLAYBLK		0x5317
#define	LINUX_CDROMREADALL		0x5318
#define	LINUX_CDROMCLOSETRAY		0x5319
#define	LINUX_CDROMLOADFROMSLOT		0x531a
#define	LINUX_CDROMGETSPINDOWN		0x531d
#define	LINUX_CDROMSETSPINDOWN		0x531e
#define	LINUX_CDROM_SET_OPTIONS		0x5320
#define	LINUX_CDROM_CLEAR_OPTIONS	0x5321
#define	LINUX_CDROM_SELECT_SPEED	0x5322
#define	LINUX_CDROM_SELECT_DISC		0x5323
#define	LINUX_CDROM_MEDIA_CHANGED	0x5325
#define	LINUX_CDROM_DRIVE_STATUS	0x5326
#define	LINUX_CDROM_DISC_STATUS		0x5327
#define	LINUX_CDROM_CHANGER_NSLOTS	0x5328
#define	LINUX_CDROM_LOCKDOOR		0x5329
#define	LINUX_CDROM_DEBUG		0x5330
#define	LINUX_CDROM_GET_CAPABILITY	0x5331
#define	LINUX_CDROMAUDIOBUFSIZ		0x5382
#define	LINUX_DVD_READ_STRUCT		0x5390
#define	LINUX_DVD_WRITE_STRUCT		0x5391
#define	LINUX_DVD_AUTH			0x5392
#define	LINUX_CDROM_SEND_PACKET		0x5393
#define	LINUX_CDROM_NEXT_WRITABLE	0x5394
#define	LINUX_CDROM_LAST_WRITTEN	0x5395

#define	LINUX_IOCTL_CDROM_MIN	LINUX_CDROMPAUSE
#define	LINUX_IOCTL_CDROM_MAX	LINUX_CDROM_LAST_WRITTEN

#define	LINUX_CDROM_LBA		0x01
#define	LINUX_CDROM_MSF		0x02

#define	LINUX_DVD_LU_SEND_AGID		0
#define	LINUX_DVD_HOST_SEND_CHALLENGE	1
#define	LINUX_DVD_LU_SEND_KEY1		2
#define	LINUX_DVD_LU_SEND_CHALLENGE	3
#define	LINUX_DVD_HOST_SEND_KEY2	4
#define	LINUX_DVD_AUTH_ESTABLISHED	5
#define	LINUX_DVD_AUTH_FAILURE		6
#define	LINUX_DVD_LU_SEND_TITLE_KEY	7
#define	LINUX_DVD_LU_SEND_ASF		8
#define	LINUX_DVD_INVALIDATE_AGID	9
#define	LINUX_DVD_LU_SEND_RPC_STATE	10
#define	LINUX_DVD_HOST_SEND_RPC_STATE	11

/*
 * VFAT
 */
#define	LINUX_VFAT_READDIR_BOTH	0x7201

#define	LINUX_IOCTL_VFAT_MIN	LINUX_VFAT_READDIR_BOTH
#define	LINUX_IOCTL_VFAT_MAX	LINUX_VFAT_READDIR_BOTH

/*
 * console
 */
#define	LINUX_KIOCSOUND		0x4B2F
#define	LINUX_KDMKTONE		0x4B30
#define	LINUX_KDGETLED		0x4B31
#define	LINUX_KDSETLED		0x4B32
#define	LINUX_KDSETMODE		0x4B3A
#define	LINUX_KDGETMODE		0x4B3B
#define	LINUX_KDGKBMODE		0x4B44
#define	LINUX_KDSKBMODE		0x4B45
#define	LINUX_VT_OPENQRY	0x5600
#define	LINUX_VT_GETMODE	0x5601
#define	LINUX_VT_SETMODE	0x5602
#define	LINUX_VT_GETSTATE	0x5603
#define	LINUX_VT_RELDISP	0x5605
#define	LINUX_VT_ACTIVATE	0x5606  
#define	LINUX_VT_WAITACTIVE	0x5607

#define	LINUX_IOCTL_CONSOLE_MIN	LINUX_KIOCSOUND
#define	LINUX_IOCTL_CONSOLE_MAX	LINUX_VT_WAITACTIVE

#define	LINUX_LED_SCR		0x01
#define	LINUX_LED_NUM		0x02
#define	LINUX_LED_CAP		0x04

#define	LINUX_KD_TEXT		0x0
#define	LINUX_KD_GRAPHICS	0x1
#define	LINUX_KD_TEXT0		0x2
#define	LINUX_KD_TEXT1		0x3

#define	LINUX_KBD_RAW		0
#define	LINUX_KBD_XLATE		1
#define	LINUX_KBD_MEDIUMRAW	2

/*
 * socket
 */
#define	LINUX_FIOSETOWN		0x8901
#define	LINUX_SIOCSPGRP		0x8902
#define	LINUX_FIOGETOWN		0x8903
#define	LINUX_SIOCGPGRP		0x8904
#define	LINUX_SIOCATMARK	0x8905
#define	LINUX_SIOCGSTAMP	0x8906
#define	LINUX_SIOCGIFCONF	0x8912
#define	LINUX_SIOCGIFFLAGS	0x8913
#define	LINUX_SIOCGIFADDR	0x8915
#define	LINUX_SIOCSIFADDR	0x8916
#define	LINUX_SIOCGIFDSTADDR	0x8917
#define	LINUX_SIOCGIFBRDADDR	0x8919
#define	LINUX_SIOCGIFNETMASK	0x891b
#define	LINUX_SIOCSIFNETMASK	0x891c
#define	LINUX_SIOCGIFMTU	0x8921
#define	LINUX_SIOCSIFMTU	0x8922
#define	LINUX_SIOCSIFNAME	0x8923
#define	LINUX_SIOCSIFHWADDR	0x8924
#define	LINUX_SIOCGIFHWADDR	0x8927
#define	LINUX_SIOCADDMULTI	0x8931
#define	LINUX_SIOCDELMULTI	0x8932

#define	LINUX_IOCTL_SOCKET_MIN	LINUX_FIOSETOWN
#define	LINUX_IOCTL_SOCKET_MAX	LINUX_SIOCDELMULTI

/*
 * Device private ioctl calls 
 */
#define LINUX_SIOCDEVPRIVATE	0x89F0  /* to 89FF */
#define LINUX_IOCTL_PRIVATE_MIN	LINUX_SIOCDEVPRIVATE
#define LINUX_IOCTL_PRIVATE_MAX	LINUX_SIOCDEVPRIVATE+0xf

/*
 * sound
 */
#define	LINUX_SOUND_MIXER_WRITE_VOLUME	0x4d00
#define	LINUX_SOUND_MIXER_WRITE_BASS	0x4d01
#define	LINUX_SOUND_MIXER_WRITE_TREBLE	0x4d02
#define	LINUX_SOUND_MIXER_WRITE_SYNTH	0x4d03
#define	LINUX_SOUND_MIXER_WRITE_PCM	0x4d04
#define	LINUX_SOUND_MIXER_WRITE_SPEAKER	0x4d05
#define	LINUX_SOUND_MIXER_WRITE_LINE	0x4d06
#define	LINUX_SOUND_MIXER_WRITE_MIC	0x4d07
#define	LINUX_SOUND_MIXER_WRITE_CD	0x4d08
#define	LINUX_SOUND_MIXER_WRITE_IMIX	0x4d09
#define	LINUX_SOUND_MIXER_WRITE_ALTPCM	0x4d0A
#define	LINUX_SOUND_MIXER_WRITE_RECLEV	0x4d0B
#define	LINUX_SOUND_MIXER_WRITE_IGAIN	0x4d0C
#define	LINUX_SOUND_MIXER_WRITE_OGAIN	0x4d0D
#define	LINUX_SOUND_MIXER_WRITE_LINE1	0x4d0E
#define	LINUX_SOUND_MIXER_WRITE_LINE2	0x4d0F
#define	LINUX_SOUND_MIXER_WRITE_LINE3	0x4d10
#define	LINUX_SOUND_MIXER_INFO		0x4d65
#define	LINUX_OSS_GETVERSION		0x4d76
#define	LINUX_SOUND_MIXER_READ_STEREODEVS	0x4dfb
#define	LINUX_SOUND_MIXER_READ_RECMASK	0x4dfd
#define	LINUX_SOUND_MIXER_READ_DEVMASK	0x4dfe
#define	LINUX_SOUND_MIXER_WRITE_RECSRC	0x4dff
#define	LINUX_SNDCTL_DSP_RESET		0x5000
#define	LINUX_SNDCTL_DSP_SYNC		0x5001
#define	LINUX_SNDCTL_DSP_SPEED		0x5002
#define	LINUX_SNDCTL_DSP_STEREO		0x5003
#define	LINUX_SNDCTL_DSP_GETBLKSIZE	0x5004
#define	LINUX_SNDCTL_DSP_SETBLKSIZE	LINUX_SNDCTL_DSP_GETBLKSIZE
#define	LINUX_SNDCTL_DSP_SETFMT		0x5005
#define	LINUX_SOUND_PCM_WRITE_CHANNELS	0x5006
#define	LINUX_SOUND_PCM_WRITE_FILTER	0x5007
#define	LINUX_SNDCTL_DSP_POST		0x5008
#define	LINUX_SNDCTL_DSP_SUBDIVIDE	0x5009
#define	LINUX_SNDCTL_DSP_SETFRAGMENT	0x500A
#define	LINUX_SNDCTL_DSP_GETFMTS	0x500B
#define	LINUX_SNDCTL_DSP_GETOSPACE	0x500C
#define	LINUX_SNDCTL_DSP_GETISPACE	0x500D
#define	LINUX_SNDCTL_DSP_NONBLOCK	0x500E
#define	LINUX_SNDCTL_DSP_GETCAPS	0x500F
#define	LINUX_SNDCTL_DSP_GETTRIGGER	0x5010
#define	LINUX_SNDCTL_DSP_SETTRIGGER	LINUX_SNDCTL_DSP_GETTRIGGER
#define	LINUX_SNDCTL_DSP_GETIPTR	0x5011
#define	LINUX_SNDCTL_DSP_GETOPTR	0x5012
#define	LINUX_SNDCTL_DSP_SETDUPLEX	0x5016
#define	LINUX_SNDCTL_DSP_GETODELAY	0x5017
#define	LINUX_SNDCTL_SEQ_RESET		0x5100
#define	LINUX_SNDCTL_SEQ_SYNC		0x5101
#define	LINUX_SNDCTL_SYNTH_INFO		0x5102
#define	LINUX_SNDCTL_SEQ_CTRLRATE	0x5103
#define	LINUX_SNDCTL_SEQ_GETOUTCOUNT	0x5104
#define	LINUX_SNDCTL_SEQ_GETINCOUNT	0x5105
#define	LINUX_SNDCTL_SEQ_PERCMODE	0x5106
#define	LINUX_SNDCTL_FM_LOAD_INSTR	0x5107
#define	LINUX_SNDCTL_SEQ_TESTMIDI	0x5108
#define	LINUX_SNDCTL_SEQ_RESETSAMPLES	0x5109
#define	LINUX_SNDCTL_SEQ_NRSYNTHS	0x510A
#define	LINUX_SNDCTL_SEQ_NRMIDIS	0x510B
#define	LINUX_SNDCTL_MIDI_INFO		0x510C
#define	LINUX_SNDCTL_SEQ_TRESHOLD	0x510D
#define	LINUX_SNDCTL_SYNTH_MEMAVL	0x510E

#define	LINUX_IOCTL_SOUND_MIN	LINUX_SOUND_MIXER_WRITE_VOLUME
#define	LINUX_IOCTL_SOUND_MAX	LINUX_SNDCTL_SYNTH_MEMAVL

/*
 * termio
 */
#ifdef __alpha__
#define	LINUX_TCGETS		0x7413
#define	LINUX_TCSETS		0x7414
#define	LINUX_TCSETSW		0x7415
#define	LINUX_TCSETSF		0x7416
#define	LINUX_TCGETA		0x7417
#define	LINUX_TCSETA		0x7418
#define	LINUX_TCSETAW		0x7419
#define	LINUX_TCSETAF		0x741c
#define	LINUX_TCSBRK		0x741d
#define	LINUX_TCXONC		0x741e
#define	LINUX_TCFLSH		0x741f
#else
#define	LINUX_TCGETS		0x5401
#define	LINUX_TCSETS		0x5402
#define	LINUX_TCSETSW		0x5403
#define	LINUX_TCSETSF		0x5404
#define	LINUX_TCGETA		0x5405
#define	LINUX_TCSETA		0x5406
#define	LINUX_TCSETAW		0x5407
#define	LINUX_TCSETAF		0x5408
#define	LINUX_TCSBRK		0x5409
#define	LINUX_TCXONC		0x540A
#define	LINUX_TCFLSH		0x540B
#endif

#define	LINUX_TIOCEXCL		0x540C
#define	LINUX_TIOCNXCL		0x540D
#define	LINUX_TIOCSCTTY		0x540E

#ifdef __alpha__
#define	LINUX_TIOCSPGRP		0x7476
#define	LINUX_TIOCGPGRP		0x7477
#else
#define	LINUX_TIOCGPGRP		0x540F
#define	LINUX_TIOCSPGRP		0x5410
#endif

#define	LINUX_TIOCOUTQ		0x5411
#define	LINUX_TIOCSTI		0x5412

#ifdef __alpha__
#define	LINUX_TIOCSWINSZ	0x7467
#define	LINUX_TIOCGWINSZ	0x7468
#else
#define	LINUX_TIOCGWINSZ	0x5413
#define	LINUX_TIOCSWINSZ	0x5414
#endif

#define	LINUX_TIOCMGET		0x5415
#define	LINUX_TIOCMBIS		0x5416
#define	LINUX_TIOCMBIC		0x5417
#define	LINUX_TIOCMSET		0x5418
#define	LINUX_TIOCGSOFTCAR	0x5419
#define	LINUX_TIOCSSOFTCAR	0x541A

#ifdef __alpha__
#define	LINUX_FIONREAD		0x667f
#else
#define	LINUX_FIONREAD		0x541B
#endif

#define	LINUX_TIOCINQ		FIONREAD
#define	LINUX_TIOCLINUX		0x541C
#define	LINUX_TIOCCONS		0x541D
#define	LINUX_TIOCGSERIAL	0x541E
#define	LINUX_TIOCSSERIAL	0x541F
#define	LINUX_TIOCPKT		0x5420

#ifdef __alpha__
#define	LINUX_FIONBIO		0x667e
#else
#define	LINUX_FIONBIO		0x5421
#endif

#define	LINUX_TIOCNOTTY		0x5422
#define	LINUX_TIOCSETD		0x5423
#define	LINUX_TIOCGETD		0x5424
#define	LINUX_TCSBRKP		0x5425
#define	LINUX_TIOCTTYGSTRUCT	0x5426

#define	LINUX_TIOCSBRK		0x5427
#define	LINUX_TIOCCBRK		0x5428

#ifdef __alpha__
#define	LINUX_FIOCLEX		0x6601
#define	LINUX_FIONCLEX		0x6602
#define	LINUX_FIOASYNC		0x667d
#else
#define	LINUX_FIONCLEX		0x5450
#define	LINUX_FIOCLEX		0x5451
#define	LINUX_FIOASYNC		0x5452
#endif

#define	LINUX_TIOCSERCONFIG	0x5453
#define	LINUX_TIOCSERGWILD	0x5454
#define	LINUX_TIOCSERSWILD	0x5455
#define	LINUX_TIOCGLCKTRMIOS	0x5456
#define	LINUX_TIOCSLCKTRMIOS	0x5457

#ifdef __alpha__
#define	LINUX_IOCTL_TERMIO_MIN	LINUX_TIOCEXCL
#define	LINUX_IOCTL_TERMIO_MAX	LINUX_TIOCGPGRP
#else
#define	LINUX_IOCTL_TERMIO_MIN	LINUX_TCGETS
#define	LINUX_IOCTL_TERMIO_MAX	LINUX_TIOCSLCKTRMIOS
#endif

/* arguments for tcflow() and LINUX_TCXONC */
#define	LINUX_TCOOFF		0
#define	LINUX_TCOON		1
#define	LINUX_TCIOFF		2
#define	LINUX_TCION		3

/* arguments for tcflush() and LINUX_TCFLSH */
#define	LINUX_TCIFLUSH		0
#define	LINUX_TCOFLUSH		1
#define	LINUX_TCIOFLUSH		2

/* line disciplines */
#define	LINUX_N_TTY		0
#define	LINUX_N_SLIP		1
#define	LINUX_N_MOUSE		2
#define	LINUX_N_PPP		3

/* Linux termio c_cc values */
#ifdef __alpha__
#define	LINUX__VINTR		0
#define	LINUX__VQUIT		1
#define	LINUX__VERASE		2
#define	LINUX__VKILL		3
#define	LINUX__VEOF		4
#define	LINUX__VMIN		4
#define	LINUX__VEOL		5
#define	LINUX__VTIME		5
#define	LINUX__VEOL2		6
#define	LINUX__VSWTC		7
#else
#define	LINUX_VINTR		0
#define	LINUX_VQUIT		1
#define	LINUX_VERASE		2
#define	LINUX_VKILL		3
#define	LINUX_VEOF		4
#define	LINUX_VTIME		5
#define	LINUX_VMIN		6
#define	LINUX_VSWTC		7
#endif
#define	LINUX_NCC		8

/* Linux termios c_cc values */
#ifdef __alpha__
#define	LINUX_VEOF		0
#define	LINUX_VEOL		1
#define	LINUX_VEOL2		2
#define	LINUX_VERASE		3
#define	LINUX_VWERASE		4
#define	LINUX_VKILL		5
#define	LINUX_VREPRINT		6
#define	LINUX_VSWTC		7
#define	LINUX_VINTR		8
#define	LINUX_VQUIT		9
#define	LINUX_VSUSP		10
#define	LINUX_VSTART		12
#define	LINUX_VSTOP		13
#define	LINUX_VLNEXT		14
#define	LINUX_VDISCARD		15
#define	LINUX_VMIN		16
#define	LINUX_VTIME		17
#else
/* In addition to the termio values */
#define	LINUX_VSTART		8
#define	LINUX_VSTOP		9
#define	LINUX_VSUSP 		10
#define	LINUX_VEOL		11
#define	LINUX_VREPRINT		12
#define	LINUX_VDISCARD		13
#define	LINUX_VWERASE		14
#define	LINUX_VLNEXT		15
#define	LINUX_VEOL2		16
#endif
#define	LINUX_NCCS		19

#define	LINUX_POSIX_VDISABLE	'\0'

/* Linux c_iflag masks */
#define	LINUX_IGNBRK		0x0000001
#define	LINUX_BRKINT		0x0000002
#define	LINUX_IGNPAR		0x0000004
#define	LINUX_PARMRK		0x0000008
#define	LINUX_INPCK		0x0000010
#define	LINUX_ISTRIP		0x0000020
#define	LINUX_INLCR		0x0000040
#define	LINUX_IGNCR		0x0000080
#define	LINUX_ICRNL		0x0000100

#ifdef __alpha__
#define	LINUX_IXON		0x0000200
#define	LINUX_IXOFF		0x0000400
#define	LINUX_IXANY		0x0000800
#define	LINUX_IUCLC		0x0001000
#else
#define	LINUX_IUCLC		0x0000200
#define	LINUX_IXON		0x0000400
#define	LINUX_IXANY		0x0000800
#define	LINUX_IXOFF		0x0001000
#endif

#define	LINUX_IMAXBEL		0x0002000

/* Linux c_oflag masks */
#define	LINUX_OPOST		0x0000001

#ifdef __alpha__
#define	LINUX_ONLCR		0x0000002
#define	LINUX_OLCUC		0x0000004
#else
#define	LINUX_OLCUC		0x0000002
#define	LINUX_ONLCR		0x0000004
#endif

#define	LINUX_OCRNL		0x0000008
#define	LINUX_ONOCR		0x0000010
#define	LINUX_ONLRET		0x0000020
#define	LINUX_OFILL		0x0000040
#define	LINUX_OFDEL		0x0000080

#ifdef __alpha__
#define	LINUX_NLDLY		0x0000300
#define	LINUX_NL0		0x0000000
#define	LINUX_NL1		0x0000100
#define	LINUX_NL2		0x0000200
#define	LINUX_NL3		0x0000300
#define	LINUX_TABDLY		0x000C000
#define	LINUX_TAB0		0x0000000
#define	LINUX_TAB1		0x0004000
#define	LINUX_TAB2		0x0008000
#define	LINUX_TAB3		0x000C000
#define	LINUX_CRDLY		0x0030000
#define	LINUX_CR0		0x0000000
#define	LINUX_CR1		0x0010000
#define	LINUX_CR2		0x0020000
#define	LINUX_CR3		0x0030000
#define	LINUX_FFDLY		0x0040000
#define	LINUX_FF0		0x0000000
#define	LINUX_FF1		0x0040000
#define	LINUX_BSDLY		0x0080000
#define	LINUX_BS0		0x0000000
#define	LINUX_BS1		0x0080000
#define	LINUX_VTDLY		0x0100000
#define	LINUX_VT0		0x0000000
#define	LINUX_VT1		0x0100000
#define	LINUX_XTABS		0x0200000
#else
#define	LINUX_NLDLY		0x0000100
#define	LINUX_NL0		0x0000000
#define	LINUX_NL1		0x0000100
#define	LINUX_CRDLY		0x0000600
#define	LINUX_CR0		0x0000000
#define	LINUX_CR1		0x0000200
#define	LINUX_CR2		0x0000400
#define	LINUX_CR3		0x0000600
#define	LINUX_TABDLY		0x0001800
#define	LINUX_TAB0		0x0000000
#define	LINUX_TAB1		0x0000800
#define	LINUX_TAB2		0x0001000
#define	LINUX_TAB3		0x0001800
#define	LINUX_XTABS		0x0001800
#define	LINUX_BSDLY		0x0002000
#define	LINUX_BS0		0x0000000
#define	LINUX_BS1		0x0002000
#define	LINUX_VTDLY		0x0004000
#define	LINUX_VT0		0x0000000
#define	LINUX_VT1		0x0004000
#define	LINUX_FFDLY		0x0008000
#define	LINUX_FF0		0x0000000
#define	LINUX_FF1		0x0008000
#endif

#ifdef __alpha__
#define	LINUX_CBAUD		0x0000001f
#else
#define	LINUX_CBAUD		0x0000100f
#endif

#define	LINUX_B0		0x00000000
#define	LINUX_B50		0x00000001
#define	LINUX_B75		0x00000002
#define	LINUX_B110		0x00000003
#define	LINUX_B134		0x00000004
#define	LINUX_B150		0x00000005
#define	LINUX_B200		0x00000006
#define	LINUX_B300		0x00000007
#define	LINUX_B600		0x00000008
#define	LINUX_B1200		0x00000009
#define	LINUX_B1800		0x0000000a
#define	LINUX_B2400		0x0000000b
#define	LINUX_B4800		0x0000000c
#define	LINUX_B9600		0x0000000d
#define	LINUX_B19200		0x0000000e
#define	LINUX_B38400		0x0000000f
#define	LINUX_EXTA		LINUX_B19200
#define	LINUX_EXTB		LINUX_B38400

#ifdef __alpha__
#define	LINUX_CBAUDEX		0x00000000
#define	LINUX_B57600		0x00000010
#define	LINUX_B115200		0x00000011
#else
#define	LINUX_CBAUDEX		0x00001000
#define	LINUX_B57600		0x00001001
#define	LINUX_B115200		0x00001002
#endif

#ifdef __alpha__
#define	LINUX_CSIZE		0x00000300
#define	LINUX_CS5		0x00000000
#define	LINUX_CS6		0x00000100
#define	LINUX_CS7		0x00000200
#define	LINUX_CS8		0x00000300
#define	LINUX_CSTOPB		0x00000400
#define	LINUX_CREAD		0x00000800
#define	LINUX_PARENB		0x00001000
#define	LINUX_PARODD		0x00002000
#define	LINUX_HUPCL		0x00004000
#define	LINUX_CLOCAL		0x00008000
#else
#define	LINUX_CSIZE		0x00000030
#define	LINUX_CS5		0x00000000
#define	LINUX_CS6		0x00000010
#define	LINUX_CS7		0x00000020
#define	LINUX_CS8		0x00000030
#define	LINUX_CSTOPB		0x00000040
#define	LINUX_CREAD		0x00000080
#define	LINUX_PARENB		0x00000100
#define	LINUX_PARODD		0x00000200
#define	LINUX_HUPCL		0x00000400
#define	LINUX_CLOCAL		0x00000800
#endif

#define	LINUX_CRTSCTS		0x80000000

/* Linux c_lflag masks */
#ifdef __alpha__
#define	LINUX_ECHOKE		0x00000001
#define	LINUX_ECHOE		0x00000002
#define	LINUX_ECHOK		0x00000004
#define	LINUX_ECHO		0x00000008
#define	LINUX_ECHONL		0x00000010
#define	LINUX_ECHOPRT		0x00000020
#define	LINUX_ECHOCTL		0x00000040
#define	LINUX_ISIG		0x00000080
#define	LINUX_ICANON		0x00000100
#define	LINUX_IEXTEN		0x00000400
#define	LINUX_XCASE		0x00004000
#define	LINUX_TOSTOP		0x00400000
#define	LINUX_FLUSHO		0x00800000
#define	LINUX_PENDIN		0x20000000
#define	LINUX_NOFLSH		0x80000000
#else
#define	LINUX_ISIG		0x00000001
#define	LINUX_ICANON		0x00000002
#define	LINUX_XCASE		0x00000004
#define	LINUX_ECHO		0x00000008
#define	LINUX_ECHOE		0x00000010
#define	LINUX_ECHOK		0x00000020
#define	LINUX_ECHONL		0x00000040
#define	LINUX_NOFLSH		0x00000080
#define	LINUX_TOSTOP		0x00000100
#define	LINUX_ECHOCTL		0x00000200
#define	LINUX_ECHOPRT		0x00000400
#define	LINUX_ECHOKE		0x00000800
#define	LINUX_FLUSHO		0x00001000
#define	LINUX_PENDIN		0x00002000
#define	LINUX_IEXTEN		0x00008000
#endif

/* serial_struct values for TIOC[GS]SERIAL ioctls */
#define	LINUX_ASYNC_CLOSING_WAIT_INF  0
#define	LINUX_ASYNC_CLOSING_WAIT_NONE 65535

#define	LINUX_PORT_UNKNOWN	0
#define	LINUX_PORT_8250		1
#define	LINUX_PORT_16450	2
#define	LINUX_PORT_16550	3
#define	LINUX_PORT_16550A	4
#define	LINUX_PORT_CIRRUS	5
#define	LINUX_PORT_16650	6

#define	LINUX_PORT_MAX		6

#define	LINUX_ASYNC_HUP_NOTIFY		0x0001
#define	LINUX_ASYNC_FOURPORT		0x0002
#define	LINUX_ASYNC_SAK			0x0004
#define	LINUX_ASYNC_SPLIT_TERMIOS	0x0008
#define	LINUX_ASYNC_SPD_MASK		0x0030
#define	LINUX_ASYNC_SPD_HI		0x0010
#define	LINUX_ASYNC_SPD_VHI		0x0020
#define	LINUX_ASYNC_SPD_CUST		0x0030
#define	LINUX_ASYNC_SKIP_TEST		0x0040
#define	LINUX_ASYNC_AUTO_IRQ		0x0080
#define	LINUX_ASYNC_SESSION_LOCKOUT	0x0100
#define	LINUX_ASYNC_PGRP_LOCKOUT	0x0200
#define	LINUX_ASYNC_CALLOUT_NOHUP	0x0400
#define	LINUX_ASYNC_FLAGS		0x0FFF

#define	LINUX_IOCTL_DRM_MIN	0x6400
#define	LINUX_IOCTL_DRM_MAX	0x64ff

/*
 * This doesn't really belong here, but I can't think of a better
 * place to put it.
 */
struct ifnet;
int		 linux_ifname(struct ifnet *, char *, size_t);

#endif /* !_LINUX_IOCTL_H_ */
