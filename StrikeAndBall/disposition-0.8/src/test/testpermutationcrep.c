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

/* tests for permutations with constant repetition */

#include "permutationcrep.h"
#include "dispcreptestutil.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int nextElemPermutationCRep(PermutationCRep *perm, int *newval);

#define NEW      newPermutationCRep
#define NEXTELEM nextElemPermutationCRep

void test_permcrep_new(void) {
	assert(new_del_crep_err(NEW, 3, "1 1 1", 1, NEW_OK));
	assert(new_del_crep_err(NEW, 3, "1 1 2", 1, NEW_OK));
	assert(new_del_crep_err(NEW, 3, "1 1 3", 1, NEW_OK));
	assert(new_del_crep_err(NEW, 3, "1 1 4", 1, NEW_OK));
	assert(new_del_crep_err(NEW, 3, "1 1 5", 1, NEW_OK));
	assert(new_del_crep_err(NEW, 3, "9 8 7", 1, NEW_OK));
	assert(new_del_crep_err(NEW, 1, NULL, 1, NEW_OK));
	assert(new_del_crep_err(NEW, 3, NULL, 1, NEW_OK));
	assert(new_del_crep_err(NEW, 5, NULL, 1, NEW_OK));
	assert(new_del_crep_err(NEW, 0, NULL, 0, NUMELEM_LT_ONE));
	assert(new_del_crep_err(NEW, -1, NULL, 0, NUMELEM_LT_ONE));
	assert(new_del_crep_err(NEW, 3, "1 1 -1", 0, SIZE_LT_ZERO));
	assert(new_del_crep_err(NEW, 3, "4 -2 1", 0, SIZE_LT_ZERO));
	assert(new_del_crep_err(NEW, 3, "6 5 -3", 0, SIZE_LT_ZERO));
	assert(new_del_crep_err(NEW, 5, "1 2 1 1 3", 1, NEW_OK));
}

void test_permcrep_first(void) {
	assert(new_del_crep_first_ok(NEW, 1, NULL,    "0"));
	assert(new_del_crep_first_ok(NEW, 2, NULL,    "0 1"));
	assert(new_del_crep_first_ok(NEW, 3, NULL,    "0 1 2"));
	assert(new_del_crep_first_ok(NEW, 4, NULL,    "0 1 2 3"));
	assert(new_del_crep_first_ok(NEW, 5, NULL,    "0 1 2 3 4"));
	assert(new_del_crep_first_ok(NEW, 6, NULL,    "0 1 2 3 4 5"));
	assert(new_del_crep_first_ok(NEW, 1, "1",     "0"));
	assert(new_del_crep_first_ok(NEW, 1, "2",     "0 0"));
	assert(new_del_crep_first_ok(NEW, 1, "5",     "0 0 0 0 0"));
	assert(new_del_crep_first_ok(NEW, 2, "1 1",   "0 1"));
	assert(new_del_crep_first_ok(NEW, 3, "1 1 1", "0 1 2"));
	assert(new_del_crep_first_ok(NEW, 3, "1 1 2", "0 1 2 2"));
	assert(new_del_crep_first_ok(NEW, 3, "1 1 3", "0 1 2 2 2"));
	assert(new_del_crep_first_ok(NEW, 3, "1 1 4", "0 1 2 2 2 2"));
	assert(new_del_crep_first_ok(NEW, 3, "1 1 5", "0 1 2 2 2 2 2"));
	assert(new_del_crep_first_ok(NEW, 3, "2 2 1", "0 0 1 1 2"));
	assert(new_del_crep_first_ok(NEW, 3, "2 1 3", "0 0 1 2 2 2"));
	assert(new_del_crep_first_ok(NEW, 5, "1 2 1 2 1", "0 1 1 2 3 3 4"));
	assert(new_del_crep_first_ok(NEW, 5, "3 1 2 1 1", "0 0 0 1 2 2 3 4"));
	assert(new_del_crep_first_ok(NEW, 5, "1 3 3 1 1", "0 1 1 1 2 2 2 3 4"));
}

