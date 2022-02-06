#!/bin/sh
#
# $Header: /usr/local/cvsroot/postgres95/src/bin/ipcclean/ipcclean.sh,v 1.1.1.1 1996/07/09 06:22:13 scrappy Exp $
#
PATH=_fUnKy_IPCCLEANPATH_sTuFf_:$PATH
export PATH
ipcs | egrep '^m .*|^s .*' | egrep "`whoami`|postgres" | \
awk '{printf "ipcrm -%s %s\n", $1, $2}' '-' | sh
