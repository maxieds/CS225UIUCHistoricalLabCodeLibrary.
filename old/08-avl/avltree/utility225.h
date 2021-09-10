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
int operator!=(const Etype& firstVal, const Etype& secondVal)
{
   return !(firstVal == secondVal);
}



// operator>
//    - parameters : firstVal - the first of two values to be compared 
//                 : secondVal - the second of two values to be compared
//    - return type : boolean integer
//    - returns 1 if firstVal > secondVal, 0 else
template <class Etype>
int operator>(const Etype& firstVal, const Etype& secondVal)
{
   return (secondVal < firstVal);
}



// operator<=
//    - parameters : firstVal - the first of two values to be compared 
//                 : secondVal - the second of two values to be compared
//    - return type : boolean integer
//    - returns 1 if firstVal <= secondVal, 0 else
template <class Etype>
int operator<=(const Etype& firstVal, const Etype& secondVal)
{
   return !(secondVal < firstVal);
}



// operator>=
//    - parameters : firstVal - the first of two values to be compared 
//                 : secondVal - the second of two values to be compared
//    - return type : boolean integer
//    - returns 1 if firstVal >= secondVal, 0 else
template <class Etype>
int operator>=(const Etype& firstVal, const Etype& secondVal)
{
   return !(firstVal < secondVal);
}


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
   pair() : first(), second()  {}


   // pair
   //    - constructor
   //    - parameters : firstVal - value of the first type
   //                 : secondVal - value of the second type
   //    - sets object to hold parameter values
   pair(const Type1& firstVal, const Type2& secondVal) :  
                          first(firstVal), second(secondVal)  {}
     

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
pair<Type1, Type2> make_pair(Type1 firstVal, Type2 secondVal)
{
   return pair<Type1, Type2>(firstVal, secondVal);
}


// operator==
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is equal to the secondpair, 0 else.
template <class Type1, class Type2>
int operator==(const pair<Type1, Type2>& firstpair, 
			const pair<Type1, Type2>& secondpair)
{ 
   // two pairs are equal if their first elements are equal and
   //   their second elements are equal
   return ((firstpair.first == secondpair.first) && 
		(firstpair.second == secondpair.second)); 
}


// operator<
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is less than the secondpair, 0 else.
template <class Type1, class Type2>
int operator<(const pair<Type1, Type2>& firstpair, 
				const pair<Type1, Type2>& secondpair)
{ 
   //  firstpair is less than secondpair if either:
   //    1) firstpair's first element is less than secondpair's 
   //        first element; that is, the first element is the key
   //        and the key is most important for comparison, so 
   //        if firstpair.first < secondpair.first, that automatically
   //        means firstpair < secondpair regardless of the relationship
   //        between the second elements of both pairs
   //    2) assuming that (1) was not the case, we at least don't
   //        want the secondpair's first element to be less than
   //        firstpair's first element. So, if (1) doesn't hold,
   //        our second case will only hold if 
   //        secondpair.first is not less than firstpair.first.
   //        Once we have established that, we also need for 
   //        firstpair's second element to be less than secondpair's
   //        second element. So, there are two conditions inherent
   //        in case (2), and they must both be true for (2) to be
   //        true.  
   return ((firstpair.first < secondpair.first) || 
                     (   (!(secondpair.first < firstpair.first)) && 
	                 (firstpair.second < secondpair.second)   )); 
}



   // ***** Once you have defined == and <, the other four operations
   //       follow from those definitions


// operator!=
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair != the secondpair, 0 else.
template <class Type1, class Type2>
int operator!=(const pair<Type1, Type2>& firstpair, 
			const pair<Type1, Type2>& secondpair)
{
   return !(firstpair==secondpair);
}




// operator<=
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is <= the secondpair, 0 else.
template <class Type1, class Type2>
int operator<=(const pair<Type1, Type2>& firstpair, 
                        const pair<Type1, Type2>& secondpair)
{
   return !(secondpair < firstpair);
}



// operator>
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is greater than the secondpair, 0 else.
template <class Type1, class Type2>
int operator>(const pair<Type1, Type2>& firstpair, 
                        const pair<Type1, Type2>& secondpair)
{
   return (secondpair < firstpair);
}



// operator>=
//    - parameters : firstpair - the first of two pairs to compare
//                 : secondpair - the second of two pairs to compare
//    - return value : boolean integer
//    - returns 1 if the firstpair is >= the secondpair, 0 else.
template <class Type1, class Type2>
int operator>=(const pair<Type1, Type2>& firstpair, 
                        const pair<Type1, Type2>& secondpair)
{
   return !(firstpair < secondpair); 
}



#endif



