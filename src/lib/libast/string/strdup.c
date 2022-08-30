/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2012 AT&T Intellectual Property          *
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

#undef	VMDEBUG
#define	VMDEBUG		0

#if defined(_MSVCRT_H)
#define strdup		______strdup
#endif

#include <ast.h>

#if defined(_MSVCRT_H)
#undef	strdup
#endif

/*
 * return a copy of s using malloc
 */

/*
 * Avoid a null-test optimization bug caused by glibc's headers
 * by naming this function '_ast_strdup' instead of 'strdup'.
 * https://bugzilla.redhat.com/1221766
 */
extern char*
_ast_strdup(const char* s)
{
	register char*	t;
	register int	n;

	return (s && (t = oldof(0, char, n = strlen(s) + 1, 0))) ? (char*)memcpy(t, s, n) : (char*)0;
}
