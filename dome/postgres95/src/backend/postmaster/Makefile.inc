#-------------------------------------------------------------------------
#
# Makefile.inc--
#    Makefile for the postmaster module
#
# Copyright (c) 1994, Regents of the University of California
#
#
# IDENTIFICATION
#    $Header: /usr/local/cvsroot/postgres95/src/backend/postmaster/Makefile.inc,v 1.1.1.1 1996/07/09 06:21:49 scrappy Exp $
#
#-------------------------------------------------------------------------

VPATH:= $(VPATH):$(CURDIR)/postmaster

SRCS_POSTMASTER= postmaster.c
