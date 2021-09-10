#*****************************************************
#  CS225 General Makefile
#
#  File originally written by Matt Buchanan in Fall 1995
#
#*****************************************************


#**************************************************************************
# List of .o files that EXENAME depends on.  Edit as appropriate for MP.

OBJS = \
	asserts.o intarrayiter.o main.o 


#**************************************************************************
# Change this line if you don't like 'a.out'.

EXENAME = simpleIter 


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

intarrayiter.o : intarrayiter.h intarrayiter.cpp asserts.h
	$(CC) -c $(CCOPTS) intarrayiter.cpp

main.o : main.cpp asserts.h intarrayiter.h
	$(CC) -c $(CCOPTS) main.cpp

