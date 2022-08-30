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
 * dirname(3) implementation
 */

#include <ast_std.h>

extern char *dirname(register char *pathname)
{
	register char  *last;
	/* go to end of path */
	for(last=pathname; *last; last++);
	/* back over trailing '/' */
	while(last>pathname && *--last=='/');
	/* back over non-slash chars */
	for(;last>pathname && *last!='/';last--);
	if(last==pathname)
	{
		/* all '/' or "" */
		if(*last!='/')
			*last = '.';
		/* preserve // */
		else if(last[1]=='/')
			last++;
	}
	else
	{
		/* back over trailing '/' */
		for(;*last=='/' && last > pathname; last--);
		/* preserve // */
		if(last==pathname && *pathname=='/' && pathname[1]=='/')
			last++;
	}
	*(last + 1) = 0;
	return(pathname);
}
