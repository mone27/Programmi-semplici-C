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

/* common declarations for testing dispositions */

#ifndef _DISPOSITIONTESTUTIL_H_
#define _DISPOSITIONTESTUTIL_H_

#include "idisposition.h"
#include "commontestutil.h"

#define disp_print(d)     print_vec(disp_vec(d), disp_size(d))
#define disp_fprint(d, f) fprint_vec(f, disp_vec(d), disp_size(d))

#define NEW_OK             DISP_NEW_OK
#define NUMELEM_LT_ONE     DISP_NEW_NUMELEM_LT_ONE
#define SIZE_LT_ZERO       DISP_NEW_SIZE_LT_ZERO
#define SIZE_GT_NUMELEM    DISP_NEW_SIZE_GT_NUMELEM
#define MEMORY_ALLOCATION  DISP_NEW_MEMORY_ALLOCATION
#define CHECK_OK           DISP_CHECK_OK
#define OK_ELEM_UNSORTED   DISP_CHECK_OK_ELEM_UNSORTED
#define ELEM_OUT_OF_RANGE  DISP_CHECK_ELEM_OUT_OF_RANGE
#define ELEM_REPEATED      DISP_CHECK_ELEM_REPEATED

typedef enum eDispStart {
	DISP_START_FIRST, DISP_START_LAST
} DispStart;

#define equal_disp(d, v)     (equal_vec(disp_vec(d), (v), disp_size(d)))
#define equal_disp_str(d, s) (equal_vec_str(disp_vec(d), disp_size(d), (s)))

int check_disp_err(Disposition *d, char *vecstr,
			DispCheckError err, int errpos);
int set_disp_ok(Disposition *d, char *vecstr);
int copy_disp_ok(Disposition *d);
int rand_disp_ok(Disposition *d, int printseed);

typedef enum eSequenceType {
	DISP_SEQ_ALL, DISP_SEQ_FIRST, DISP_SEQ_LAST, DISP_SEQ_MIDDLE
} SequenceType;

typedef struct stDispSequence {
	Disposition *d;
	SequenceType t;
	char **strarr;
	int num, arrsize;
} DispSequence;

#define ALL    DISP_SEQ_ALL
#define LAST   DISP_SEQ_LAST
#define FIRST  DISP_SEQ_FIRST
#define MIDDLE DISP_SEQ_MIDDLE

DispSequence disp_sequence(Disposition *d, SequenceType t,
					char **strarr, int arrsize);
int disp_sequence_add(DispSequence *seq, char *str);
int disp_sequence_next_ok(DispSequence *seq); /* only next implemented */
int disp_sequence_prev_ok(DispSequence *seq); /* only prev implemented */
#define disp_sequence_ok(seq) \
		(disp_sequence_next_ok(seq) && disp_sequence_prev_ok(seq))
#define ADD(seq,str)  disp_sequence_add((seq),(str))

/* example of use: */
/*
#define MAX 100
...
	char *a[MAX];
	DispSequence s;
	...
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 1 2");
	ADD(&s, "0 1 3");
	ADD(&s, "0 3 2");
	...
	assert(disp_sequence_ok(&s));
	...
*/

#endif

