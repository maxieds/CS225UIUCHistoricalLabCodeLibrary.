// ***********************************************************
// *                                                         *
// *   asserts.h                                             *    
// *                                                         *
// *   Interface for error alert functions                   *
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

#ifndef ASSERTS_225_H
#define ASSERTS_225_H


// There are two versions each of Assert and Warn below. The 
// first in each case is meant for when you aren't sure if the
// assertion or warning is needed, so the function checks a 
// condition for you. The second is meant for when you already 
// know for sure that you want that assertion or warning to activate;
// in those situations, just passing in the message is easier than 
// requiring a 0 to be passed in for the condition.

// The "char const *" type refers to a C++ low-level string; we
// will discuss the "const" keyword further in lecture 4. 


// Assert
//    - parameters : safeCondition - value of a boolean expression
//                 : errorMessage - a pointer to a character array 
//                    containing an error message to print out;
//                    we cannot change this character array through
//                    this pointer
//    - if safeCondition is true, do nothing. Otherwise, print
//              errorMessage with specific formatting, and then 
//              forcefully exit the program with error status flag. 
void Assert(bool safeCondition, char const * errorMessage);



// Assert
//    - parameters : errorMessage - a pointer to a character array 
//                    containing an error message to print out;
//                    we cannot change this character array through
//                    this pointer
//    - print errorMessage with specific formatting, and then forcefully 
//        exit the program with error status flag.
void Assert(char const * errorMessage);



// Warn
//    - parameters : safeCondition - value of a boolean expression
//                 : warningMessage - a pointer to a character array
//                    containing a warning message to print out;
//                    we cannot change this character array through
//                    this pointer
//    - if safeCondition is true, do nothing. Otherwise, print
//              warningMessage with specific formatting
void Warn(bool safeCondition, char const * warningMessage);



// Warn
//    - parameters : warningMessage - a pointer to a character array
//                    containing a warning message to print out;
//                    we cannot change this character array through
//                    this pointer
//    - print warningMessage with specific formatting
void Warn(char const * warningMessage);


#endif

