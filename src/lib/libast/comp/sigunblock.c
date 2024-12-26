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
*                                                                      *
***********************************************************************/

/*
 * There is no longer a test for a native sigunblock() here because we
 * always use the sigprocmask(3) version now. Obsolete functions don't
 * necessarily mix with the POSIX interface. Plus, on QNX, sigunblock()
 * expects a signal mask argument, not a signal number.
 */

#include <ast.h>
#include <sig.h>

/*
 * remove s from the set of blocked signals
 * s==0 unblocks them all
 */

int
sigunblock(int s)
{
	int		op;
	sigset_t	mask;

	sigemptyset(&mask);
	if (s)
	{
		sigaddset(&mask, s);
		op = SIG_UNBLOCK;
	}
	else op = SIG_SETMASK;
	return sigprocmask(op, &mask, NULL);
}
