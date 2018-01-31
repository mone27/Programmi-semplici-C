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

/* console program for generate dispositions */

#include "disposition.h"
#include "dispositionrrep.h"
#include "permutationcrep.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum eDispType {
	tNone,
	tPermutation, tPermutationRep,
	tCombination, tCombinationRep,
	tPermutationRRep, tCombinationRRep,
	tPermutationCRep
} DispType;

void print_help(void);
void print_err(const char *strerr, const char *progname);
void print_disp(Disposition *disp, char *chars);
char *gettypename(DispType type);
char *getnewerrorname(DispNewError error);
DispType get_disposition_type(const char *arg);
int has_repeated_chars(const char *arg);
void init_rrep_vectors(const char *arg, int *repvec, char *charvec,
					int vecsize, int *numelem);

#define NUMCHARS 256
#define MAXREPSIZE NUMCHARS
int main(int argc, char *argv[]) {
	char *chars, charvec[MAXREPSIZE];
	int numelem, size, repvec[MAXREPSIZE];
	int reverse, random, shift;
	DispNewError e;
	DispType t;
	Disposition *disp;
	argc--; /* not count the name of the program */
	if (argc == 0) {
		print_help();
		return 1;
	}
	/* optional parameter -v or -r: */
	reverse = random = shift = 0;
	if (strcmp(argv[1], "-v") == 0)
		reverse = shift = 1;
	else if (strcmp(argv[1], "-r") == 0)
		random = shift = 1;
	if (argc - shift < 2) {
		print_err("too few parameters", argv[0]);
		return 1;
	}
	t = get_disposition_type(argv[1 + shift]);
	if (t == tNone) {
		print_err("type must be one of these: -p|-pr|-c|-cr|-prr|-crr",
				argv[0]);
		return 1;
	}
	chars = argv[2 + shift];
	numelem = strlen(chars);
	if (argc - shift >= 3) /* if exists the SIZE parameter: */
		size = atoi(argv[3 + shift]);
	else size = numelem;
	if (t == tPermutationRRep && numelem == size)
		t = tPermutationCRep;
	switch (t) {
	case tPermutation: case tPermutationRep:
	case tCombination: case tCombinationRep:
		if (has_repeated_chars(chars)) {
		print_err("basic types can not have repeated characters",
				argv[0]);
			return 1;
		}
		disp = newDispositionBasic[((int) t) - ((int) tPermutation)]
						(numelem, size, &e);
		break;
	case tPermutationRRep:
	case tCombinationRRep:
		init_rrep_vectors(argv[2 + shift], repvec, charvec,
						MAXREPSIZE, &numelem);
		chars = charvec;
		disp = newDispositionRRep[((int) t) - ((int) tPermutationRRep)]
						(numelem, size, repvec, &e);
		break;
	case tPermutationCRep:
		init_rrep_vectors(argv[2 + shift], repvec, charvec,
						MAXREPSIZE, &numelem);
		chars = charvec;
		disp = newPermutationCRep(numelem, repvec, &e);
		break;
	case tNone:
	default:
		disp = NULL;
		break;
	}
	if (disp == NULL) {
		fprintf(stderr, "%s: error: %s: %s\n",
				argv[0], gettypename(t), getnewerrorname(e));
		fprintf(stderr, "Try `%s' for more information.\n", argv[0]);
		return 1;
	}
	if (random) {
		srand(time(NULL));
		do {
			disp_rand(disp);
			print_disp(disp, chars);
		} while (1);
	}
	else if (reverse) {
		disp_last(disp);
		do
			print_disp(disp, chars);
		while (disp_prev(disp));
	}
	else {
		disp_first(disp);
		do
			print_disp(disp, chars);
		while (disp_next(disp));
	}
	disp_delete(disp);
	return 0;
}

void print_err(const char *strerr, const char *progname) {
	fprintf(stderr, "%s: error: %s\n", progname, strerr);
	fprintf(stderr, "Try `%s' for more information.\n", progname);
}

DispType get_disposition_type(const char *arg) {
	if      (strcmp(arg, "-p")  == 0)  return tPermutation;
	else if (strcmp(arg, "-pr") == 0)  return tPermutationRep;
	else if (strcmp(arg, "-c")  == 0)  return tCombination;
	else if (strcmp(arg, "-cr") == 0)  return tCombinationRep;
	else if (strcmp(arg, "-prr") == 0)  return tPermutationRRep;
	else if (strcmp(arg, "-crr") == 0)  return tCombinationRRep;
	else return tNone;
}

