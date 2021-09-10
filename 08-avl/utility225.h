// *************************************************************
// *                                                           *
// *  utility225.h                                             *
// *                                                           *
// *  This file provides four general relational operator      *
// *   functions and the pair class.
// *                                                           *
// *  Written July 1999 by Jason Zych                          *
// *                                                           *
// *************************************************************

#ifndef _UTILITY225_H
#define _UTILITY225_H

#include <iostream.h>


// ************ Types used to fill in the template parameter 
//              for a template class often need to have the 
//              relational operations defined. Typically, the 
//              specification requires only that the < and == operations
//              be defined, since the other four operations can be
//              derived from those two. So, the function implementations
//              below all assume that < and == exist on the Etype in
//              question.
// 
// ************ Note that we have the implementation in the .h file.
//              This *is* permissible in some situations, usually when
//              the code for a function is very short. There is also 
//              an "inline" keyword which makes these function calls
//              to short functions more efficient, but we have not 
//              discussed it yet so we will leave it out of these function
//              implementations. 
// 
// ************ Note that we went ahead and defined these four relational
//              operators again for the pair class (or rather, as global
//              functions after we had finished the pair class declaration --
//              see below). I am not entirely sure this was necessary,
//              as pair<Type1, Type2> can probably be filled in for Etype
//              below and the four functions below could be used instead. 
//              However, I have seen some implementations which implement 
//              pair's other four relational operations separately, as we
//              have done. For that reason, I defined them separately in
//              our code as well. I suspect that they were originally 
//              defined separately for the purposes of getting around any
//              difficulty compilers may have had filling in generic types
//              with other template expressions, as we would be doing
//              if we replaced Etype below with some pair<Type1, Type2> 
//              expression.



// operator!=
//    - parameters : firstVal - the first of two values to be compared
//                 : secondVal - the second of two values to be compared
//    - return type : boolean integer
//    - returns 1 if firstVal != secondVal, 0 else
template <class Etype>
int operator!=(const Etype& firstVal, const Etype& secondVal);



// operator>
//    - parameters : firstVal - the first of two values to be compared 
//                 : secondVal - the second of two values to be compared
//    - return type : boolean integer
//    - returns 1 if firstVal > secondVal, 0 else
template <class Etype>
int operator>(const Etype& firstVal, const Etype& secondVal);



// operator<=
//    - parameters : firstVal - the first of two values to be compared 
//                 : secondVal - the second of two values to be compared
//    - return type : boolean integer
//    - returns 1 if firstVal <= secondVal, 0 else
template <class Etype>
int operator<=(const Etype& firstVal, const Etype& secondVal);



// operator>=
//    - parameters : firstVal - the first of two values to be compared 
//                 : secondVal - the second of two values to be compared
//    - return type : boolean integer
//    - returns 1 if firstVal >= secondVal, 0 else
template <class Etype>
int operator>=(const Etype& firstVal, const Etype& secondVal);



template <class Type1, class Type2>
class pair
{
public:

   // ************* Useful type definitions for later
 
   typedef Type1 first_type;  // whatever Type1 is can now also
                              // be called First_Type...well, 
                              // with some scoping restrictions 
                              // that we won't worry about right now

   typedef Type2 second_type; // whatever Type2 is can now also
                              // be called Second_Type...well, 
                              // with some scoping restrictions 
                              // that we won't worry about right now


 
   // ************ Member functions 

   // pair
   //    - default constructor
   //    - sets object to hold default values
   //        (on the initializer line, each member variable
   //         is being initialized to the default value
   //         of the appropriate type) 
   pair();


   // pair
   //    - constructor
   //    - parameters : firstVal - value of the first type
   //                 : secondVal - value of the second type
   //    - sets object to hold parameter values
   pair(const Type1& firstVal, const Type2& secondVal);



  // There is also another constructor that is similar to a 
  // copy constructor but makes use of the Type1 and Type2 constructors,
  // but it requires template member functions and the compiler isn't
  // fond of those, so we'll leave it out right now.
 


   // ************* Member data
   //    - we intend for the data to be public, too

   Type1 first;       // variable of the first type
   Type2 second;      // variable of the second type

};   // end of pair class






// ************ Helpful functions for pair which we will just
//               put in the .h since they are so short. This is
//               actually okay in certain cases but it is an
//               issue we haven't discussed yet. We also haven't
//               gone over the "inline" command so I will leave
//               that out even though it would be helpful to use 
//               such a command here to improve code efficiency.
// 



// make_pair
//    - parameters : firstVal - value of the first type of pair
//                 : secondVal - value of the second type of pair
//    - returns a pair object holding the two parameter values
template <class Type1, class Type2>
pair<Type1, Type2> make_pair(Type1 firstVal, Type2 secondVal);



// operator==
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is equal to the secondpair, 0 else.
template <class Type1, class Type2>
int operator==(const pair<Type1, Type2>& firstpair, 
                           const pair<Type1, Type2>& secondpair);



// operator<
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is less than the secondpair, 0 else.
template <class Type1, class Type2>
int operator<(const pair<Type1, Type2>& firstpair, 
				const pair<Type1, Type2>& secondpair);



// operator!=
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair != the secondpair, 0 else.
template <class Type1, class Type2>
int operator!=(const pair<Type1, Type2>& firstpair, 
			const pair<Type1, Type2>& secondpair);



// operator<=
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is <= the secondpair, 0 else.
template <class Type1, class Type2>
int operator<=(const pair<Type1, Type2>& firstpair, 
                        const pair<Type1, Type2>& secondpair);



// operator>
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is greater than the secondpair, 0 else.
template <class Type1, class Type2>
int operator>(const pair<Type1, Type2>& firstpair, 
                        const pair<Type1, Type2>& secondpair);




// operator>=
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is >= the secondpair, 0 else.
template <class Type1, class Type2>
int operator>=(const pair<Type1, Type2>& firstpair, 
                        const pair<Type1, Type2>& secondpair);




#endif



