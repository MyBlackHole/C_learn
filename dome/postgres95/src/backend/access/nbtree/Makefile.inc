#-------------------------------------------------------------------------
#
# Makefile.inc--
#    Makefile for access/nbtree (btree acess methods)
#
# Copyright (c) 1994, Regents of the University of California
#
#
# IDENTIFICATION
#    $Header: /usr/local/cvsroot/postgres95/src/backend/access/nbtree/Makefile.inc,v 1.1.1.1 1996/07/09 06:21:11 scrappy Exp $
#
#-------------------------------------------------------------------------

SUBSRCS+= nbtcompare.c nbtinsert.c nbtpage.c nbtree.c nbtscan.c nbtsearch.c \
	nbtstrat.c nbtutils.c nbtsort.c
