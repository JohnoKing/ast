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

#include <ast_lib.h>

#if _lib_execvpe

#include <ast.h>

NoN(execvpe)

#else

#include <ast.h>
#include <errno.h>

extern int
execvpe(const char* name, char* const argv[], char* const envv[])
{
	register const char*	path = name;
	char			buffer[PATH_MAX];

	if (*path != '/' && !(path = pathpath(name, NULL, PATH_REGULAR|PATH_EXECUTE, buffer, sizeof(buffer))))
		path = name;
	execve(path, argv, envv);
	if (errno == ENOEXEC)
	{
		register char**	newargv;
		register char**	ov;
		register char**	nv;

		for (ov = (char**)argv; *ov++;);
		if (newargv = newof(0, char*, ov + 1 - (char**)argv, 0))
		{
			nv = newargv;
			*nv++ = "sh";
			*nv++ = (char*)path;
			ov = (char**)argv;
			while (*nv++ = *++ov);
			path = pathshell();
			execve(path, newargv, envv);
			free(newargv);
		}
		else
			errno = ENOMEM;
	}
	return -1;
}

#endif
