/**************************************************************************
Disposition - Library to generate permutations and combinations of elements
Copyright (C) 2005 Carlos Rica Espinosa (jasampler@yahoo.es)

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.
**************************************************************************/

/* internal functions for dispositions */

#include "dispcommon.h"
#include "cmem.h"
#include <assert.h>
#include <stdlib.h>

Disposition *allocDisposition(int dispsize, size_t datasize) {
	Disposition *disp;
	size_t totalsize;
	totalsize = sizeof(Disposition);
	totalsize += datasize;
	if (dispsize > 0)
		totalsize += sizeof(int) * dispsize;
	disp = (Disposition *) cmem_malloc(totalsize);
	if (disp != NULL) {
		disp->dispsize = dispsize;
		if (datasize)
			disp->dispdata = (void *) (disp + 1);
		else
			disp->dispdata = NULL;
		if (dispsize > 0)
			disp->dispvec = (int *)
					((char *) (disp + 1) + datasize);
		else
			disp->dispvec = NULL;
	}
	return disp;
}

void freeDisposition(Disposition *disp) {
	assert(disp != NULL);
	cmem_free(disp);
}

Disposition *copyDisposition(Disposition *disp, size_t datasize) {
	Disposition *copy;
	assert(disp != NULL);
	copy = allocDisposition(disp->dispsize, datasize);
	if (copy != NULL) {
		copy->dispnumelem = disp->dispnumelem;
		copy->dispfunc = disp->dispfunc;
		if (copy->dispvec != NULL)
			memcpy(copy->dispvec, disp->dispvec,
						sizeof(int) * copy->dispsize);
	}
	return copy;
}

