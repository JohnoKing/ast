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

#include "asohdr.h"

#if _PACKAGE_ast
#include <tv.h>
#else
#include <time.h>
#endif

int
asorelax(long nsec)
{
#if _PACKAGE_ast
	Tv_t		tv;

	tv.tv_sec = 0;
	tv.tv_nsec = nsec;
	return tvsleep(&tv, 0);
#else
	struct timespec	ts;

	ts.tv_sec = 0;
	ts.tv_nsec = nsec;
	return nanosleep(&ts, 0);
#endif
}
