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

/*
**	Any required functions for process exiting.
**	Written by Kiem-Phong Vo, kpv@research.att.com (05/25/93).
*/
#if _PACKAGE_ast || _lib_atexit

NoN(vmexit)

#else

#if _lib_onexit

int atexit(void (*exitf)(void))
{
	return onexit(exitf);
}

#else /*!_lib_onexit*/

typedef struct _exit_s
{	struct _exit_s*	next;
	void(*		exitf)(void);
} Exit_t;
static Exit_t*	Exit;

atexit(void (*exitf)(void))
{	Exit_t*	e;

	if(!(e = (Exit_t*)malloc(sizeof(Exit_t))) )
		return -1;
	e->exitf = exitf;
	e->next = Exit;
	Exit = e;
	return 0;
}

void exit(int type)
{
	Exit_t*	e;

	for(e = Exit; e; e = e->next)
		(*e->exitf)();

#if _exit_cleanup
	_cleanup();
#endif

	_exit(type);
	return type;
}

#endif	/* _lib_onexit */

#endif /*!PACKAGE_ast*/
