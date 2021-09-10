// ***********************************************************
// *                                                         *
// *   asserts.C                                             *
// *                                                         *
// *   Implementation for two helpful debugging              *
// *                 alert functions                         * 
// *                                                         *
// *   Based on the assertion files of Decker & Hirshfield   *
// *                                                         *
// ***********************************************************

#include <stdlib.h>
#include <iostream.h>
#include "asserts.h"


// Assert
//    - parameters : safeCondition - int result of a boolean
//                                     expression
//                 : errMsg - error message to print out
//    - if safe condition is true, do nothing. Otherwise, print
//              errMsg and forcefully exit the program. Meant for
//              when continuing with program is destined to be 
//              fatal to program anyway (ex.: divide by zero)
void Assert(int safeCondition, const char* errMsg)
{
   if (!safeCondition)
   {
      cerr << "***Error: " << errMsg << endl;
      exit(1);
   }
}



// Assert
//    - parameters : errMsg - error message to print out
//    - print errMsg and forcefully exit the program. Meant for
//              when continuing with program is destined to be
//              fatal to program anyway (ex.: divide by zero)
void Assert(const char* errMsg)
{
   cerr << "***Error: " << errMsg << endl;
   exit(1);
}





// Warn
//    - parameters : safeCondition - int result of a boolean
//                                     expression
//                 : errMsg - error message to print out
//    - if safe condition is true, do nothing. Otherwise, print
//              errMsg and then continue with the program. Meant
//              for when the condition being false is troublesome,
//              or perhaps unusual, but not fatal to program. 
void Warn(int safeCondition, const char* errMsg)
{
   if (!safeCondition)
      cerr << "***Warning: " << errMsg << endl;
}



// Warn
//    - parameters : errMsg - error message to print out
//    - print errMsg and then continue with the program. Meant
//              for when the condition being false is troublesome,
//              or perhaps unusual, but not fatal to program.
void Warn(const char* errMsg)
{
   cerr << "***Warning: " << errMsg << endl;
}



