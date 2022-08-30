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
 * aux function for <ls.h> iblocks() macro
 *
 * return number of blocks, including indirect block count
 * given stat info
 *
 * mail gsf@research.att.com when you figure out the stat.st_blocks units
 * until then we assume LS_BLOCKSIZE (512)
 */

#include <ast.h>
#if _AIX /* XXX */
#undef	major
#undef	minor
#undef	makedev
#endif
#include <ast_param.h>
#include <ls.h>

#if !_mem_st_blocks_stat

#ifndef B_DIRECT
#define B_DIRECT	10
#endif

#ifdef BITFS

#define B_SIZE		BSIZE(st->st_dev)
#define B_INDIRECT	NINDIR(st->st_dev)

#else

#ifdef BSIZE
#define B_SIZE		BSIZE
#else
#define B_SIZE		1024
#endif

#ifdef NINDIR
#define B_INDIRECT	NINDIR
#else
#define B_INDIRECT	128
#endif

#endif

#endif

off_t
_iblocks(register struct stat* st)
{
#if _mem_st_blocks_stat

	return (st->st_blocks <= 0 || st->st_size <= 0) ? 0 : st->st_blocks;

#else
	unsigned long	b;
	unsigned long	t;

	t = b = (st->st_size + B_SIZE - 1) / B_SIZE;
	if ((b -= B_DIRECT) > 0)
	{
		t += (b - 1) / B_INDIRECT + 1;
		if ((b -= B_INDIRECT) > 0)
		{
			t += (b - 1) / (B_INDIRECT * B_INDIRECT) + 1;
			if (b > B_INDIRECT * B_INDIRECT)
				t++;
		}
	}
	return t * B_SIZE / LS_BLOCKSIZE;
#endif
}
