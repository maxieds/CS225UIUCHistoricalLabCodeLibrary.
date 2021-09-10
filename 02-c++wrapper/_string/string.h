// ********************************************************
// *                                                      *
// *   string.h                                           *    
// *                                                      *
// *   Interface for a character string class.            *
// *     NOTE: This interface does not exactly match      *
// *     that of the C++ standard library string          *
// *     class; it's a separate String class entirely.    *
// *                                                      *
// *   Written June 1998 by Jason Zych                    *
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
// *    - changes by Jason Zych October 2004:             *
// *       - const standardized on right side of          *
// *          modified item                               *
// *       - enhanced some comments                       *
// *       - replaced int with bool as comparison         *
// *            return type                               *
// *                                                      *   
// *    - changes by Jason Zych January 2005:             *
// *       - return value of const version of operator[]  *
// *           changed from "by const reference" to       *
// *           "by value"                                 *
// *                                                      *
// ********************************************************

// every header file declaring a class, needs a #ifndef setup like 
//   this to avoid issues with multiple inclusion

#ifndef STRING_225_H
#define STRING_225_H



// *** includes of files in the standard library

#include <iostream>    // contains output stream tools 

// lack of the line
//     using namespace std;
// here means we have to have "std::" in front of all usages 
// of ostream below. If we indicated we were using the
// "std" namespace, then we automatically get to use everything
// in that namespace -- including ostream -- without specifically 
// noting that it is from the std namespace.




class String
{
public:

   // String
   //    - constructor
   //    - initializes object to the empty string
   String();



   // String
   //    - constructor 
   //    - parameters : initString - a pointer to a character array;
   //                     that character array cannot be changed 
   //                     through the parameter pointer 
   //    - initializes object to the string stored in the character 
   //         array 
   String(char const * initString);



   // String
   //    - constructor
   //    - parameters : origVal - reference to previously-created String
   //                    object; that String object cannot be changed
   //                    through the parameter reference variable
   //    - initializes object to be a copy of origVal
   String(String const & origVal);



   // ~String
   //    - destructor
   //    - deletes dynamically allocated memory
   ~String();



   // operator=
   //    - parameters : origVal - reference to previously-created String
   //                    object; that String object cannot be changed 
   //                    through the parameter reference variable
   //    - return value : reference to this String object, after the 
   //          assignment operation has been performed; we cannot change
   //          this object through the returned reference
   //    - assigns this object to be a copy of origVal  
   String const & operator=(String const & origVal);



   // operator[]
   //    - parameters : index - integer index into the String
   //    - return type : copy of the character at the parameter index
   //    - This version of the operator[] will be called on const String
   //       objects. The parameter index is required to be a legal index 
   //       into the String, i.e. 0 <= index and index <= stringLength.  
   //       (If index == stringLength you are indexing the null character.)
   //       If the index is NOT legal, an assertion is triggered. Otherwise, 
   //       the function returns a copy of the character at the given index. 
   //       (Since you return a copy of that character, the String cannot
   //       have its characters changed via the use of this function.)
   char operator[](int index) const;



   // operator[]
   //    - parameters : index - integer index into the String
   //    - return type : reference to the character at the parameter
   //         index; that character cannot be changed through the 
   //         returned reference
   //    - This version of the operator[] will be called on non-const String
   //       objects. The parameter index is required to be a legal index 
   //       into the String, i.e. 0 <= index and index <= stringLength.  
   //       (If index == stringLength you are indexing the null character.)
   //       If the index is NOT legal, an assertion is triggered. Otherwise, 
   //       the function returns a reference to the character at the given 
   //       index.
   char & operator[](int index);



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
   //    - parameters : secondString - reference to another String object;
   //                      that String object cannot be changed through
   //                      the parameter reference variable
   //    - return value : a String object
   //    - creates a String object, initialized to the concatenation
   //         of this String object and the parameter String object, 
   //         and returns a copy of that newly-created String object
   String concat(String const & secondString) const;



