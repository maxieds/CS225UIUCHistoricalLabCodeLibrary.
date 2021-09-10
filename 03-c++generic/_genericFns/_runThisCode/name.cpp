// ********************************************************
// *                                                      *   
// *  name.cpp                                            *
// *                                                      *
// *  Implementation for a name class                     *
// *                                                      *
// *  Written October 2001 by Jason Zych                  *
// *                                                      *
// *    - changes by Jason Zych September 2004            *
// *         - added operator<<                           *
// *                                                      *
// *    - changes by Jason Zych January 2005              *
// *        - const standardized on right side of         *
// *               modified item                          *
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
Name::Name(String const & first, String const & last) : 
                                  firstName(first), lastName(last)
{
   // no code needed here
}



// getFirstName
//    - return value : a name string
//    - returns first name
String const & Name::getFirstName() const
{
   return firstName;
}


// getLastName
//    - return value : a name string
//    - returns last name
String const & Name::getLastName() const
{
   return lastName;
}
 


// operator<<
//    - parameters : Out - an ostream reference
//                 : theName - a Name to write to output 
//    - return value : an ostream reference
//    - writes the given Name to the given output stream
std::ostream& operator<<(std::ostream& Out, Name const & theName)
{
   Out << theName.lastName << ", " << theName.firstName;
   return Out;
}



