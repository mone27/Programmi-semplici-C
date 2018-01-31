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

/* tests for permutations with repetition */

#include "permutationrep.h"
#include "dispbasictestutil.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NEW newPermutationRep

void test_permrep_new(void) {
	assert(new_del_disp_err(NEW,  9,  5, NEW_OK));
	assert(new_del_disp_err(NEW,  5,  5, NEW_OK));
	assert(new_del_disp_err(NEW,  3,  5, NEW_OK));
	assert(new_del_disp_err(NEW,  5, 10, NEW_OK));
	assert(new_del_disp_err(NEW,  5,  0, NEW_OK));
	assert(new_del_disp_err(NEW,  0,  5, NUMELEM_LT_ONE));
	assert(new_del_disp_err(NEW, -5,  5, NUMELEM_LT_ONE));
	assert(new_del_disp_err(NEW, -5,  0, NUMELEM_LT_ONE));
	assert(new_del_disp_err(NEW,  0,  0, NUMELEM_LT_ONE));
	assert(new_del_disp_err(NEW,  5, -5, SIZE_LT_ZERO));
}

void test_permrep_first(void) {
	assert(new_del_disp_first_ok(NEW, 9, 5, "0 0 0 0 0"));
	assert(new_del_disp_first_ok(NEW, 5, 5, "0 0 0 0 0"));
	assert(new_del_disp_first_ok(NEW, 3, 5, "0 0 0 0 0"));
	assert(new_del_disp_first_ok(NEW, 1, 5, "0 0 0 0 0"));
	assert(new_del_disp_first_ok(NEW, 5, 1, "0"));
	assert(new_del_disp_first_ok(NEW, 5, 0, ""));
}

void test_permrep_last(void) {
	assert(new_del_disp_last_ok(NEW, 9, 5, "8 8 8 8 8"));
	assert(new_del_disp_last_ok(NEW, 5, 5, "4 4 4 4 4"));
	assert(new_del_disp_last_ok(NEW, 3, 5, "2 2 2 2 2"));
	assert(new_del_disp_last_ok(NEW, 1, 5, "0 0 0 0 0"));
	assert(new_del_disp_last_ok(NEW, 5, 1, "4"));
	assert(new_del_disp_last_ok(NEW, 5, 0, ""));
}

