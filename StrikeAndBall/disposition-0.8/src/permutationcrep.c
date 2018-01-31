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

/* functions for permutations with constant repetition */

#include "permutationcrep.h"
#include "dispcommon.h"
#include <assert.h>
#include <stdlib.h>

DispFunctions globalfuncPermutationCRep = {
	firstPermutationCRep, lastPermutationCRep,
	nextPermutationCRep, previousPermutationCRep,
	checkPermutationCRep, copyPermutationCRep,
	randPermutationCRep, deletePermutationCRep
};

#define disprep(d) ((int *) (d)->dispdata)

#define checkStructPermutationCRep(d) \
		(d != NULL && d->dispnumelem > 0 \
			&& ((d->dispsize > 0 && d->dispvec != NULL) \
				|| (d->dispsize == 0 && d->dispvec == NULL)))

PermutationCRep *newPermutationCRep(int numelem, int *repvec,
						DispNewError *err) {
	int i, size;
	DispNewError e;
	PermutationCRep *perm = NULL;
	if (numelem < 1)
		e = DISP_NEW_NUMELEM_LT_ONE;
	else {
		if (repvec == NULL)
			i = size = numelem;
		else
			for (i = 0, size = 0; i < numelem; size += repvec[i++])
				if (repvec[i] < 0) break;
		if (i < numelem || size < 0)
			e = DISP_NEW_SIZE_LT_ZERO;
		else {
			if (repvec == NULL)
				perm = (PermutationCRep *) allocDisposition(
								size, 0);
			else
				perm = (PermutationCRep *) allocDisposition(
						size, sizeof(int) * numelem);
			if (perm == NULL)
				e = DISP_NEW_MEMORY_ALLOCATION;
			else {
				e = DISP_NEW_OK;
				perm->dispnumelem = numelem;
				perm->dispfunc = &globalfuncPermutationCRep;
				if (repvec == NULL)
					perm->dispdata = NULL;
				else
					for (i = 0; i < numelem; i++)
						disprep(perm)[i] = repvec[i];
			}
		}
	}
	if (err != NULL) *err = e;
	return perm;
}

void deletePermutationCRep(PermutationCRep *perm) {
	assert(checkStructPermutationCRep(perm));
	freeDisposition(perm);
}

/* first permutation with constant repetition of
 * m elements, PCRr1,r2,...,rm-1,rm with size r1+r2+...+rm is:
 * |<----r1--->|<----r2--->|...|<---rm-1-->|<----rm--->|
 * (0,0,...,0,0,1,1,...,1,1,...,m-2,...,m-2,m-1,...,m-1)
 * |<-------------------r1+r2+...+rm------------------>| */
void firstPermutationCRep(PermutationCRep *perm) {
	int i, j, r;
	assert(checkStructPermutationCRep(perm));
	if (disprep(perm) != NULL)
		for (i = j = 0; i < perm->dispnumelem; i++)
			for (r = disprep(perm)[i]; r > 0; r--)
				perm->dispvec[j++] = i;
	else
		for (i = 0; i < perm->dispsize; i++)
			perm->dispvec[i] = i;
}

/* last permutation with constant repetition of
 * m elements, PCRr1,r2,...,rm-1,rm with size r1+r2+...+rm is:
 * |<----rm--->|<---rm-1-->|...|<----r2--->|<----r1--->|
 * (m-1,...,m-1,m-2,...,m-2,...,1,1,...,1,1,0,0,...,0,0)
 * |<-------------------r1+r2+...+rm------------------>| */
void lastPermutationCRep(PermutationCRep *perm) {
	int j, k, r;
	assert(checkStructPermutationCRep(perm));
	if (disprep(perm) != NULL)
		for (j = 0, k = perm->dispnumelem - 1; k > -1; k--)
			for (r = disprep(perm)[k]; r > 0; r--)
				perm->dispvec[j++] = k;
	else
		for (j = 0, k = perm->dispsize - 1; k > -1; k--)
			perm->dispvec[j++] = k;
}

DispCheckError checkPermutationCRep(PermutationCRep *perm, int *errpos) {
	int i, j, val, r;
	assert(checkStructPermutationCRep(perm));
	/* check if every value is in the range: */
	for (i = 0; i < perm->dispsize; i++) {
		val = perm->dispvec[i];
		if (val < 0 || val >= perm->dispnumelem) {
			if (errpos != NULL) *errpos = i;
			return DISP_CHECK_ELEM_OUT_OF_RANGE;
		}
	}
	/* check if every value is repeated the correct number of times: */
	if (disprep(perm) != NULL)
		for (i = 0; i < perm->dispnumelem; i++) {
			for (j = 0, r = 0; j < perm->dispsize; j++)
				if (perm->dispvec[j] == i
						&& ++r > disprep(perm)[i]) {
					if (errpos != NULL) *errpos = j;
					return DISP_CHECK_ELEM_REPEATED;
				}
			if (r < disprep(perm)[i]) {
				if (errpos != NULL) *errpos = -1;
				return DISP_CHECK_ELEM_REPEATED;
			}
		}
	else
		for (i = 0; i < perm->dispsize; i++) {
			for (j = 0, r = 0; j < perm->dispsize; j++)
				if (perm->dispvec[j] == i && ++r > 1) {
					if (errpos != NULL) *errpos = i;
					return DISP_CHECK_ELEM_REPEATED;
				}
			if (r == 0) {
				if (errpos != NULL) *errpos = -1;
				return DISP_CHECK_ELEM_REPEATED;
			}
		}
	return DISP_CHECK_OK;
}

