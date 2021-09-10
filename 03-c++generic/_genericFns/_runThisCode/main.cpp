// ******************************************************
// *                                                    *
// *  main.cpp                                          *
// *                                                    *
// *  Test code for sample generic programming files    *
// *                                                    *
// *  Written January 2005 by Jason Zych                * 
// *                                                    *
// ******************************************************

#include <cstddef>
#include <iostream>
using namespace std;

#include "string.h"
#include "name.h"
#include "vector225.h"
#include "array.h"
#include "generic.h"

int main()
{
   Name testName1("Bob", "Williams");

   cout << "*** First -- we run a bunch of tests on vectors..." << endl;
   cout << endl << endl << endl;;


   vector<Name> vectorTestObj;    
   vectorTestObj.push_back(Name("Susan", "Williams"));
   vectorTestObj.push_back(Name("Fred", "Williams"));
   vectorTestObj.push_back(Name("Sam", "Jackson"));
   vectorTestObj.push_back(Name("Boba", "Fett"));
   vectorTestObj.push_back(Name("Roberta", "Williams"));
   vectorTestObj.push_back(Name("Bob", "Collins"));
   vectorTestObj.push_back(Name("Frank", "Collins"));
   vectorTestObj.push_back(Name("Frank", "Williams"));
   vectorTestObj.push_back(Name("Susan", "Jackson"));
   vectorTestObj.push_back(Name("Michael", "Jackson"));
   vectorTestObj.push_back(Name("Sam", "Wiliams"));
   vectorTestObj.push_back(Name("Williams", "Jackson"));
   vectorTestObj.push_back(Name("Sam", "Bob"));
   vectorTestObj.push_back(Name("Robin", "Williams"));
   vectorTestObj.push_back(Name("Roberta", "Jackson"));
   vectorTestObj.push_back(Name("Fred", "Jackson"));
   vectorTestObj.push_back(Name("Michael", "Collins"));
   vectorTestObj.push_back(Name("Bob", "Fett"));


   cout << "*** Printing out names, first name first, without using function";
   cout << endl << endl;
   vector<Name>::iterator vecIt1;
   vecIt1 = vectorTestObj.begin();
   while (vecIt1 != vectorTestObj.end())
   {
      cout << (*vecIt1).getFirstName() << " ";
      cout << vecIt1->getLastName() << endl;
      ++vecIt1;
   }
   cout << endl << endl;
  
   cout << "*** Printing out names, first name first" << endl << endl;
   print(vectorTestObj.begin(), vectorTestObj.end(), PrintFirstThenLast());
   cout << endl << endl;

   PrintFirstThenLast vecFirstObj;
   cout << "*** Printing out names, first name first, again" << endl << endl;
   print(vectorTestObj.begin(), vectorTestObj.end(), vecFirstObj);
   cout << endl << endl;

   cout << "*** Printing out names, last name first" << endl << endl;
   print(vectorTestObj.begin(), vectorTestObj.end(), PrintLastThenFirst());
   cout << endl << endl;

   PrintLastThenFirst vecLastObj;
   cout << "*** Printing out names, last name first, again" << endl << endl;
   print(vectorTestObj.begin(), vectorTestObj.end(), vecLastObj);
   cout << endl << endl;

   vector<Name>::iterator vecMarker1, vecMarker2;
   vecMarker1 = vectorTestObj.begin();
   ++vecMarker1;
   ++vecMarker1;
   ++vecMarker1;
   vecMarker2 = vectorTestObj.end();
   --vecMarker2;
   --vecMarker2;

   cout << "*** Printing out subset, first name first" << endl << endl;
   print(vecMarker1, vecMarker2, vecFirstObj);
   cout << endl << endl;
   
   cout << "*** Printing out subset, last name first" << endl << endl;
   print(vecMarker1, vecMarker2, vecLastObj);
   cout << endl << endl;




   
   cout << "*** Printing all names with last name Williams, ";
   cout << "in first/last form" << endl << endl;
   printRelevant(vectorTestObj.begin(), vectorTestObj.end(), CompareLast(),
                       testName1, PrintFirstThenLast());
   cout << endl << endl;


   cout << "*** Printing all names with first name Bob, ";
   cout << "in last, first form" << endl << endl;
   printRelevant(vectorTestObj.begin(), vectorTestObj.end(), CompareFirst(),
                       testName1, PrintLastThenFirst());
   cout << endl << endl;


   CompareFirst vecCompFirstObj;
   
   cout << "*** Printing all names in subset with first name Bob, ";
   cout << "in last, first form" << endl << endl;
   printRelevant(vecMarker1, vecMarker2, vecCompFirstObj,
                           testName1, PrintLastThenFirst());

   cout << endl << endl << endl;


   cout << "*** Then -- we run the exact same tests on Arrays..." << endl;
   cout << endl << endl << endl;;



   Array<Name> arrayTestObj(100, 117);    
   arrayTestObj[100] = Name("Susan", "Williams");
   arrayTestObj[101] = Name("Fred", "Williams");
   arrayTestObj[102] = Name("Sam", "Jackson");
   arrayTestObj[103] = Name("Boba", "Fett");
   arrayTestObj[104] = Name("Roberta", "Williams");
   arrayTestObj[105] = Name("Bob", "Collins");
   arrayTestObj[106] = Name("Frank", "Collins");
   arrayTestObj[107] = Name("Frank", "Williams");
   arrayTestObj[108] = Name("Susan", "Jackson");
   arrayTestObj[109] = Name("Michael", "Jackson");
   arrayTestObj[110] = Name("Sam", "Wiliams");
   arrayTestObj[111] = Name("Williams", "Jackson");
   arrayTestObj[112] = Name("Sam", "Bob");
   arrayTestObj[113] = Name("Robin", "Williams");
   arrayTestObj[114] = Name("Roberta", "Jackson");
   arrayTestObj[115] = Name("Fred", "Jackson");
   arrayTestObj[116] = Name("Michael", "Collins");
   arrayTestObj[117] = Name("Bob", "Fett");


   cout << "*** Printing out names, first name first, without using function";
   cout << endl << endl;
   Array<Name>::iterator arrIt1;
   arrIt1 = arrayTestObj.begin();
   while (arrIt1 != arrayTestObj.end())
   {
      cout << (*arrIt1).getFirstName() << " ";
      cout << arrIt1->getLastName() << endl;
      ++arrIt1;
   }
   cout << endl << endl;
  
   cout << "*** Printing out names, first name first" << endl << endl;
   print(arrayTestObj.begin(), arrayTestObj.end(), PrintFirstThenLast());
   cout << endl << endl;

   PrintFirstThenLast arrFirstObj;
   cout << "*** Printing out names, first name first, again" << endl << endl;
   print(arrayTestObj.begin(), arrayTestObj.end(), arrFirstObj);
   cout << endl << endl;

   cout << "*** Printing out names, last name first" << endl << endl;
   print(arrayTestObj.begin(), arrayTestObj.end(), PrintLastThenFirst());
   cout << endl << endl;

   PrintLastThenFirst arrLastObj;
   cout << "*** Printing out names, last name first, again" << endl << endl;
   print(arrayTestObj.begin(), arrayTestObj.end(), arrLastObj);
   cout << endl << endl;

   Array<Name>::iterator arrMarker1, arrMarker2;
   arrMarker1 = arrayTestObj.begin();
   ++arrMarker1;
   ++arrMarker1;
   ++arrMarker1;
   arrMarker2 = arrayTestObj.end();
   --arrMarker2;
   --arrMarker2;

   cout << "*** Printing out subset, first name first" << endl << endl;
   print(arrMarker1, arrMarker2, arrFirstObj);
   cout << endl << endl;
   
   cout << "*** Printing out subset, last name first" << endl << endl;
   print(arrMarker1, arrMarker2, arrLastObj);
   cout << endl << endl;




   
   cout << "*** Printing all names with last name Williams, ";
   cout << "in first/last form" << endl << endl;
   printRelevant(arrayTestObj.begin(), arrayTestObj.end(), CompareLast(),
                       testName1, PrintFirstThenLast());
   cout << endl << endl;


   cout << "*** Printing all names with first name Bob, ";
   cout << "in last, first form" << endl << endl;
   printRelevant(arrayTestObj.begin(), arrayTestObj.end(), CompareFirst(),
                       testName1, PrintLastThenFirst());
   cout << endl << endl;


   CompareFirst arrCompFirstObj;
   
   cout << "*** Printing all names in subset with first name Bob, ";
   cout << "in last, first form" << endl << endl;
   printRelevant(arrMarker1, arrMarker2, arrCompFirstObj,
                           testName1, PrintLastThenFirst());
   cout << endl << endl;


   return EXIT_SUCCESS;
}


