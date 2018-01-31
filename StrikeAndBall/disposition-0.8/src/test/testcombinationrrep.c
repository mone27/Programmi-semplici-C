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

/* tests for combinations with restricted repetition */

#include "combinationrrep.h"
#include "disprreptestutil.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int nextElemCombinationRRep(CombinationRRep *comb);

#define NEW      newCombinationRRep
#define NEXTELEM nextElemCombinationRRep

void test_combrrep_new(void) {
	assert(new_del_rrep_err(NEW, 3, 3, "1 1 1", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 3, 4, "1 1 2", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 3, 5, "1 1 3", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 3, 5, "1 1 4", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 3, 5, "1 1 5", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 3, 5, "1 1 2", 0, SIZE_GT_NUMELEM));
	assert(new_del_rrep_err(NEW, 3, 5, "0 1 4", 0, SIZE_LT_ZERO));
	assert(new_del_rrep_err(NEW, 3, 5, "3 0 2", 0, SIZE_LT_ZERO));
	assert(new_del_rrep_err(NEW, 5, 3, "1 2 1 1 3", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 5, 5, "1 2 1 1 3", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 5, 8, "1 2 1 1 3", 1, NEW_OK));
	assert(new_del_rrep_err(NEW, 5, 9, "1 2 1 1 3", 0, SIZE_GT_NUMELEM));
}

void test_combrrep_first(void) {
	assert(new_del_rrep_first_ok(NEW, 2, 2, "1 1", "0 1"));
	assert(new_del_rrep_first_ok(NEW, 3, 3, "1 1 1", "0 1 2"));
	assert(new_del_rrep_first_ok(NEW, 3, 4, "1 1 2", "0 1 2 2"));
	assert(new_del_rrep_first_ok(NEW, 3, 5, "1 1 3", "0 1 2 2 2"));
	assert(new_del_rrep_first_ok(NEW, 3, 5, "1 1 4", "0 1 2 2 2"));
	assert(new_del_rrep_first_ok(NEW, 3, 5, "1 1 5", "0 1 2 2 2"));
	assert(new_del_rrep_first_ok(NEW, 3, 5, "2 2 1", "0 0 1 1 2"));
	assert(new_del_rrep_first_ok(NEW, 3, 5, "2 1 3", "0 0 1 2 2"));
	assert(new_del_rrep_first_ok(NEW, 5, 3, "1 2 1 1 3", "0 1 1"));
	assert(new_del_rrep_first_ok(NEW, 5, 5, "1 2 1 1 3", "0 1 1 2 3"));
	assert(new_del_rrep_first_ok(NEW, 5, 8, "1 2 1 1 3","0 1 1 2 3 4 4 4"));
}

void test_combrrep_last(void) {
	assert(new_del_rrep_last_ok(NEW, 2, 2, "1 1", "0 1"));
	assert(new_del_rrep_last_ok(NEW, 3, 3, "1 1 1", "0 1 2"));
	assert(new_del_rrep_last_ok(NEW, 3, 4, "1 1 2", "0 1 2 2"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "1 1 3", "0 1 2 2 2"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "1 1 4", "1 2 2 2 2"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "1 1 5", "2 2 2 2 2"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "2 2 1", "0 0 1 1 2"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "2 1 3", "0 1 2 2 2"));
	assert(new_del_rrep_last_ok(NEW, 5, 3, "1 2 1 1 3", "4 4 4"));
	assert(new_del_rrep_last_ok(NEW, 5, 5, "1 2 1 1 3", "2 3 4 4 4"));
	assert(new_del_rrep_last_ok(NEW, 5, 8, "1 2 1 1 3", "0 1 1 2 3 4 4 4"));
}

#define MAXSIZE 256
void test_combrrep_check(void) {
	char *str;
	CombinationRRep *d = NULL;
	int ok, num, size, v[MAXSIZE]; v[0] = 0;
	num = 4; size = 5; str = "3 2 1 1";
	ok = new_disp_rrep_str(d, v, NEW, num, size, str); assert(ok);
	assert(check_disp_err(d, "0 0 0 1 1", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 1 1 2", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 0 2 3", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 1 2 3", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 4", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "0 1 2 -3 3", ELEM_OUT_OF_RANGE, 3));
	assert(check_disp_err(d, "0 0 1 1 1", ELEM_REPEATED, 4));
	assert(check_disp_err(d, "0 0 0 0 1", ELEM_REPEATED, 3));
	assert(check_disp_err(d, "3 2 1 1 0", OK_ELEM_UNSORTED, 1));
	assert(check_disp_err(d, "0 1 0 1 0", OK_ELEM_UNSORTED, 2));
	assert(check_disp_err(d, "0 1 3 1 2", OK_ELEM_UNSORTED, 3));
	assert(check_disp_err(d, "0 0 1 1 0", OK_ELEM_UNSORTED, 4));
	disp_delete(d);
}

