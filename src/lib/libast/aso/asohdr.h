/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2012 AT&T Intellectual Property          *
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
#ifndef _ASOHDR_H
#define _ASOHDR_H	1

#if _PACKAGE_ast

#include	<ast.h>
#include	<error.h>
#include	<fnv.h>

#else

#include	<errno.h>

#ifndef elementsof
#define elementsof(x)	(sizeof(x)/sizeof(x[0]))
#endif
#ifndef integralof
#define integralof(x)	(((char*)(x))-((char*)0))
#endif
#ifndef FNV_MULT
#define FNV_MULT	0x01000193L
#endif
#ifndef NiL
#define NiL		((void*)0)
#endif
#ifndef NoN 
#define NoN(x)		void _STUB_ ## x () {}
#if !defined(_STUB_)
#define _STUB_
#endif
#endif

#endif

#include	"FEATURE/asometh"

#include	"aso.h"

#define HASH(p,z)	((integralof(p)*FNV_MULT)%(z))

#endif
