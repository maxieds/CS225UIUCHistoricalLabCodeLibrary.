// ***********************************************************
// *                                                         *
// *   asserts.cpp                                           *
// *                                                         *
// *   Implementation for error alert functions              *
// *                                                         *
// *   Written September 2003 by Jason Zych                  *
// *                                                         *            
// *     - changes by Jason Zych October 2004:               *
// *        - changed ints-as-booleans to bool               *
// *        - standardized const on right of item            *
// *        - enhanced comments                              *
// *        - #ifndef macro changed                          *
// *        - EXIT_FAILURE used as return value              *
// *                                                         *
// ***********************************************************

// *** includes of files in the standard library

#include <cstdlib>     // contains exit() function and EXIT_FAILURE flag
#include <iostream>    // contains output stream tools (such as cerr)

// lack of the line
//     using namespace std;
// here means we have to have "std::" in front of all usages 
// of cerr and endl below. If we indicated we were using the
// "std" namespace, then we automatically get to use everything
// in that namespace -- including cerr and endl -- without 
// specifically noting that it is from the std namespace.


// *** includes of our own declarations

#include "asserts.h"       // contains declarations for the four 
                           //   functions defined below


// Assert
//    - parameters : safeCondition - value of a boolean expression
//                 : errorMessage - a pointer to a character array 
//                    containing an error message to print out;
//                    we cannot change this character array through
//                    this pointer
//    - if safeCondition is true, do nothing. Otherwise, print
//              errorMessage with specific formatting, and then 
//              forcefully exit the program with error status flag.
void Assert(bool safeCondition, char const * errorMessage)
{
   if (!safeCondition)
   {
      std::cerr << "***Error: " << errorMessage << std::endl;
      exit(EXIT_FAILURE);   // exits the program, sends "program 
                            // ended abnormally" flag to operating system
   }
}



// Assert
//    - parameters :  errorMessage - a pointer to a character array
//                     containing an error message to print out;
//                     we cannot change this character array through
//                     this pointer
//    - print errorMessage with specific formatting, and then forcefully 
//        exit the program with error status flag.
void Assert(char const * errorMessage)
{
   std::cerr << "***Error: " << errorMessage << std::endl;
   exit(EXIT_FAILURE);   // exits the program, sends "program
                         // ended abnormally" flag to operating system
}





// Warn
//    - parameters : safeCondition - value of a boolean expression
//                 : warningMessage - a pointer to a character array
//                    containing a warning message to print out;
//                    we cannot change this character array through
//                    this pointer
//    - if safeCondition is true, do nothing. Otherwise, print
//              warningMessage with specific formatting
void Warn(bool safeCondition, char const * warningMessage)
{
   if (!safeCondition)
      std::cerr << "***Warning: " << warningMessage << std::endl;
}



// Warn
//    - parameters : warningMessage - a pointer to a character array
//                    containing a warning message to print out;
//                    we cannot change this character array through
//                    this pointer
//    - print warningMessage with specific formatting
void Warn(char const * warningMessage)
{
   std::cerr << "***Warning: " << warningMessage << std::endl;
}



