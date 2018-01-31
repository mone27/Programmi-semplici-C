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

/* functions for testing permutations with constant repetition */

#include "dispcreptestutil.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
int new_del_crep_err(newDispCRepFunction newfunc, int numelem,
			char *repstr, int ok, DispNewError err) {
	int repvec[MAXSIZE];
	Disposition *d;
	DispNewError e;
	if (repstr != NULL) {
		if (str_to_vec(repvec, numelem, repstr) == 0) return 0;
		d = newfunc(numelem, repvec, &e);
	}
	else
		d = newfunc(numelem, NULL, &e);
	if ((ok != 0) != (d != NULL)) return 0;
	if (e != err) return 0;
	/*
	printf("v: "); show_vec(disp_vec(d), disp_size(d));
	*/
	if (d != NULL) disp_delete(d);
	return 1;
}

int new_del_crep_ok(DispStart start, newDispCRepFunction newfunc,
			int numelem, char *repstr, char *vecstr) {
	int repvec[MAXSIZE];
	Disposition *d;
	if (repstr != NULL) {
		if (str_to_vec(repvec, numelem, repstr) == 0) return 0;
		d = newfunc(numelem, repvec, NULL);
	}
	else
		d = newfunc(numelem, NULL, NULL);
	if (d == NULL) return 0;
	switch (start) {
	case DISP_START_FIRST: disp_first(d); break;
	case DISP_START_LAST: disp_last(d); break;
	}
	if (!equal_disp_str(d, vecstr)) {
		disp_delete(d); return 0;
	}
	disp_delete(d);
	return 1;
}

int copy_disprep_ok(Disposition *d) {
	Disposition *copy;
	if (copy_disp_ok(d) == 0)
		return 0;
	copy = disp_copy(d);
	if (copy->dispdata == NULL || d->dispdata == NULL) {
		if (copy->dispdata != d->dispdata)
			return 0;
	}
	else if (!equal_vec(copy->dispdata, d->dispdata, disp_numelem(d)))
		return 0;
	disp_delete(copy);
	return 1;
}

