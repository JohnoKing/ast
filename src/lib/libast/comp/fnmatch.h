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
 * POSIX fnmatch interface definitions
 */

#ifndef _FNMATCH_H
#define _FNMATCH_H

#include <ast_common.h>

/* fnmatch flags */

#define FNM_NOESCAPE	0x0001		/* \ is literal			*/
#define FNM_PATHNAME	0x0002		/* explicit match for /		*/
#define FNM_PERIOD	0x0004		/* explicit match for leading .	*/
#define FNM_NOSYS	0x0010		/* not implemented		*/

/* nonstandard fnmatch() flags */

#define FNM_AUGMENTED	0x0008		/* enable ! & ( | )		*/
#define FNM_ICASE	0x0020		/* ignore case in match		*/
#define FNM_LEADING_DIR	0x0040		/* match up to implicit /	*/

#define FNM_CASEFOLD	FNM_ICASE	/* GNU/BSD compatibility	*/
#define FNM_IGNORECASE	FNM_ICASE	/* GNU/BSD compatibility	*/
#define FNM_FILE_NAME	FNM_PATHNAME	/* GNU compatibility		*/

/* fnmatch error codes -- other non-zero values from <regex.h> */

#define FNM_NOMATCH	1		/* == REG_NOMATCH		*/

extern int	fnmatch(const char*, const char*, int);

#endif
