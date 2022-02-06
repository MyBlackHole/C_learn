/*-------------------------------------------------------------------------
 *
 * excabort.c--
 *    Default exception abort code.
 *
 * Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *    $Header: /usr/local/cvsroot/postgres95/src/backend/utils/error/excabort.c,v 1.1.1.1 1996/07/09 06:22:07 scrappy Exp $
 *
 *-------------------------------------------------------------------------
 */
#include "utils/exc.h"		/* where function declarations go */

void
ExcAbort(const Exception *excP, 
	 ExcDetail detail, 
	 ExcData data,
	 ExcMessage message)
{
#ifdef	__SABER__
    saber_stop();
#else
    /* dump core */
    abort();
#endif
}
