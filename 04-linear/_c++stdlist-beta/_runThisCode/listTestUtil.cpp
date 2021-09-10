// **********************************************************
// *                                                        *
// *  listTestUtil.cpp                                      *
// *                                                        *
// *  Implementation file for list class testing functions  *
// *                                                        *
// *  Written September 2004 by Jason Zych                  *
// *                                                        *
// **********************************************************

#include <iostream>
using namespace std;

#include "list225.h"
#include "string.h"

void NonConstTests(list<String>& myList) 
{
   cout << "*** Testing non-const forward iterator using prefix";
   cout << endl << endl;

   list<String>::iterator it1;
   it1 = myList.begin();
   while (it1 != myList.end()) 
   {
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
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
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
   } while (it1 != myList.begin());

   cout << endl << endl;

   cout << "*** Testing non-const forward iterator using postfix";
   cout << endl << endl;

   it1 = myList.begin();
   while (it1 != myList.end())
   {
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
      cout << "Moving iterator forward one cell." << endl;
      it1++;
      cout << "Moved iterator forward one cell." << endl;
   }

   cout << endl << endl;

   do {
      cout << "Moving iterator backward one cell." << endl;
      it1--;
      cout << "Moved iterator backward one cell." << endl;
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
   } while (it1 != myList.begin());

   cout << endl << endl;

   cout << "*** Testing non-const reverse iterator using prefix";
   cout << endl << endl;

   list<String>::reverse_iterator it2;
   it2 = myList.rbegin();
   while (it2 != myList.rend())
   {
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
      cout << "Moving iterator forward one cell." << endl;
      ++it2;
      cout << "Moved iterator forward one cell." << endl;
   }

   cout << endl << endl;

   do {
      cout << "Moving iterator backward one cell." << endl;
      --it2;
      cout << "Moved iterator backward one cell." << endl;
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
   } while (it2 != myList.rbegin());

   cout << endl << endl;

   cout << "*** Testing non-const reverse iterator using postfix";
   cout << endl << endl;

   it2 = myList.rbegin();
   while (it2 != myList.rend())
   {
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
      cout << "Moving iterator forward one cell." << endl;
      it2++;
      cout << "Moved iterator forward one cell." << endl;
   }

   cout << endl << endl;

   do {
      cout << "Moving iterator backward one cell." << endl;
      it2--;
      cout << "Moved iterator backward one cell." << endl;
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
   } while (it2 != myList.rbegin());
}


void ConstTests(const list<String>& myList) 
{
   cout << "*** Testing const forward iterator using prefix";
   cout << endl << endl;

   list<String>::const_iterator it1;
   it1 = myList.begin();
   while (it1 != myList.end()) 
   {
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
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
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
   } while (it1 != myList.begin());

   cout << endl << endl;

   cout << "*** Testing const forward iterator using postfix";
   cout << endl << endl;

   it1 = myList.begin();
   while (it1 != myList.end())
   {
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
      cout << "Moving iterator forward one cell." << endl;
      it1++;
      cout << "Moved iterator forward one cell." << endl;
   }

   cout << endl << endl;

   do {
      cout << "Moving iterator backward one cell." << endl;
      it1--;
      cout << "Moved iterator backward one cell." << endl;
      cout << "Printing iterator value: ";
      cout << *it1 << endl;
      cout << "Printing iterator value's length: ";
      cout << it1->length() << endl;
   } while (it1 != myList.begin());

   cout << endl << endl;

   cout << "*** Testing const reverse iterator using prefix";
   cout << endl << endl;

   list<String>::const_reverse_iterator it2;
   it2 = myList.rbegin();
   while (it2 != myList.rend())
   {
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
      cout << "Moving iterator forward one cell." << endl;
      ++it2;
      cout << "Moved iterator forward one cell." << endl;
   }

   cout << endl << endl;

   do {
      cout << "Moving iterator backward one cell." << endl;
      --it2;
      cout << "Moved iterator backward one cell." << endl;
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
   } while (it2 != myList.rbegin());

   cout << endl << endl;

   cout << "*** Testing const reverse iterator using postfix";
   cout << endl << endl;

   it2 = myList.rbegin();
   while (it2 != myList.rend())
   {
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
      cout << "Moving iterator forward one cell." << endl;
      it2++;
      cout << "Moved iterator forward one cell." << endl;
   }

   cout << endl << endl;

   do {
      cout << "Moving iterator backward one cell." << endl;
      it2--;
      cout << "Moved iterator backward one cell." << endl;
      cout << "Printing iterator value: ";
      cout << *it2 << endl;
      cout << "Printing iterator value's length: ";
      cout << it2->length() << endl;
   } while (it2 != myList.rbegin());
}



