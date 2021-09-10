// ***********************************************************
// *                                                         *
// *   asserts.h                                             *    
// *                                                         *
// *   Interface for two helpful debugging alert functions   *
// *                                                         *
// *   Based on the assertion files of Decker & Hirshfield   *
// *                                                         * 
// ***********************************************************

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



// Warn
//    - parameters : safeCondition - int result of a boolean
//                                     expression
//                 : errMsg - error message to print out
//    - if safe condition is true, do nothing. Otherwise, print
//              errMsg and then continue with the program. Meant
//              for when the condition being false is troublesome,
//              or perhaps unusual, but not fatal to program. 
void Warn(int safeCondition, const char* errMsg);


#endif

