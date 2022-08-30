/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1992-2012 AT&T Intellectual Property          *
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
*                  Martijn Dekker <martijn@inlv.org>                   *
*                                                                      *
***********************************************************************/
/*
 * command initialization
 */

#include <cmd.h>
#include <shcmd.h>

int
_cmd_init(int argc, char** argv, Shbltin_t* context, const char* catalog, int flags)
{
	register char*	cp;

	if (argc <= 0)
		return -1;
	if (context)
	{
		if (flags & ERROR_CALLBACK)
		{
			flags &= ~ERROR_CALLBACK;
			flags |= ERROR_NOTIFY;
		}
		else if (flags & ERROR_NOTIFY)
		{
			context->notify = 1;
			flags &= ~ERROR_NOTIFY;
		}
		error_info.flags |= flags;
	}
	if (cp = strrchr(argv[0], '/'))
		cp++;
	else
		cp = argv[0];
	error_info.id = cp;
	if (!error_info.catalog)
		error_info.catalog = catalog;
	opt_info.index = 0;
	return 0;
}
