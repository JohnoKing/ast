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

/*	Return the containing region of an allocated piece of memory.
**	Beware: this only works with Vmbest, Vmdebug and Vmprofile.
**
**	10/31/2009: Add handling of shared/persistent memory regions.
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 01/16/94.
*/
Vmalloc_t* vmregion(void* addr)
{
	Vmalloc_t	*vm;
	Vmdata_t	*vd;

	if(!addr)
		return NIL(Vmalloc_t*);

	vd = SEG(BLOCK(addr))->vmdt;

	_vmlock(NIL(Vmalloc_t*), 1);
	for(vm = Vmheap; vm; vm = vm->next)
		if(vm->data == vd)
			break;
	_vmlock(NIL(Vmalloc_t*), 0);

	return vm;
}
