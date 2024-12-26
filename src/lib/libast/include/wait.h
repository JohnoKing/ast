/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
*          Copyright (c) 2020-2024 Contributors to ksh 93u+m           *
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
*            Johnothan King <johnothanking@protonmail.com>             *
*                                                                      *
***********************************************************************/
/*
 * AST POSIX wait/exit support
 */

#ifndef _WAIT_H
#define _WAIT_H

#include <ast.h>

#define wait		______wait
#define waitpid		______waitpid
#include <sys/wait.h>
#undef	wait
#undef	waitpid

/*
 * WCOREDUMP was added in POSIX Issue 8 (2024); AST always had WTERMCORE instead.
 */
#ifndef WTERMCORE
#  ifdef WCOREDUMP
#    define WTERMCORE(x)	WCOREDUMP(x)
#  else
#    define WTERMCORE(x)	((x) & 128)
#  endif
#endif

extern pid_t		wait(int*);
extern pid_t		waitpid(pid_t, int*, int);

#endif
