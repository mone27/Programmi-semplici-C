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

/* functions for combinations with restricted repetition */

#include "combinationrrep.h"
#include "dispcommon.h"
#include <assert.h>
#include <stdlib.h>

DispFunctions globalfuncCombinationRRep = {
	firstCombinationRRep, lastCombinationRRep,
	nextCombinationRRep, previousCombinationRRep,
	checkCombinationRRep, copyCombinationRRep,
	randCombinationRRep, deleteCombinationRRep
};

#define disprep(d) ((int *) (d)->dispdata)

#define checkStructCombinationRRep(d) \
		(d != NULL && d->dispnumelem > 0 \
			&& ((d->dispvec != NULL && d->dispsize > 0) \
				|| (d->dispvec == NULL && d->dispsize == 0)))

CombinationRRep *newCombinationRRep(int numelem, int size, int *repvec,
					DispNewError *err) {
	int i, maxsize;
	DispNewError e;
	CombinationRRep *comb = NULL;
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
			comb = (CombinationRRep *) allocDisposition(size,
							sizeof(int) * numelem);
			if (comb == NULL)
				e = DISP_NEW_MEMORY_ALLOCATION;
			else {
				e = DISP_NEW_OK;
				comb->dispnumelem = numelem;
				comb->dispfunc    = &globalfuncCombinationRRep;
				for (i = 0; i < numelem; i++)
					disprep(comb)[i] = repvec[i];
			}
		}
	}
	if (err != NULL) *err = e;
	return comb;
}

void deleteCombinationRRep(CombinationRRep *comb) {
	assert(checkStructCombinationRRep(comb));
	freeDisposition(comb);
}

/* first combination with constrained repetition of
 * m elements and size n, CCRn,r1,r2,..,rm-1,rm is, for example:
 * |<---r1-->|<---r2-->|<---r3-->|
 * (0,0,...,0,1,1,...,1,2,2)
 * |<----------n---------->| */
void firstCombinationRRep(CombinationRRep *comb) {
	int i, j, r;
	assert(checkStructCombinationRRep(comb));
	for (i = j = 0; i < comb->dispnumelem; i++) {
		for (r = disprep(comb)[i]; r > 0; r--) {
			comb->dispvec[j++] = i;
			if (j >= comb->dispsize) break;
		}
		if (j >= comb->dispsize) break;
	}
}

/* last combination with constrained repetition of
 * m elements and size n, CCRn,r1,r2,..,rm-1,rm is, for example:
 * |<---rm-2-->|<---rm-1-->|<----rm--->|
 *     (m-3,m-3,m-2,...,m-2,m-1,...,m-1)
 *     |<--------------n-------------->| */
void lastCombinationRRep(CombinationRRep *comb) {
	int i, k, r;
	assert(checkStructCombinationRRep(comb));
	for (i = comb->dispsize - 1, k = comb->dispnumelem - 1; k >= 0; k--) {
		for (r = disprep(comb)[k]; r > 0; r--) {
			comb->dispvec[i--] = k;
			if (i < 0) break;
		}
		if (i < 0) break;
	}
	assert(k >= 0);
}

DispCheckError checkCombinationRRep(CombinationRRep *comb, int *errpos) {
	int i, j, val, r;
	assert(checkStructCombinationRRep(comb));
	for (i = 0; i < comb->dispsize; i++) {
		val = comb->dispvec[i];
		if (val >= 0 && val < comb->dispnumelem) {
			/* check if the value is repeated
			 * too many times before: */
			for (j = 0, r = 1; j < i; j++)
				if (comb->dispvec[j] == val
						&& ++r > disprep(comb)[val]) {
					if (errpos != NULL) *errpos = i;
					return DISP_CHECK_ELEM_REPEATED;
				}
		}
		else {
			if (errpos != NULL) *errpos = i;
			return DISP_CHECK_ELEM_OUT_OF_RANGE;
		}
	}
	for (i = 1; i < comb->dispsize; i++)
		if (comb->dispvec[i] < comb->dispvec[i - 1]) {
			if (errpos != NULL) *errpos = i;
			return DISP_CHECK_OK_ELEM_UNSORTED;
		}
	return DISP_CHECK_OK;
}

