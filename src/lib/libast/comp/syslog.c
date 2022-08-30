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
 * syslog implementation
 */

#include <ast.h>

#if _lib_syslog

NoN(syslog)

#else

#define LOG_TABLES

#include "sysloglib.h"

#include <error.h>
#include <tm.h>

Syslog_state_t		log = { LOG_USER, -1, 0, ~0 };

static const Namval_t	attempt[] =
{
	"/dev/log",			0,
	"var/log/syslog",		0,
	"lib/syslog/log",		0,
	"/dev/console",			LOG_CONS,
};

const Namval_t		log_facility[] =
{
	"default",	0,
	"user",		LOG_USER,
	"kernel",	LOG_KERN,
	"mail",		LOG_MAIL,
	"daemon",	LOG_DAEMON,
	"security",	LOG_AUTH,
	"syslog",	LOG_SYSLOG,
	"lpr",		LOG_LPR,
	"news",		LOG_NEWS,
	"uucp",		LOG_UUCP,
	"cron",		LOG_CRON,
	"audit",	LOG_AUDIT,
	"logalert",	LOG_LFMT,
#ifdef LOG_SYSTEM2
	"system2",	LOG_SYSTEM2,
#endif
#ifdef LOG_SYSTEM1
	"system1",	LOG_SYSTEM1,
#endif
#ifdef LOG_SYSTEM0
	"system0",	LOG_SYSTEM0,
#endif
	0,		0
};

const Namval_t		log_severity[] =
{
	"panic",	LOG_EMERG,
	"alert",	LOG_ALERT,
	"critical",	LOG_CRIT,
	"error",	LOG_ERR,
	"warning",	LOG_WARNING,
	"notice",	LOG_NOTICE,
	"info",		LOG_INFO,
	"debug",	LOG_DEBUG,
	0,		0
};

void
sendlog(const char* msg)
{
	register char*		s;
	register Namval_t*	p;
	register int		n;

	n = msg ? strlen(msg) : 0;
	for (;;)
	{
		if (log.fd < 0)
		{
			char	buf[PATH_MAX];

			if (log.attempt >= elementsof(attempt))
				break;
			p = (Namval_t*)&attempt[log.attempt++];
			if (p->value && !(p->value & log.flags))
				continue;
			if (*(s = p->name) != '/' && !(s = pathpath(buf, s, "", PATH_REGULAR|PATH_READ, sizeof(buf))))
				continue;
			if ((log.fd = open(s, O_WRONLY|O_APPEND|O_NOCTTY|O_cloexec)) < 0)
				continue;
#if !O_cloexec
			fcntl(log.fd, F_SETFD, FD_CLOEXEC);
#endif
		}
		if (!n || write(log.fd, msg, n) > 0)
			break;
		close(log.fd);
		log.fd = -1;
	}
	if (n && (log.flags & LOG_PERROR))
		write(2, msg, n);
}

static int
extend(Sfio_t* sp, void* vp, Sffmt_t* dp)
{
	if (dp->fmt == 'm')
	{
		dp->flags |= SFFMT_VALUE;
		dp->fmt = 's';
		dp->size = -1;
		*((char**)vp) = fmterror(errno);
	}
	return 0;
}

void
vsyslog(int priority, const char* format, va_list ap)
{
	register int	c;
	register char*	s;
	Sfio_t*		sp;
	Sffmt_t		fmt;
	char		buf[16];

	if (!LOG_FACILITY(priority))
		priority |= log.facility;
	if (!(priority & log.mask))
		return;
	if (sp = sfstropen())
	{
		sfputr(sp, fmttime("%b %d %H:%M:%S", time(NiL)), -1);
		if (log.flags & LOG_LEVEL)
		{
			if ((c = LOG_SEVERITY(priority)) < elementsof(log_severity))
				s = (char*)log_severity[c].name;
			else
				sfsprintf(s = buf, sizeof(buf), "debug%d", c);
			sfprintf(sp, " %-8s ", s);
			if ((c = LOG_FACILITY(priority)) < elementsof(log_facility))
				s = (char*)log_facility[c].name;
			else
				sfsprintf(s = buf, sizeof(buf), "local%d", c);
			sfprintf(sp, " %-8s ", s);
		}
#if _lib_gethostname
		if (!*log.host && gethostname(log.host, sizeof(log.host)-1))
			strcpy(log.host, "localhost");
		sfprintf(sp, " %s", log.host);
#endif
		if (*log.ident)
			sfprintf(sp, " %s", log.ident);
		if (log.flags & LOG_PID)
		{
			if (!*log.ident)
				sfprintf(sp, " ");
			sfprintf(sp, "[%d]", getpid());
		}
		if (format)
		{
			sfprintf(sp, ": ");
			memset(&fmt, 0, sizeof(fmt));
			fmt.version = SFIO_VERSION;
			fmt.form = (char*)format;
			fmt.extf = extend;
			va_copy(fmt.args, ap);
			sfprintf(sp, "%!", &fmt);
		}
		if ((s = sfstrseek(sp, 0, SEEK_CUR)) && *(s - 1) != '\n')
			sfputc(sp, '\n');
		if (s = sfstruse(sp))
			sendlog(s);
		sfstrclose(sp);
	}
}

void
syslog(int priority, const char* format, ...)
{
	va_list		ap;

	va_start(ap, format);
	vsyslog(priority, format, ap);
	va_end(ap);
}

#endif