   // length
   //    - return value : integer length of string
   //    - returns the number of characters in the String
   //        (not counting terminating null character); this
   //        function cannot change this String
   int length() const;


   
   // operator==
   //    - parameters : secondString - reference to another String object;
   //                    that String object cannot be changed through the
   //                    parameter reference variable
   //    - return value : a boolean indicating whether or not this
   //          String and the object refered to by the parameter reference
   //          are equal
   //    - returns true if this String object and the String object referred 
   //        to by the parameter reference, are a character-by-character 
   //        match. Otherwise, returns false.
   bool operator==(String const & secondString) const;

 

   // operator!=
   //    - parameters : secondString - reference to another String object;
   //                    that String object cannot be changed through the
   //                    parameter reference variable
   //    - return value : a boolean indicating whether or not this
   //          String and the object refered to by the parameter reference
   //          are unequal
   //    - returns true if this String object and the String object referred 
   //        to by the parameter reference, are NOT a character-by-character 
   //        match. Otherwise, returns false.
   bool operator!=(String const & secondString) const;



   // operator<
   //    - parameters : secondString - reference to another String object;
   //                    that String object cannot be changed through the
   //                    parameter reference variable
   //    - return value : a boolean indicating whether or not this
   //          String is less than the object refered to by the parameter 
   //          reference
   //    - returns true if there is at least one index where this String object 
   //       and the String object referred to by the parameter reference
   //       differ, and if at the smallest such index, this String object's 
   //       character is less than the character at that index in the 
   //       parameter String. Otherwise returns false.
   bool operator<(String const & secondString) const;



   // operator>
   //    - parameters : secondString - reference to another String object;
   //                    that String object cannot be changed through the
   //                    parameter reference variable
   //    - return value : a boolean indicating whether or not this
   //          String is greater than the object refered to by the parameter
   //          reference
   //    - returns true if there is at least one index where this String object 
   //       and the String object referred to by the parameter reference
   //       differ, and if at the smallest such index, this String object's 
   //       character is greater than the character at that index in the 
   //       parameter String. Otherwise returns false.
   bool operator>(String const & secondString) const;



   // operator<=
   //    - parameters : secondString - reference to another String object;
   //                    that String object cannot be changed through the
   //                    parameter reference variable
   //    - return value : a boolean indicating whether or not this
   //          String is less than or equal to the object refered to by 
   //          the parameter reference
   //    - returns true if either this String and the String referred to
   //       by the parameter reference are a perfect character-by-
   //       character match, or else if at the lowest index where the two
   //       String objects differ, this String object's character is less 
   //       than the character at that index in the parameter String.
   //       Otherwise returns false.
   bool operator<=(String const & secondString) const;




   // operator>=
   //    - parameters : secondString - reference to another String object;
   //                    that String object cannot be changed through the
   //                    parameter reference variable
   //    - return value : a boolean indicating whether or not this
   //          String is greater than or equal to the object refered to by 
   //          the parameter reference
   //    - returns true if either this String and the String referred to
   //       by the parameter reference are a perfect character-by-
   //       character match, or else if at the lowest index where the two
   //       String objects differ, this String object's character is greater
   //       than the character at that index in the parameter String.
   //       Otherwise returns false.
   bool operator>=(String const & secondString) const;


   // operator<< 
   //    - friend function of the String class, not member function
   //    - parameters : Out - a reference to an ostream object
   //                 : outputString - a reference to a String object we 
   //                     wish to write to the output stream; that String
   //                     object cannot be changed through the parameter 
   //                     reference variable
   //    - return value : the parameter ostream reference, after it has
   //          been altered through this operation
   //    - writes the data of the parameter String to the parameter  
   //        output stream, and then returns that output stream 
   friend std::ostream & operator<<(std::ostream & Out, 
                                 String const & outputString);


private:

   int stringLength;    // length of string
   char * stringArray;   // pointer to array holding string characters 
};

#endif

