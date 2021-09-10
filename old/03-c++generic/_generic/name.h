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
   Name(const String& first, const String& last);


   // getFirstName
   //    - return value : a name string
   //    - returns first name
   const String& getFirstName() const;


   // getLastName
   //    - return value : a name string
   //    - returns last name
   const String& getLastName() const;
  


   // operator<< 
   //    - parameters : Out - an ostream reference 
   //                 : theName - a Name to write to output 
   //    - return value : an ostream reference
   //    - writes the given Name to the given output stream 
   friend std::ostream& operator<<(std::ostream& Out, const Name& theName);


private:

   String firstName;
   String lastName;
 
};


#endif


