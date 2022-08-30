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
 * openlog implementation
 */

#include <ast.h>

#if _lib_syslog

NoN(openlog)

#else

#include "sysloglib.h"

void
openlog(const char* ident, int flags, int facility)
{
	int		n;

	if (ident)
	{
		n = strlen(ident);
		if (n >= sizeof(log.ident))
			n = sizeof(log.ident) - 1;
		memcpy(log.ident, ident, n);
		log.ident[n] = 0;
	}
	else
		log.ident[0] = 0;
	log.facility = facility;
	log.flags = flags;
	if (!(log.flags & LOG_ODELAY))
		sendlog(NiL);
}

#endif
