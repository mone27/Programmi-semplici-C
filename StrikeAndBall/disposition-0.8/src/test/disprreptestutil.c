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

/* functions for testing dispositions with restricted repetition */

#include "disprreptestutil.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
int new_del_rrep_err(newDispRRepFunction newfunc, int numelem, int size,
			char *repstr, int ok, DispNewError err) {
	int repvec[MAXSIZE];
	Disposition *d;
	DispNewError e;
	if (repstr != NULL) {
		if (str_to_vec(repvec, numelem, repstr) == 0) return 0;
		d = newfunc(numelem, size, repvec, &e);
	}
	else
		d = newfunc(numelem, size, NULL, &e);
	if ((ok != 0) != (d != NULL)) return 0;
	if (e != err) return 0;
	/*
	printf("v: "); show_vec(disp_vec(d), disp_size(d));
	*/
	if (d != NULL) disp_delete(d);
	return 1;
}

int new_del_rrep_ok(DispStart start, newDispRRepFunction newfunc,
			int numelem, int size, char *repstr, char *vecstr) {
	int repvec[MAXSIZE];
	Disposition *d;
	if (repstr != NULL) {
		if (str_to_vec(repvec, numelem, repstr) == 0) return 0;
		d = newfunc(numelem, size, repvec, NULL);
	}
	else
		d = newfunc(numelem, size, NULL, NULL);
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

int next_elem_permrrep_ok(Disposition *d, elemPermRRepFunction elemfunc,
			char *vecstr, int ielem, int newval) {
	int i, val;
	if (str_to_vec(disp_vec(d), disp_size(d), vecstr) == 0)
		return 0;
	if (disp_check(d, NULL) != DISP_CHECK_OK) return 0;
	i = elemfunc(d, &val);
	if (i != ielem) return 0;
	if (i != -1 && val != newval) return 0;
	return 1;
}

int next_elem_combrrep_ok(Disposition *d, elemCombRRepFunction elemfunc,
			char *vecstr, int ielem) {
	int i;
	if (str_to_vec(disp_vec(d), disp_size(d), vecstr) == 0)
		return 0;
	if (disp_check(d, NULL) != DISP_CHECK_OK) return 0;
	i = elemfunc(d);
	if (i != ielem) return 0;
	return 1;
}