void test_permcrep_last(void) {
	assert(new_del_crep_last_ok(NEW, 1, NULL,    "0"));
	assert(new_del_crep_last_ok(NEW, 2, NULL,    "1 0"));
	assert(new_del_crep_last_ok(NEW, 3, NULL,    "2 1 0"));
	assert(new_del_crep_last_ok(NEW, 4, NULL,    "3 2 1 0"));
	assert(new_del_crep_last_ok(NEW, 5, NULL,    "4 3 2 1 0"));
	assert(new_del_crep_last_ok(NEW, 6, NULL,    "5 4 3 2 1 0"));
	assert(new_del_crep_last_ok(NEW, 1, "1",     "0"));
	assert(new_del_crep_last_ok(NEW, 1, "2",     "0 0"));
	assert(new_del_crep_last_ok(NEW, 1, "5",     "0 0 0 0 0"));
	assert(new_del_crep_last_ok(NEW, 2, "1 1",   "1 0"));
	assert(new_del_crep_last_ok(NEW, 3, "1 1 1", "2 1 0"));
	assert(new_del_crep_last_ok(NEW, 3, "1 1 2", "2 2 1 0"));
	assert(new_del_crep_last_ok(NEW, 3, "1 1 3", "2 2 2 1 0"));
	assert(new_del_crep_last_ok(NEW, 3, "1 1 4", "2 2 2 2 1 0"));
	assert(new_del_crep_last_ok(NEW, 3, "1 1 5", "2 2 2 2 2 1 0"));
	assert(new_del_crep_last_ok(NEW, 3, "2 2 1", "2 1 1 0 0"));
	assert(new_del_crep_last_ok(NEW, 3, "2 1 3", "2 2 2 1 0 0"));
	assert(new_del_crep_last_ok(NEW, 5, "1 2 1 2 1", "4 3 3 2 1 1 0"));
	assert(new_del_crep_last_ok(NEW, 5, "3 1 2 1 1", "4 3 2 2 1 0 0 0"));
	assert(new_del_crep_last_ok(NEW, 5, "1 3 3 1 1", "4 3 2 2 2 1 1 1 0"));
}

