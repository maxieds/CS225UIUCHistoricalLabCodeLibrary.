// ***********************************************************
// *                                                         *
// *   generic.C                                             *
// *                                                         *
// *   Definitions for generic functions                     *
// *                                                         *
// *   Written June 2002 by Jason Zych                       *
// *                                                         * 
// ***********************************************************

#include <iostream>
using namespace std;

#include "generic.h"
#include "string.h"


// print
//    - parameters : first- iterator to the first value in the
//                             relevant range
//                 : last - iterator just past the last value in
//                              the relevant_range
//                 : printer - a function object for formatting
//                               the value_type of the iterator
//    - prints out every element in the range [first, last), 
//       using the Formatter parameter to format the information
template <class Iterator, class Formatter>
void print(Iterator first, Iterator last, Formatter printer)
{
   while (first != last)
   {
      printer(*first);
      ++first;
   }
}



// printRelevant
//    - parameters : first- iterator to the first value in the
//                             relevant range
//                 : last - iterator just past the last value in
//                              the relevant_range
//                 : tester - a function object for testing 
//                               our values in some way to produce
//                               true or false
//                 : item - an item to search for
//                 : printer - a function object for formatting
//                               the value_type of the iterator
//    - prints out every element in the range [first, last),
//        that equals item using our "tester" function as the
//        criteria for comparison. Printing is done using the
//        printer as a formatter.
template <class Iterator, class SearchCriteria, class Ktype, class Formatter>
void printRelevant(Iterator first, Iterator last, SearchCriteria tester,
                     Ktype item, Formatter printer)
{
   while (first != last)
   {
      if (tester(*first, item))
         printer(*first);
      ++first;
   }
}



// PrintLastThenFirst
//    - constructor
//    - does nothing since there are no member variables
PrintLastThenFirst::PrintLastThenFirst()
{
   // no code here
}
 


// operator()
//    - parameters : item - the name to print
//    - prints out the Name item, last name before first name,
//         with a comma in between
void PrintLastThenFirst::operator()(const Name& item) const
{
   cout << item.getLastName() << ", " << item.getFirstName() << endl;
}



// PrintFirstThenLast
//    - constructor
//    - does nothing since there are no member variables
PrintFirstThenLast::PrintFirstThenLast()
{
   // no code here
}




// operator()
//    - parameters : item - the name to print
//    - prints out the Name item, first name before last name,
void PrintFirstThenLast::operator()(const Name& item) const
{
   cout << item.getFirstName() << " " << item.getLastName() << endl;
}




// CompareFirst
//    - constructor
//    - does nothing since there are no member variables
CompareFirst::CompareFirst()
{
   // no code here
}



// operator()
//    - parameters : first - one of the two names to compare
//                 : second - the other of the two names to compare
//    - returns 1 if the first names of the two parameters are
//         equal; returns 0 otherwise.
int CompareFirst::operator() (const Name& first, const Name& second) const
{
   return (first.getFirstName() == second.getFirstName());
}



// CompareLast
//    - constructor
//    - does nothing since there are no member variables
CompareLast::CompareLast()
{
   // no code here
}



// operator()
//    - parameters : first - one of the two names to compare
//                 : second - the other of the two names to compare
//    - returns 1 if the last names of the two parameters are
//         equal; returns 0 otherwise.
int CompareLast::operator() (const Name& first, const Name& second) const
{
   return (first.getLastName() == second.getLastName());
}




