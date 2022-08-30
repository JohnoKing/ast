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
 * ccmapchr(ccmap(CC_NATIVE,CC_ASCII),c) and strcmp
 */

#include <ast.h>
#include <ccode.h>

#if _lib_stracmp

NoN(stracmp)

#else

#include <ctype.h>

int
stracmp(const char* aa, const char* ab)
{
	register unsigned char*	a;
	register unsigned char*	b;
	register unsigned char*	m;
	register int		c;
	register int		d;

	if (!(m = ccmap(CC_NATIVE, CC_ASCII)))
		return strcmp(aa, ab);
	a = (unsigned char*)aa;
	b = (unsigned char*)ab;
	for (;;)
	{
		c = m[*a++];
		if (d = c - m[*b++])
			return d;
		if (!c)
			return 0;
	}
}

#endif
