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

/* common functions for testing dispositions */

#include "disptestutil.h"

int check_disp_err(Disposition *d, char *vecstr,
			DispCheckError err, int errpos) {
	DispCheckError e;
	int pos;
	if (str_to_vec(disp_vec(d), disp_size(d), vecstr) == 0) return 0;
	e = disp_check(d, &pos);
	if (e != err) return 0;
	if (e != DISP_CHECK_OK) {
		if (pos != errpos) return 0;
	}
	return 1;
}

int set_disp_ok(Disposition *d, char *vecstr) {
	if (str_to_vec(disp_vec(d), disp_size(d), vecstr) == 0) return 0;
	if (disp_check(d, NULL) != DISP_CHECK_OK) return 0;
	return 1;
}

int copy_disp_ok(Disposition *d) {
	Disposition *copy;
	copy = disp_copy(d);
	if (copy == NULL) return 0;
	if (disp_numelem(copy) != disp_numelem(d)) return 0;
	if (disp_size(copy) != disp_size(d)) return 0;
	if (!equal_vec(disp_vec(copy), disp_vec(d), disp_size(d)))
		return 0;
	disp_delete(copy);
	return 1;
}

#include <stdlib.h>
#define NUMRANDTESTS 10
int rand_disp_ok(Disposition *d, int printseed) {
	int i, j;
	if (d == NULL) return 0;
	for (i = 0; i < NUMRANDTESTS; i++) {
		for (j = 0; j < disp_size(d); j++)
			disp_vec(d)[j] = disp_numelem(d);
		set_seed(rand(), printseed);
		disp_rand(d);
		/*
		disp_print(d);
		*/
		if (disp_check(d, NULL) != DISP_CHECK_OK) return 0;
	}
	return 1;
}

DispSequence disp_sequence(Disposition *d, SequenceType t,
					char **strarr, int arrsize) {
	DispSequence seq;
	if (strarr == NULL || arrsize < 0)
		arrsize = 0;
	seq.d = d;
	seq.t = t;
	seq.strarr = strarr;
	seq.num = 0;
	seq.arrsize = arrsize;
	return seq;
}

int disp_sequence_add(DispSequence *seq, char *str) {
	if (seq->num == seq->arrsize)
		return 0;
	seq->strarr[seq->num++] = str;
	return 1;
}

#include <stdio.h>
#define SEQ_ERR(op)     fprintf(stderr, "%s\n", (op))
#define SEQ_ERR_STR(op, n, str) \
			fprintf(stderr, "%s: [%d] \"%s\"\n", (op), (n), (str))
#define SEQ_ERR_STR_DISP(op, n, str) \
			fprintf(stderr, "%s: [%d] \"%s\": ", (op), (n), (str))

int disp_sequence_elements_ok(DispSequence *seq) {
	if (seq->num == 0) {
		SEQ_ERR("no elements in the array of strings");
		return 0;
	}
	return 1;
}

int disp_sequence_next_ok(DispSequence *seq) {
	int i;
	if (!disp_sequence_elements_ok(seq)) return 0;
	if (!set_disp_ok(seq->d, seq->strarr[0])) {
		SEQ_ERR_STR("first string not valid", 0, seq->strarr[0]);
		return 0;
	}
	for (i = 1; i < seq->num; i++) {
		if (!disp_next(seq->d)) {
			SEQ_ERR_STR("unable to get next", i - 1,
							seq->strarr[i - 1]);
			return 0;
		}
		if (!equal_disp_str(seq->d, seq->strarr[i])) {
			SEQ_ERR_STR_DISP("next is not equal", i,
							seq->strarr[i]);
			disp_fprint(seq->d, stderr);
			return 0;
		}
	}
	if (seq->t == DISP_SEQ_ALL || seq->t == DISP_SEQ_LAST) {
		disp_last(seq->d);
		if (!equal_disp_str(seq->d, seq->strarr[seq->num - 1])) {
			SEQ_ERR_STR_DISP("last is not equal", seq->num - 1,
						seq->strarr[seq->num - 1]);
			disp_fprint(seq->d, stderr);
			return 0;
		}
		if (disp_next(seq->d)) {
			SEQ_ERR_STR_DISP("last has next", seq->num - 1,
						seq->strarr[seq->num - 1]);
			disp_fprint(seq->d, stderr);
			return 0;
		}
	}
	return 1;
}

int disp_sequence_prev_ok(DispSequence *seq) {
	int i;
	if (!disp_sequence_elements_ok(seq)) return 0;
	if (!set_disp_ok(seq->d, seq->strarr[seq->num - 1])) {
		SEQ_ERR_STR("last string not valid", seq->num - 1,
						seq->strarr[seq->num - 1]);
		return 0;
	}
	for (i = seq->num - 2; i >= 0; i--) {
		if (!disp_prev(seq->d)) {
			SEQ_ERR_STR("unable to get previous", i + 1,
							seq->strarr[i + 1]);
			return 0;
		}
		if (!equal_disp_str(seq->d, seq->strarr[i])) {
			SEQ_ERR_STR_DISP("previous is not equal", i,
							seq->strarr[i]);
			disp_fprint(seq->d, stderr);
			return 0;
		}
	}
	if (seq->t == DISP_SEQ_ALL || seq->t == DISP_SEQ_FIRST) {
		disp_first(seq->d);
		if (!equal_disp_str(seq->d, seq->strarr[0])) {
			SEQ_ERR_STR_DISP("first is not equal", 0,
							seq->strarr[0]);
			disp_fprint(seq->d, stderr);
			return 0;
		}
		if (disp_prev(seq->d)) {
			SEQ_ERR_STR_DISP("first has previous", 0,
							seq->strarr[0]);
			disp_fprint(seq->d, stderr);
			return 0;
		}
	}
	return 1;
}

