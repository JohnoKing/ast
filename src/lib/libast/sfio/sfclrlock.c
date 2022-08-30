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
#include	"sfhdr.h"

/*	Function to clear a locked stream.
**	This is useful for programs that longjmp from the mid of an sfio function.
**	There is no guarantee on data integrity in such a case.
**
**	Written by Kiem-Phong Vo
*/
int sfclrlock(Sfio_t* f)
{
	int	rv;

	/* already closed */
	if(f && (f->mode&SF_AVAIL) || !f)
		return 0;

	/* clear error bits */
	f->flags &= ~(SF_ERROR|SF_EOF);

	/* clear peek locks */
	if(f->mode&SF_PKRD)
	{	f->here -= f->endb-f->next;
		f->endb = f->next;
	}

	SFCLRBITS(f);

	/* throw away all lock bits except for stacking state SF_PUSH */
	f->mode &= (SF_RDWR|SF_INIT|SF_POOL|SF_PUSH|SF_SYNCED|SF_STDIO);

	rv = (f->mode&SF_PUSH) ? 0 : (f->flags&SFIO_FLAGS);

	return rv;
}
