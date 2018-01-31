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

/* Cmem - functions for tracking the memory allocated by a program */
/* You must call to cmem_malloc() and cmem_free() instead malloc() and free() */

#include "cmem.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* if true, a message is generated every time it allocates or frees memory: */ 
int cmem_messages = 0;

/* if not NULL, it saves the messages in a file instead send them to stderr: */
char *cmem_messages_file = NULL;

/* if true, the program exits when a call to cmem_free() fails: */
int cmem_exit_on_error = 1;

/* remove the functions to replace them with the macros of the header: */
#ifndef NCMEM

/* these functions allocate blocks (vectors) of elements that are stacked
 * in a linked list of blocks, never freed, from which the elements are
 * taken to use them as needed, inserting them in the linked list of
 * allocated elements when memory is allocated, or returning them back to
 * the linked list of free elements when memory is freed. */

/* element of allocated memory: */
struct cmemelem {
	size_t id, size;
	void *ptr;
	struct cmemelem *next;
};

/* block of elements: */
struct cmemblock {
	struct cmemelem *velem;
	struct cmemblock *next;
};

/* global data structure: */
struct cmemdat {
	size_t countid, totalbytes;
	struct cmemblock *listblocks;
	unsigned int numblocks;
	/* number of elements of the last block of the list:
	 * (previous blocks never have free elements) */
	size_t maxelemlastb, numelemlastb;
	struct cmemelem *listalloc, *listfree;
	size_t numalloc, numfree;
	FILE *fp;
} cmem = { 0, 0, NULL, 0, 0, 0, NULL, NULL, 0, 0, NULL };

/* internal functions must be declared before its use: */
void *cmemfind(void *ptr);
int cmemdel(void *);
void insblock(void);
void cmemins(void *, size_t);
void cmeminfostruct(void);
void cmemtest(void);
void cmemopenfile(void);
void cmemclosefile(void);

void *cmem_malloc(size_t size) {
	void *p = malloc(size);
	if (p != NULL) cmemins(p, size);
	return p;
}

void cmem_free(void *ptr) {
	if (cmemdel(ptr))
		free(ptr);
}

void *cmem_realloc(void *ptr, size_t size) {
	void *p = realloc(ptr, size);
	if (p != NULL) {
		if (ptr != NULL) cmemdel(ptr);
		cmemins(p, size);
	} else if (size == 0)
		cmemdel(ptr);
	return p;
}

void cmemopenfile(void) {
	assert(cmem.fp == NULL);
	if (cmem_messages_file != NULL)
		if ((cmem.fp = fopen(cmem_messages_file, "a")) == NULL)
			fprintf(stderr, "\ncmem: unable to open file: \"%s\"\n",
							cmem_messages_file);
	if (cmem.fp == NULL)
		cmem.fp = stderr;
}

void cmemclosefile(void) {
	assert(cmem.fp != NULL);
	if (cmem.fp != stderr)
		fclose(cmem.fp);
	cmem.fp = NULL;
}

/* cmem_info() prints the summary of the total of allocated memory: */
void cmem_info(void) {
	cmemopenfile();
	fprintf(cmem.fp, "\t[mem: %d bytes (%d elem)]\n", cmem.totalbytes,
							cmem.numalloc);
	cmemclosefile();
}

/* cmem_info_ext() prints the ID and bytes allocated for every element: */
void cmem_info_ext(void) {
	size_t i;
	struct cmemelem *elem;
	cmemopenfile();
	for (elem = cmem.listalloc, i = 1; elem != NULL; elem = elem->next, i++)
		fprintf(cmem.fp, "\t%d. %d bytes (id %d)\n", i,
						elem->size, elem->id);
	cmemclosefile();
	cmem_info();
}

/* cmeminfostruct() prints the total of allocated memory for the structure: */
void cmeminfostruct(void) {
	size_t numelems;
	cmemtest(); /* test to check the structure */
	cmemopenfile();
	numelems = cmem.numalloc + cmem.numfree +
				(cmem.maxelemlastb - cmem.numelemlastb);
	fprintf(cmem.fp,
		"\t[cmem: %d bytes (%d elems x %d + %d blocks x %d)]\n",
			(sizeof(struct cmemelem) * numelems) +
				(sizeof(struct cmemblock) * cmem.numblocks),
			numelems, sizeof(struct cmemelem),
			cmem.numblocks, sizeof(struct cmemblock));
	cmemclosefile();
}

void *cmemfind(void *ptr) {
	struct cmemelem *p;
	/* finds if the address is inside a block: */
	for (p = cmem.listalloc; p != NULL; p = p->next)
		if ((char *) ptr > (char *) p->ptr
				&& (char *) ptr < (char *) (p->ptr) + p->size)
			return p->ptr;
	return NULL;
}

