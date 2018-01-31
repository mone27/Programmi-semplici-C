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

/* functions for combinations */

#include "combination.h"
#include "dispcommon.h"
#include <assert.h>
#include <stdlib.h>

DispFunctions globalfuncCombination = {
	firstCombination, lastCombination,
	nextCombination, previousCombination,
	checkCombination, copyCombination,
	randCombination, deleteCombination
};

#define checkStructCombination(d) \
		(d != NULL && d->dispnumelem > 0 \
		 	&& d->dispsize <= d->dispnumelem \
			&& ((d->dispvec != NULL && d->dispsize > 0) \
				|| (d->dispvec == NULL && d->dispsize == 0)))

Combination *newCombination(int numelem, int size, DispNewError *err) {
	DispNewError e;
	Combination *comb = NULL;
	if (numelem < 1)
		e = DISP_NEW_NUMELEM_LT_ONE;
	else if (size < 0)
		e = DISP_NEW_SIZE_LT_ZERO;
	else if (size > numelem)
		e = DISP_NEW_SIZE_GT_NUMELEM;
	else {
		comb = (Combination *) allocDisposition(size, 0);
		if (comb == NULL)
			e = DISP_NEW_MEMORY_ALLOCATION;
		else {
			e = DISP_NEW_OK;
			comb->dispnumelem = numelem;
			comb->dispfunc    = &globalfuncCombination;
		}
	}
	if (err != NULL) *err = e;
	return comb;
}

void deleteCombination(Combination *comb) {
	assert(checkStructCombination(comb));
	freeDisposition(comb);
}

/* first combination Cm,n is (0,1,2,...,n-1) */
void firstCombination(Combination *comb) {
	int i;
	assert(checkStructCombination(comb));
	for (i = 0; i < comb->dispsize; i++)
		comb->dispvec[i] = i;
}

/* last combination Pm,n is (m-n,...,m-2,m-1) */
void lastCombination(Combination *comb) {
	int i, j;
	assert(checkStructCombination(comb));
	for (i = 0, j = comb->dispnumelem - comb->dispsize;
				i < comb->dispsize; comb->dispvec[i++] = j++);
}

DispCheckError checkCombination(Combination *comb, int *errpos) {
	int i, j, val;
	assert(checkStructCombination(comb));
	for (i = 0; i < comb->dispsize; i++) {
		val = comb->dispvec[i];
		if (val >= 0 && val < comb->dispnumelem) {
			/* check if the value is repeated before: */
			for (j = 0; j < i; j++)
				if (comb->dispvec[j] == val) {
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

int nextCombination(Combination *comb) {
	int i, val;
	assert(checkStructCombination(comb));
	assert(checkCombination(comb, NULL) == DISP_CHECK_OK);
	/* finds the first element wich has the same value that
	 * it will have in the last combination: */
	val = comb->dispnumelem - comb->dispsize;
	for (i = 0; i < comb->dispsize && comb->dispvec[i] != val + i; i++);
	if (i == 0) return 0;
	/* increments the value of the previous element and
	 * fills the rest of the vector with its following values: */
	comb->dispvec[i - 1]++;
	for (val = comb->dispvec[i - 1] + 1; i < comb->dispsize; val++, i++)
		comb->dispvec[i] = val;
	return 1;
}

int previousCombination(Combination *comb) {
	int i, val;
	assert(checkStructCombination(comb));
	assert(checkCombination(comb, NULL) == DISP_CHECK_OK);
	/* finds from the last element to the first, an element which value
	 * is not equal to the value of its following element minus one:
	 * (for example, the element with value 3 in the vector {1,3,5,6,7}) */
	/* Q: could be made in reverse order too? */
	if (comb->dispvec == NULL) return 0;
	for (i = comb->dispsize - 2; i >= 0
			&& comb->dispvec[i] == comb->dispvec[i + 1] - 1; i--);
	if (i < 0 && comb->dispvec[0] == 0) return 0;
	/* decrements the next element and fills the following elements with
	 * the values which those elements will have in the last combination: */
	comb->dispvec[++i]--;
	for (val = ++i + comb->dispnumelem - comb->dispsize;
						i < comb->dispsize; i++, val++)
		comb->dispvec[i] = val;
	return 1;
}

Combination *copyCombination(Combination *comb) {
	assert(checkStructCombination(comb));
	return (Combination *) copyDisposition(comb, 0);
}

/* returns the Nth element which is not already in the sorted vector
 * and saves the position in the vector in which that element must be: */
int findNthElemCombination(Combination *comb, int nthelem, int currsize,
							int *destpos) {
	int e, k, i;
	assert(checkStructCombination(comb));
	assert(currsize >= 0 && currsize < comb->dispsize
		&& nthelem > 0 && nthelem <= comb->dispnumelem - currsize);
	for (i = 0, e = -1, k = 0; i < nthelem; i++)
		for (e++; k < currsize && e == comb->dispvec[k]; e++, k++);
	*destpos = k;
	return e;
}

void randCombination(Combination *comb) {
	int i, j, e, pos;
	assert(checkStructCombination(comb));
	for (i = 0; i < comb->dispsize; i++) {
		e = findNthElemCombination(comb,
				RAND_1N(comb->dispnumelem - i), i, &pos);
		/* inserts the element e in the position pos: */
		for (j = i; j > pos; j--)
			comb->dispvec[j] = comb->dispvec[j - 1];
		comb->dispvec[pos] = e;
	}
}