void test_permrep_check(void) {
	PermutationRep *d;
	d = NEW(9, 5, NULL);
	assert(check_disp_err(d, "0 0 0 0 0", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 4", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 0", CHECK_OK, -1));
	assert(check_disp_err(d, "8 7 6 5 4", CHECK_OK, -1));
	assert(check_disp_err(d, "8 8 8 8 8", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 9", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "8 8 8 8 9", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "0 1 2 -3 4",ELEM_OUT_OF_RANGE, 3));
	disp_delete(d);
	d = NEW(5, 5, NULL);
	assert(check_disp_err(d, "0 0 0 0 0", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 4", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 0", CHECK_OK, -1));
	assert(check_disp_err(d, "4 3 2 1 0", CHECK_OK, -1));
	assert(check_disp_err(d, "4 4 4 4 4", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 5", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "4 4 4 4 5", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "0 1 2 -3 4",ELEM_OUT_OF_RANGE, 3));
	disp_delete(d);
	d = NEW(3, 5, NULL);
	assert(check_disp_err(d, "0 0 0 0 0", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 2 1", CHECK_OK, -1));
	assert(check_disp_err(d, "2 1 0 0 1", CHECK_OK, -1));
	assert(check_disp_err(d, "2 2 2 2 2", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 2 3", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "2 2 2 2 3", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "0 1 2 -2 1",ELEM_OUT_OF_RANGE, 3));
	disp_delete(d);
	d = NEW(1, 5, NULL);
	assert(check_disp_err(d, "0 0 0 0 0", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 0 0 1", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "0 0 0 -1 0",ELEM_OUT_OF_RANGE, 3));
	disp_delete(d);
	d = NEW(5, 1, NULL);
	assert(check_disp_err(d, "0", CHECK_OK, -1));
	assert(check_disp_err(d, "2", CHECK_OK, -1));
	assert(check_disp_err(d, "4", CHECK_OK, -1));
	assert(check_disp_err(d, "5", ELEM_OUT_OF_RANGE, 0));
	assert(check_disp_err(d, "-3", ELEM_OUT_OF_RANGE, 0));
	disp_delete(d);
	d = NEW(5, 0, NULL);
	assert(check_disp_err(d, "", CHECK_OK, -1));
	disp_delete(d);
}

#define MAX 100
void test_permrep_sequence(void) {
	PermutationRep *d;
	char *a[MAX];
	DispSequence s;
	/* 9,5 */
	d = NEW(9, 5, NULL);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 0 0 0 0");
	ADD(&s, "0 0 0 0 1");
	ADD(&s, "0 0 0 0 2");
	ADD(&s, "0 0 0 0 3");
	ADD(&s, "0 0 0 0 4");
	ADD(&s, "0 0 0 0 5");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, MIDDLE, a, MAX);
	ADD(&s, "0 1 2 3 6");
	ADD(&s, "0 1 2 3 7");
	ADD(&s, "0 1 2 3 8");
	ADD(&s, "0 1 2 4 0");
	ADD(&s, "0 1 2 4 1");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, MIDDLE, a, MAX);
	ADD(&s, "0 1 2 8 7");
	ADD(&s, "0 1 2 8 8");
	ADD(&s, "0 1 3 0 0");
	ADD(&s, "0 1 3 0 1");
	ADD(&s, "0 1 3 0 2");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "8 8 8 8 4");
	ADD(&s, "8 8 8 8 5");
	ADD(&s, "8 8 8 8 6");
	ADD(&s, "8 8 8 8 7");
	ADD(&s, "8 8 8 8 8");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* 5,5 */
	d = NEW(5, 5, NULL);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 0 0 0 0");
	ADD(&s, "0 0 0 0 1");
	ADD(&s, "0 0 0 0 2");
	ADD(&s, "0 0 0 0 3");
	ADD(&s, "0 0 0 0 4");
	ADD(&s, "0 0 0 1 0");
	ADD(&s, "0 0 0 1 1");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, MIDDLE, a, MAX);
	ADD(&s, "0 1 2 3 2");
	ADD(&s, "0 1 2 3 3");
	ADD(&s, "0 1 2 3 4");
	ADD(&s, "0 1 2 4 0");
	ADD(&s, "0 1 2 4 1");
	ADD(&s, "0 1 2 4 2");
	ADD(&s, "0 1 2 4 3");
	ADD(&s, "0 1 2 4 4");
	ADD(&s, "0 1 3 0 0");
	ADD(&s, "0 1 3 0 1");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "4 4 4 3 3");
	ADD(&s, "4 4 4 3 4");
	ADD(&s, "4 4 4 4 0");
	ADD(&s, "4 4 4 4 1");
	ADD(&s, "4 4 4 4 2");
	ADD(&s, "4 4 4 4 3");
	ADD(&s, "4 4 4 4 4");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* 3,5 */
	d = NEW(3, 5, NULL);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 0 0 0 0");
	ADD(&s, "0 0 0 0 1");
	ADD(&s, "0 0 0 0 2");
	ADD(&s, "0 0 0 1 0");
	ADD(&s, "0 0 0 1 1");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, MIDDLE, a, MAX);
	ADD(&s, "0 1 0 0 1");
	ADD(&s, "0 1 0 0 2");
	ADD(&s, "0 1 0 1 0");
	ADD(&s, "0 1 0 1 1");
	ADD(&s, "0 1 0 1 2");
	ADD(&s, "0 1 0 2 0");
	ADD(&s, "0 1 0 2 1");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, MIDDLE, a, MAX);
	ADD(&s, "0 1 2 2 0");
	ADD(&s, "0 1 2 2 1");
	ADD(&s, "0 1 2 2 2");
	ADD(&s, "0 2 0 0 0");
	ADD(&s, "0 2 0 0 1");
	ADD(&s, "0 2 0 0 2");
	ADD(&s, "0 2 0 1 0");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "2 2 2 0 2");
	ADD(&s, "2 2 2 1 0");
	ADD(&s, "2 2 2 1 1");
	ADD(&s, "2 2 2 1 2");
	ADD(&s, "2 2 2 2 0");
	ADD(&s, "2 2 2 2 1");
	ADD(&s, "2 2 2 2 2");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* 1,5 */
	d = NEW(1, 5, NULL);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 0 0 0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* 5,1 */
	d = NEW(5, 1, NULL);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0");
	ADD(&s, "1");
	ADD(&s, "2");
	ADD(&s, "3");
	ADD(&s, "4");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* 5,0 */
	d = NEW(5, 0, NULL);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
}

void test_permrep_copy(void) {
	PermutationRep *d;
	d = NEW(9, 5, NULL);
	disp_first(d); assert(copy_disp_ok(d));
	disp_next(d); assert(copy_disp_ok(d));
	disp_last(d); assert(copy_disp_ok(d));
	disp_prev(d); assert(copy_disp_ok(d));
	disp_first(d); disp_prev(d); assert(copy_disp_ok(d));
	disp_last(d); disp_next(d); assert(copy_disp_ok(d));
	assert(set_disp_ok(d, "0 3 8 0 6")); assert(copy_disp_ok(d));
	disp_delete(d);
	d = NEW(5, 5, NULL);
	disp_first(d); assert(copy_disp_ok(d));
	disp_next(d); assert(copy_disp_ok(d));
	disp_last(d); assert(copy_disp_ok(d));
	disp_prev(d); assert(copy_disp_ok(d));
	disp_first(d); disp_prev(d); assert(copy_disp_ok(d));
	disp_last(d); disp_next(d); assert(copy_disp_ok(d));
	assert(set_disp_ok(d, "0 1 3 0 2")); assert(copy_disp_ok(d));
	disp_delete(d);
	d = NEW(3, 5, NULL);
	disp_first(d); assert(copy_disp_ok(d));
	disp_next(d); assert(copy_disp_ok(d));
	disp_last(d); assert(copy_disp_ok(d));
	disp_prev(d); assert(copy_disp_ok(d));
	disp_first(d); disp_prev(d); assert(copy_disp_ok(d));
	disp_last(d); disp_next(d); assert(copy_disp_ok(d));
	assert(set_disp_ok(d, "0 2 0 0 1")); assert(copy_disp_ok(d));
	disp_delete(d);
	d = NEW(1, 5, NULL);
	disp_first(d); assert(copy_disp_ok(d));
	disp_next(d); assert(copy_disp_ok(d));
	disp_last(d); assert(copy_disp_ok(d));
	disp_prev(d); assert(copy_disp_ok(d));
	disp_first(d); disp_prev(d); assert(copy_disp_ok(d));
	disp_last(d); disp_next(d); assert(copy_disp_ok(d));
	assert(set_disp_ok(d, "0 0 0 0 0")); assert(copy_disp_ok(d));
	disp_delete(d);
	d = NEW(5, 1, NULL);
	disp_first(d); assert(copy_disp_ok(d));
	disp_next(d); assert(copy_disp_ok(d));
	disp_last(d); assert(copy_disp_ok(d));
	disp_prev(d); assert(copy_disp_ok(d));
	disp_first(d); disp_prev(d); assert(copy_disp_ok(d));
	disp_last(d); disp_next(d); assert(copy_disp_ok(d));
	assert(set_disp_ok(d, "2")); assert(copy_disp_ok(d));
	disp_delete(d);
	d = NEW(5, 0, NULL);
	disp_first(d); assert(copy_disp_ok(d));
	disp_next(d); assert(copy_disp_ok(d));
	disp_last(d); assert(copy_disp_ok(d));
	disp_prev(d); assert(copy_disp_ok(d));
	disp_first(d); disp_prev(d); assert(copy_disp_ok(d));
	disp_last(d); disp_next(d); assert(copy_disp_ok(d));
	assert(set_disp_ok(d, "")); assert(copy_disp_ok(d));
	disp_delete(d);
}

#include <time.h>
void test_permrep_rand(void) {
	PermutationRep *d;
	set_seed(time(NULL), 1);
	d = NEW(9, 5, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
	d = NEW(5, 5, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
	d = NEW(5, 3, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
	d = NEW(3, 5, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
	d = NEW(1, 5, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
	d = NEW(5, 1, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
	d = NEW(5, 0, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
	d = NEW(1, 1, NULL); assert(rand_disp_ok(d, 0)); disp_delete(d);
}

void testpermutationrep(void) {
	test_permrep_new();
	test_permrep_first();
	test_permrep_last();
	test_permrep_check();
	test_permrep_sequence();
	test_permrep_copy();
	test_permrep_rand();
}

