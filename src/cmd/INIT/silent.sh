########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1994-2011 AT&T Intellectual Property          #
#          Copyright (c) 2020-2022 Contributors to ksh 93u+m           #
#                      and is licensed under the                       #
#                 Eclipse Public License, Version 2.0                  #
#                                                                      #
#                A copy of the License is available at                 #
#      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      #
#         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         #
#                                                                      #
#                 Glenn Fowler <gsf@research.att.com>                  #
#                  Martijn Dekker <martijn@inlv.org>                   #
#                                                                      #
########################################################################
# non-ksh stub for the nmake silent prefix
# @(#)silent (ksh 93u+m) 2021-12-31

while	:
do	case $# in
	0)	exit 0 ;;
	esac
	case $1 in
	*=*)	export "$1"
		shift
		;;
	*)	break
		;;
	esac
done
"$@"
