#*****************************************************
#  CS225 General Makefile
#
#  File originally written by Matt Buchanan in Fall 1995
#
#*****************************************************


#**************************************************************************
# List of .o files that EXENAME depends on.  Edit as appropriate for MP.

OBJS = \
	asserts.o list225.o string.o listTestUtil.o main.o 


#**************************************************************************
# Change this line if you don't like 'a.out'.

EXENAME = listTest


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

list225.o : list225.h list225.cpp asserts.h
	$(CC) -c $(CCOPTS) list225.cpp

string.o : string.h string.cpp asserts.h
	$(CC) -c $(CCOPTS) string.cpp

listTestUtil.o : listTestUtil.h listTestUtil.cpp list225.h string.h
	$(CC) -c $(CCOPTS) listTestUtil.cpp

main.o : main.cpp asserts.h list225.h string.h listTestUtil.h
	$(CC) -c $(CCOPTS) main.cpp

