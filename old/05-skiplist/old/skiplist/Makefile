#*****************************************************
#  CS225 General Makefile
#
#  File originally written by Matt Buchanan in Fall 1995
#
#*****************************************************


#**************************************************************************
# List of .o files that EXENAME depends on.  Edit as appropriate for MP.

OBJS = \
	asserts.o array.o skiplist.o main.o 

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

asserts.o : asserts.h asserts.cpp
	$(CC) -c $(CCOPTS) asserts.cpp

array.o : array.h array.cpp asserts.h
	$(CC) -c $(CCOPTS) array.cpp

skiplist.o : skiplist.h skiplist.cpp asserts.h array.h 
	$(CC) -c $(CCOPTS) skiplist.cpp

main.o : main.cpp skiplist.h
	$(CC) -c $(CCOPTS) main.cpp


