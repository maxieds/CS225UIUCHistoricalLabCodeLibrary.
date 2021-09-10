// **************************************************
// *                                                *
// *  main.cpp                                      *
// *                                                *
// *  Testing file for simple iterator class code   *
// *                                                *
// *  Written Septemner 2004 by Jason Zych          *
// *                                                *
// **************************************************

#include <iostream>
using namespace std;

#include "intarrayiter.h"


int main()
{
   IntArrayIter myArray(1, 10);

   for (int i = 1; i <= 10; i++)
      myArray[i] = 4 * i;

   IntArrayIter::iterator it1;
   it1 = myArray.begin();
   while (it1 != myArray.end()) 
   {
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
      cout << "Moving iterator forward one cell." << endl;
      ++it1;
      cout << "Moved iterator forward one cell." << endl;
   }

   cout << endl << endl;


   do {
      cout << "Moving iterator backward one cell." << endl;
      --it1;
      cout << "Moved iterator backward one cell." << endl;
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
   } while (it1 != myArray.begin());


   return 0;
}