/* it does not need the repetition vector, only the disposition vector: */
int nextPermutationCRep(PermutationCRep *perm) {
	int i, tmp, j, opp;
	assert(checkStructPermutationCRep(perm));
	assert(checkPermutationCRep(perm, NULL) == DISP_CHECK_OK);
	/* search from the last an element greater than the previous one: */
	for (i = perm->dispsize - 1; i > 0
			&& perm->dispvec[i] <= perm->dispvec[i - 1]; i--);
	if (i == 0) return 0;
	/* the previous element is the key element: */
	tmp = perm->dispvec[--i];
	/* search from the last the first element greater than the key: */
	for (j = perm->dispsize - 1; j > i && perm->dispvec[j] <= tmp; j--);
	/* the element is swapped with the key: */
	perm->dispvec[i] = perm->dispvec[j];
	perm->dispvec[j] = tmp;
	/* reverse the order of the elements following the old index of key: */
	for (j = i + 1, opp = perm->dispsize - j + i; j < opp; j++, opp--) {
		tmp = perm->dispvec[j];
		perm->dispvec[j] = perm->dispvec[opp];
		perm->dispvec[opp] = tmp;
	}
	return 1;
}

/* it does not need the repetition vector, only the disposition vector: */
int previousPermutationCRep(PermutationCRep *perm) {
	int i, tmp, j, opp;
	assert(checkStructPermutationCRep(perm));
	assert(checkPermutationCRep(perm, NULL) == DISP_CHECK_OK);
	/* search from the last an element less than the previous one: */
	for (i = perm->dispsize - 1; i > 0
			&& perm->dispvec[i] >= perm->dispvec[i - 1]; i--);
	if (i == 0) return 0;
	/* the previous element is the key element: */
	tmp = perm->dispvec[--i];
	/* search from the last the first element less than the key: */
	for (j = perm->dispsize - 1; j > i && perm->dispvec[j] >= tmp; j--);
	/* the element is swapped with the key: */
	perm->dispvec[i] = perm->dispvec[j];
	perm->dispvec[j] = tmp;
	/* reverse the order of the elements following the old index of key: */
	for (j = i + 1, opp = perm->dispsize - j + i; j < opp; j++, opp--) {
		tmp = perm->dispvec[j];
		perm->dispvec[j] = perm->dispvec[opp];
		perm->dispvec[opp] = tmp;
	}
	return 1;
}

PermutationCRep *copyPermutationCRep(PermutationCRep *perm) {
	PermutationCRep *copy;
	size_t datasize;
	assert(checkStructPermutationCRep(perm));
	if (disprep(perm) != NULL)
		datasize = sizeof(int) * perm->dispnumelem;
	else
		datasize = 0;
	copy = copyDisposition(perm, datasize);
	if (copy != NULL && disprep(perm) != NULL)
		memcpy(disprep(copy), disprep(perm),
					sizeof(int) * perm->dispnumelem);
	return copy;
}

/* gets each element of the vector and inserts it in
 * a random position at the beginning of the vector:
 * "_a_|bccdee"  gets the next ("b") and inserts it in a random position
 * "_b_a_|ccdee" gets the next ("c") and inserts it in a random position
 * ... */
void randPermutationCRep(PermutationCRep *perm) {
	int i, j, k, l, pos;
	assert(checkStructPermutationCRep(perm));
	if (perm->dispsize == 0) return;
	if (disprep(perm) != NULL)
		for (i = 0, k = 0; i < perm->dispnumelem; i++)
			for (j = 0; j < disprep(perm)[i]; j++, k++) {
				pos = RAND_0N(k);
				for (l = k; l > pos; l--)
					perm->dispvec[l] = perm->dispvec[l - 1];
				perm->dispvec[pos] = i;
			}
	else
		for (i = 0; i < perm->dispsize; i++) {
			pos = RAND_0N(i);
			for (l = i; l > pos; l--)
				perm->dispvec[l] = perm->dispvec[l - 1];
			perm->dispvec[pos] = i;
		}
}

