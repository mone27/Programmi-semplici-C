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

/* tests for permutations with restricted repetition */

#include "permutationrrep.h"
#include "disprreptestutil.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int nextElemPermutationRRep(PermutationRRep *perm, int *newval);

#define NEW      newPermutationRRep
#define NEXTELEM nextElemPermutationRRep

void test_permrrep_new(void) {
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

void test_permrrep_first(void) {
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

void test_permrrep_last(void) {
	assert(new_del_rrep_last_ok(NEW, 2, 2, "1 1", "1 0"));
	assert(new_del_rrep_last_ok(NEW, 3, 3, "1 1 1", "2 1 0"));
	assert(new_del_rrep_last_ok(NEW, 3, 4, "1 1 2", "2 2 1 0"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "1 1 3", "2 2 2 1 0"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "1 1 4", "2 2 2 2 1"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "1 1 5", "2 2 2 2 2"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "2 2 1", "2 1 1 0 0"));
	assert(new_del_rrep_last_ok(NEW, 3, 5, "2 1 3", "2 2 2 1 0"));
	assert(new_del_rrep_last_ok(NEW, 5, 3, "1 2 1 1 3", "4 4 4"));
	assert(new_del_rrep_last_ok(NEW, 5, 5, "1 2 1 1 3", "4 4 4 3 2"));
	assert(new_del_rrep_last_ok(NEW, 5, 8, "1 2 1 1 3", "4 4 4 3 2 1 1 0"));
}

#define MAXSIZE 256
void test_permrrep_check(void) {
	PermutationRRep *d = NULL;
	int ok, num, size, v[MAXSIZE]; v[0] = 0;
	num = 4; size = 5;
	ok = new_disp_rrep_str(d, v, NEW, num, size, "3 2 1 1"); assert(ok);
	assert(check_disp_err(d, "0 0 0 1 1", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 1 1 2", CHECK_OK, -1));
	assert(check_disp_err(d, "0 0 0 2 3", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 1 2 3", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 0 1 0", CHECK_OK, -1));
	assert(check_disp_err(d, "2 0 1 1 0", CHECK_OK, -1));
	assert(check_disp_err(d, "2 0 0 3 0", CHECK_OK, -1));
	assert(check_disp_err(d, "3 2 1 1 0", CHECK_OK, -1));
	assert(check_disp_err(d, "0 1 2 3 4", ELEM_OUT_OF_RANGE, 4));
	assert(check_disp_err(d, "0 1 2 -3 3", ELEM_OUT_OF_RANGE, 3));
	assert(check_disp_err(d, "0 0 1 1 1", ELEM_REPEATED, 4));
	assert(check_disp_err(d, "0 0 0 0 1", ELEM_REPEATED, 3));
	disp_delete(d);
}

void test_permrrep_next_elem(void) {
	PermutationRRep *d = NULL;
	int ok, num, size, v[MAXSIZE]; v[0] = 0;
	num = 4; size = 5;
	ok = new_disp_rrep_str(d, v, NEW, num, size, "2 3 1 1"); assert(ok);
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 1 1 1", 4, 2));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 1 1 2", 4, 3));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 1 1 3", 3, 2));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 1 2 1", 4, 3));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 1 2 3", 3, 3));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 1 3 1", 4, 2));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 1 3 2", 2, 2));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "0 0 2 1 1", 4, 3));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 1 1 2 0", 4, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 1 1 2 1", 2, 2));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 1 2 0 0", 4, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 1 2 0 1", 3, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 1 2 1 0", 4, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 1 2 1 1", 1, 2));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 2 0 0 1", 3, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 2 0 1 0", 4, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 2 0 1 1", 2, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 2 1 0 0", 4, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 2 1 0 1", 3, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 2 1 1 0", 4, 1));
	assert(next_elem_permrrep_ok(d, NEXTELEM, "3 2 1 1 1", -1, 3333));
	disp_delete(d);
}

