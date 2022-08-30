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
 * AT&T Bell Laboratories
 * force current command to run under dir preroot
 */

#include <ast.h>
#include <preroot.h>

#if FS_PREROOT

#include <option.h>

void
setpreroot(register char** argv, const char* dir)
{
	register char*	s;
	register char**	ap;
	int		argc;
	char*		cmd;
	char**		av;
	char		buf[PATH_MAX];

	if ((argv || (argv = opt_info.argv)) && (dir || (dir = getenv(PR_BASE)) && *dir) && !ispreroot(dir) && (*(cmd = *argv++) == '/' || (cmd = pathpath(cmd, NiL, PATH_ABSOLUTE|PATH_REGULAR|PATH_EXECUTE, buf, sizeof(buf)))))
	{
		argc = 3;
		for (ap = argv; *ap++; argc++);
		if (av = newof(0, char*, argc, 0))
		{
			ap = av;
			*ap++ = PR_COMMAND;
			*ap++ = (char*)dir;
			*ap++ = cmd;
			while (*ap++ = *argv++);
			if (!(s = getenv(PR_SILENT)) || !*s)
			{
				sfprintf(sfstderr, "+");
				ap = av;
				while (s = *ap++)
					sfprintf(sfstderr, " %s", s);
				sfprintf(sfstderr, "\n");
				sfsync(sfstderr);
			}
			execv(*av, av);
			free(av);
		}
	}
}

#else

NoN(setpreroot)

#endif
