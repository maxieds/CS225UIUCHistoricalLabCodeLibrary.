// ***********************************************************
// *                                                         *
// *   asserts.h                                             *    
// *                                                         *
// *   Interface for four helpful debugging alert functions  *
// *                                                         *
// *   Based on the assertion files of Decker & Hirshfield   *
// *                                                         * 
// ***********************************************************

// There are two versions each of Assert and Warn below. The 
// first in each case is meant for when you aren't sure if the
// assertion or warning is needed, so the function checks a 
// condition for you. The second is meant for when you already 
// know for sure that you want that assertion or warning to activate;
// in those situations, just passing in the message is easier than 
// requiring a 0 is passed in for the condition.


#ifndef ASSERTS_H
#define ASSERTS_H


// Assert
//    - parameters : safeCondition - int result of a boolean
//                                     expression
//                 : errMsg - error message to print out
//    - if safe condition is true, do nothing. Otherwise, print
//              errMsg and forcefully exit the program. Meant for
//              when continuing with program is destined to be 
//              fatal to program anyway (ex.: divide by zero)
void Assert(int safeCondition, const char* errMsg);



// Assert
//    - parameters : errMsg - error message to print out
//    - print errMsg and forcefully exit the program. Meant for
//              when continuing with program is destined to be
//              fatal to program anyway (ex.: divide by zero)
void Assert(const char* errMsg);



// Warn
//    - parameters : safeCondition - int result of a boolean
//                                     expression
//                 : errMsg - error message to print out
//    - if safe condition is true, do nothing. Otherwise, print
//              errMsg and then continue with the program. Meant
//              for when the condition being false is troublesome,
//              or perhaps unusual, but not fatal to program. 
void Warn(int safeCondition, const char* errMsg);



// Warn
//    - parameters : errMsg - error message to print out
//    - print errMsg and then continue with the program. Meant
//              for when the condition being false is troublesome,
//              or perhaps unusual, but not fatal to program.
void Warn(const char* errMsg);


#endif

