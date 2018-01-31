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

/* examples of common free errors detected by Cmem: */

#include <stdio.h>
#include <stdlib.h>
#include "cmem.h"

int main(void) {
	int cas;
	/*
	cmem_enable_messages();
	cmem_enable_file("cmemfree.txt");
	*/
	cmem_disable_exit_on_error();
	for (cas = 1; cas <= 6; cas++) {
	switch (cas) {
	case 1:
		{
			int *p;
			fprintf(stdout,
			"trying to free a pointer not initializated...\n");
			cmem_free(p);
		}
		break;
	case 2:
		{
			int *p = (int *) 222222;
			fprintf(stdout,
			"trying to free a pointer with a random value...\n");
			cmem_free(p);
		}
		break;
	case 3:
		{
			int *p = NULL;
			fprintf(stdout, "trying to free a NULL pointer...\n");
			cmem_free(p);
		}
		break;
	case 4:
		{
			int i, *p;
			p = &i;
			fprintf(stdout,
				"trying to free an automatic variable...\n");
			cmem_free(p);
		}
		break;
	case 5:
		{
			int *p;
			p = (int *) cmem_malloc(sizeof(int) * 5);
			cmem_free(p);
			fprintf(stdout,
		"trying to free a pointer to memory already freed...\n");
			cmem_free(p);
		}
		break;
	case 6:
		{
			int *p;
			p = (int *) cmem_malloc(sizeof(int) * 5);
			fprintf(stdout, "trying to free a pointer to a position not at the start of the block...\n");
			cmem_free(p + 3);
		}
		break;
	default:
		break;
	} /* switch */
	} /* for */
	return 0;
}

