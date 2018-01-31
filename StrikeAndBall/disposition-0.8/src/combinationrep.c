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

/* functions for combinations with repetition */

#include "combinationrep.h"
#include "dispcommon.h"
#include <assert.h>
#include <stdlib.h>

DispFunctions globalfuncCombinationRep = {
	firstCombinationRep, lastCombinationRep,
	nextCombinationRep, previousCombinationRep,
	checkCombinationRep, copyCombinationRep,
	randCombinationRep, deleteCombinationRep
};

#define checkStructCombinationRep(d) \
		(d != NULL && d->dispnumelem > 0 \
			&& ((d->dispvec != NULL && d->dispsize > 0) \
				|| (d->dispvec == NULL && d->dispsize == 0)))

CombinationRep *newCombinationRep(int numelem, int size, DispNewError *err) {
	DispNewError e;
	CombinationRep *comb = NULL;
	if (numelem < 1)
		e = DISP_NEW_NUMELEM_LT_ONE;
	else if (size < 0)
		e = DISP_NEW_SIZE_LT_ZERO;
	else {
		comb = (CombinationRep *) allocDisposition(size, 0);
		if (comb == NULL)
			e = DISP_NEW_MEMORY_ALLOCATION;
		else {
			e = DISP_NEW_OK;
			comb->dispnumelem = numelem;
			comb->dispfunc    = &globalfuncCombinationRep;
		}
	}
	if (err != NULL) *err = e;
	return comb;
}

void deleteCombinationRep(CombinationRep *comb) {
	assert(checkStructCombinationRep(comb));
	freeDisposition(comb);
}

/* first combination with repetition PRm,n is (0,0,0,...,0) */
void firstCombinationRep(CombinationRep *comb) {
	int i;
	assert(checkStructCombinationRep(comb));
	for (i = 0; i < comb->dispsize; i++)
		comb->dispvec[i] = 0;
}

/* last combination with repetition PRm,n is (m-1,m-1,...,m-1) */
void lastCombinationRep(CombinationRep *comb) {
	int i;
	assert(checkStructCombinationRep(comb));
	for (i = 0; i < comb->dispsize; i++)
		comb->dispvec[i] = comb->dispnumelem - 1;
}

DispCheckError checkCombinationRep(CombinationRep *comb, int *errpos) {
	int i, val;
	assert(checkStructCombinationRep(comb));
	for (i = 0; i < comb->dispsize; i++) {
		val = comb->dispvec[i];
		if (val < 0 || val >= comb->dispnumelem) {
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

int nextCombinationRep(CombinationRep *comb) {
	int i, val;
	assert(checkStructCombinationRep(comb));
	assert(checkCombinationRep(comb, NULL) == DISP_CHECK_OK);
	/* finds the last element with a value not equal to the biggest: */
	for (i = comb->dispsize - 1; i >= 0
			&& comb->dispvec[i] == comb->dispnumelem - 1; i--);
	if (i < 0) return 0;
	/* increments that element and fills the rest with the same value: */
	val = ++(comb->dispvec[i]);
	for (++i; i < comb->dispsize; i++)
		comb->dispvec[i] = val;
	return 1;
}

int previousCombinationRep(CombinationRep *comb) {
	int i, val;
	assert(checkStructCombinationRep(comb));
	assert(checkCombinationRep(comb, NULL) == DISP_CHECK_OK);
	/* finds from the last element to the first, an element
	 * which value is not equal to the value of the last element:
	 * (for example, the element with value 3 in the vector {1,3,5,5,5}) */
	if (comb->dispvec == NULL) return 0;
	val = comb->dispvec[comb->dispsize - 1];
	for (i = comb->dispsize - 2; i >= 0 && comb->dispvec[i] == val; i--);
	if (i < 0 && comb->dispvec[0] == 0) return 0;
	/* decrements the next element and fills
	 * the following elements with the maximum value: */
	comb->dispvec[++i]--;
	for (i++, val = comb->dispnumelem - 1; i < comb->dispsize; i++)
		comb->dispvec[i] = val;
	return 1;
}

CombinationRep *copyCombinationRep(CombinationRep *comb) {
	assert(checkStructCombinationRep(comb));
	return (CombinationRep *) copyDisposition(comb, 0);
}

/* returns the Nth element which is not already in the sorted vector
 * and saves the position in the vector in which that element must be:
 * (this is mostly the same function used in Combinations) */
int findNthElemCombinationRep(CombinationRep *comb, int nthelem, int currsize,
							int *destpos) {
	int e, k, i;
	assert(checkStructCombinationRep(comb));
	assert(currsize >= 0 && currsize < comb->dispsize && nthelem > 0
	&& nthelem <= comb->dispnumelem + comb->dispsize - currsize - 1);
	for (i = 0, e = -1, k = 0; i < nthelem; i++)
		for (e++; k < currsize && e == comb->dispvec[k]; e++, k++);
	*destpos = k;
	return e;
}

/* to get a random combination with repetition firstly
 * it gets a random combination of numelem+size-1 elements:
 * CR4,3  C4+3-1,3
 *  aaa    abc
 *  aab    abd
 *  aac    abe
 *  aad    abf
 *  abb    acd
 *  abc    ace
 *  abd    acf
 *  acc    ade
 *  acd    adf
 *  add    aef
 *  bbb    bcd
 *  bbc    bce
 *  ...    ...
 *  To convert that combinations into combinations with repetition
 *  you can substract 1 from the element in the position 1 of the vector,
 *  2 from element in the position 2, 3 from the element in 3, etc.
 *  For example, for the combination "acf", "c"-1 is "b" and "f"-2 is "d",
 *  so the corresponding combination with repetition is: "abd".
 */
void randCombinationRep(CombinationRep *comb) {
	int i, j, e, pos;
	assert(checkStructCombinationRep(comb));
	for (i = 0; i < comb->dispsize; i++) {
		e = findNthElemCombinationRep(comb,
			RAND_1N(comb->dispnumelem + comb->dispsize - i - 1),
					i, &pos);
		/* inserts the element e in the position pos: */
		for (j = i; j > pos; j--)
			comb->dispvec[j] = comb->dispvec[j - 1];
		comb->dispvec[pos] = e;
	}
	for (i = 1; i < comb->dispsize; i++)
		comb->dispvec[i] -= i;
}

