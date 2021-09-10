// ********************************************************
// *                                                      * 
// *  name.cpp                                            *
// *                                                      *
// *  Implementation for a name class                     *
// *                                                      *
// *  Written October 2001 by Jason Zych                  *
// *                                                      *
// *    - changes by Jason Zych September 2004            *
// *          added operator<<                            *
// *                                                      *  
// ********************************************************

#include "name.h"

// Name
//    - constructor
//    - initializes name to be empty
Name::Name()  // : firstName(), lastName()
{
   // no code needed here
}



// Name
//    - parameters : first - the first name 
//                 : last - the last name
//    - initializes object to parameter values. 
Name::Name(const String& first, const String& last) : 
                                  firstName(first), lastName(last)
{
   // no code needed here
}



// getFirstName
//    - return value : a name string
//    - returns first name
const String& Name::getFirstName() const
{
   return firstName;
}


// getLastName
//    - return value : a name string
//    - returns last name
const String& Name::getLastName() const
{
   return lastName;
}
 


// operator<<
//    - parameters : Out - an ostream reference
//                 : theName - a Name to write to output 
//    - return value : an ostream reference
//    - writes the given Name to the given output stream
std::ostream& operator<<(std::ostream& Out, const Name& theName)
{
   Out << theName.lastName << ", " << theName.firstName;
   return Out;
}



