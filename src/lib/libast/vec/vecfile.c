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
/*
 * Glenn Fowler
 * AT&T Research
 *
 * string vector load support
 */

#include <ast.h>
#include <ls.h>
#include <vecargs.h>

/*
 * load a string vector from lines in file
 */

char**
vecfile(const char* file)
{
	register int	n;
	register char*	buf;
	register char**	vec;
	int		fd;
	struct stat	st;

	vec = 0;
	if ((fd = open(file, O_RDONLY|O_cloexec)) >= 0)
	{
		if (!fstat(fd, &st) && S_ISREG(st.st_mode) && (n = st.st_size) > 0 && (buf = newof(0, char, n + 1, 0)))
		{
			if (read(fd, buf, n) == n)
			{
				buf[n] = 0;
				vec = vecload(buf);
			}
			if (!vec) free(buf);
		}
		close(fd);
	}
	return(vec);
}
