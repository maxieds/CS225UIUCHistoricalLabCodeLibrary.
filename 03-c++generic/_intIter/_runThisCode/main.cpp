// *********************************************************
// *                                                       *
// *  main.cpp                                             *
// *                                                       *
// *  File for simple testing of a integer array class     *
// *      containing a built-in iterator                   *
// *                                                       *
// *  Written January 2005 by Jason Zych                   *
// *                                                       *
// *********************************************************

#include <iostream>
using namespace std;

#include "intarrayIter.h"

int main()
{
   cout << "*** We are testing array code" << endl << endl;
   cout << "*** Testing arrays of integers:" << endl << endl;
   IntArrayIter integerArray1;
 
   cout << "*** Values for array created with no-argument constructor:";
   cout << endl; 
   cout << "lower: " << integerArray1.lower() << endl;
   cout << "upper: " << integerArray1.upper() << endl;
   cout << "size: " << integerArray1.size() << endl;
   cout << endl << endl;

   IntArrayIter integerArray2(-6, 4);
   cout << "*** Values for array created with two-int constructor:" << endl;
   cout << "lower: " << integerArray2.lower() << endl;
   cout << "upper: " << integerArray2.upper() << endl;
   cout << "size: " << integerArray2.size() << endl;
   cout << endl << endl;

   cout << "*** Initialize and print out array:" << endl;
   int intVal = 3;
   integerArray2.initialize(intVal);
   for (int i = integerArray2.lower(); i <= integerArray2.upper(); ++i)
   {
      cout << "i: " << i << "   val: " << integerArray2[i] << endl; 
      integerArray2[i] = 4;
   }
   cout << endl << endl;

   cout << "*** print out array again:" << endl;
   for (int i = integerArray2.lower(); i <= integerArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << integerArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call, lower--->    and upper---->" << endl;
   integerArray2.setBounds(-4, 7);
   cout << "lower: " << integerArray2.lower() << endl;
   cout << "upper: " << integerArray2.upper() << endl;
   cout << "size: " << integerArray2.size() << endl;
   integerArray2[5] = 19;
   integerArray2[6] = 20;
   integerArray2[7] = 21;
   for (int i = integerArray2.lower(); i <= integerArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << integerArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call <-----lower and  <-----upper" << endl;
   integerArray2.setBounds(-8, 2);
   cout << "lower: " << integerArray2.lower() << endl;
   cout << "upper: " << integerArray2.upper() << endl;
   cout << "size: " << integerArray2.size() << endl;
   integerArray2[-8] = 360;
   integerArray2[-7] = 361;
   integerArray2[-6] = 362;
   integerArray2[-5] = 363;
   for (int i = integerArray2.lower(); i <= integerArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << integerArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call <-----lower and  upper---->" << endl;
   integerArray2.setBounds(-13, 5);
   cout << "lower: " << integerArray2.lower() << endl;
   cout << "upper: " << integerArray2.upper() << endl;
   cout << "size: " << integerArray2.size() << endl;
   integerArray2[-13] = 91;
   integerArray2[-12] = 92;
   integerArray2[-11] = 93;
   integerArray2[-10] = 94;
   integerArray2[-9] = 95;
   integerArray2[5] = 96;
   integerArray2[4] = 97;
   integerArray2[3] = 98;
   for (int i = integerArray2.lower(); i <= integerArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << integerArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call lower-----> and <------upper" << endl;
   integerArray2.setBounds(-2, 1);
   cout << "lower: " << integerArray2.lower() << endl;
   cout << "upper: " << integerArray2.upper() << endl;
   cout << "size: " << integerArray2.size() << endl;
   for (int i = integerArray2.lower(); i <= integerArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << integerArray2[i] << endl;
   cout << endl << endl;


   cout << "*** copy constructor call:" << endl;
   const IntArrayIter integerArray3(integerArray2);
   cout << endl;

   cout << "*** const operator[]:" << endl;
   cout << "lower: " << integerArray3.lower() << endl;
   cout << "upper: " << integerArray3.upper() << endl;
   cout << "size: " << integerArray3.size() << endl;
   for (int i = integerArray3.lower(); i <= integerArray3.upper(); ++i)
      cout << "i: " << i << "   val: " << integerArray3[i] << endl;
   cout << endl << endl;
   // integerArray3[0] = 5;
   cout << endl;

   cout << "*** assignment call:" << endl;
   integerArray1 = integerArray2;
   cout << endl;
   cout << "lower: " << integerArray1.lower() << endl;
   cout << "upper: " << integerArray1.upper() << endl;
   cout << "size: " << integerArray1.size() << endl;
   for (int i = integerArray1.lower(); i <= integerArray1.upper(); ++i)
      cout << "i: " << i << "   val: " << integerArray1[i] << endl;
   cout << endl << endl;


   IntArrayIter myArray(1, 10);

   for (int i = 1; i <= 10; i++)
      myArray[i] = 4 * i;

   IntArrayIter::iterator it1;
   it1 = myArray.begin();
   while (!(it1 == myArray.end()))
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
   } while (!(it1 == myArray.begin()));


   return EXIT_SUCCESS; 
}

