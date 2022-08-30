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
 * obsolete streval() interface to strexpr()
 */

#include <ast.h>

typedef long (*Old_convert_t)(const char*, char**);

typedef long (*Convert_t)(const char*, char**, void*);

typedef struct
{
	Old_convert_t	convert;
} Handle_t;

static long
userconv(const char* s, char** end, void* handle)
{
	return((*((Handle_t*)handle)->convert)(s, end));
}

long
streval(const char* s, char** end, Old_convert_t convert)
{
	Handle_t	handle;

	return((handle.convert = convert) ? strexpr(s, end, userconv, &handle) : strexpr(s, end, (Convert_t)0, NiL));
}