/* search the index of the last element which value is not the
 * same that it will have in the last combination (INTERNAL): */
int nextElemCombinationRRep(CombinationRRep *comb) {
	int i, k, r;
	for (i = comb->dispsize - 1, k = comb->dispnumelem - 1; k >= 0; k--) {
		for (r = disprep(comb)[k]; r > 0; r--) {
			if (comb->dispvec[i] != k)
				return i;
			i--;
			if (i < 0) break;
		}
		if (i < 0) break;
	}
	assert(k >= 0);
	return i;
}

/* fills the element and the rest of the vector
 * with its following values (INTERNAL): */
void nextFillCombinationRRep(CombinationRRep *comb, int i) {
	int val, max, r;
	val = ++(comb->dispvec[i]);
	max = disprep(comb)[val];
	assert(val < comb->dispnumelem);
	for (++i, r = 1; i < comb->dispsize; i++, r++) {
		if (r >= max) {
			assert(r == max);
			max = disprep(comb)[++val];
			assert(val < comb->dispnumelem);
			r = 0;
		}
		comb->dispvec[i] = val;
	}
}

int nextCombinationRRep(CombinationRRep *comb) {
	int i;
	assert(checkStructCombinationRRep(comb));
	assert(checkCombinationRRep(comb, NULL) == DISP_CHECK_OK);
	i = nextElemCombinationRRep(comb);
	/* if the element was not found, last combination was reached: */
	if (i < 0) return 0;
	nextFillCombinationRRep(comb, i);
	return 1;
}

/* search the index of the last element which value is not the
 * same that it will have in the last combination (INTERNAL): */
int prevElemCombinationRRep(CombinationRRep *comb) {
	/* TODO */
	int i, k, r;
	for (i = comb->dispsize - 1, k = comb->dispnumelem - 1; k >= 0; k--) {
		for (r = disprep(comb)[k]; r > 0; r--) {
			if (comb->dispvec[i] != k)
				return i;
			i--;
			if (i < 0) break;
		}
		if (i < 0) break;
	}
	assert(k >= 0);
	return i;
}

/* fills the element and the rest of the vector
 * with its following values (INTERNAL): */
void prevFillCombinationRRep(CombinationRRep *comb, int i) {
	/* TODO */
	int val, max, r;
	val = ++(comb->dispvec[i]);
	max = disprep(comb)[val];
	assert(val < comb->dispnumelem);
	for (++i, r = 1; i < comb->dispsize; i++, r++) {
		if (r >= max) {
			assert(r == max);
			max = disprep(comb)[++val];
			assert(val < comb->dispnumelem);
			r = 0;
		}
		comb->dispvec[i] = val;
	}
}

#include <stdio.h>
int previousCombinationRRep(CombinationRRep *comb) {
	/*
	int i;
	*/
	assert(checkStructCombinationRRep(comb));
	assert(checkCombinationRRep(comb, NULL) == DISP_CHECK_OK);
	/* TODO */
	fprintf(stderr, "error: previousCombinationRRep: uninplemented\n");
	return 0;
	/*
	i = prevElemCombinationRRep(comb);
	*/
	/* if the element was not found, last combination was reached: */
	/*
	if (i < 0) return 0;
	prevFillCombinationRRep(comb, i);
	return 1;
	*/
}

CombinationRRep *copyCombinationRRep(CombinationRRep *comb) {
	CombinationRRep *copy;
	assert(checkStructCombinationRRep(comb));
	copy = copyDisposition(comb, sizeof(int) * comb->dispnumelem);
	if (copy != NULL && disprep(comb) != NULL)
		memcpy(disprep(copy), disprep(comb),
					sizeof(int) * comb->dispnumelem);
	return copy;
}

/* TODO */
void randCombinationRRep(CombinationRRep *comb) {
	assert(checkStructCombinationRRep(comb));
	fprintf(stderr, "error: randCombinationRRep: uninplemented\n");
	firstCombinationRRep(comb);
}

