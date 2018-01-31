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

/* declarations for testing basic dispositions */

#ifndef _DISPBASICTESTUTIL_H_
#define _DISPBASICTESTUTIL_H_

#include "disptestutil.h"

typedef Disposition *(*newDispBasicFunction)(int numelem, int size,
						DispNewError *err);

#define new_del_disp_first_ok(f,m,n,s) new_del_disp_ok(DISP_START_FIRST,f,m,n,s)
#define new_del_disp_last_ok(f,m,n,s)  new_del_disp_ok(DISP_START_LAST,f,m,n,s)

int new_del_disp_err(newDispBasicFunction newfunc,
			int numelem, int size, DispNewError err);
int new_del_disp_ok(DispStart start, newDispBasicFunction newfunc,
			int numelem, int size, char *vecstr);

#endif