int cmemdel(void *ptr) {
	struct cmemelem aux, *p, *tmp;
	void *start;
	/* inserts an auxiliary element as header of the list: */
	aux.next = cmem.listalloc;
	/* finds the element in the list saving a pointer to the previous: */
	for (p = &aux; p->next != NULL && p->next->ptr != ptr; p = p->next);
	if (p->next == NULL) {
		cmemopenfile();
		fprintf(cmem.fp, "\ncmem: free() incorrect: ");
		if (ptr != NULL) {
			/* find if the address is inside a block: */
			start = cmemfind(ptr);
			if (start == NULL)
				fprintf(cmem.fp, "%p NOT allocated.\n", ptr);
			else {
				fprintf(cmem.fp, "%p NOT allocated: ", ptr);
				fprintf(cmem.fp, "inside the block %p.\n",
								start);
			}
		}
		else
			fprintf(cmem.fp, "NULL pointer.\n");
		cmemclosefile();
		if (cmem_exit_on_error)
			exit(1);
		else
			return 0;
	}
	tmp = p->next;
	/* extracts the element from the allocated element's list
	 * and inserts it in the freed element's list: */
	if (p != &aux)
		p->next = tmp->next;
	else /* if the element found is the first or there are no elements: */
		cmem.listalloc = tmp->next;
	tmp->next = cmem.listfree;
	cmem.listfree = tmp;
	cmem.numalloc--;
	cmem.numfree++;
	cmem.totalbytes -= tmp->size;
	if (cmem_messages) {
		cmemopenfile();
		fprintf(cmem.fp, "\n\t%d bytes freed (id %d)\n",
							tmp->size, tmp->id);
		cmemclosefile();
	}
	if (cmem_messages)
		cmem_info();
	return 1;
}

/* allocates a new block of elements: */
void insblock(void) {
	struct cmemblock *block;
	block = (struct cmemblock *) malloc(sizeof(struct cmemblock));
	assert(block != NULL);
	cmem.maxelemlastb = (cmem.maxelemlastb > 0 ? 2 * cmem.maxelemlastb : 1);
	block->velem = (struct cmemelem *) malloc(sizeof(struct cmemelem) *
							cmem.maxelemlastb);
	assert(block->velem != NULL);
	block->next = cmem.listblocks;
	cmem.listblocks = block;
	cmem.numelemlastb = 0;
	cmem.numblocks++;
}

void cmemins(void *ptr, size_t size) {
	struct cmemelem *tmp;
	if (cmem.numfree > 0) {
		/* if there are elements in the list of freed elements,
		 * then it uses the first element from that list: */
		tmp = cmem.listfree;
		cmem.listfree = tmp->next;
		cmem.numfree--;
	} else {
		/* if there are no elements available in the last block,
		 * then it inserts a new block: */
		if (cmem.numelemlastb == cmem.maxelemlastb)
			insblock();
		/* uses the last element from the last block: */
		tmp = cmem.listblocks->velem + cmem.numelemlastb;
		cmem.numelemlastb++;
	}
	/* initializes the element and inserts it in the list of allocated: */
	tmp->id = cmem.countid++;
	tmp->ptr = ptr;
	tmp->size = size;
	tmp->next = cmem.listalloc;
	cmem.listalloc = tmp;
	cmem.numalloc++;
	cmem.totalbytes += size;
	if (cmem_messages) {
		cmemopenfile();
		fprintf(cmem.fp, "\n\t%d bytes allocated (id %d)\n",
							tmp->size, tmp->id);
		cmemclosefile();
	}
	if (cmem_messages)
		cmem_info();
}

/* performs some checks to verify the integrity of the structure: */
void cmemtest(void) {
	size_t i, sum, pow;
	struct cmemelem *elem;
	for (elem = cmem.listalloc, i = sum = 0; elem != NULL;
				sum += elem->size, elem = elem->next, i++);
	assert(i == cmem.numalloc);
	assert(sum == cmem.totalbytes);
	for (elem = cmem.listfree, i = 0; elem != NULL; elem = elem->next, i++);
	assert(i == cmem.numfree);
	sum = pow = 0;
	if (cmem.numblocks > 0)
		for (i = 1, sum = pow = 1; i < cmem.numblocks;
						i++, pow *= 2, sum += pow);
	assert(cmem.maxelemlastb == pow);
	assert(cmem.numalloc + cmem.numfree +
			(cmem.maxelemlastb - cmem.numelemlastb) == sum);
}

#endif

