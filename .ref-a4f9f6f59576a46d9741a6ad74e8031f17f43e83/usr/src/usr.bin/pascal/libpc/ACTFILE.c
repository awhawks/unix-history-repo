/* Copyright (c) 1979 Regents of the University of California */

static char sccsid[] = "@(#)ACTFILE.c 1.1 %G%";

#include "h00vars.h"

FILE *
ACTFILE(curfile)

	struct iorec	*curfile;
{
	return curfile->fbuf;
}
