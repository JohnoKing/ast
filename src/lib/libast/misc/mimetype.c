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
 * mime/mailcap to magic support
 */

#include "mimelib.h"

/*
 * close magic handle
 * done this way so that magic is only pulled in
 * if mimetype() is used
 */

static void
drop(Mime_t* mp)
{
	if (mp->magic)
	{
		magicclose(mp->magic);
		mp->magic = 0;
	}
}

/*
 * return mime type for file
 */

char*
mimetype(Mime_t* mp, Sfio_t* fp, const char* file, struct stat* st)
{
	if (mp->disc->flags & MIME_NOMAGIC)
		return 0;
	if (!mp->magic)
	{
		mp->magicd.version = MAGIC_VERSION;
		mp->magicd.flags = MAGIC_MIME;
		mp->magicd.errorf = mp->disc->errorf;
		if (!(mp->magic = magicopen(&mp->magicd)))
		{
			mp->disc->flags |= MIME_NOMAGIC;
			return 0;
		}
		mp->freef = drop;
		magicload(mp->magic, NiL, 0);
	}
	return magictype(mp->magic, fp, file, st);
}
