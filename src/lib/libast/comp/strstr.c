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

#define strstr		______strstr

#include <ast.h>

#undef	strstr

#if _lib_strstr

NoN(strstr)

#else

extern char*
strstr(register const char* s1, register const char* s2)
{
	register int		c1;
	register int		c2;
	register const char*	t1;
	register const char*	t2;
	
	if (s2)
	{
		if (!*s2)
			return (char*)s1;
		c2 = *s2++;
		while (c1 = *s1++)
			if (c1 == c2)
			{
				t1 = s1;
				t2 = s2;
				do
				{
					if (!*t2)
						return (char*)s1 - 1;
				} while (*t1++ == *t2++);
			}
	}
	return 0;
}

#endif
