// ********************************************************
// *                                                      * 
// *  name.h                                              *
// *                                                      *
// *  Interface for a name class                          *
// *                                                      *
// *  Written October 2001 by Jason Zych                  *
// *                                                      *
// *    - changes by Jason Zych September 2004            *
// *          added operator<<                            *
// *                                                      *
// *    - changes by Jason Zych January 2005              *
// *        - const standardized on right side of         * 
// *               modified item                          *
// *                                                      *
// ********************************************************

#ifndef NAME_H
#define NAME_H

#include <iostream>
#include "string.h"

class Name
{
public:

   // Name
   //    - constructor
   //    - initializes name to be empty
   Name();


   // Name
   //    - parameters : first - the first name 
   //                 : last - the last name
   //    - initializes object to parameter values. 
   Name(String const & first, String const & last);


   // getFirstName
   //    - return value : a name string
   //    - returns first name
   String const & getFirstName() const;


   // getLastName
   //    - return value : a name string
   //    - returns last name
   String const & getLastName() const;
  


   // operator<< 
   //    - parameters : Out - an ostream reference 
   //                 : theName - a Name to write to output 
   //    - return value : an ostream reference
   //    - writes the given Name to the given output stream 
   friend std::ostream& operator<<(std::ostream& Out, Name const & theName);


private:

   String firstName;
   String lastName;
 
};


#endif


