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
 * Glenn Fowler
 * AT&T Research
 *
 * homogeneous stack routine definitions
 */

#ifndef _STACK_H
#define _STACK_H

typedef struct stacktable* STACK;	/* stack pointer		*/
typedef struct stackposition STACKPOS;	/* stack position		*/

struct stackblock			/* stack block cell		*/
{
	void**		  stack;	/* actual stack			*/
	struct stackblock* prev;	/* previous block in list	*/
	struct stackblock* next;	/* next block in list		*/
};

struct stackposition			/* stack position		*/
{
	struct stackblock* block;	/* current block pointer	*/
	int		index;		/* index within current block	*/
};

struct stacktable			/* stack information		*/
{
	struct stackblock* blocks;	/* stack table blocks		*/
	void*		error;		/* error return value		*/
	int		size;		/* size of each block		*/
	STACKPOS	position;	/* current stack position	*/
};

/*
 * map old names to new
 */

#define mkstack		stackalloc
#define rmstack		stackfree
#define clrstack	stackclear
#define getstack	stackget
#define pushstack	stackpush
#define popstack	stackpop
#define posstack	stacktell

extern STACK		stackalloc(int, void*);
extern void		stackfree(STACK);
extern void		stackclear(STACK);
extern void*		stackget(STACK);
extern int		stackpush(STACK, void*);
extern int		stackpop(STACK);
extern void		stacktell(STACK, int, STACKPOS*);

#endif