void test_combrrep_next_elem(void) {
	char *str;
	CombinationRRep *d = NULL;
	int ok, num, size, v[MAXSIZE]; v[0] = 0;
	num = 4; size = 3; str = "2 3 1 1";
	ok = new_disp_rrep_str(d, v, NEW, num, size, str); assert(ok);
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 2", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 3", 1));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 2", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 3", 1));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 2 3", 0));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 1 1", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 1 2", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 1 3", 1));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 2 3", -1));
	disp_delete(d);
	d = NEW(num, size = 4, v, NULL);
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 2", 3));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 3", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 2 3", 1));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1 1", 3));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1 2", 3));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1 3", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 2 3", 0));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 1 1 2", 3));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 1 1 3", 2));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 1 2 3", -1));
	disp_delete(d);
	d = NEW(num, size = 5, v, NULL);
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 1 2", 4));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 1 3", 3));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 2 3", 1));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1 1 2", 4));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1 1 3", 3));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1 2 3", 0));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "1 1 1 2 3", -1));
	disp_delete(d);
	d = NEW(num, size = 6, v, NULL);
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 1 1 2", 5));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 1 1 3", 4));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 1 2 3", 1));
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 1 1 1 2 3", -1));
	disp_delete(d);
	d = NEW(num, size = 7, v, NULL);
	assert(next_elem_combrrep_ok(d, NEXTELEM, "0 0 1 1 1 2 3", -1));
	disp_delete(d);
}

#define MAX 100
void test_combrrep_sequence(void) {
	int ok, v[MAXSIZE];
	CombinationRRep *d = NULL;
	char *a[MAX];
	DispSequence s;
	/* (2,3,1,1),3 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 3, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 1");
	ADD(&s, "0 0 2");
	ADD(&s, "0 0 3");
	ADD(&s, "0 1 1");
	ADD(&s, "0 1 2");
	ADD(&s, "0 1 3");
	ADD(&s, "0 2 3");
	ADD(&s, "1 1 1");
	ADD(&s, "1 1 2");
	ADD(&s, "1 1 3");
	ADD(&s, "1 2 3");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
	/* (2,3,1,1),4 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 4, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 1 1");
	ADD(&s, "0 0 1 2");
	ADD(&s, "0 0 1 3");
	ADD(&s, "0 0 2 3");
	ADD(&s, "0 1 1 1");
	ADD(&s, "0 1 1 2");
	ADD(&s, "0 1 1 3");
	ADD(&s, "0 1 2 3");
	ADD(&s, "1 1 1 2");
	ADD(&s, "1 1 1 3");
	ADD(&s, "1 1 2 3");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
	/* (2,3,1,1),5 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 5, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 1 1 1");
	ADD(&s, "0 0 1 1 2");
	ADD(&s, "0 0 1 1 3");
	ADD(&s, "0 0 1 2 3");
	ADD(&s, "0 1 1 1 2");
	ADD(&s, "0 1 1 1 3");
	ADD(&s, "0 1 1 2 3");
	ADD(&s, "1 1 1 2 3");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
	/* (2,3,1,1),6 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 6, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 1 1 1 2");
	ADD(&s, "0 0 1 1 1 3");
	ADD(&s, "0 0 1 1 2 3");
	ADD(&s, "0 1 1 1 2 3");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
	/* (2,3,1,1),7 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 7, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, ALL, a, MAX);
	ADD(&s, "0 0 1 1 1 2 3");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
}

#include "cmem.h"
void testcombinationrrep(void) {
	test_combrrep_new();
	test_combrrep_first();
	test_combrrep_last();
	test_combrrep_check();
	test_combrrep_next_elem();
	test_combrrep_sequence();
	/*
	test_combrrep_rand();
	test_combrrep_copy();
	*/
	cmem_info_ext();
	printf("TODO\n");
}

