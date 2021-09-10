// ******************************************************
// *                                                    *
// *  main.C                                            *
// *                                                    *
// *  Test file for generic programming demo            *
// *                                                    *
// *  Written September 2004 by Jason Zych              * 
// *                                                    *
// ******************************************************

#include <iostream>
#include <cstddef>
using namespace std;

#include "name.h"
#include "string.h"
#include "vector225.h"
#include "generic.h"

int main()
{
   vector<Name> genericTester;    
   genericTester.push_back(Name("Susan", "Williams"));
   genericTester.push_back(Name("Fred", "Williams"));
   genericTester.push_back(Name("Sam", "Jackson"));
   genericTester.push_back(Name("Boba", "Fett"));
   genericTester.push_back(Name("Roberta", "Williams"));
   genericTester.push_back(Name("Bob", "Collins"));
   genericTester.push_back(Name("Frank", "Collins"));
   genericTester.push_back(Name("Frank", "Williams"));
   genericTester.push_back(Name("Susan", "Jackson"));
   genericTester.push_back(Name("Michael", "Jackson"));
   genericTester.push_back(Name("Sam", "Wiliams"));
   genericTester.push_back(Name("Williams", "Jackson"));
   genericTester.push_back(Name("Sam", "Bob"));
   genericTester.push_back(Name("Robin", "Williams"));
   genericTester.push_back(Name("Roberta", "Jackson"));
   genericTester.push_back(Name("Fred", "Jackson"));
   genericTester.push_back(Name("Michael", "Collins"));
   genericTester.push_back(Name("Bob", "Fett"));


   cout << "*** Printing out names, first name first, without using function";
   cout << endl << endl;
   vector<Name>::iterator it1;
   it1 = genericTester.begin();
   while (it1 != genericTester.end())
   {
      cout << (*it1).getFirstName() << " ";
      cout << it1->getLastName() << endl;
      ++it1;
   }
   cout << endl << endl;
  
   cout << "*** Printing out names, first name first" << endl << endl;
   print(genericTester.begin(), genericTester.end(), PrintFirstThenLast());
   cout << endl << endl;

   PrintFirstThenLast firstObj;
   cout << "*** Printing out names, first name first, again" << endl << endl;
   print(genericTester.begin(), genericTester.end(), firstObj);
   cout << endl << endl;

   cout << "*** Printing out names, last name first" << endl << endl;
   print(genericTester.begin(), genericTester.end(), PrintLastThenFirst());
   cout << endl << endl;

   PrintLastThenFirst lastObj;
   cout << "*** Printing out names, last name first, again" << endl << endl;
   print(genericTester.begin(), genericTester.end(), lastObj);
   cout << endl << endl;

   vector<Name>::iterator marker1, marker2;
   marker1 = genericTester.begin();
   ++marker1;
   ++marker1;
   ++marker1;
   marker2 = genericTester.end();
   --marker2;
   --marker2;

   cout << "*** Printing out subset, first name first" << endl << endl;
   print(marker1, marker2, firstObj);
   cout << endl << endl;
   
   cout << "*** Printing out subset, last name first" << endl << endl;
   print(marker1, marker2, lastObj);
   cout << endl << endl;




   Name testName1("Bob", "Williams");
   
   cout << "*** Printing all names with last name Williams, ";
   cout << "in first/last form" << endl << endl;
   printRelevant(genericTester.begin(), genericTester.end(), CompareLast(),
                       testName1, PrintFirstThenLast());
   cout << endl << endl;


   cout << "*** Printing all names with first name Bob, ";
   cout << "in last, first form" << endl << endl;
   printRelevant(genericTester.begin(), genericTester.end(), CompareFirst(),
                       testName1, PrintLastThenFirst());
   cout << endl << endl;


   CompareFirst compFirstObj;
   
   cout << "*** Printing all names in subset with first name Bob, ";
   cout << "in last, first form" << endl << endl;
   printRelevant(marker1, marker2, compFirstObj,
                           testName1, PrintLastThenFirst());
   cout << endl << endl;


   return 0;
}


