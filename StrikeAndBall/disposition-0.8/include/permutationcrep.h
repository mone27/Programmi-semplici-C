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

/* declarations for permutations with constant repetition */

#ifndef _PERMUTATIONCREP_H_
#define _PERMUTATIONCREP_H_

#include "idisposition.h"

typedef Disposition PermutationCRep;

PermutationCRep *newPermutationCRep(int numelem, int *repvec,
					DispNewError *err);
PermutationCRep *newPermutationCRepNoVector(int numelem, int *repvec,
						DispNewError *err);
void firstPermutationCRep(PermutationCRep *perm);
void lastPermutationCRep(PermutationCRep *perm);
int nextPermutationCRep(PermutationCRep *perm);
int previousPermutationCRep(PermutationCRep *perm);
DispCheckError checkPermutationCRep(PermutationCRep *perm, int *errpos);
PermutationCRep *copyPermutationCRep(PermutationCRep *perm);
void randPermutationCRep(PermutationCRep *perm);
void deletePermutationCRep(PermutationCRep *perm);

#endif

