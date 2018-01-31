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

/* utility functions to write tests */

#include "commontestutil.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

void copy_vec(int *dst, int *src, int size) {
	int i;
	for (i = 0; i < size; i++)
		dst[i] = src[i];
}

int equal_vec(int *a, int *b, int size) {
	int i;
	for (i = 0; i < size; i++)
		if (a[i] != b[i]) return 0;
	return 1;
}

void fprint_vec(FILE *f, int *v, int size) {
	fprintf(f, "(");
	fprint_vec_sep(f, v, size, ", ");
	fprintf(f, ")\n");
}

void fprint_vec_sep(FILE *f, int *v, int size, const char *sep) {
	int i;
	if (size > 0)
		fprintf(f, "%d", v[0]);
	for (i = 1; i < size; i++)
		fprintf(f, "%s%d", sep, v[i]);
}

/* returns if the numbers in the string are equal than the size says or not: */
int str_to_vec(int *v, int size, char *str) {
	int i;
	long l;
	char *p, *q;
	for (i = 0, p = str; i < size; i++, p = q) {
		l = strtol(p, &q, 10);
		if (!(l < INT_MAX && l > INT_MIN) || q == p)
			return 0;
		v[i] = l;
	}
	if (*p != '\0') {
		l = strtol(p, &q, 10);
		if (p != q)
			return 0;
	}
	return 1;
}

int equal_vec_str(int *v, int size, char *str) {
	int i;
	long l;
	char *p, *q;
	for (i = 0, p = str; i < size; i++, p = q) {
		l = strtol(p, &q, 10);
		if (!(l < INT_MAX && l > INT_MIN) || q == p || v[i] != l)
			return 0;
	}
	if (*p != '\0') {
		l = strtol(p, &q, 10);
		if (p != q)
			return 0;
	}
	return 1;
}

int fset_seed(FILE *f, int seed, int printseed) {
	srand(seed);
	if (printseed)
		fprintf(f, "random seed: %d\n", seed);
	return seed;
}

