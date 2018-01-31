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

/* tests for the common functions used in tests */

#include "commontestutil.h"
#include <assert.h>
#include <stdio.h>

#define I5(v,n0,n1,n2,n3,n4) (v[0]=(n0),v[1]=(n1),v[2]=(n2),v[3]=(n3),v[4]=(n4))
void test_str_to_vec(void) {
	int v[5], w[5], n, m, ok;
	char *str;
	m = 5;
	/* checks the returned value and if the vector is filled correctly: */
	I5(v,2,2,2,2,2); I5(w,3,3,3,3,2); str = "3 3 3 3"; n = 4;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,1,1,1,1,1); I5(w,2,2,2,1,1); str = "2 2 2"; n = 3;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,5,5,5,5,5); I5(w,7,7,5,5,5); str = "7 7"; n = 2;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,8,8,8,8,8); I5(w,9,8,8,8,8); str = "9"; n = 1;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,6,6,6,6,6); I5(w,6,6,6,6,6); str = ""; n = 0;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,2,2,2,2,2); I5(w,3,3,3,3,2); str = "      3 3   3  3 "; n = 4;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,1,1,1,1,1); I5(w,2,2,2,1,1); str = "2           2  2   "; n = 3;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,5,5,5,5,5); I5(w,7,7,5,5,5); str = "    7 7"; n = 2;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,8,8,8,8,8); I5(w,9,8,8,8,8); str = "         9"; n = 1;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
	I5(v,6,6,6,6,6); I5(w,6,6,6,6,6); str = "         "; n = 0;
	ok = str_to_vec(v, n, str); assert(ok && equal_vec(v, w, m));
}

void test_equal_vec_str(void) {
	int v[] = { 2,2,2,2,2 }, n;
	int w[] = { 5,3,2,4,1 }, m;
	n = sizeof(v) / sizeof(int);
	m = sizeof(w) / sizeof(int);
	I5(v, 2,2,2,2,2); assert(1 == equal_vec_str(v, n, "2 2 2 2 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 2 2 0"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 2 0 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "0 2 2 2 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 2 2 2 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 2 2 2 0"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 2 2 0 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "0 2 2 2 2 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 2 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 2 0"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2 2 0 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "0 2 2 2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "2"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, "0"));
	I5(v, 2,2,2,2,2); assert(0 == equal_vec_str(v, n, ""));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, m, "5 3 2 4 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 4 4"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 1 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 4 0"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 0 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 4 1 0"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 4 1 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 4 1 6"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 4"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5 3 2 0"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "5"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, "0"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, m, ""));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 0, ""));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 1, "5"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 2, "5 3"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 3, "5 3 2"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 4, "5 3 2 4"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 5, "5 3 2 4 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, 6, "5 3 2 4 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w,99, "5 3 2 4 1"));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w,88, "5 3 2 4 1 1 1"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 0, "     "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 1, " 5"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 1, "5 "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 1, " 5 "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 1, "  5   "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 2, " 5 3"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 2, "5 3 "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 2, " 5 3 "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 2, "  5   3    "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 3, " 5 3 2"));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 3, "5 3 2 "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 3, " 5 3 2 "));
	I5(w, 5,3,2,4,1); assert(1 == equal_vec_str(w, 3, "  5   3    2     "));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, 3, "  5   3    "));
	I5(w, 5,3,2,4,1); assert(0 == equal_vec_str(w, 3, "  5   3  2 4"));
}

void testcommontestutil(void) {
	test_str_to_vec();
	test_equal_vec_str();
}

