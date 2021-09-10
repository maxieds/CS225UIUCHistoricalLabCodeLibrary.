// ***********************************************************
// *                                                         *
// *   generic.h                                             * 
// *                                                         *
// *   Declarations for generic functions                    *
// *                                                         *
// *   Written June 2002 by Jason Zych                       *
// *                                                         *
// *    - changes by Jason Zych January 2005                 *
// *        - const standardized on right side of            *   
// *               modified item                             *
// *                                                         *
// ***********************************************************

#ifndef GENERIC_H
#define GENERIC_H

#include "name.h"


// ******** Generic functions **************


// print
//    - parameters : first- iterator to the first value in the
//                             relevant range
//                 : last - iterator just past the last value in
//                              the relevant_range
//                 : printer - a function object for formatting
//                               the value_type of the iterator
//    - prints out every element in the range [first, last), 
//       using the Formatter parameter to format the information
template <typename Iterator, typename Formatter>
void print(Iterator first, Iterator last, Formatter printer);



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
template <typename Iterator, typename SearchCriteria, 
          typename Ktype, typename Formatter>
void printRelevant(Iterator first, Iterator last, SearchCriteria tester,
                     Ktype item, Formatter printer);





   // ************************************************************
   // *                                                          *
   // *  PrintLastThenFirst                                      * 
   // *                                                          *
   // *  Function object class for printing a Name object, with  *
   // *  the last name first                                     * 
   // *                                                          *
   // ************************************************************ 


class PrintLastThenFirst
{
public:

   // PrintLastThenFirst
   //    - constructor
   //    - does nothing since there are no member variables
   PrintLastThenFirst();

   // operator()
   //    - parameters : item - the name to print
   //    - prints out the Name item, last name before first name,
   //         with a comma in between
   void operator()(Name const & item) const;
};




   // ************************************************************
   // *                                                          *
   // *  PrintFirstThenLast                                      *
   // *                                                          *
   // *  Function object class for printing a Name object, with  *
   // *  the first name prior to the last name                   *
   // *                                                          *
   // ************************************************************


class PrintFirstThenLast
{
public:

   // PrintFirstThenLast
   //    - constructor
   //    - does nothing since there are no member variables
   PrintFirstThenLast();

   // operator()
   //    - parameters : item - the name to print
   //    - prints out the Name item, first name before last name,
   void operator()(Name const & item) const;
};




   // ************************************************************
   // *                                                          *
   // *  CompareFirst                                            *
   // *                                                          *
   // *  Function object class for comparing two Names based     *
   // *  on first name                                           *
   // *                                                          *
   // ************************************************************


class CompareFirst
{
public:

   // CompareFirst
   //    - constructor
   //    - does nothing since there are no member variables
   CompareFirst();


   // operator()
   //    - parameters : first - one of the two names to compare
   //                 : second - the other of the two names to compare
   //    - returns 1 if the first names of the two parameters are
   //         equal; returns 0 otherwise.
   int operator()(Name const & first, Name const & second) const;
};




   // ************************************************************
   // *                                                          *
   // *  CompareLast                                             *
   // *                                                          *
   // *  Function object class for comparing two Names based     *
   // *  on last name                                            *
   // *                                                          *
   // ************************************************************


class CompareLast
{
public:

   // CompareLast
   //    - constructor
   //    - does nothing since there are no member variables
   CompareLast();


   // operator()
   //    - parameters : first - one of the two names to compare
   //                 : second - the other of the two names to compare
   //    - returns 1 if the last names of the two parameters are
   //         equal; returns 0 otherwise.
   int operator()(Name const & first, Name const & second) const;
};



#endif

