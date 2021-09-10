// ************************************************************
// *                                                          *
// *  main.cpp                                                *
// *                                                          *
// *  File for simple testing of simple generic array class   *
// *                                                          *
// *  Written October 2004 by Jason Zych                      *
// *                                                          *
// *     - changes by Jason Zych January 2005                 *
// *         - file modified for change in array class type   *
// *           name from Array to SimpleArray                 *
// *                                                          *
// ************************************************************

#include <iostream>
using namespace std;

#include "string.h"
#include "simpleArray.h"

int main()
{
   cout << "*** We are testing array code" << endl << endl;
   cout << "*** Testing arrays of integers:" << endl << endl;
   SimpleArray<int> intSimpleArray1;
 
   cout << "*** Values for array created with no-argument constructor:";
   cout << endl; 
   cout << "lower: " << intSimpleArray1.lower() << endl;
   cout << "upper: " << intSimpleArray1.upper() << endl;
   cout << "size: " << intSimpleArray1.size() << endl;
   cout << endl << endl;

   SimpleArray<int> intSimpleArray2(-6, 4);
   cout << "*** Values for array created with two-int constructor:" << endl;
   cout << "lower: " << intSimpleArray2.lower() << endl;
   cout << "upper: " << intSimpleArray2.upper() << endl;
   cout << "size: " << intSimpleArray2.size() << endl;
   cout << endl << endl;

   cout << "*** Initialize and print out array:" << endl;
   int intVal = 3;
   intSimpleArray2.initialize(intVal);
   for (int i = intSimpleArray2.lower(); i <= intSimpleArray2.upper(); ++i)
   {
      cout << "i: " << i << "   val: " << intSimpleArray2[i] << endl; 
      intSimpleArray2[i] = 4;
   }
   cout << endl << endl;

   cout << "*** print out array again:" << endl;
   for (int i = intSimpleArray2.lower(); i <= intSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << intSimpleArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call, lower--->    and upper---->" << endl;
   intSimpleArray2.setBounds(-4, 7);
   cout << "lower: " << intSimpleArray2.lower() << endl;
   cout << "upper: " << intSimpleArray2.upper() << endl;
   cout << "size: " << intSimpleArray2.size() << endl;
   intSimpleArray2[5] = 19;
   intSimpleArray2[6] = 20;
   intSimpleArray2[7] = 21;
   for (int i = intSimpleArray2.lower(); i <= intSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << intSimpleArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call <-----lower and  <-----upper" << endl;
   intSimpleArray2.setBounds(-8, 2);
   cout << "lower: " << intSimpleArray2.lower() << endl;
   cout << "upper: " << intSimpleArray2.upper() << endl;
   cout << "size: " << intSimpleArray2.size() << endl;
   intSimpleArray2[-8] = 360;
   intSimpleArray2[-7] = 361;
   intSimpleArray2[-6] = 362;
   intSimpleArray2[-5] = 363;
   for (int i = intSimpleArray2.lower(); i <= intSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << intSimpleArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call <-----lower and  upper---->" << endl;
   intSimpleArray2.setBounds(-13, 5);
   cout << "lower: " << intSimpleArray2.lower() << endl;
   cout << "upper: " << intSimpleArray2.upper() << endl;
   cout << "size: " << intSimpleArray2.size() << endl;
   intSimpleArray2[-13] = 91;
   intSimpleArray2[-12] = 92;
   intSimpleArray2[-11] = 93;
   intSimpleArray2[-10] = 94;
   intSimpleArray2[-9] = 95;
   intSimpleArray2[5] = 96;
   intSimpleArray2[4] = 97;
   intSimpleArray2[3] = 98;
   for (int i = intSimpleArray2.lower(); i <= intSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << intSimpleArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call lower-----> and <------upper" << endl;
   intSimpleArray2.setBounds(-2, 1);
   cout << "lower: " << intSimpleArray2.lower() << endl;
   cout << "upper: " << intSimpleArray2.upper() << endl;
   cout << "size: " << intSimpleArray2.size() << endl;
   for (int i = intSimpleArray2.lower(); i <= intSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << intSimpleArray2[i] << endl;
   cout << endl << endl;


   cout << "*** copy constructor call:" << endl;
   const SimpleArray<int> intSimpleArray3(intSimpleArray2);
   cout << endl;

   cout << "*** const operator[]:" << endl;
   cout << "lower: " << intSimpleArray3.lower() << endl;
   cout << "upper: " << intSimpleArray3.upper() << endl;
   cout << "size: " << intSimpleArray3.size() << endl;
   for (int i = intSimpleArray3.lower(); i <= intSimpleArray3.upper(); ++i)
      cout << "i: " << i << "   val: " << intSimpleArray3[i] << endl;
   cout << endl << endl;
   // intSimpleArray3[0] = 5;
   cout << endl;

   cout << "*** assignment call:" << endl;
   intSimpleArray1 = intSimpleArray2;
   cout << endl;
   cout << "lower: " << intSimpleArray1.lower() << endl;
   cout << "upper: " << intSimpleArray1.upper() << endl;
   cout << "size: " << intSimpleArray1.size() << endl;
   for (int i = intSimpleArray1.lower(); i <= intSimpleArray1.upper(); ++i)
      cout << "i: " << i << "   val: " << intSimpleArray1[i] << endl;
   cout << endl << endl;

   cout << "*** Testing arrays of strings:" << endl << endl;
   SimpleArray<String> strSimpleArray1;
 
   cout << "*** Values for array created with no-argument constructor:";
   cout << endl; 
   cout << "lower: " << strSimpleArray1.lower() << endl;
   cout << "upper: " << strSimpleArray1.upper() << endl;
   cout << "size: " << strSimpleArray1.size() << endl;
   cout << endl << endl;

   SimpleArray<String> strSimpleArray2(-6, 4);
   cout << "*** Values for array created with two-String constructor:" << endl;
   cout << "lower: " << strSimpleArray2.lower() << endl;
   cout << "upper: " << strSimpleArray2.upper() << endl;
   cout << "size: " << strSimpleArray2.size() << endl;
   cout << endl << endl;

   cout << "*** Initialize and print out array:" << endl;
   String stringVal = "foo";
   strSimpleArray2.initialize(stringVal);
   for (int i = strSimpleArray2.lower(); i <= strSimpleArray2.upper(); ++i)
   {
      cout << "i: " << i << "   val: " << strSimpleArray2[i] << endl; 
      strSimpleArray2[i] = "another foo";
   }
   cout << endl << endl;

   cout << "*** print out array again:" << endl;
   for (int i = strSimpleArray2.lower(); i <= strSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << strSimpleArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call, lower--->    and upper---->" << endl;
   strSimpleArray2.setBounds(-4, 7);
   cout << "lower: " << strSimpleArray2.lower() << endl;
   cout << "upper: " << strSimpleArray2.upper() << endl;
   cout << "size: " << strSimpleArray2.size() << endl;
   strSimpleArray2[5] = "one";
   strSimpleArray2[6] = "two";
   // let strSimpleArray2[7] stay as empty string
   for (int i = strSimpleArray2.lower(); i <= strSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << strSimpleArray2[i] << endl; 
   cout << endl << endl;

   cout << "*** setBounds call <-----lower and  <-----upper" << endl;
   strSimpleArray2.setBounds(-8, 2);
   cout << "lower: " << strSimpleArray2.lower() << endl;
   cout << "upper: " << strSimpleArray2.upper() << endl;
   cout << "size: " << strSimpleArray2.size() << endl;
   strSimpleArray2[-8] = "360";
   strSimpleArray2[-7] = "361";
   strSimpleArray2[-6] = "362";
   strSimpleArray2[-5] = "363";
   for (int i = strSimpleArray2.lower(); i <= strSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << strSimpleArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call <-----lower and  upper---->" << endl;
   strSimpleArray2.setBounds(-13, 5);
   cout << "lower: " << strSimpleArray2.lower() << endl;
   cout << "upper: " << strSimpleArray2.upper() << endl;
   cout << "size: " << strSimpleArray2.size() << endl;
   // new cells hold empty string
   for (int i = strSimpleArray2.lower(); i <= strSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << strSimpleArray2[i] << endl;
   cout << endl << endl;


   cout << "*** setBounds call lower-----> and <------upper" << endl;
   strSimpleArray2.setBounds(-2, 1);
   cout << "lower: " << strSimpleArray2.lower() << endl;
   cout << "upper: " << strSimpleArray2.upper() << endl;
   cout << "size: " << strSimpleArray2.size() << endl;
   for (int i = strSimpleArray2.lower(); i <= strSimpleArray2.upper(); ++i)
      cout << "i: " << i << "   val: " << strSimpleArray2[i] << endl;
   cout << endl << endl;


   cout << "*** copy constructor call:" << endl;
   const SimpleArray<String> strSimpleArray3(strSimpleArray2);
   cout << endl;

   cout << "*** const operator[]:" << endl;
   cout << "lower: " << strSimpleArray3.lower() << endl;
   cout << "upper: " << strSimpleArray3.upper() << endl;
   cout << "size: " << strSimpleArray3.size() << endl;
   for (int i = strSimpleArray3.lower(); i <= strSimpleArray3.upper(); ++i)
      cout << "i: " << i << "   val: " << strSimpleArray3[i] << endl;
   cout << endl << endl;
   // strSimpleArray3[0] = 5;
   cout << endl;

   cout << "*** assignment call:" << endl;
   strSimpleArray1 = strSimpleArray2;
   cout << endl;
   cout << "lower: " << strSimpleArray1.lower() << endl;
   cout << "upper: " << strSimpleArray1.upper() << endl;
   cout << "size: " << strSimpleArray1.size() << endl;
   for (int i = strSimpleArray1.lower(); i <= strSimpleArray1.upper(); ++i)
      cout << "i: " << i << "   val: " << strSimpleArray1[i] << endl;
   cout << endl << endl;

   return EXIT_SUCCESS; 
}

