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

/* declarations for testing dispositions with constant repetition */

#ifndef _DISPCREPTESTUTIL_H_
#define _DISPCREPTESTUTIL_H_

#include "disptestutil.h"

typedef Disposition *(*newDispCRepFunction)(int numelem, int *repvec,
						DispNewError *err);

#define new_disp_crep_str(d, v, newfunc, num, str) \
		(str_to_vec(v, num, str) != 0 \
	 	&& (d = newfunc(num, v, NULL)) != NULL)
#define new_disp_crep_str_null(d, newfunc, num) \
	 	((d = newfunc(num, NULL, NULL)) != NULL)

#define new_del_crep_first_ok(f,m,s,v) \
			new_del_crep_ok(DISP_START_FIRST,f,m,s,v)
#define new_del_crep_last_ok(f,m,s,v)  \
			new_del_crep_ok(DISP_START_LAST,f,m,s,v)

int new_del_crep_err(newDispCRepFunction newfunc, int numelem,
			char *repstr, int ok, DispNewError err);
int new_del_crep_ok(DispStart start, newDispCRepFunction newfunc,
			int numelem, char *repstr, char *vecstr);
int copy_disprep_ok(Disposition *d);

#endif

