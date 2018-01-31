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

/* functions for managing dispositions in pages */

#include "disppage.h"
#include "cmem.h"
#include <stdlib.h>

DispPage *newDispPage(Disposition *disp, int maxpagesize) {
	DispPage *page;
	if (disp == NULL) return NULL;
	if (maxpagesize <= 0)
		return NULL;
	page = (DispPage *) cmem_malloc(sizeof(DispPage));
	if (page == NULL) return NULL;
	page->firstofpage = disp_copy(disp);
	if (page->firstofpage == NULL) {
		cmem_free(page);
		return NULL;
	}
	page->lastofpage  = disp_copy(disp);
	if (page->lastofpage == NULL) {
		disp_delete(page->firstofpage);
		cmem_free(page);
		return NULL;
	}
	page->currentpagesize = 1;
	page->maxpagesize = maxpagesize;
	page->disp = disp;
	return page;
}

Disposition *deleteDispPage(DispPage *page) {
	Disposition *disp;
	disp_delete(page->firstofpage); page->firstofpage = NULL;
	disp_delete(page->lastofpage); page->lastofpage = NULL;
	disp = page->disp; page->disp = NULL;
	cmem_free(page);
	return disp;
}

int nextDispPage(DispPage *page) {
	int i, enter;
	if (!disp_next(page->lastofpage))
		return 0;
	disp_set(page->firstofpage, disp_vec(page->lastofpage));
	for (i = 1, enter = 1; i < page->maxpagesize && enter; i++)
		enter = disp_next(page->lastofpage);
	page->currentpagesize = i;
	return 1;
}

int prevDispPage(DispPage *page) {
	int i, enter;
	if (!disp_prev(page->firstofpage))
		return 0;
	disp_set(page->lastofpage, disp_vec(page->firstofpage));
	for (i = 1, enter = 1; i < page->maxpagesize && enter; i++)
		enter = disp_prev(page->firstofpage);
	page->currentpagesize = i;
	return 1;
}

void firstDispPage(DispPage *page) {
	int i, enter;
	disp_first(page->firstofpage);
	disp_first(page->lastofpage);
	for (i = 1, enter = 1; i < page->maxpagesize && enter; i++)
		enter = disp_next(page->lastofpage);
	page->currentpagesize = i;
}

void lastDispPage(DispPage *page) {
	int i, enter;
	disp_last(page->lastofpage);
	disp_last(page->firstofpage);
	for (i = 1, enter = 1; i < page->maxpagesize && enter; i++)
		enter = disp_prev(page->firstofpage);
	page->currentpagesize = i;
}

