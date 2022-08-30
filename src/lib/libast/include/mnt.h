/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                  Martijn Dekker <martijn@inlv.org>                   *
*                                                                      *
***********************************************************************/
/*
 * Glenn Fowler
 * AT&T Research
 *
 * mounted filesystem scan interface
 */

#ifndef _MNT_H
#define _MNT_H	1

#undef	MNT_REMOTE			/* AIX clash			*/
#define MNT_REMOTE	(1<<0)		/* remote mount			*/

typedef struct
{
	char*	fs;			/* filesystem name		*/
	char*	dir;			/* mounted dir			*/
	char*	type;			/* filesystem type		*/
	char*	options;		/* options			*/
	int	freq;			/* backup frequency		*/
	int	npass;			/* number of parallel passes	*/
	int	flags;			/* MNT_* flags			*/
} Mnt_t;

extern void*	mntopen(const char*, const char*);
extern Mnt_t*	mntread(void*);
extern int	mntwrite(void*, const Mnt_t*);
extern int	mntclose(void*);

#endif
