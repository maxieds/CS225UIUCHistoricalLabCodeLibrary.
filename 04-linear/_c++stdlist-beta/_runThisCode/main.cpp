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

#include "list225.h"
#include "string.h"
#include "listTestUtil.h"


int main()
{
   list<String> myList;

   myList.push_back("Aire");
   myList.push_back("Beginnings");    
   myList.push_back("Colour My World");
   myList.push_back("Dialogue");    
   myList.push_back("Feelin' Stronger Every Day");    
   myList.push_back("Goodbye");    
   myList.push_back("Introduction");    
   myList.push_back("Just You 'N' Me");    
   myList.push_back("Liberation");
   myList.push_back("Make Me Smile");

   NonConstTests(myList);
   cout << endl << endl;
   ConstTests(myList);


   return 0;
}

