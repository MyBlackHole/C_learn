#-------------------------------------------------------------------------
#
# Makefile.inc--
#    Makefile for port/linux (Linux specific stuff)
#
# Copyright (c) 1994, Regents of the University of California
#
#
# IDENTIFICATION
#    $Header: /usr/local/cvsroot/postgres95/src/backend/port/dgux/Makefile.inc,v 1.1 1996/07/25 20:43:56 scrappy Exp $
#
# NOTES
#    The Linux port is included here by courtesy of Kai Petzke.
#
#    (C) 1994, Kai Petzke, wpp@marie.physik.tu-berlin.de
#
#-------------------------------------------------------------------------

BIGOBJS= false

CFLAGS+= -DLINUX_ELF

HEADERS+= machine.h port-protos.h
CFLAGS+= #-DNEED_CBRT

