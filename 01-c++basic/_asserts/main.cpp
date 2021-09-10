// **********************************************************
// *                                                        *
// *  main.cpp                                              *
// *                                                        *
// *  File for simple testing of Assert and Warn functions  *
// *                                                        *
// *  Written October 2004 by Jason Zych                    *
// *                                                        *
// **********************************************************

#include <iostream>
using namespace std;

#include "asserts.h"

int main()
{
   Warn(6 < 5, "This is a warning!");
   Warn(5 < 6, "This is a warning too!");
   cout << "that's all" << endl;

   Warn("This is also a warning!");
   cout << "that's all, again" << endl;

   // Assert(6 < 5, "This is an assert!");
   Assert(5 < 6, "This is an assert too!");
   cout << "that is still all!" << endl;
   
   // Assert("This is also an assert!");
   cout << "That is finally all." << endl;

   return EXIT_SUCCESS; 

}

