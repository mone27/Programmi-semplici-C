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

/* simple version of the UNIX `wc -l' command for use on non-UNIX systems */

#include <stdio.h>

size_t count_lines(FILE *file) {
	int c;
	size_t lines = 0;
	while ((c = getc(file)) != EOF)
		if (c == '\n')
			lines++;
	return lines;
}

/* #define IS_STDIN(s) (!strcmp((s), "-")) */
#define IS_STDIN(s) (*(s) == '-' && *((s) + 1) == '\0')

int main(int argc, char *argv[]) {
	int i, retval = 0;
	size_t lines, total = 0;
	FILE *file;
	if (argc == 1) /* no arguments: */
		fprintf(stdout, "%7u\n", count_lines(stdin));
	else {
		for (i = 1; i < argc; i++) {
			if (IS_STDIN(argv[i])) {
				fprintf(stdout, "%7u -\n",
						lines = count_lines(stdin));
				total += lines;
			}
			else if ((file = fopen(argv[i], "rb")) == NULL) {
				fprintf(stderr,
					"%s: %s: No such file or directory\n",
						argv[0], argv[i]);
				retval = 1;
			}
			else {
				fprintf(stdout, "%7u %s\n",
						lines = count_lines(file),
						argv[i]);
				fclose(file);
				total += lines;
			}
		}
		if (argc > 2)
			fprintf(stdout, "%7u %s\n", total, "total");
	}
	return retval;
}

