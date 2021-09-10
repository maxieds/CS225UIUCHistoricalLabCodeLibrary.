#*****************************************************
#  CS225 General Makefile
#
#  File originally written by Matt Buchanan in Fall 1995
#
#*****************************************************


#**************************************************************************
# List of .o files that EXENAME depends on.  Edit as appropriate for MP.

OBJS = \
	asserts.o singly-linked-stack.o stackTest.o 

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

singly-linked-stack.o : singly-linked-stack.h singly-linked-stack.C asserts.h
	$(CC) -c $(CCOPTS) singly-linked-stack.C

stackTest.o : stackTest.C singly-linked-stack.h singly-linked-stack.C 
	$(CC) -c $(CCOPTS) stackTest.C


