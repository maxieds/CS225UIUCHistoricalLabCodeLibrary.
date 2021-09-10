// *************************************************************
// *                                                           *
// *  utility225.cpp                                           *
// *                                                           *
// *  This file provides definitions for the four general      *
// *  relational operator functions and the pair class.        * 
// *                                                           *
// *  Written July 1999 by Jason Zych                          *
// *                                                           *
// *************************************************************


#include "utility225.h"


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



// pair
//    - default constructor
//    - sets object to hold default values
//        (on the initializer line, each member variable
//         is being initialized to the default value
//         of the appropriate type) 
template <class Type1, class Type2>
pair<Type1, Type2>::pair() : first(), second()  {}


// pair
//    - constructor
//    - parameters : firstVal - value of the first type
//                 : secondVal - value of the second type
//    - sets object to hold parameter values
template <class Type1, class Type2>
pair<Type1, Type2>::pair(const Type1& firstVal, const Type2& secondVal) :  
                          first(firstVal), second(secondVal)  {}
     



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




