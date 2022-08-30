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
/*
 * POSIX wordexp interface definitions
 */

#ifndef _WORDEXP_H
#define _WORDEXP_H

#include <ast_common.h>

#define WRDE_APPEND	01
#define WRDE_DOOFFS	02
#define WRDE_NOCMD	04
#define WRDE_NOSYS	0100
#define WRDE_REUSE	010
#define WRDE_SHOWERR	020
#define WRDE_UNDEF	040

#define WRDE_BADCHAR	1
#define WRDE_BADVAL	2
#define WRDE_CMDSUB	3
#define WRDE_NOSPACE	4
#define WRDE_SYNTAX	5
#define WRDE_NOSHELL	6

typedef struct _wdarg
{
	size_t	we_wordc;
	char	**we_wordv;
	size_t	we_offs;
} wordexp_t;

extern int wordexp(const char*, wordexp_t*, int);
extern int wordfree(wordexp_t*);

#endif /* _WORDEXP_H */
