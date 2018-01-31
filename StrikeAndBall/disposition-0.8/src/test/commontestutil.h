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

/* declarations of the utility functions for write tests */

#ifndef _COMMONTESTUTIL_H_
#define _COMMONTESTUTIL_H_

#include <stdio.h>

void copy_vec(int *dst, int *src, int size);
int equal_vec(int *a, int *b, int size);
#define print_vec(v, size)           fprint_vec(stdout, (v), (size))
#define print_vec_sep(v, size, sep)  fprint_vec_sep(stdout, (v), (size), (sep))
void fprint_vec(FILE *f, int *v, int size);
void fprint_vec_sep(FILE *f, int *v, int size, const char *sep);
/* returns if the numbers in the string are equal than the size says or not: */
int str_to_vec(int *v, int size, char *str);
int equal_vec_str(int *v, int size, char *str);
#define set_seed(seed, printseed)  fset_seed(stdout, (seed), (printseed))
int fset_seed(FILE *f, int seed, int printseed);

#endif

