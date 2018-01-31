# Makefile for the disposition library

CC=gcc
LINK=gcc
AR=ar
CP=cp -f
RM=rm -f
AFLAGS=-ansi -Wall -pedantic

# to compile final versions: before change the Makefile, run make veryclean
# the routines for tracking the allocated memory can be disabled (NCMEM)
# asserts can be disabled (NDEBUG), but must be enabled when compiling tests

## comment OFLAGS and DFLAGS to disable the optimizations and
## enable asserts and Cmem when compiling development versions:
OFLAGS=-O2
DFLAGS=-DNDEBUG -DNCMEM

## uncomment this to enable cmem.o when compiling development versions:
OBJ_CMEM_FILE=#obj/cmem/cmem.o

## set the correct script to test the program disp under other platforms:
TEST_DISP=src/test/testdisp.sh
#TEST_DISP=src/test/testdisp.bat

SLIB_DISP_NAME=libdisp.a
SLIB_DISP=lib/$(SLIB_DISP_NAME)
SLIB_DISP_FILE_INSTALL=$(LIB)/$(SLIB_DISP_NAME)

VERSION_NUMBER=0.8
DLIB_DISP_SONAME=libdisp.so.0
DLIB_DISP_NAME=$(DLIB_DISP_SONAME).$(VERSION_NUMBER)
DLIB_DISP=lib/$(DLIB_DISP_NAME)
DLIB_DISP_FILE_INSTALL=$(LIB)/$(DLIB_DISP_NAME)

## put the corresponding files to make the static library or the dynamic one,
## and uncomment -fpic to compile the shared library instead the static one:
## (dynamic library needs more commands, so now it does not work)
LIB_DISP_FILE=$(SLIB_DISP)
LIB_DISP_FILE_INSTALL=$(SLIB_DISP_FILE_INSTALL)
PICFLAG=#-fpic

# instalation directories:
LIB=/usr/local/lib
BIN=/usr/local/bin
INCLUDE=/usr/local/include

INCLUDE_FILES=include/idisposition.h \
		include/permutation.h include/combination.h \
		include/permutationcrep.h \
		include/permutationrep.h include/combinationrep.h \
		include/permutationrrep.h include/combinationrrep.h
INCLUDE_FILES_INSTALL=$(INCLUDE)/idisposition.h \
		$(INCLUDE)/permutation.h $(INCLUDE)/combination.h \
		$(INCLUDE)/permutationcrep.h \
		$(INCLUDE)/permutationrep.h $(INCLUDE)/combinationrep.h \
		$(INCLUDE)/permutationrrep.h $(INCLUDE)/combinationrrep.h

CFLAGS=$(AFLAGS) $(OFLAGS) $(DFLAGS) $(PICFLAG) -Isrc -Iinclude -Isrc/cmem

OBJ_COMMON_LIB=obj/dispcommon.o $(OBJ_CMEM_FILE)
OBJ_BASIC_LIB=obj/permutation.o obj/combination.o obj/permutationrep.o obj/combinationrep.o
OBJ_RREP_LIB=obj/permutationrrep.o obj/combinationrrep.o obj/permutationcrep.o
OBJ_LIB=$(OBJ_COMMON_LIB) $(OBJ_BASIC_LIB) $(OBJ_RREP_LIB)

OBJ_TEST_ONLY=obj/test/testpermutation.o obj/test/testcombination.o obj/test/testpermutationrep.o obj/test/testcombinationrep.o obj/test/testpermutationrrep.o obj/test/testcombinationrrep.o obj/test/testpermutationcrep.o obj/test/commontestutil.o obj/test/disptestutil.o obj/test/dispbasictestutil.o obj/test/dispcreptestutil.o obj/test/disprreptestutil.o
OBJ_TEST=$(OBJ_LIB) $(OBJ_TEST_ONLY)

OBJ_DISP=obj/disp.o
OBJ_EXAMPLE_ONLY=obj/disp.o obj/cmem/cmemfree.o
OBJ_CMEM_EXAMPLE=obj/cmem/cmemfree.o $(OBJ_CMEM_FILE)

OBJ_LC_COMMAND=obj/util/lc.o
OBJ_CMP_COMMAND=obj/util/cmp.o
OBJ_UTIL=$(OBJ_LC_COMMAND) $(OBJ_CMP_COMMAND)

OBJ_TESTDISPOSITION=$(OBJ_TEST) obj/test/testcommontestutil.o obj/test/testdisposition.o

DISP_NAME=disp
EXE_DISP=bin/$(DISP_NAME)
EXE_DISP_INSTALL=$(BIN)/$(DISP_NAME)
EXE_LC=bin/lc
EXE_CMP=bin/cmp
EXE_UTIL=$(EXE_LC) $(EXE_CMP)
EXE_TESTDISPOSITION=bin/testdisposition
EXE_TEST=$(EXE_TESTDISPOSITION)
EXE_CMEM_EXAMPLE=bin/cmemfree

.PHONY: all exe lib test clean veryclean \
		install install-dev uninstall uninstall-dev 

all: exe lib

exe: $(EXE_DISP) $(EXE_UTIL)

lib: $(LIB_DISP_FILE)

# clean:
clean:
	$(RM) $(OBJ_TESTDISPOSITION)
	$(RM) $(OBJ_EXAMPLE_ONLY) $(OBJ_UTIL)
	$(RM) $(EXE_TEST) $(EXE_CMEM_EXAMPLE)
veryclean: clean
	$(RM) $(EXE_DISP) $(EXE_UTIL)
	$(RM) $(SLIB_DISP) $(DLIB_DISP)

# objects:
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# programs:
$(EXE_DISP): $(OBJ_DISP) $(SLIB_DISP)
	$(LINK) -o $@ $^
$(EXE_CMEM_EXAMPLE): $(OBJ_CMEM_EXAMPLE)
	$(LINK) -o $@ $^
$(EXE_LC): $(OBJ_LC_COMMAND)
	$(LINK) -o $@ $^
$(EXE_CMP): $(OBJ_CMP_COMMAND)
	$(LINK) -o $@ $^

# library:
$(SLIB_DISP): $(OBJ_LIB)
	$(AR) rs $@ $^
$(DLIB_DISP): $(OBJ_LIB)
	$(LINK) -shared -Wl,-soname,$(LIB)/$(DLIB_DISP_SONAME) -o $@ $^

# tests:
$(EXE_TESTDISPOSITION): $(OBJ_TESTDISPOSITION)
	$(LINK) -o $@ $^
test: $(EXE_TEST) $(EXE_CMEM_EXAMPLE) $(EXE_DISP) $(EXE_UTIL) $(TEST_DISP)
	$(EXE_TESTDISPOSITION)
	$(TEST_DISP)

# install:
install: $(EXE_DISP)
	$(CP) $(EXE_DISP) $(BIN)
install-dev: $(LIB_DISP_FILE)
	$(CP) $(LIB_DISP_FILE) $(LIB)
	$(CP) $(INCLUDE_FILES) $(INCLUDE)
uninstall:
	$(RM) $(EXE_DISP_INSTALL)
uninstall-dev:
	$(RM) $(LIB_DISP_FILE_INSTALL)
	$(RM) $(INCLUDE_FILES_INSTALL)

