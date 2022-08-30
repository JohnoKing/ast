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

#if _lib_rmdir

NoN(rmdir)

#else

#include <ls.h>
#include <error.h>

int
rmdir(const char* path)
{
	register int	n;
	struct stat	st;
	char*		av[3];

	static char*	cmd[] = { "/bin/rmdir", 0 };

	if (stat(path, &st) < 0) return(-1);
	if (!S_ISDIR(st.st_mode))
	{
		errno = ENOTDIR;
		return(-1);
	}
	av[0] = "rmdir";
	av[1] = path;
	av[2] = 0;
	for (n = 0; n < elementsof(cmd); n++)
		if (procclose(procopen(cmd[n], av, NiL, NiL, 0)) != -1)
			break;
	n = errno;
	if (access(path, F_OK) < 0)
	{
		errno = n;
		return(0);
	}
	errno = EPERM;
	return(-1);
}

#endif
