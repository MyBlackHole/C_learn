#-------------------------------------------------------------------------
#
# Makefile.inc--
#    Makefile for port/sparc (SPARC/SunOS 4 specific stuff)
#
# Copyright (c) 1994, Regents of the University of California
#
#
# IDENTIFICATION
#    $Header: /usr/local/cvsroot/postgres95/src/backend/port/sparc/Makefile.inc,v 1.1.1.1 1996/07/09 06:21:44 scrappy Exp $
#
#-------------------------------------------------------------------------

CFLAGS+= -DUSE_POSIX_TIME

LDADD+= -lln -ldl

#
# SunOS 4 strtol is broken -- doesn't report overflow using errno.
#
SUBSRCS= strtol.c

HEADERS+= float.h machine.h port-protos.h
