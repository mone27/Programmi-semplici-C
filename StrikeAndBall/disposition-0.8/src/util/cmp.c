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

/* simple version of the UNIX `cmp' command for use on non-UNIX systems */

#include <stdio.h>

typedef struct stCmpResult {
	size_t bytes, lines; /* bytes and lines read until the files differ */
	int ca, cb; /* last char read from the files */
} CmpResult;

/* returns 1 when the files are equal: */
int cmp_files(FILE *fa, FILE *fb, CmpResult *result) {
	int ca, cb;
	size_t bytes = 1, lines = 1;
	while (1) {
		ca = getc(fa);
		cb = getc(fb);
		if (ca == cb && ca != EOF) {
			bytes++;
			if (ca == '\n')
				lines++;
		}
		else break;
	}
	result->ca = ca;
	result->cb = cb;
	if (ca != cb && ca != EOF && cb != EOF) {
		result->bytes = bytes;
		result->lines = lines;
	}
	return (ca == cb);
}

/* #define IS_STDIN(s) (!strcmp((s), "-")) */
#define IS_STDIN(s) (*(s) == '-' && *((s) + 1) == '\0')

int main(int argc, char *argv[]) {
	int retval;
	char *na, *nb;
	CmpResult result;
	FILE *fa, *fb;
	if (argc == 1) { /* no arguments: */
		fprintf(stderr, "%s: missing operand after `%s'\n",
					argv[0], argv[0]);
		return 1;
	}
	else {
		na = argv[1];
		if (argc == 2)
			nb = "-";
		else
			nb = argv[2];
		if (IS_STDIN(na))
			fa = stdin;
		else if ((fa = fopen(na, "rb")) == NULL) {
			fprintf(stderr, "%s: %s: No such file or directory\n",
						argv[0], na);
			return 1;
		}
		if (IS_STDIN(nb))
			fb = stdin;
		else if ((fb = fopen(nb, "rb")) == NULL) {
			fprintf(stderr, "%s: %s: No such file or directory\n",
						argv[0], nb);
			if (!IS_STDIN(na))
				fclose(fa);
			return 1;
		}
		if (cmp_files(fa, fb, &result)) {
			retval = 0;
		}
		else {
			retval = 1;
			if (result.ca == EOF)
				fprintf(stderr, "%s: EOF on %s\n", argv[0], na);
			else if (result.cb == EOF)
				fprintf(stderr, "%s: EOF on %s\n", argv[0], nb);
			else
				fprintf(stdout,
					"%s %s differ: char %u, line %u\n",
					na, nb, result.bytes, result.lines);
		}
		if (!IS_STDIN(na))
			fclose(fa);
		if (!IS_STDIN(nb))
			fclose(fb);
		return retval;
	}
}