#define MAX 100
void test_permrrep_sequence(void) {
	int ok, v[MAXSIZE];
	PermutationRRep *d = NULL;
	char *a[MAX];
	DispSequence s;
	/* (2,3,1,1),3 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 3, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 0 1");
	ADD(&s, "0 0 2");
	ADD(&s, "0 0 3");
	ADD(&s, "0 1 0");
	ADD(&s, "0 1 1");
	ADD(&s, "0 1 2");
	ADD(&s, "0 1 3");
	ADD(&s, "0 2 0");
	ADD(&s, "0 2 1");
	ADD(&s, "0 2 3");
	ADD(&s, "0 3 0");
	ADD(&s, "0 3 1");
	ADD(&s, "0 3 2");
	ADD(&s, "1 0 0");
	ADD(&s, "1 0 1");
	ADD(&s, "1 0 2");
	ADD(&s, "1 0 3");
	ADD(&s, "1 1 0");
	ADD(&s, "1 1 1");
	ADD(&s, "1 1 2");
	ADD(&s, "1 1 3");
	ADD(&s, "1 2 0");
	ADD(&s, "1 2 1");
	ADD(&s, "1 2 3");
	ADD(&s, "1 3 0");
	ADD(&s, "1 3 1");
	ADD(&s, "1 3 2");
	ADD(&s, "2 0 0");
	ADD(&s, "2 0 1");
	ADD(&s, "2 0 3");
	ADD(&s, "2 1 0");
	ADD(&s, "2 1 1");
	ADD(&s, "2 1 3");
	ADD(&s, "2 3 0");
	ADD(&s, "2 3 1");
	ADD(&s, "3 0 0");
	ADD(&s, "3 0 1");
	ADD(&s, "3 0 2");
	ADD(&s, "3 1 0");
	ADD(&s, "3 1 1");
	ADD(&s, "3 1 2");
	ADD(&s, "3 2 0");
	ADD(&s, "3 2 1");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
	/* (2,3,1,1),4 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 4, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 0 1 1");
	ADD(&s, "0 0 1 2");
	ADD(&s, "0 0 1 3");
	ADD(&s, "0 0 2 1");
	ADD(&s, "0 0 2 3");
	ADD(&s, "0 0 3 1");
	ADD(&s, "0 0 3 2");
	ADD(&s, "0 1 0 1");
	ADD(&s, "0 1 0 2");
	ADD(&s, "0 1 0 3");
	ADD(&s, "0 1 1 0");
	ADD(&s, "0 1 1 1");
	ADD(&s, "0 1 1 2");
	ADD(&s, "0 1 1 3");
	ADD(&s, "0 1 2 0");
	assert(disp_sequence_next_ok(&s));
	s = disp_sequence(d, MIDDLE, a, MAX);
	ADD(&s, "1 1 0 3");
	ADD(&s, "1 1 1 0");
	ADD(&s, "1 1 1 2");
	ADD(&s, "1 1 1 3");
	ADD(&s, "1 1 2 0");
	ADD(&s, "1 1 2 1");
	ADD(&s, "1 1 2 3");
	ADD(&s, "1 1 3 0");
	ADD(&s, "1 1 3 1");
	ADD(&s, "1 1 3 2");
	ADD(&s, "1 2 0 0");
	ADD(&s, "1 2 0 1");
	ADD(&s, "1 2 0 3");
	ADD(&s, "1 2 1 0");
	ADD(&s, "1 2 1 1");
	ADD(&s, "1 2 1 3");
	ADD(&s, "1 2 3 0");
	ADD(&s, "1 2 3 1");
	ADD(&s, "1 3 0 0");
	ADD(&s, "1 3 0 1");
	assert(disp_sequence_next_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "3 1 1 0");
	ADD(&s, "3 1 1 1");
	ADD(&s, "3 1 1 2");
	ADD(&s, "3 1 2 0");
	ADD(&s, "3 1 2 1");
	ADD(&s, "3 2 0 0");
	ADD(&s, "3 2 0 1");
	ADD(&s, "3 2 1 0");
	ADD(&s, "3 2 1 1");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
	/* (2,3,1,1),5 */
	ok = new_disp_rrep_str(d, v, NEW, 4, 5, "2 3 1 1"); assert(ok);
	s = disp_sequence(d, FIRST, a, MAX);
	ADD(&s, "0 0 1 1 1");
	ADD(&s, "0 0 1 1 2");
	ADD(&s, "0 0 1 1 3");
	ADD(&s, "0 0 1 2 1");
	ADD(&s, "0 0 1 2 3");
	ADD(&s, "0 0 1 3 1");
	ADD(&s, "0 0 1 3 2");
	ADD(&s, "0 0 2 1 1");
	ADD(&s, "0 0 2 1 3");
	ADD(&s, "0 0 2 3 1");
	ADD(&s, "0 0 3 1 1");
	ADD(&s, "0 0 3 1 2");
	ADD(&s, "0 0 3 2 1");
	ADD(&s, "0 1 0 1 1");
	ADD(&s, "0 1 0 1 2");
	ADD(&s, "0 1 0 1 3");
	ADD(&s, "0 1 0 2 1");
	ADD(&s, "0 1 0 2 3");
	ADD(&s, "0 1 0 3 1");
	ADD(&s, "0 1 0 3 2");
	ADD(&s, "0 1 1 0 1");
	ADD(&s, "0 1 1 0 2");
	ADD(&s, "0 1 1 0 3");
	ADD(&s, "0 1 1 1 0");
	ADD(&s, "0 1 1 1 2");
	ADD(&s, "0 1 1 1 3");
	ADD(&s, "0 1 1 2 0");
	ADD(&s, "0 1 1 2 1");
	ADD(&s, "0 1 1 2 3");
	ADD(&s, "0 1 1 3 0");
	ADD(&s, "0 1 1 3 1");
	ADD(&s, "0 1 1 3 2");
	ADD(&s, "0 1 2 0 1");
	ADD(&s, "0 1 2 0 3");
	ADD(&s, "0 1 2 1 0");
	ADD(&s, "0 1 2 1 1");
	ADD(&s, "0 1 2 1 3");
	assert(disp_sequence_next_ok(&s));
	s = disp_sequence(d, LAST, a, MAX);
	ADD(&s, "3 1 1 2 0");
	ADD(&s, "3 1 1 2 1");
	ADD(&s, "3 1 2 0 0");
	ADD(&s, "3 1 2 0 1");
	ADD(&s, "3 1 2 1 0");
	ADD(&s, "3 1 2 1 1");
	ADD(&s, "3 2 0 0 1");
	ADD(&s, "3 2 0 1 0");
	ADD(&s, "3 2 0 1 1");
	ADD(&s, "3 2 1 0 0");
	ADD(&s, "3 2 1 0 1");
	ADD(&s, "3 2 1 1 0");
	ADD(&s, "3 2 1 1 1");
	assert(disp_sequence_next_ok(&s));
	disp_delete(d);
}

#include "cmem.h"
void testpermutationrrep(void) {
	test_permrrep_new();
	test_permrrep_first();
	test_permrrep_last();
	test_permrrep_check();
	test_permrrep_next_elem();
	test_permrrep_sequence();
	/*
	test_permrrep_rand();
	test_permrrep_copy();
	*/
	cmem_info();
	printf("TODO\n");
}