#define MAXSIZE 256
void test_permcrep_check(void) {
	PermutationCRep *d = NULL;
	int ok, v[MAXSIZE];
	ok = new_disp_crep_str(d, v, NEW, 4, "3 2 1 1"); assert(ok);
	assert(check_disp_err(d, "0 0 0 1 1 2 3", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 1 1 2 3 0", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 1 1 2 3 0", CHECK_OK, -1));
	assert(check_disp_err(d, "3 1 0 1 0 2 0", CHECK_OK, -1));
	assert(check_disp_err(d, "3 0 0 0 1 1 2", CHECK_OK, -1));
	assert(check_disp_err(d, "2 3 0 0 0 1 1", CHECK_OK, -1));
	assert(check_disp_err(d, "1 2 3 0 0 0 1", CHECK_OK, -1));
	assert(check_disp_err(d, "1 1 2 3 0 0 0", CHECK_OK, -1));
	assert(check_disp_err(d, "3 1 1 0 0 0 2", CHECK_OK, -1));
	assert(check_disp_err(d, "3 2 1 1 0 0 0", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 0 1 1 2 4", ELEM_OUT_OF_RANGE, 6));
	assert(check_disp_err(d, "0 0 0 1 1 -1 4", ELEM_OUT_OF_RANGE, 5));
	assert(check_disp_err(d, "0 0 0 0 1 2 3", ELEM_REPEATED, 3));
	assert(check_disp_err(d, "0 0 0 1 0 2 3", ELEM_REPEATED, 4));
	assert(check_disp_err(d, "0 0 0 1 1 1 3", ELEM_REPEATED, 5));
	assert(check_disp_err(d, "0 0 2 1 1 2 3", ELEM_REPEATED, -1));
	assert(check_disp_err(d, "0 0 0 1 2 1 2", ELEM_REPEATED, 6));
	disp_delete(d);
}

#define MAX 100
void test_permcrep_sequence(void) {
	int ok, v[MAXSIZE];
	PermutationCRep *d = NULL;
	char *a[MAX];
	DispSequence s;
	/* (2,3,1,1) */
	ok = new_disp_crep_str(d, v, NEW, 4, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 0 1 1 1 2 3");
	ADD(&s, "0 0 1 1 1 3 2");
	ADD(&s, "0 0 1 1 2 1 3");
	ADD(&s, "0 0 1 1 2 3 1");
	ADD(&s, "0 0 1 1 3 1 2");
	ADD(&s, "0 0 1 1 3 2 1");
	ADD(&s, "0 0 1 2 1 1 3");
	ADD(&s, "0 0 1 2 1 3 1");
	ADD(&s, "0 0 1 2 3 1 1");
	ADD(&s, "0 0 1 3 1 1 2");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "3 1 2 1 1 0 0");
	ADD(&s, "3 2 0 0 1 1 1");
	ADD(&s, "3 2 0 1 0 1 1");
	ADD(&s, "3 2 0 1 1 0 1");
	ADD(&s, "3 2 0 1 1 1 0");
	ADD(&s, "3 2 1 0 0 1 1");
	ADD(&s, "3 2 1 0 1 0 1");
	ADD(&s, "3 2 1 0 1 1 0");
	ADD(&s, "3 2 1 1 0 0 1");
	ADD(&s, "3 2 1 1 0 1 0");
	ADD(&s, "3 2 1 1 1 0 0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* (1,1,1,1) */
	ok = new_disp_crep_str(d, v, NEW, 4, "1 1 1 1"); assert(ok);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 1 2 3");
	ADD(&s, "0 1 3 2");
	ADD(&s, "0 2 1 3");
	ADD(&s, "0 2 3 1");
	ADD(&s, "0 3 1 2");
	ADD(&s, "0 3 2 1");
	ADD(&s, "1 0 2 3");
	ADD(&s, "1 0 3 2");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "2 3 0 1");
	ADD(&s, "2 3 1 0");
	ADD(&s, "3 0 1 2");
	ADD(&s, "3 0 2 1");
	ADD(&s, "3 1 0 2");
	ADD(&s, "3 1 2 0");
	ADD(&s, "3 2 0 1");
	ADD(&s, "3 2 1 0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* (1,1,1,1) */
	ok = new_disp_crep_str_null(d, NEW, 4); assert(ok);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 1 2 3");
	ADD(&s, "0 1 3 2");
	ADD(&s, "0 2 1 3");
	ADD(&s, "0 2 3 1");
	ADD(&s, "0 3 1 2");
	ADD(&s, "0 3 2 1");
	ADD(&s, "1 0 2 3");
	ADD(&s, "1 0 3 2");
	assert(disp_sequence_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "2 3 0 1");
	ADD(&s, "2 3 1 0");
	ADD(&s, "3 0 1 2");
	ADD(&s, "3 0 2 1");
	ADD(&s, "3 1 0 2");
	ADD(&s, "3 1 2 0");
	ADD(&s, "3 2 0 1");
	ADD(&s, "3 2 1 0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* (1,4) */
	ok = new_disp_crep_str(d, v, NEW, 2, "1 4"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 1 1 1 1");
	ADD(&s, "1 0 1 1 1");
	ADD(&s, "1 1 0 1 1");
	ADD(&s, "1 1 1 0 1");
	ADD(&s, "1 1 1 1 0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* (4,1) */
	ok = new_disp_crep_str(d, v, NEW, 2, "4 1"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 0 0 1");
	ADD(&s, "0 0 0 1 0");
	ADD(&s, "0 0 1 0 0");
	ADD(&s, "0 1 0 0 0");
	ADD(&s, "1 0 0 0 0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* (5) */
	ok = new_disp_crep_str(d, v, NEW, 1, "5"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 0 0 0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* (1) */
	ok = new_disp_crep_str(d, v, NEW, 1, "1"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
	/* (1) */
	ok = new_disp_crep_str_null(d, NEW, 1); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0");
	assert(disp_sequence_ok(&s));
	disp_delete(d);
}

void test_permcrep_copy(void) {
	int ok, v[MAXSIZE];
	PermutationCRep *d = NULL;
	/* (2,3,1,1) */
	ok = new_disp_crep_str(d, v, NEW, 4, "2 3 1 1"); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "1 0 1 2 3 1 0")); assert(copy_disprep_ok(d));
	disp_delete(d);
	/* (1,1,1,1) */
	ok = new_disp_crep_str(d, v, NEW, 4, "1 1 1 1"); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "2 0 3 1")); assert(copy_disprep_ok(d));
	disp_delete(d);
	/* (1,1,1,1) */
	ok = new_disp_crep_str_null(d, NEW, 4); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "2 0 3 1")); assert(copy_disprep_ok(d));
	disp_delete(d);
	/* (1,4) */
	ok = new_disp_crep_str(d, v, NEW, 2, "1 4"); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "1 1 1 0 1")); assert(copy_disprep_ok(d));
	disp_delete(d);
	/* (4,1) */
	ok = new_disp_crep_str(d, v, NEW, 2, "4 1"); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "0 1 0 0 0")); assert(copy_disprep_ok(d));
	disp_delete(d);
	/* (5) */
	ok = new_disp_crep_str(d, v, NEW, 1, "5"); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "0 0 0 0 0")); assert(copy_disprep_ok(d));
	disp_delete(d);
	/* (1) */
	ok = new_disp_crep_str(d, v, NEW, 1, "1"); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "0")); assert(copy_disprep_ok(d));
	disp_delete(d);
	/* (1) */
	ok = new_disp_crep_str_null(d, NEW, 1); assert(ok);
	disp_first(d); assert(copy_disprep_ok(d));
	disp_next(d); assert(copy_disprep_ok(d));
	disp_last(d); assert(copy_disprep_ok(d));
	disp_prev(d); assert(copy_disprep_ok(d));
	assert(set_disp_ok(d, "0")); assert(copy_disprep_ok(d));
	disp_delete(d);
}

#include <time.h>
void test_permcrep_rand(void) {
	PermutationCRep *d = NULL;
	int ok, v[MAXSIZE];
	set_seed(time(NULL), 1);
	ok = new_disp_crep_str_null(d, NEW, 1); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str_null(d, NEW, 2); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str_null(d, NEW, 3); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str_null(d, NEW, 4); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str_null(d, NEW, 5); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str(d, v, NEW, 1, "7"); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str(d, v, NEW, 2, "1 5"); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str(d, v, NEW, 3, "3 1 4"); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
	ok = new_disp_crep_str(d, v, NEW, 4, "2 3 1 1"); assert(ok);
	assert(rand_disp_ok(d, 0)); disp_delete(d);
}

void testpermutationcrep(void) {
	test_permcrep_new();
	test_permcrep_first();
	test_permcrep_last();
	test_permcrep_check();
	test_permcrep_sequence();
	test_permcrep_copy();
	test_permcrep_rand();
}

