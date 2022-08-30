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

#if _lib_memccpy

NoN(memccpy)

#else

/*
 * Copy s2 to s1, stopping if character c is copied. Copy no more than n bytes.
 * Return a pointer to the byte after character c in the copy,
 * or 0 if c is not found in the first n bytes.
 */

void*
memccpy(void* as1, const void* as2, register int c, size_t n)
{
	register char*		s1 = (char*)as1;
	register const char*	s2 = (char*)as2;
	register const char*	ep = s2 + n;

	while (s2 < ep)
		if ((*s1++ = *s2++) == c)
			return(s1);
	return(0);
}

#endif
