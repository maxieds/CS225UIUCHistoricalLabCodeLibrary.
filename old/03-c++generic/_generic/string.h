// ********************************************************
// *                                                      *
// *   string.h                                           *    
// *                                                      *
// *   Interface for a character string class.            *
// *     NOTE: This interface does not exactly match      *
// *     that of the C++ standard library string          *
// *     class; it's a separate String class entirely.    *
// *                                                      *
// *   Written 6/16/98 by Jason Zych                      *
// *                                                      *
// *    - changes by Jason Zych January 2003:             *
// *       - remaining const correctness added            *
// *       - assorted comments/other style issues tweaked *
// *       - operator<= and operator>= added              *
// *                                                      *
// *    - changes by Jason Zych August 2004:              *
// *       - default value in const char* constructor     *
// *          eliminated and new, no-argument constructor *
// *          written to handle that case instead.        *
// *       - operator+ renamed to concat                  *
// *                                                      *   
// ********************************************************
 
#ifndef STRING_CS225_H
#define STRING_CS225_H

#include <cstdlib>
#include <iostream>

class String
{
public:

   // String
   //    - constructor
   //    - initializes object to the empty string
   String();



   // String
   //    - constructor 
   //    - parameters : initString - a pointer to a character array 
   //    - initializes object to the string stored in the character 
   //         array 
   String(const char* initString);



   // String
   //    - copy constructor
   //    - parameters : origVal - previously allocated String object
   //    - initializes object to be a copy of origVal
   String(const String& origVal);



   // ~String
   //    - destructor
   //    - deletes dynamically allocated memory
   ~String();



   // operator=
   //    - parameters : origVal - previously allocated String object
   //    - return value : reference to String object
   //    - sets object to be a copy of origVal  
   const String& operator=(const String& origVal);



   // operator[]
   //    - parameters : index - the index into the String array
   //    - return value : const reference to a character object
   //    - This version of the operator[] function will be called
   //        on const String objects. It returns a const reference 
   //         to the String character located at the parameter index. 
   //         An assertion is triggered if the index is not a legal
   //         index for the String (legal indices are be between 0 
   //         and the length of the String, inclusive -- storing
   //         a "real" character or the String-terminating null
   //         character. 
   const char& operator[](int index) const;



   // operator[]
   //    - parameters : index - the index into the String array
   //    - return value : reference to a character object
   //    - This version of the operator[] function will be called on
   //         non-const String objects. It returns a non-const reference 
   //         to the String character located at the parameter index. 
   //         An assertion is triggered if the index is not a legal
   //         index for the String (legal indices are be between 0 
   //         and the length of the String, inclusive -- storing
   //         a "real" character or the String-terminating null
   //         character. 
   char& operator[](int index);



   // substring
   //    - parameters : startIndex - index in string where substring 
   //                        begins
   //                 : substringLength - length of substring
   //    - return value : a String object
   //    - returns a String which is a substring of this object, 
   //         starting at parameter index and with parameter length.
   //         If the suffix starting at startIndex is less than the
   //         requested substring length, then the substring
   //         consisting of only that suffix is what is returned.
   //         Assertions are triggered if the starting index of
   //         the substring is not a real (non-null) character of
   //         the String, and if the substring length is negative.  
   String substring(int startIndex, int substringLength) const;



   // concat
   //    - parameters : secondString - the second string in the 
   //                      concatenation
   //    - return value : a String value  
   //    - creates a String formed by concatenating this string
   //         and the parameter String, and returns that String 
   String concat(const String& secondString) const;



   // length
   //    - return value : integer length of string
   //    - returns the number of characters in the String
   //            (not counting terminating null character)
   int length() const;



   // operator==
   //    - parameters : secondString - the second string in the 
   //                         comparison
   //    - return value : a boolean-valued integer
   //    - returns 1 if this string is equal to the parameter
   //        string, 0 otherwise 
   int operator==(const String& secondString) const;

 

   // operator!= 
   //    - parameters : secondString - the second string in the 
   //                        comparison
   //    - return value : a boolean-valued integer
   //    - returns 1 if this string is not equal to the parameter
   //       String, 0 otherwise
   int operator!=(const String& secondString) const;



   // operator< 
   //    - parameters : secondString - the second string in the 
   //                       comparison
   //    - return value : a boolean-valued integer
   //    - returns 1 if the this string comes before the second in 
   //         alphabetical order; 0 otherwise 
   int operator<(const String& secondString) const;



   // operator> 
   //    - parameters : secondString - the second string in the 
   //                      comparison
   //    - return value : a boolean-valued integer
   //    - returns 1 if the first string comes after the second in 
   //         alphabetical order; 0 otherwise
   int operator>(const String& secondString) const;



   // operator<=
   //    - parameters : secondString - the second string in the 
   //                       comparison
   //    - return value : a boolean-valued integer
   //    - returns 1 if the this string comes before the second in
   //         alphabetical order or they are equivalent; 0 otherwise
   int operator<=(const String& secondString) const;



   // operator>=
   //    - parameters : secondString - the second string in the 
   //                      comparison
   //    - return value : a boolean-valued integer
   //    - returns 1 if the first string comes after the second in
   //         alphabetical order or they are equal; 0 otherwise
   int operator>=(const String& secondString) const;


   // operator<< 
   //    - parameters : Out - an ostream reference 
   //                 : outputString - a String to write to output 
   //    - return value : an ostream reference
   //    - writes the given String to the given output stream 
   friend std::ostream& operator<<(std::ostream& Out, 
                                 const String& outputString);


private:

   int stringLength;    // length of string
   char* stringArray;   // pointer to array holding string characters 
};

#endif

