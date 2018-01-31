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

/* Cmem - functions for tracking the amount of memory allocated by a program */
/* You must call to cmem_malloc() and cmem_free() instead malloc() and free() */

#ifndef __CMEM_H_
#define __CMEM_H_

#include <stdlib.h>

/* if true, a message is generated every time it allocates or frees memory: */ 
extern int cmem_messages;

/* if not NULL, it saves the messages in a file instead send them to stderr: */
extern char *cmem_messages_file;

/* if true, the program exits when a call to cmem_free() fails: */
extern int cmem_exit_on_error;

/* A declaration #define NCMEM before the #include <cmem.h> must
 * replace or disable the calls to the functions of Cmem: */
#ifdef NCMEM

#define cmem_malloc(s)               malloc(s)
#define cmem_free(p)                 free(p)
#define cmem_realloc(p, s)           realloc((p), (s))
#define cmem_enable_messages()       ((void) 0)
#define cmem_disable_messages()      ((void) 0)
#define cmem_enable_file(p)          ((void) 0)
#define cmem_disable_file(p)         ((void) 0)
#define cmem_enable_exit_on_error()  ((void) 0)
#define cmem_disable_exit_on_error() ((void) 0)
#define cmem_disable_file(p)         ((void) 0)
#define cmem_info()                  ((void) 0)
#define cmem_info_ext()              ((void) 0)

#else

#define cmem_enable_messages()  (cmem_messages = 1)
#define cmem_disable_messages() (cmem_messages = 0)
#define cmem_enable_file(f) (cmem_messages_file = (f))
#define cmem_disable_file() (cmem_messages_file = (NULL))
#define cmem_disable_exit_on_error() (cmem_exit_on_error = 0)
#define cmem_enable_exit_on_error() (cmem_exit_on_error = 1)

void *cmem_malloc(size_t);
void cmem_free(void *);
void *cmem_realloc(void *ptr, size_t size);
/* cmem_info() prints the summary of the total of allocated memory: */
void cmem_info(void);
/* cmem_info_ext() prints the ID and bytes allocated for every element: */
void cmem_info_ext(void);

#endif

#endif

