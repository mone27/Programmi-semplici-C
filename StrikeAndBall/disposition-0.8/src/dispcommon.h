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

/* declarations of internal functions for dispositions */

#ifndef _DISPOSITIONCOMMON_H_
#define _DISPOSITIONCOMMON_H_

#include "idisposition.h"
#include <stdlib.h>

#define RAND_1N(n) ((rand() % (n)) + 1)
#define RAND_0N(n) (rand() % ((n) + 1))
Disposition *allocDisposition(int dispsize, size_t datasize);
void freeDisposition(Disposition *disp);
Disposition *copyDisposition(Disposition *disp, size_t datasize);

#endif

