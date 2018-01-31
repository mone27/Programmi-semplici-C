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

/* functions for permutations with repetition */

#include "permutationrep.h"
#include "dispcommon.h"
#include <assert.h>
#include <stdlib.h>

DispFunctions globalfuncPermutationRep = {
	firstPermutationRep, lastPermutationRep,
	nextPermutationRep, previousPermutationRep,
	checkPermutationRep, copyPermutationRep,
	randPermutationRep, deletePermutationRep
};

#define checkStructPermutationRep(d) \
		(d != NULL && d->dispnumelem > 0 \
			&& ((d->dispvec != NULL && d->dispsize > 0) \
				|| (d->dispvec == NULL && d->dispsize == 0)))

PermutationRep *newPermutationRep(int numelem, int size, DispNewError *err) {
	DispNewError e;
	PermutationRep *perm = NULL;
	if (numelem < 1)
		e = DISP_NEW_NUMELEM_LT_ONE;
	else if (size < 0)
		e = DISP_NEW_SIZE_LT_ZERO;
	else {
		perm = (PermutationRep *) allocDisposition(size, 0);
		if (perm == NULL)
			e = DISP_NEW_MEMORY_ALLOCATION;
		else {
			e = DISP_NEW_OK;
			perm->dispnumelem = numelem;
			perm->dispfunc    = &globalfuncPermutationRep;
		}
	}
	if (err != NULL) *err = e;
	return perm;
}

void deletePermutationRep(PermutationRep *perm) {
	assert(checkStructPermutationRep(perm));
	freeDisposition(perm);
}

/* first permutation with repetition PRm,n is (0,0,0,...,0) */
void firstPermutationRep(PermutationRep *perm) {
	int i;
	assert(checkStructPermutationRep(perm));
	for (i = 0; i < perm->dispsize; i++)
		perm->dispvec[i] = 0;
}

/* last permutation with repetition PRm,n is (m-1,m-1,...,m-1) */
void lastPermutationRep(PermutationRep *perm) {
	int i;
	assert(checkStructPermutationRep(perm));
	for (i = 0; i < perm->dispsize; i++)
		perm->dispvec[i] = perm->dispnumelem - 1;
}

DispCheckError checkPermutationRep(PermutationRep *perm, int *errpos) {
	int i, val;
	assert(checkStructPermutationRep(perm));
	for (i = 0; i < perm->dispsize; i++) {
		val = perm->dispvec[i];
		if (val < 0 || val >= perm->dispnumelem) {
			if (errpos != NULL) *errpos = i;
			return DISP_CHECK_ELEM_OUT_OF_RANGE;
		}
	}
	return DISP_CHECK_OK;
}

int nextPermutationRep(PermutationRep *perm) {
	int i;
	assert(checkStructPermutationRep(perm));
	assert(checkPermutationRep(perm, NULL) == DISP_CHECK_OK);
	/* finds the last element wich can be incremented: */
	for (i = perm->dispsize - 1; i >= 0
			&& perm->dispvec[i] == perm->dispnumelem - 1; i--);
	if (i < 0) return 0;
	/* increment that element and set to 0 the following elements: */
	for (perm->dispvec[i++]++; i < perm->dispsize; perm->dispvec[i++] = 0);
	return 1;
}

int previousPermutationRep(PermutationRep *perm) {
	int i;
	assert(checkStructPermutationRep(perm));
	assert(checkPermutationRep(perm, NULL) == DISP_CHECK_OK);
	/* finds the last element that can be decremented: */
	for (i = perm->dispsize - 1; i >= 0 && perm->dispvec[i] == 0; i--);
	if (i < 0) return 0;
	/* decrement that element and set the following to the last value: */
	for (perm->dispvec[i++]--; i < perm->dispsize;
			perm->dispvec[i++] = perm->dispnumelem - 1);
	return 1;
}

PermutationRep *copyPermutationRep(PermutationRep *perm) {
	assert(checkStructPermutationRep(perm));
	return (PermutationRep *) copyDisposition(perm, 0);
}

void randPermutationRep(PermutationRep *perm) {
	int i;
	assert(checkStructPermutationRep(perm));
	for (i = 0; i < perm->dispsize; i++)
		perm->dispvec[i] = rand() % perm->dispnumelem;
}

