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

/* functions for permutations with restricted repetition */

#include "permutationrrep.h"
#include "dispcommon.h"
#include <assert.h>
#include <stdlib.h>

DispFunctions globalfuncPermutationRRep = {
	firstPermutationRRep, lastPermutationRRep,
	nextPermutationRRep, previousPermutationRRep,
	checkPermutationRRep, copyPermutationRRep,
	randPermutationRRep, deletePermutationRRep
};

#define disprep(d) ((int *) (d)->dispdata)

#define checkStructPermutationRRep(d) \
		(d != NULL && d->dispnumelem > 0 \
			&& ((d->dispvec != NULL && d->dispsize > 0) \
				|| (d->dispvec == NULL && d->dispsize == 0)))

PermutationRRep *newPermutationRRep(int numelem, int size, int *repvec,
					DispNewError *err) {
	int i, maxsize;
	DispNewError e;
	PermutationRRep *perm = NULL;
	if (numelem < 1)
		e = DISP_NEW_NUMELEM_LT_ONE;
	else if (repvec == NULL)
		e = DISP_NEW_SIZE_LT_ZERO;
	else {
		for (i = 0, maxsize = 0; i < numelem; maxsize += repvec[i++])
			if (repvec[i] <= 0)
				break;
		if (i < numelem || maxsize <= 0)
			e = DISP_NEW_SIZE_LT_ZERO;
		else if (size > maxsize)
			e = DISP_NEW_SIZE_GT_NUMELEM;
		else {
			perm = (PermutationRRep *) allocDisposition(size,
							sizeof(int) * numelem);
			if (perm == NULL)
				e = DISP_NEW_MEMORY_ALLOCATION;
			else {
				e = DISP_NEW_OK;
				perm->dispnumelem = numelem;
				perm->dispfunc    = &globalfuncPermutationRRep;
				for (i = 0; i < numelem; i++)
					disprep(perm)[i] = repvec[i];
			}
		}
	}
	if (err != NULL) *err = e;
	return perm;
}

void deletePermutationRRep(PermutationRRep *perm) {
	assert(checkStructPermutationRRep(perm));
	freeDisposition(perm);
}

/* first permutation with restricted repetition of
 * m elements and size n, PCRn,r1,r2,..,rm-1,rm is, for example:
 * |<---r1-->|<---r2-->|<---r3-->|
 * (0,0,...,0,1,1,...,1,2,2)
 * |<----------n---------->| */
void firstPermutationRRep(PermutationRRep *perm) {
	int i, j, r;
	assert(checkStructPermutationRRep(perm));
	for (i = j = 0; i < perm->dispnumelem; i++) {
		for (r = disprep(perm)[i]; r > 0; r--) {
			perm->dispvec[j++] = i;
			if (j >= perm->dispsize) break;
		}
		if (j >= perm->dispsize) break;
	}
}

/* last permutation with restricted repetition of
 * m elements and size n, PCRn,r1,r2,..,rm-1,rm is, for example:
 * |<----rm--->|<---rm-1---|<---rm-2--->|
 * (m-1,...,m-1,m-2,...,m-2,m-3,m-3)
 * |<--------------n-------------->| */
void lastPermutationRRep(PermutationRRep *perm) {
	int i, j, k, r;
	assert(checkStructPermutationRRep(perm));
	for (i = j = 0, k = perm->dispnumelem - 1;
					i < perm->dispnumelem; i++, k--) {
		for (r = disprep(perm)[k]; r > 0; r--) {
			perm->dispvec[j++] = k;
			if (j >= perm->dispsize) break;
		}
		if (j >= perm->dispsize) break;
	}
}

