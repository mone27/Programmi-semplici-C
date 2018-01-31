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

/* declarations for testing dispositions with restricted repetition */

#ifndef _DISPRREPTESTUTIL_H_
#define _DISPRREPTESTUTIL_H_

#include "disptestutil.h"

typedef Disposition *(*newDispRRepFunction)(int numelem, int size,
					int *repvec, DispNewError *err);

#define new_del_rrep_first_ok(f,m,n,s,v) \
			new_del_rrep_ok(DISP_START_FIRST,f,m,n,s,v)
#define new_del_rrep_last_ok(f,m,n,s,v)  \
			new_del_rrep_ok(DISP_START_LAST,f,m,n,s,v)

#define new_disp_rrep_str(d, v, newfunc, num, size, str) \
		(str_to_vec(v, num, str) != 0 \
	 	&& (d = newfunc(num, size, v, NULL)) != NULL)

int new_del_rrep_err(newDispRRepFunction newfunc, int numelem, int size,
			char *repstr, int ok, DispNewError err);
int new_del_rrep_ok(DispStart start, newDispRRepFunction newfunc,
			int numelem, int size, char *repstr, char *vecstr);

typedef int (*elemPermRRepFunction)(Disposition *d, int *newval);
typedef int (*elemCombRRepFunction)(Disposition *d);
int next_elem_permrrep_ok(Disposition *d, elemPermRRepFunction elemfunc,
			char *vecstr, int ielem, int newval);
int next_elem_combrrep_ok(Disposition *d, elemCombRRepFunction elemfunc,
			char *vecstr, int ielem);

#endif

