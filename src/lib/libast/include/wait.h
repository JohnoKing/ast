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
 * AST POSIX wait/exit support
 */

#ifndef _WAIT_H
#define _WAIT_H

#include <ast.h>
#include <ast_wait.h>

#if _sys_wait
#define wait		______wait
#define waitpid		______waitpid
#include <sys/wait.h>
#undef	wait
#undef	waitpid
#endif

#ifndef WNOHANG
#define WNOHANG		1
#endif

#ifndef WUNTRACED
#define WUNTRACED	2
#endif

#if !_ok_wif
#undef	WIFEXITED
#undef	WEXITSTATUS
#undef	WIFSIGNALED
#undef	WTERMSIG
#undef	WIFSTOPPED
#undef	WSTOPSIG
#undef	WTERMCORE
#endif

#ifndef WIFEXITED
#define WIFEXITED(x)	(!((x) & EXIT_NOTFOUND))
#endif

#ifndef WEXITSTATUS
#define WEXITSTATUS(x)	(((x) >> 8) & EXIT_QUIT)
#endif

#ifndef WIFSIGNALED
#define WIFSIGNALED(x)	(((x) & EXIT_NOTFOUND) != 0)
#endif

#ifndef WTERMSIG
#define WTERMSIG(x)	((x) & EXIT_NOTFOUND)
#endif

#ifndef WIFSTOPPED
#define WIFSTOPPED(x)	(((x) & EXIT_QUIT) == EXIT_NOTFOUND)
#endif

#ifndef WSTOPSIG
#define WSTOPSIG(x)	WEXITSTATUS(x)
#endif

#ifndef WTERMCORE
#define WTERMCORE(x)	((x) & 128)
#endif

extern pid_t		wait(int*);
extern pid_t		waitpid(pid_t, int*, int);

#endif
