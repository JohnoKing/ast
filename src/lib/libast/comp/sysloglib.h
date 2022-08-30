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
 * POSIX syslog implementation definitions
 */

#ifndef _SYSLOGLIB_H
#define _SYSLOGLIB_H

#include <syslog.h>

#define log		_log_info_
#define sendlog		_log_send_

/*
 * NOTE: syslog() has a static initializer for Syslog_state_t log
 */

typedef struct
{
	int		facility;	/* openlog facility		*/
	int		fd;		/* log to this fd		*/
	int		flags;		/* openlog flags		*/
	unsigned int	mask;		/* setlogmask mask		*/
	int		attempt;	/* logfile attempt state	*/
	char		ident[64];	/* openlog ident		*/
	char		host[64];	/* openlog host name		*/
} Syslog_state_t;

extern Syslog_state_t	log;

extern void		sendlog(const char*);

#endif
