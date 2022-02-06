#-------------------------------------------------------------------------
#
# Makefile.inc--
#    Makefile for access/common
#
# Copyright (c) 1994, Regents of the University of California
#
#
# IDENTIFICATION
#    $Header: /usr/local/cvsroot/postgres95/src/backend/access/common/Makefile.inc,v 1.1.1.1 1996/07/09 06:21:09 scrappy Exp $
#
#-------------------------------------------------------------------------

SUBSRCS+= heaptuple.c heapvalid.c indextuple.c indexvalid.c printtup.c \
	scankey.c tupdesc.c

