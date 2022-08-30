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

#if _lib_memmove

NoN(memmove)

#else

void*
memmove(void* to, const void* from, register size_t n)
{
	register char*	out = (char*)to;
	register char*	in = (char*)from;

	if (n <= 0)	/* works if size_t is signed or not */
		;
	else if (in + n <= out || out + n <= in)
		return(memcpy(to, from, n));	/* hope it's fast */
	else if (out < in)
		do *out++ = *in++; while (--n > 0);
	else
	{
		out += n;
		in += n;
		do *--out = *--in; while(--n > 0);
	}
	return(to);
}

#endif
