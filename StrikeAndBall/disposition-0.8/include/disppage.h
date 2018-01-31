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

/* declarations for managing dispositions in pages */

#ifndef _DISPPAGE_H_
#define _DISPPAGE_H_

#include "idisposition.h"

/* field disp saves the disposition provided by the user when newDispPage()
 * was called, is returned by deleteDispPage(), and it's not changed by the
 * functions of the structure. It is for the user to move along the page: */
/* TODO: int *firstofpage, *lastofpage; Disposition *disp; */
typedef struct tDispPage {
	Disposition *firstofpage, *lastofpage, *disp;
	int currentpagesize, maxpagesize;
} DispPage;

DispPage *newDispPage(Disposition *disp, int maxpagesize);
Disposition *deleteDispPage(DispPage *page);
int nextDispPage(DispPage *page);
int prevDispPage(DispPage *page);
void firstDispPage(DispPage *page);
void lastDispPage(DispPage *page);

#endif

