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

/*	Safe access to the internal stream buffer.
**	This function is obsolete. sfreserve() should be used.
**
**	Written by Kiem-Phong Vo (06/27/90).
*/

extern ssize_t sfpeek(reg Sfio_t*	f,	/* file to peek */
		      void**		bp,	/* start of data area */
		      reg size_t	size)	/* size of peek */
{	reg ssize_t	n, sz;
	reg int		mode;

	/* query for the extent of the remainder of the buffer */
	if((sz = size) == 0 || !bp)
	{	if(f->mode&SF_INIT)
			(void)_sfmode(f,0,0);

		if((f->flags&SF_RDWRSTR) == SF_RDWRSTR)
		{	SFSTRSIZE(f);
			n = (f->data+f->here) - f->next;
		}
		else	n = f->endb - f->next;

		if(!bp)
			return n;
		else if(n > 0)	/* size == 0 */
		{	*bp = (void*)f->next;
			return 0;
		}
		/* else fall down and fill buffer */
	}

	if(!(mode = f->flags&SF_READ) )
		mode = SF_WRITE;
	if((int)f->mode != mode && _sfmode(f,mode,0) < 0)
		return -1;

	*bp = sfreserve(f, sz <= 0 ? 0 : sz > f->size ? f->size : sz, 0);

	if(*bp && sz >= 0)
		return sz;

	if((n = sfvalue(f)) > 0)
	{	*bp = (void*)f->next;
		if(sz < 0)
		{	f->mode |= SF_PEEK;
			f->endr = f->endw = f->data;
		}
		else
		{	if(sz > n)
				sz = n;
			f->next += sz;
		}
	}

	return (sz >= 0 && n >= sz) ? sz : n;
}
