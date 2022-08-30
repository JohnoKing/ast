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
 * porting hacks here
 */

#include <ast.h>
#include <ls.h>

#include "FEATURE/hack"

NoN(gross)

#if _lcl_xstat

extern int fstat(int fd, struct stat* st)
{
#if _lib___fxstat
	return __fxstat(_STAT_VER, fd, st);
#else
	return _fxstat(_STAT_VER, fd, st);
#endif
}

extern int lstat(const char* path, struct stat* st)
{
#if _lib___lxstat
	return __lxstat(_STAT_VER, path, st);
#else
	return _lxstat(_STAT_VER, path, st);
#endif
}

extern int stat(const char* path, struct stat* st)
{
#if _lib___xstat
	return __xstat(_STAT_VER, path, st);
#else
	return _xstat(_STAT_VER, path, st);
#endif
}

#endif

#if __sgi && _hdr_locale_attr

#include "gross_sgi.h"

#endif
