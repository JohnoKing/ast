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
 * ftw implementation
 */

#include <ast.h>
#include <ftw.h>

static int	(*ftw_userf)(const char*, const struct stat*, int);

static int
ftw_user(Ftw_t* ftw)
{
	register int	n = ftw->info;

	if (n & (FTW_C|FTW_NX))
		n = FTW_DNR;
	else if (n & FTW_SL)
		n = FTW_NS;
	return (*ftw_userf)(ftw->path, &ftw->statb, n);
}

int
ftw(const char* path, int(*userf)(const char*, const struct stat*, int), int depth)
{
	NoP(depth);
	ftw_userf = userf;
	return ftwalk(path, ftw_user, FTW_DOT, NiL);
}
