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

/* interface of the different types of dispositions */

#ifndef _IDISPOSITION_H_
#define _IDISPOSITION_H_

#define disp_size(d)     ((d)->dispsize)
#define disp_numelem(d)  ((d)->dispnumelem)
#define disp_vec(d)      ((d)->dispvec)

/* Warning! the first argument of these macros is evaluated two times: */
#define disp_first(d)    ((d)->dispfunc->first(d))
#define disp_last(d)     ((d)->dispfunc->last(d))
#define disp_check(d,p)  ((d)->dispfunc->check(d,p))
#define disp_copy(d)     ((d)->dispfunc->copy(d))
#define disp_next(d)     ((d)->dispfunc->next(d))
#define disp_prev(d)     ((d)->dispfunc->prev(d))
#define disp_rand(d)     ((d)->dispfunc->rand(d))
#define disp_delete(d)   ((d)->dispfunc->del(d))

#include <string.h>
#define disp_set(d,v)  memcpy(disp_vec(d), (v), sizeof(int) * disp_size(d))

/* Warning! fields must not be changed by the user: */
struct tDispFunctions;
typedef struct tDisposition {
	int dispsize, dispnumelem;
	int *dispvec;
	struct tDispFunctions *dispfunc;
	void *dispdata;
} Disposition;

typedef enum eDispNewError {
	DISP_NEW_OK,
	DISP_NEW_NUMELEM_LT_ONE,
	DISP_NEW_SIZE_LT_ZERO,
	DISP_NEW_SIZE_GT_NUMELEM,
	DISP_NEW_MEMORY_ALLOCATION
} DispNewError;

typedef enum eDispCheckError {
	DISP_CHECK_OK,
	DISP_CHECK_OK_ELEM_UNSORTED,
	DISP_CHECK_ELEM_OUT_OF_RANGE,
	DISP_CHECK_ELEM_REPEATED
} DispCheckError;

typedef struct tDispFunctions {
	void (*first)(Disposition *disp);
	void (*last)(Disposition *disp);
	int (*next)(Disposition *disp);
	int (*prev)(Disposition *disp);
	DispCheckError (*check)(Disposition *disp, int *errpos);
	Disposition *(*copy)(Disposition *disp);
	void (*rand)(Disposition *disp);
	void (*del)(Disposition *disp);
} DispFunctions;

#endif

