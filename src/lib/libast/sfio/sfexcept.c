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

/*	Function to handle io exceptions.
**	Written by Kiem-Phong Vo
*/

int _sfexcept(Sfio_t*	f,	/* stream where the exception happened */
	      int	type,	/* io type that was performed */
	      ssize_t	io,	/* the io return value that indicated exception */
	      Sfdisc_t*	disc)	/* discipline in use */
{
	reg int		ev, local, lock;
	reg ssize_t	size;
	reg uchar*	data;

	if(!f)
		return -1;

	GETLOCAL(f,local);
	lock = f->mode&SF_LOCK;

	if(local && io <= 0)
		f->flags |= io < 0 ? SF_ERROR : SF_EOF;

	if(disc && disc->exceptf)
	{	/* let the stream be generally accessible for this duration */
		if(local && lock)
			SFOPEN(f,0);

		/* so that exception handler knows what we are asking for */
		_Sfi = f->val = io;
		ev = (*(disc->exceptf))(f,type,&io,disc);

		/* relock if necessary */
		if(local && lock)
			SFLOCK(f,0);

		if(io > 0 && !(f->flags&SF_STRING) )
			return ev;
		if(ev < 0)
			return SF_EDONE;
		if(ev > 0)
			return SF_EDISC;
	}

	if(f->flags&SF_STRING)
	{	if(type == SF_READ)
			goto chk_stack;
		else if(type != SF_WRITE && type != SF_SEEK)
			return SF_EDONE;
		if(local && io >= 0)
		{	if(f->size >= 0 && !(f->flags&SF_MALLOC))
				goto chk_stack;
			/* extend buffer */
			if((size = f->size) < 0)
				size = 0;
			if((io -= size) <= 0)
				io = SF_GRAIN;
			size = ((size+io+SF_GRAIN-1)/SF_GRAIN)*SF_GRAIN;
			if(f->size > 0)
				data = (uchar*)realloc((char*)f->data,size);
			else	data = (uchar*)malloc(size);
			if(!data)
				goto chk_stack;
			f->endb = data + size;
			f->next = data + (f->next - f->data);
			f->endr = f->endw = f->data = data;
			f->size = size;
		}
		return SF_EDISC;
	}

	if(errno == EINTR)
	{	if(_Sfexiting || (f->bits&SF_ENDING) ||	/* stop being a hero	*/
		   (f->flags&SF_IOINTR) ) /* application requests to return	*/
			return SF_EDONE;

		/* a normal interrupt, we can continue */
		errno = 0;
		f->flags &= ~(SF_EOF|SF_ERROR);
		return SF_ECONT;
	}

chk_stack:
	if(local && f->push &&
	   ((type == SF_READ  && f->next >= f->endb) ||
	    (type == SF_WRITE && f->next <= f->data)))
	{	/* pop the stack */
		reg Sfio_t	*pf;

		if(lock)
			SFOPEN(f,0);

		/* pop and close */
		pf = (*_Sfstack)(f,NIL(Sfio_t*));
		if((ev = sfclose(pf)) < 0) /* can't close, restack */
			(*_Sfstack)(f,pf);

		if(lock)
			SFLOCK(f,0);

		ev = ev < 0 ? SF_EDONE : SF_ESTACK;
	}
	else	ev = SF_EDONE;

	return ev;
}
