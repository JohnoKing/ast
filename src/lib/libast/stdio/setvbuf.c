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

#include "stdhdr.h"

int
setvbuf(Sfio_t* f, char* buf, int type, size_t size)
{
	if (type == _IOLBF)
		sfset(f, SF_LINE, 1);
	else if (f->flags & SF_STRING)
		return -1;
	else if (type == _IONBF)
	{	
		sfsync(f);
		sfsetbuf(f, NiL, 0);
	}
	else if (type == _IOFBF)
	{	
		if (size == 0)
			size = SF_BUFSIZE;
		sfsync(f);
		sfsetbuf(f, (void*)buf, size);
	}
	return 0;
}
