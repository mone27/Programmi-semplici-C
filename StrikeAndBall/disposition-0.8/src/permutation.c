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

/* functions for permutations */

#include "permutation.h"
#include "dispcommon.h"
#include <assert.h>
#include <stdlib.h>

DispFunctions globalfuncPermutation = {
	firstPermutation, lastPermutation,
	nextPermutation, previousPermutation,
	checkPermutation, copyPermutation,
	randPermutation, deletePermutation
};

#define checkStructPermutation(d) \
		(d != NULL && d->dispnumelem > 0 \
		 	&& d->dispsize <= d->dispnumelem \
			&& ((d->dispvec != NULL && d->dispsize > 0) \
				|| (d->dispvec == NULL && d->dispsize == 0)))

Permutation *newPermutation(int numelem, int size, DispNewError *err) {
	DispNewError e;
	Permutation *perm = NULL;
	if (numelem < 1)
		e = DISP_NEW_NUMELEM_LT_ONE;
	else if (size < 0)
		e = DISP_NEW_SIZE_LT_ZERO;
	else if (size > numelem)
		e = DISP_NEW_SIZE_GT_NUMELEM;
	else {
		perm = (Permutation *) allocDisposition(size, 0);
		if (perm == NULL)
			e = DISP_NEW_MEMORY_ALLOCATION;
		else {
			e = DISP_NEW_OK;
			perm->dispnumelem = numelem;
			perm->dispfunc    = &globalfuncPermutation;
		}
	}
	if (err != NULL) *err = e;
	return perm;
}

void deletePermutation(Permutation *perm) {
	assert(checkStructPermutation(perm));
	freeDisposition(perm);
}

/* first permutation Pm,n is (0,1,2,...,n-1) */
void firstPermutation(Permutation *perm) {
	int i;
	assert(checkStructPermutation(perm));
	for (i = 0; i < perm->dispsize; i++)
		perm->dispvec[i] = i;
}

/* last permutation Pm,n is (m-1,m-2,...,m-n) */
void lastPermutation(Permutation *perm) {
	int i, j;
	assert(checkStructPermutation(perm));
	for (i = 0, j = perm->dispnumelem - 1; i < perm->dispsize;
						perm->dispvec[i++] = j--);
}

DispCheckError checkPermutation(Permutation *perm, int *errpos) {
	int i, j, val;
	assert(checkStructPermutation(perm));
	for (i = 0; i < perm->dispsize; i++) {
		val = perm->dispvec[i];
		if (val >= 0 && val < perm->dispnumelem) {
			/* check if the value is repeated before: */
			for (j = 0; j < i; j++)
				if (perm->dispvec[j] == val) {
					if (errpos != NULL) *errpos = i;
					return DISP_CHECK_ELEM_REPEATED;
				}
		}
		else {
			if (errpos != NULL) *errpos = i;
			return DISP_CHECK_ELEM_OUT_OF_RANGE;
		}
	}
	return DISP_CHECK_OK;
}

int nextPermutation(Permutation *perm) {
	int i, j, k, val;
	assert(checkStructPermutation(perm));
	assert(checkPermutation(perm, NULL) == DISP_CHECK_OK);
	/* finds the last element which value can be incremented
	 * without repeat the values of previous elements, if exists: */
	for (i = perm->dispsize - 1; i >= 0; i--) {
		/* increment the value and search if is repeated previously: */
		for (val = perm->dispvec[i] + 1;
					val < perm->dispnumelem; val++) {
			for (j = 0; j < i && perm->dispvec[j] != val; j++);
			if (j >= i) break; /* value not found */
		}
		if (val < perm->dispnumelem) break;
	}
	/* if the element was not found, last permutation was reached: */
	if (i < 0) return 0;
	perm->dispvec[i] = val;
	/* fills the rest of the vector with the first free values: */
	for (k = ++i, val = 0; k < perm->dispsize; k++) {
		for (;;val++) {
			for (j = 0; j < i && perm->dispvec[j] != val; j++);
			if (j >= i) break; /* value not found */
		}
		perm->dispvec[k] = val++;
	}
	return 1;
}

int previousPermutation(Permutation *perm) {
	int i, j, k, val;
	assert(checkStructPermutation(perm));
	assert(checkPermutation(perm, NULL) == DISP_CHECK_OK);
	/* finds the last element which value can be reduced
	 * without repeat the values of previous elements, if exists: */
	for (i = perm->dispsize - 1; i >= 0; i--) {
		/* decrement the value and search if is repeated previously: */
		for (val = perm->dispvec[i] - 1; val >= 0; val--) {
			for (j = 0; j < i && perm->dispvec[j] != val; j++);
			if (j >= i) break; /* value not found */
		}
		if (val >= 0) break;
	}
	/* if the element was not found, first permutation was reached: */
	if (i < 0) return 0;
	perm->dispvec[i] = val;
	/* fills the rest of the vector with the last free values: */
	for (k = ++i, val = perm->dispnumelem - 1; k < perm->dispsize; k++) {
		for (;;val--) {
			for (j = 0; j < i && perm->dispvec[j] != val; j++);
			if (j >= i) break; /* value not found */
		}
		perm->dispvec[k] = val--;
	}
	return 1;
}

Permutation *copyPermutation(Permutation *perm) {
	assert(checkStructPermutation(perm));
	return (Permutation *) copyDisposition(perm, 0);
}

/* returns the Nth element which is not already in the vector: */
int findNthElemPermutation(Permutation *perm, int nthelem, int currsize) {
	int e, k, i;
	assert(checkStructPermutation(perm));
	assert(currsize >= 0 && currsize < perm->dispsize
		&& nthelem > 0 && nthelem <= perm->dispnumelem - currsize);
	for (i = 0, e = -1; i < nthelem; i++) {
		/* finds the next element which is not already in the vector: */
		e++;
		do {
			for (k = 0; k < currsize && perm->dispvec[k] != e; k++);
			if (k < currsize) e++;
		} while (k < currsize);
	}
	return e;
}

void randPermutation(Permutation *perm) {
	int i;
	assert(checkStructPermutation(perm));
	for (i = 0; i < perm->dispsize; i++)
		perm->dispvec[i] = findNthElemPermutation(perm,
					RAND_1N(perm->dispnumelem - i), i);
}

