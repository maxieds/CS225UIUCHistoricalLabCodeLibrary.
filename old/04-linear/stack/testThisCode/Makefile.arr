#*****************************************************
#  CS225 General Makefile
#
#  File originally written by Matt Buchanan in Fall 1995
#
#*****************************************************


#**************************************************************************
# List of .o files that EXENAME depends on.  Edit as appropriate for MP.

OBJS = \
	asserts.o array.o array-implemented-stack.o stackTest.o 

#**************************************************************************
# Change this line if you don't like 'a.out'.

EXENAME = a.out


#**************************************************************************
# Macros defining the C/C++ compiler and linker.

CC = CC
CCOPTS = -g 
LINK = CC
LINKOPTS =


#**************************************************************************
# Rules for building EXENAME from OBJS and OBJS from your source.

$(EXENAME):  $(OBJS)
	$(LINK) $(LINKOPTS) $(OBJS)

clean:
	-rm *.o $(EXENAME)
	-rm -rf SunWS_cache

asserts.o : asserts.h asserts.C
	$(CC) -c $(CCOPTS) asserts.C

array.o : array.h array.C asserts.h
	$(CC) -c $(CCOPTS) array.C

array-implemented-stack.o : array-implemented-stack.h \
	array-implemented-stack.C array.h array.C asserts.h
	$(CC) -c $(CCOPTS) array-implemented-stack.C

stackTest.o : stackTest.C array-implemented-stack.h array-implemented-stack.C
	$(CC) -c $(CCOPTS) stackTest.C