int has_repeated_chars(const char *arg) {
	int i, chartable[NUMCHARS];
	for (i = 0; i < NUMCHARS; i++)
		chartable[i] = 0;
	for (i = 0; arg[i] != '\0'; i++)
		if (chartable[(unsigned char) arg[i]]++)
			return 1;
	return 0;
}

void init_rrep_vectors(const char *arg, int *repvec, char *charvec,
					int vecsize, int *numelem) {
	int i, chartable[NUMCHARS];
	for (i = 0; i < NUMCHARS; i++)
		chartable[i] = 0;
	for (i = 0, *numelem = 0; arg[i] != '\0'; i++)
		if (chartable[(unsigned char) arg[i]]++ == 0)
			charvec[(*numelem)++] = arg[i];
	for (i = 0; i < *numelem; i++)
		repvec[i] = chartable[(unsigned char) charvec[i]];
}

void print_disp(Disposition *disp, char *chars) {
	int i;
	for (i = 0; i < disp_size(disp); i++)
		putchar(chars[disp_vec(disp)[i]]);
	putchar('\n');
}

void print_help(void) {
fprintf(stderr,
	"`disp' prints permutations and combinations of characters.\n");
fprintf(stderr, "\n");
fprintf(stderr, "Usage: disp [-v|-r] TYPE CHARLIST [SIZE]\n");
fprintf(stderr, "\n");
fprintf(stderr, "TYPE must be one of these: -p|-pr|-c|-cr|-prr|-crr\n");
fprintf(stderr,
	"By default, the SIZE number is equal to the length of CHARLIST.\n");
fprintf(stderr, "\n");
fprintf(stderr, "-p        Permutations (nPk)\n");
fprintf(stderr, "-pr       Permutations with repetition (nPRk)\n");
fprintf(stderr, "-c        Combinations (nCk)\n");
fprintf(stderr, "-cr       Combinations with repetition (nCRk)\n");
fprintf(stderr, "-prr      Permutations with \"restricted\" repetition\n");
fprintf(stderr, "-crr      Combinations with \"restricted\" repetition\n");
fprintf(stderr,
	"CHARLIST  string with the n characters used in the dispositions\n");
fprintf(stderr,
	"SIZE      length k of every disposition, equal to n by default\n");
fprintf(stderr, "-v        output in reverse order\n");
fprintf(stderr, "-r        print only random dispositions\n");
fprintf(stderr, "\n");
fprintf(stderr,
	"For Permutations and Combinations with \"restricted\" repetition,\n");
fprintf(stderr,
	"characters in CHARLIST can be repeated to set the maximum number\n");
fprintf(stderr,
	"of times that each character can appear in the dispositions.\n");
fprintf(stderr, "\n");
/*
fprintf(stderr, "Examples:\n");
fprintf(stderr, "disp -p abc\n");
fprintf(stderr, "disp -pr 01 4\n");
fprintf(stderr, "disp -c aeiou 3\n");
fprintf(stderr, "disp -v -cr ABC 5\n");
fprintf(stderr, "disp -prr SISSI\n");
fprintf(stderr, "disp -crr aabbbcd 4\n");
fprintf(stderr, "\n");
*/
}

char *gettypename(DispType type) {
	char *s;
	switch (type) {
	case tPermutation:
		s = "permutations"; break;
	case tPermutationRep:
		s = "permutations with repetition"; break;
	case tCombination:
		s = "combinations"; break;
	case tCombinationRep:
		s = "combinations with repetition"; break;
	case tPermutationRRep:
		s = "permutations with restricted repetition"; break;
	case tCombinationRRep:
		s = "combinations with restricted repetition"; break;
	case tNone:
	default:
		s = NULL;
	}
	return s;
}

char *getnewerrorname(DispNewError error) {
	char *s = NULL;
	switch (error) {
	case DISP_NEW_OK:
		s = NULL; break;
	case DISP_NEW_NUMELEM_LT_ONE:
		s = "number of elements less than one"; break;
	case DISP_NEW_SIZE_LT_ZERO:
		s = "size less than zero"; break;
	case DISP_NEW_SIZE_GT_NUMELEM:
		s = "size greater than number of elements"; break;
	case DISP_NEW_MEMORY_ALLOCATION:
		s = "memory allocation failed"; break;
	}
	return s;
}

