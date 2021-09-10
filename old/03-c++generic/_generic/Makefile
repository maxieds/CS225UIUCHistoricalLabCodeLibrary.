#*****************************************************
#  CS225 General Makefile
#
#  File originally written by Matt Buchanan in Fall 1995
#
#*****************************************************


#**************************************************************************
# List of .o files that EXENAME depends on.  Edit as appropriate for MP.

OBJS = \
	asserts.o vector225.o name.o string.o generic.o main.o 


#**************************************************************************
# Change this line if you don't like 'a.out'.

EXENAME = genFunTest


#**************************************************************************
# Macros defining the C/C++ compiler and linker.

CC = CC
CCOPTS = -g 
LINK = CC
LINKOPTS = -o $(EXENAME)


#**************************************************************************
# Rules for building EXENAME from OBJS and OBJS from your source.

$(EXENAME):  $(OBJS)
	$(LINK) $(LINKOPTS) $(OBJS)

clean:
	-rm *.o $(EXENAME)
	-rm -rf SunWS_cache

asserts.o : asserts.h asserts.cpp
	$(CC) -c $(CCOPTS) asserts.cpp

vector225.o : vector225.h vector225.cpp asserts.h
	$(CC) -c $(CCOPTS) vector225.cpp

name.o : name.h name.cpp 
	$(CC) -c $(CCOPTS) name.cpp 

string.o : string.h string.cpp
	$(CC) -c $(CCOPTS) string.cpp

generic.o : generic.h generic.cpp name.h
	$(CC) -c $(CCOPTS) generic.cpp

main.o : main.cpp asserts.h vector225.h name.h string.h
	$(CC) -c $(CCOPTS) main.cpp

