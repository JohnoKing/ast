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
 * readdir
 *
 * read from directory stream
 *
 * NOTE: directory entries must fit within DIRBLKSIZ boundaries
 */

#include "dirlib.h"

#if _dir_ok

NoN(readdir)

#else

struct dirent*
readdir(register DIR* dirp)
{
	register struct dirent*	dp;

	for (;;)
	{
		if (dirp->dd_loc >= dirp->dd_size)
		{
			if (dirp->dd_size < 0) return(0);
			dirp->dd_loc = 0;
			if ((dirp->dd_size = getdents(dirp->dd_fd, dirp->dd_buf, DIRBLKSIZ)) <= 0)
				return(0);
		}
		dp = (struct dirent*)((char*)dirp->dd_buf + dirp->dd_loc);
		if (dp->d_reclen <= 0) return(0);
		dirp->dd_loc += dp->d_reclen;
		if (dp->d_fileno) return(dp);
	}
	UNREACHABLE();
}

#endif
