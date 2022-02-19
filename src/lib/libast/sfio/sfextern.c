/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 1.0                  *
*                    by AT&T Intellectual Property                     *
*                                                                      *
*                A copy of the License is available at                 *
*          http://www.eclipse.org/org/documents/epl-v10.html           *
*         (with md5 checksum b35adb5213ca9657e911e9befb180842)         *
*                                                                      *
*              Information and Software Systems Research               *
*                            AT&T Research                             *
*                           Florham Park NJ                            *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                                                                      *
***********************************************************************/
#include	"sfhdr.h"

/*	External variables and functions used only by Sfio
**	Written by Kiem-Phong Vo
*/

/* global variables used internally to the package */
Sfextern_t _Sfextern =
{	0,						/* _Sfpage	*/
	{ NIL(Sfpool_t*), 0, 0, 0, NIL(Sfio_t**) },	/* _Sfpool	*/
	NIL(int(*)(Sfio_t*,int)),			/* _Sfpmove	*/
	NIL(Sfio_t*(*)(Sfio_t*, Sfio_t*)),		/* _Sfstack	*/
	NIL(void(*)(Sfio_t*, int, void*)),		/* _Sfnotify	*/
	NIL(int(*)(Sfio_t*)),				/* _Sfstdsync	*/
	{ NIL(Sfread_f),				/* _Sfudisc	*/
	  NIL(Sfwrite_f),
	  NIL(Sfseek_f),
	  NIL(Sfexcept_f),
	  NIL(Sfdisc_t*)
	},
	NIL(void(*)(void)),				/* _Sfcleanup	*/
	0,						/* _Sfexiting	*/
	0,						/* _Sfdone	*/
};

ssize_t	_Sfi = -1;		/* value for a few fast macro functions	*/
ssize_t _Sfmaxr = 0;		/* default (unlimited) max record size	*/

Sfio_t	_Sfstdin  = SFNEW(NIL(char*),-1,0,
			  (SF_READ |SF_STATIC),NIL(Sfdisc_t*));
Sfio_t	_Sfstdout = SFNEW(NIL(char*),-1,1,
			  (SF_WRITE|SF_STATIC),NIL(Sfdisc_t*));
Sfio_t	_Sfstderr = SFNEW(NIL(char*),-1,2,
			  (SF_WRITE|SF_STATIC),NIL(Sfdisc_t*));

#undef	sfstdin
#undef	sfstdout
#undef	sfstderr

Sfio_t*	sfstdin  = &_Sfstdin;
Sfio_t*	sfstdout = &_Sfstdout;
Sfio_t*	sfstderr = &_Sfstderr;

__EXTERN__(ssize_t,_Sfi);
__EXTERN__(Sfio_t,_Sfstdin);
__EXTERN__(Sfio_t,_Sfstdout);
__EXTERN__(Sfio_t,_Sfstderr);
__EXTERN__(Sfio_t*,sfstdin);
__EXTERN__(Sfio_t*,sfstdout);
__EXTERN__(Sfio_t*,sfstderr);
