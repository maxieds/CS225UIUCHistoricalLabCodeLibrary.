// ************************************************************
// *                                                          *
// *  main.cpp                                                *
// *                                                          *
// *  File for simple testing of generic array class          *
// *                                                          *
// *  Written January 2005 by Jason Zych                      *
// *                                                          *
// ************************************************************

#include <iostream>
using namespace std;

#include "string.h"
#include "array.h"
#include "iterArrayFns.h"

int main()
{
   cout << "*** We are testing array code" << endl << endl;
   cout << "*** Testing arrays of integers:" << endl << endl;
   Array<int> integerArray1;
 
   cout << "*** Values for array created with no-argument constructor:";
   cout << endl; 
   cout << "lower: " << integerArray1.lower() << endl;
   cout << "upper: " << integerArray1.upper() << endl;
   cout << "size: " << integerArray1.size() << endl;
   cout << endl << endl;

   Array<int> integerArray2(-6, 4);
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
   const Array<int> integerArray3(integerArray2);
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

   cout << "*** Testing arrays of strings:" << endl << endl;
   Array<String> stringArray1;
 
   cout << "*** Values for array created with no-argument constructor:";
   cout << endl; 
   cout << "lower: " << stringArray1.lower() << endl;
   cout << "upper: " << stringArray1.upper() << endl;
   cout << "size: " << stringArray1.size() << endl;
   cout << endl << endl;

   Array<String> stringArray2(-6, 4);
   cout << "*** Values for array created with two-String constructor:" << endl;
   cout << "lower: " << stringArray2.lower() << endl;
   cout << "upper: " << stringArray2.upper() << endl;
   cout << "size: " << stringArray2.size() << endl;
   cout << endl << endl;

   cout << "*** Initialize and print out array:" << endl;
   String stringVal = "foo";
   stringArray2.initialize(stringVal);
   for (int i = stringArray2.lower(); i <= stringArray2.upper(); ++i)
   {
      cout << "i: " << i << "   val: " << stringArray2[i] << endl; 
      stringArray2[i] = "another foo";
   }
   cout << endl << endl;

   cout << "*** print out array again:" << endl;
   for (int i = stringArray2.lower(); i <= stringArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << stringArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call, lower--->    and upper---->" << endl;
   stringArray2.setBounds(-4, 7);
   cout << "lower: " << stringArray2.lower() << endl;
   cout << "upper: " << stringArray2.upper() << endl;
   cout << "size: " << stringArray2.size() << endl;
   stringArray2[5] = "one";
   stringArray2[6] = "two";
   // let stringArray2[7] stay as empty string
   for (int i = stringArray2.lower(); i <= stringArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << stringArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call <-----lower and  <-----upper" << endl;
   stringArray2.setBounds(-8, 2);
   cout << "lower: " << stringArray2.lower() << endl;
   cout << "upper: " << stringArray2.upper() << endl;
   cout << "size: " << stringArray2.size() << endl;
   stringArray2[-8] = "360";
   stringArray2[-7] = "361";
   stringArray2[-6] = "362";
   stringArray2[-5] = "363";
   for (int i = stringArray2.lower(); i <= stringArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << stringArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call <-----lower and  upper---->" << endl;
   stringArray2.setBounds(-13, 5);
   cout << "lower: " << stringArray2.lower() << endl;
   cout << "upper: " << stringArray2.upper() << endl;
   cout << "size: " << stringArray2.size() << endl;
   // new cells hold empty string
   for (int i = stringArray2.lower(); i <= stringArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << stringArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call lower-----> and <------upper" << endl;
   stringArray2.setBounds(-2, 1);
   cout << "lower: " << stringArray2.lower() << endl;
   cout << "upper: " << stringArray2.upper() << endl;
   cout << "size: " << stringArray2.size() << endl;
   for (int i = stringArray2.lower(); i <= stringArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << stringArray2[i] << endl;
   cout << endl << endl;


   cout << "*** copy constructor call:" << endl;
   const Array<String> stringArray3(stringArray2);
   cout << endl;

   cout << "*** const operator[]:" << endl;
   cout << "lower: " << stringArray3.lower() << endl;
   cout << "upper: " << stringArray3.upper() << endl;
   cout << "size: " << stringArray3.size() << endl;
   for (int i = stringArray3.lower(); i <= stringArray3.upper(); ++i)
      cout << "i: " << i << "   val: " << stringArray3[i] << endl;
   cout << endl << endl;
   // stringArray3[0] = 5;
   cout << endl;

   cout << "*** assignment call:" << endl;
   stringArray1 = stringArray2;
   cout << endl;
   cout << "lower: " << stringArray1.lower() << endl;
   cout << "upper: " << stringArray1.upper() << endl;
   cout << "size: " << stringArray1.size() << endl;
   for (int i = stringArray1.lower(); i <= stringArray1.upper(); ++i)
      cout << "i: " << i << "   val: " << stringArray1[i] << endl;
   cout << endl << endl;

   cout << "*** Testing iterators with Array class..." << endl << endl;

   Array<String> iterArray(-5, 6);

   iterArray[-5] = "Crichton";
   iterArray[-4] = "Aeryn";
   iterArray[-3] = "D'Argo";
   iterArray[-2] = "Chiana";
   iterArray[-1] = "Rygel";
   iterArray[0] = "Pilot";
   iterArray[1] = "Zhann";
   iterArray[2] = "Scorpius";
   iterArray[3] = "Crais";
   iterArray[4] = "Jool";
   iterArray[5] = "Sizoku";
   iterArray[6] = "Moya";
   cout << endl << endl;


   cout << "*** Testing iterators: " << endl << endl;
   ForwardIteration(iterArray);
   ForwardConstIteration(iterArray);
   ReverseIteration(iterArray);
   ReverseConstIteration(iterArray);
   ForwardIterationWithChanges(iterArray);
   ReverseIterationWithChanges(iterArray);

   cout << endl << endl;


   return EXIT_SUCCESS; 
}

