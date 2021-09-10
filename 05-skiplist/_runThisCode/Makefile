#*************************************************************************
#  CS225 General Makefile
#*************************************************************************

#*************************************************************************
# To begin our Makefile, we want to create various helpful macros.
#
# First of all, we need to name our program. The "executable file" is the 
# actual program -- all the individual compiled files linked together.

NAME_OF_EXECUTABLE_FILE = skiplistTest

# Next, we want to define which C++ compiler we are using and what options
# we are using for that compiler. 

COMPILER = CC
COMPILER_OPTS = -c -g

# Next, we want to define which program we are using to link all our
# files together (often, we are using the compiler we used to compile them
# in the first place) and what options we are using for that linker.

LINKER = CC
LINKER_OPTS = -o $(NAME_OF_EXECUTABLE_FILE)

# Finally, we want a list of all the .o files (object files) that 
# NAME_OF_EXECUTABLE_FILE depends on. That is, we want a list of all 
# the object files that make up the program. 

OBJS = asserts.o array.o skiplist.o main.o

# And that is it for the macros; we now are ready to compile and link
# the program.
#**************************************************************************


#************************************************************************
# Rule for linking the program.

$(NAME_OF_EXECUTABLE_FILE) : $(OBJS)
	$(LINKER) $(LINKER_OPTS) $(OBJS)

# And that is it for the linking step! However, the assorted .o files 
# must be created before the above line can finish, so the compilation
# rules below get run before the above rule can finish.
#************************************************************************


#**************************************************************************
# Rules for performing the compilation of each individual object file.

asserts.o : asserts.h asserts.cpp
	$(COMPILER) $(COMPILER_OPTS) asserts.cpp

array.o : array.h array.cpp asserts.h
	$(COMPILER) $(COMPILER_OPTS) array.cpp

skiplist.o : skiplist.h skiplist.cpp array.h asserts.h
	$(COMPILER) $(COMPILER_OPTS) skiplist.cpp

main.o : main.cpp array.h skiplist.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

# And now we have created all the individual object files specified with 
# the macro "OBJS". 
#************************************************************************


#***********************************************************************
# The "clean" rule -- triggered with the command "make clean" -- will
# erase any files created by the compilation. That is, it cleans up
# the directory you are in, so that the next compilation must proceed
# completely from scratch. This is sometimes very helpful.

clean:
	-rm *.o $(NAME_OF_EXECUTABLE_FILE)
	-rm -rf SunWS_cache

# 
#***********************************************************************



