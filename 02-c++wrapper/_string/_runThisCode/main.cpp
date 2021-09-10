// **************************************************
// *                                                *
// *  main.cpp                                      *
// *                                                *
// *  File for simple testing of string class       *
// *                                                *
// *  Written January 2005 by Jason Zych            *
// *                                                *
// **************************************************

#include <iostream>
using namespace std;

#include "string.h"

// TestingConstant
//    - parameters : unchangingStr - a String to print out and 
//                    attempt to alter
//    - prints out each character of the String
void TestingConstant(String const & unchangingStr);


void TestingConstant(String const & unchangingStr) 
{
   for (int i = 0; i < unchangingStr.length(); i++)
      cout << unchangingStr[i] << endl;

   // If you uncomment this line, the code will not compile
   //      unchangingStr[0] = 'C';
   // because the const version of operator[] is run on a 
   // String that is const -- and the const version of 
   // operator[] does not return an lvalue.
}


int main()
{
   cout << "*** Testing the String no-argument constructor..." << endl;
   String blank;
   cout << "String is: " << blank << endl;
   cout << endl;
  
   cout << "*** Testing the second String constructor..." << endl; 
   String phrase("Hello world!");
   cout << "String is: " << phrase << endl;
   cout << endl;

   cout << "*** Testing String copy constructor..." << endl;
   String theCopy(phrase);
   cout << "String is: " << theCopy << endl;
   cout << endl;

   cout << "*** Testing String assignment operator..." << endl;
   String theAssign("First value");
   cout << "String's initial value is: " << theAssign << endl;
   theAssign = blank;
   cout << "Latest value of String is: " << theAssign << endl;
   theAssign = phrase;
   cout << "Final value of String is: " << theAssign << endl;
   cout << endl;


   cout << "*** Printing blank string character by character..." << endl;
   for (int i = 0; i < blank.length(); i++)
      cout << blank[i] << endl;
   cout << endl;
  
   cout << "*** Printing second string character by character..." << endl;
   for (int i = 0; i < phrase.length(); i++)
      cout << phrase[i] << endl;
   cout << endl;

   cout << "*** Changing first letter of second string..." << endl;
   phrase[0] = 's';
   cout << "Second String is now: " << phrase << endl;
   cout << endl;

   cout << "*** Testing concat..." << endl;
   String cat1 = phrase.concat(theCopy);
   cout << "First concat is: " << cat1 << endl;
   String cat2 = blank.concat(phrase);
   cout << "Second concat is: " << cat2 << endl;
   String cat3 = phrase.concat(blank);
   cout << "Third concat is: " << cat3 << endl;
   cout << endl;
   
   cout << "*** Testing substring..." << endl;
   String sub1 = cat1.substring(4, 8);
   cout << "First substring is: " << sub1 << endl;
   String sub2 = cat1.substring(0, 7);
   cout << "Second substring is: " << sub2 << endl;
   String sub3 = cat1.substring(20, 4);
   cout << "Third substring is: " << sub3 << endl;
   String sub4 = cat1.substring(21, 5);
   cout << "Fourth substring is: " << sub4 << endl;

   cout << "*** Performing some comparisons..." << endl;
   cout << (cat1 < sub1) << endl;
   cout << (cat1 < cat1) << endl;
   cout << (sub1 < cat1) << endl;
   cout << endl;

   cout << (cat1 > sub1) << endl;
   cout << (cat1 > cat1) << endl;
   cout << (sub1 > cat1) << endl;
   cout << endl;

   cout << (cat1 == sub1) << endl;
   cout << (cat2 == cat3) << endl;
   cout << endl;

   cout << (cat1 != sub1) << endl;
   cout << (cat2 != cat3) << endl;
   cout << endl;

   cout << (cat1 <= sub1) << endl;
   cout << (cat2 <= cat3) << endl;
   cout << (cat1 <= cat3) << endl;
   cout << (sub1 <= cat1) << endl;
   cout << endl;

   cout << (cat1 >= sub1) << endl;
   cout << (cat2 >= cat3) << endl;
   cout << (cat1 >= cat3) << endl;
   cout << (sub1 >= cat1) << endl;
   cout << endl;

   return EXIT_SUCCESS; 
}

