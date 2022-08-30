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
 * ftw,nftw over ftwalk
 */

#ifndef _FTW_H
#define _FTW_H

#define FTW		FTWALK
#include <ftwalk.h>
#undef			FTW

#define FTW_SLN		(FTW_SL|FTW_NR)

#define FTW_PHYS	(FTW_PHYSICAL)
#define FTW_CHDIR	(FTW_DOT)
#define FTW_DEPTH	(FTW_POST)
#define FTW_OPEN	(0)

struct FTW
{
	int		quit;
	int		base;
	int		level;
};

#define FTW_SKD		FTW_SKIP
#define FTW_PRUNE	FTW_SKIP

extern int	ftw(const char*, int(*)(const char*, const struct stat*, int), int);
extern int	nftw(const char*, int(*)(const char*, const struct stat*, int, struct FTW*), int, int);

#endif
