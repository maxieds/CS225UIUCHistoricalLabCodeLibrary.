// ***********************************************************
// *                                                         *
// *   iterVectorFns.cpp                                     *    
// *                                                         *
// *   Implementation for functions that perform             *
// *    iteration on vector objects                          *
// *                                                         *
// *   Written January 2005 by Jason Zych                    *
// *                                                         * 
// ***********************************************************

#include <iostream>
using namespace std;

#include "iterVectorFns.h"



// BriefForwardIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward order once
void BriefForwardIteration(vector<String> & theVector)
{
   vector<String>::iterator it1;

   cout << "*** Forward non-const iteration; prefix versions..." << endl;
   it1 = theVector.begin();
   while (it1 != theVector.end())
   {
      cout << *it1 << endl;
      ++it1;
   }
}



// ForwardIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward and reverse
//        order, twice, using an iterator. 
void ForwardIteration(vector<String> & theVector)
{
   vector<String>::iterator it1;
   
   cout << "*** Forward non-const iteration; prefix versions..." << endl;
   it1 = theVector.begin();
   while (it1 != theVector.end())
   {
      cout << *it1 << endl;
      ++it1;
   }
   cout << "...and now go backwards..." << endl;
   while (it1 != theVector.begin())  // uses operator!=
   {
      --it1;
      cout << *it1 << endl;
   } 
   cout << endl;



   cout << "*** Forward non-const iteration; postfix versions..." << endl;
   it1 = theVector.begin();
   while (it1 != theVector.end())
   {
      cout << *it1 << endl;
      it1++;
   }
   cout << "...and now go backwards..." << endl;
   while (!(it1 == theVector.begin()))  // uses operator==
   {
      it1--;
      cout << *it1 << endl;
   }
   cout << endl; 



   if (it1 != theVector.end())
   {
      vector<String>::const_iterator conit1(it1);
      cout << "Here's the first value again: " << *conit1 << endl;
   }
   cout << endl << endl;
}



// ForwardConstIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward and reverse
//        order, twice, using a const_iterator. 
void ForwardConstIteration(vector<String> const & theVector)
{
   // this line would not compile
   //    vector<String>::iterator it1 = theVector.begin();

   vector<String>::const_iterator conit1;

   cout << "*** Forward const iteration; prefix versions..." << endl;
   conit1 = theVector.begin();
   while (conit1 != theVector.end())
   {
      cout << *conit1 << endl;

      // this line would not compile
      //    *conit1 = (*conit1).concat("M");

      ++conit1;
   }
   cout << "...and now go backwards..." << endl;
   while (conit1 != theVector.begin())   // uses operator!=
   {
      --conit1;
      cout << *conit1 << endl;
   }
   cout << endl;



   cout << "*** Forward const iteration; postfix versions..." << endl;
   conit1 = theVector.begin();
   while (conit1 != theVector.end())
   {
      cout << *conit1;

      // this line would not compile
      //    conit1->operator[](conit1->length() - 1) = 'L';

      cout << " (the last character is: ";
      cout << conit1->operator[](conit1->length() - 1) << ")" << endl;

      conit1++;
   }
   cout << "...and now go backwards..." << endl;
   while (!(conit1 == theVector.begin()))   // uses operator==
   {
      conit1--;
      cout << *conit1 << endl;
   } 
   cout << endl << endl;
}



// ReverseIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in "reverse order" forwards
//        and backwards, twice, using a reverse_iterator. 
void ReverseIteration(vector<String> & theVector)
{
   vector<String>::reverse_iterator revit1;

   cout << "*** Reverse non-const iteration; prefix versions..." << endl;
   revit1 = theVector.rbegin();
   while (revit1 != theVector.rend())
   {
      cout << *revit1 << endl;
      ++revit1;
   }
   cout << "...and now go backwards..." << endl;
   while (revit1 != theVector.rbegin())    // uses operator!=
   {
      --revit1;
      cout << *revit1 << endl;
   }
   cout << endl;



   cout << "*** Reverse non-const iteration; postfix versions..." << endl;
   revit1 = theVector.rbegin();
   while (revit1 != theVector.rend())
   {
      cout << *revit1 << endl;
      revit1++;
   }
   cout << "...and now go backwards..." << endl;
   while (!(revit1 == theVector.rbegin()))    // uses operator==
   {
      revit1--;
      cout << *revit1 << endl;
   } 
   cout << endl;



   if (revit1 != theVector.rend())
   {
      vector<String>::const_reverse_iterator revconit1(revit1);
      cout << "Here's the first value again: " << *revconit1 << endl;
   }
   cout << endl << endl;
}


// ReverseConstIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in "reverse order" forwards
//        and backwards, twice, using a const_reverse_iterator. 
void ReverseConstIteration(vector<String> const & theVector)
{
   // this line would not compile
   //    vector<String>::reverse_iterator it1 = theVector.begin();

   vector<String>::const_reverse_iterator revconit1;

   cout << "*** Reverse const iteration; prefix versions..." << endl;
   revconit1 = theVector.rbegin();
   while (revconit1 != theVector.rend())
   {
      cout << *revconit1 << endl;

      // this line would not compile
      //    *revconit1 = (*revconit1).concat("M");

      ++revconit1;
   }
   cout << "...and now go backwards..." << endl;
   while (revconit1 != theVector.rbegin())    // uses operator!=
   {
      --revconit1;
      cout << *revconit1 << endl;
   }
   cout << endl;



   cout << "*** Reverse const iteration; postfix versions..." << endl;
   revconit1 = theVector.rbegin();
   while (revconit1 != theVector.rend())
   {
      cout << *revconit1;

      // this line would not compile
      //    revconit1->operator[](revconit1->length() - 1) = 'L';
  
      cout << " (the last character is: ";
      cout << revconit1->operator[](revconit1->length() - 1) << ")" << endl;

      revconit1++;
   }
   cout << "...and now go backwards..." << endl;
   while (!(revconit1 == theVector.rbegin()))      // uses operator==
   {
      revconit1--;
      cout << *revconit1 << endl;
   }
   cout << endl << endl;
}




// ForwardIterationWithChanges
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward and reverse
//        order, twice, using an iterator. A letter 'M' is 
//        added to the end of each String the first time forward, 
//        and that 'M' is changed to a 'L' the second time forward. 
void ForwardIterationWithChanges(vector<String> & theVector)
{
   vector<String>::iterator it1;
   
   cout << "*** Forward iteration using prefix versions..." << endl;
   it1 = theVector.begin();
   while (it1 != theVector.end())
   {
      cout << *it1 << endl;
      *it1 = (*it1).concat("M");
      ++it1;
   }
   cout << "...and now go backwards..." << endl;
   while (it1 != theVector.begin())  // uses operator!=
   {
      --it1;
      cout << *it1 << endl;
   } 

   cout << endl << endl;

   cout << "*** Forward iteration using postfix versions..." << endl;
   it1 = theVector.begin();
   while (it1 != theVector.end())
   {
      cout << *it1 << endl;
      it1->operator[](it1->length() - 1) = 'L';
      it1++;
   }
   cout << "...and now go backwards..." << endl;
   while (!(it1 == theVector.begin()))  // uses operator==
   {
      it1--;
      cout << *it1 << endl;
   } while (!(it1 == theVector.begin()));  

   if (it1 != theVector.end())
   {
      vector<String>::const_iterator conit1(it1);
      cout << "Here's the first value again: " << *conit1 << endl;
   }
  
   cout << endl << endl;
}



// ReverseIterationWithChanges
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in "reverse order" forwards
//        and backwards, twice, using a reverse_iterator. A letter 'M' 
//        is added to the end of each String the first time in forwards
//        "reverse order", and that 'M' is changed to a 'L' the second 
//        time forwards in "reverse order". 
void ReverseIterationWithChanges(vector<String> & theVector)
{
   vector<String>::reverse_iterator revit1;

   cout << "*** Forward iteration using prefix versions..." << endl;
   revit1 = theVector.rbegin();
   while (revit1 != theVector.rend())
   {
      cout << *revit1 << endl;
      *revit1 = (*revit1).concat("M");
      ++revit1;
   }
   cout << "...and now go backwards..." << endl;
   do
   {
      --revit1;
      cout << *revit1 << endl;
   } while (revit1 != theVector.rbegin());   // uses operator!=

   cout << endl << endl;

   cout << "*** Forward iteration using postfix versions..." << endl;
   revit1 = theVector.rbegin();
   while (revit1 != theVector.rend())
   {
      cout << *revit1 << endl;
      revit1->operator[](revit1->length() - 1) = 'L';
      revit1++;
   }
   cout << "...and now go backwards..." << endl;
   do
   {
      revit1--;
      cout << *revit1 << endl;
   } while (!(revit1 == theVector.rbegin()));   // uses operator==
   cout << endl;

   if (revit1 != theVector.rend())
   {
      vector<String>::const_reverse_iterator revconit1(revit1);
      cout << "Here's the first value again: " << *revconit1 << endl;
   }
 
   cout << endl << endl;
}




