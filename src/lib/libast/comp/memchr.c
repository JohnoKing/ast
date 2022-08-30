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

#include <ast.h>

#if _lib_memchr

NoN(memchr)

#else

/*
 * Return the ptr in sp at which the character c appears;
 * 0 if not found in n chars; don't stop at \0.
 */

void*
memchr(const void* asp, register int c, size_t n)
{
	register const char*	sp = (char*)asp;
	register const char*	ep = sp + n;

	while (sp < ep)
		if (*sp++ == c)
			return(--sp);
	return(0);
}

#endif
