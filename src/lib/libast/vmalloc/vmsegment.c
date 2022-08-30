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

/*	Get the segment containing this address
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 02/07/95
*/

void* vmsegment(Vmalloc_t*	vm,	/* region	*/
		void*		addr)	/* address	*/
{
	Seg_t		*seg;
	Vmdata_t	*vd = vm->data;

	SETLOCK(vm, 0);

	for(seg = vd->seg; seg; seg = seg->next)
		if((Vmuchar_t*)addr >= (Vmuchar_t*)seg->addr &&
		   (Vmuchar_t*)addr <  (Vmuchar_t*)seg->baddr )
			break;

	CLRLOCK(vm, 0);

	return seg ? (void*)seg->addr : NIL(void*);
}
