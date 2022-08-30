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
 * GNU getopt interface
 */

#ifndef _GETOPT_H
#ifdef	_AST_STD_I
#define _GETOPT_H		-1
#else
#define _GETOPT_H		1

#include <ast_getopt.h>

#define no_argument		0
#define required_argument	1
#define optional_argument	2

struct option
{
	const char*	name;
	int		has_arg;
	int*		flag;
	int		val;
};

extern int	getopt_long(int, char* const*, const char*, const struct option*, int*);
extern int	getopt_long_only(int, char* const*, const char*, const struct option*, int*);

#endif
#endif
