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

#include	"vmhdr.h"

/*	A discipline to get memory from the heap.
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 01/16/94.
*/
static void* heapmem(Vmalloc_t*	vm,	/* region doing allocation from 	*/
		     void*	caddr,	/* current low address			*/
		     size_t	csize,	/* current size				*/
		     size_t	nsize,	/* new size				*/
		     Vmdisc_t*	disc)	/* discipline structure			*/
{
	if(csize == 0 && nsize == 0)
		return NIL(void*);
	else if(csize == 0)
		return vmalloc(Vmheap,nsize);
	else if(nsize == 0)
		return vmfree(Vmheap,caddr) >= 0 ? caddr : NIL(void*);
	else	return vmresize(Vmheap,caddr,nsize,0);
}

static Vmdisc_t _Vmdcheap = { heapmem, NIL(Vmexcept_f), 0 };
Vmdisc_t*	Vmdcheap = &_Vmdcheap;

#ifdef NoF
NoF(vmdcheap)
#endif
