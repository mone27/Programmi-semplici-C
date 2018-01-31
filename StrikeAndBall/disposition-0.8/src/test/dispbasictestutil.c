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

/* utility functions to write tests for dispositions */

#include "dispbasictestutil.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256

int new_del_disp_err(newDispBasicFunction newfunc,
			int numelem, int size, DispNewError err) {
	Disposition *d;
	DispNewError e;
	d = newfunc(numelem, size, &e);
	if (d != NULL) disp_delete(d);
	if (e != err) return 0;
	return 1;
}

int new_del_disp_ok(DispStart start, newDispBasicFunction newfunc,
			int numelem, int size, char *vecstr) {
	Disposition *d;
	d = newfunc(numelem, size, NULL);
	if (d == NULL) return 0;
	switch (start) {
	case DISP_START_FIRST: disp_first(d); break;
	case DISP_START_LAST: disp_last(d); break;
	}
	if (!equal_disp_str(d, vecstr)) {
		disp_delete(d); return 0;
	}
	/*
	printf("v: "); show_vec(disp_vec(d), disp_size(d));
	*/
	disp_delete(d);
	return 1;
}