DispCheckError checkPermutationRRep(PermutationRRep *perm, int *errpos) {
	int i, j, val, r;
	assert(checkStructPermutationRRep(perm));
	for (i = 0; i < perm->dispsize; i++) {
		val = perm->dispvec[i];
		if (val >= 0 && val < perm->dispnumelem) {
			/* check if the value is repeated
			 * too many times before: */
			for (j = 0, r = 1; j < i; j++)
				if (perm->dispvec[j] == val
						&& ++r > disprep(perm)[val]) {
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

/* search the index of the last element which value can be incremented
 * without repeat the values of previous elements too many times (INTERNAL): */
int nextElemPermutationRRep(PermutationRRep *perm, int *newval) {
	int i, j, val, n, max;
	for (i = perm->dispsize - 1; i >= 0; i--) {
		/* search a value for the element incrementing current one: */
		for (val = perm->dispvec[i] + 1;
					val < perm->dispnumelem; val++) {
			/* search if previously the value is already
			 * repeated the maximum of times: */
			for (j = 0, n = 1, max = disprep(perm)[val]; j < i; j++)
				if (perm->dispvec[j] == val)
					if (++n > max) break;
			if (j >= i) break;
			/* continue if this value is repeated too many times */
		}
		if (val < perm->dispnumelem) { /* element found */
			*newval = val;
			break;
		}
	}
	return i;
}

/* fills the element and the rest of the vector
 * with the first free values (INTERNAL): */
void nextFillPermutationRRep(PermutationRRep *perm, int i, int val) {
	int j, n, max;
	perm->dispvec[i++] = val;
	for (val = 0; i < perm->dispsize; i++) {
		for (; val < perm->dispnumelem; val++) {
			/* search if previously the value is already
			 * repeated the maximum of times: */
			for (j = 0, n = 1, max = disprep(perm)[val]; j < i; j++)
				if (perm->dispvec[j] == val)
					if (++n > max) break;
			if (j >= i) break;
			/* continue if this value is repeated too many times */
		}
		assert(val < perm->dispnumelem);
		perm->dispvec[i] = val;
	}
}

int nextPermutationRRep(PermutationRRep *perm) {
	int i, val;
	assert(checkStructPermutationRRep(perm));
	assert(checkPermutationRRep(perm, NULL) == DISP_CHECK_OK);
	i = nextElemPermutationRRep(perm, &val);
	/* if the element was not found, last permutation was reached: */
	if (i < 0) return 0;
	nextFillPermutationRRep(perm, i, val);
	return 1;
}

/* search the index of the last element which value can be incremented
 * without repeat the values of previous elements too many times (INTERNAL): */
int prevElemPermutationRRep(PermutationRRep *perm, int *newval) {
	/* TODO */
	int i, j, val, n, max;
	for (i = perm->dispsize - 1; i >= 0; i--) {
		/* search a value for the element incrementing current one: */
		for (val = perm->dispvec[i] + 1;
					val < perm->dispnumelem; val++) {
			/* search if previously the value is already
			 * repeated the maximum of times: */
			for (j = 0, n = 1, max = disprep(perm)[val]; j < i; j++)
				if (perm->dispvec[j] == val)
					if (++n > max) break;
			if (j >= i) break;
			/* continue if this value is repeated too many times */
		}
		if (val < perm->dispnumelem) { /* element found */
			*newval = val;
			break;
		}
	}
	return i;
}

/* fills the element and the rest of the vector
 * with the first free values (INTERNAL): */
void prevFillPermutationRRep(PermutationRRep *perm, int i, int val) {
	/* TODO */
	int j, n, max;
	perm->dispvec[i++] = val;
	for (val = 0; i < perm->dispsize; i++) {
		for (; val < perm->dispnumelem; val++) {
			/* search if previously the value is already
			 * repeated the maximum of times: */
			for (j = 0, n = 1, max = disprep(perm)[val]; j < i; j++)
				if (perm->dispvec[j] == val)
					if (++n > max) break;
			if (j >= i) break;
			/* continue if this value is repeated too many times */
		}
		assert(val < perm->dispnumelem);
		perm->dispvec[i] = val;
	}
}

#include <stdio.h>
int previousPermutationRRep(PermutationRRep *perm) {
	/*
	int i, val;
	*/
	assert(checkStructPermutationRRep(perm));
	assert(checkPermutationRRep(perm, NULL) == DISP_CHECK_OK);
	/* TODO */
	fprintf(stderr, "error: previousPermutationRRep: uninplemented\n");
	return 0;
	/*
	i = prevElemPermutationRRep(perm, &val);
	*/
	/* if the element was not found, first permutation was reached: */
	/*
	if (i < 0) return 0;
	prevFillPermutationRRep(perm, i, val);
	return 1;
	*/
}

PermutationRRep *copyPermutationRRep(PermutationRRep *perm) {
	PermutationRRep *copy;
	assert(checkStructPermutationRRep(perm));
	copy = copyDisposition(perm, sizeof(int) * perm->dispnumelem);
	if (copy != NULL && disprep(perm) != NULL)
		memcpy(disprep(copy), disprep(perm),
					sizeof(int) * perm->dispnumelem);
	return copy;
}

/* TODO */
void randPermutationRRep(PermutationRRep *perm) {
	assert(checkStructPermutationRRep(perm));
	fprintf(stderr, "error: randPermutationRRep: uninplemented\n");
	firstPermutationRRep(perm);
}

