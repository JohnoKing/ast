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

/*	Walks all segments created in region(s)
**
**	Written by Kiem-Phong Vo, kpv@research.att.com (02/08/96)
*/

int vmwalk(Vmalloc_t* vm, int(*segf)(Vmalloc_t*, void*, size_t, Vmdisc_t*, void*), void* handle )
{	
	reg Seg_t	*seg;
	reg int		rv = 0;

	if(!vm)
	{	_vmlock(NIL(Vmalloc_t*), 1);
		for(vm = Vmheap; vm; vm = vm->next)
		{	SETLOCK(vm, 0);
			for(seg = vm->data->seg; seg; seg = seg->next)
				if((rv = (*segf)(vm, seg->addr, seg->extent, vm->disc, handle)) < 0 )
					break;
			CLRLOCK(vm, 0);
		}
		_vmlock(NIL(Vmalloc_t*), 0);
	}
	else
	{	SETLOCK(vm, 0);
		for(seg = vm->data->seg; seg; seg = seg->next)
			if((rv = (*segf)(vm, seg->addr, seg->extent, vm->disc, handle)) < 0 )
				break;
		CLRLOCK(vm, 0);
	}

	return rv;
}
