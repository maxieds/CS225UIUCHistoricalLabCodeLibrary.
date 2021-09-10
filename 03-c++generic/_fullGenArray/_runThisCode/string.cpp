// ********************************************************
// *                                                      *
// *   string.cpp                                         *
// *                                                      *
// *   Implementation for a character string class.       *
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

// *** includes of files in the standard library

#include <cstring>    // contains the strlen and strcmp functions
#include <iostream>   // contains output stream tools

// lack of the line
//     using namespace std;
// here means we have to have "std::" in front of all usages 
// of ostream below. If we indicated we were using the
// "std" namespace, then we automatically get to use everything
// in that namespace -- including ostream -- without specifically 
// noting that it is from the std namespace.



// *** includes of our own declarations

#include "string.h"
#include "asserts.h"



// String
//    - constructor
//    - initializes object to the empty string
String::String()
{
   stringLength = 0;
   stringArray = new char[1];
   stringArray[0] = '\0';
}




// String
//    - constructor
//    - parameters : initString - a pointer to a character array;
//                     that character array cannot be changed
//                     through the parameter pointer
//    - initializes object to the string stored in the character
//         array
String::String(char const * initString) 
{ 
    if (initString == NULL)
    {
        stringLength = 0; 
        stringArray = new char[1];  
        stringArray[0]='\0';
    }
    else
    {
        stringLength = strlen(initString); 
        stringArray = new char[stringLength+1];
        for (int i = 0; i <= stringLength; i++)
            stringArray[i] = initString[i];
    }
}



// String
//    - constructor
//    - parameters : origVal - reference to previously-created String
//                    object; that String object cannot be changed
//                    through the parameter reference variable
//    - initializes object to be a copy of origVal
String::String(String const & origVal)
{
    stringLength = origVal.stringLength; 
    stringArray = new char[stringLength+1]; 
    for (int i = 0; i <= stringLength; i++)
        stringArray[i] = origVal.stringArray[i];
}


 
// ~String
//    - destructor
//    - deletes dynamically allocated memory
String::~String()
{ 
   delete[] stringArray; 
}



// operator=
//    - parameters : origVal - reference to previously-created String
//                    object; that String object cannot be changed 
//                    through the parameter reference variable
//    - return value : reference to this String object, after the 
//          assignment operation has been performed; we cannot change
//          this object through the returned reference
//    - assigns this object to be a copy of origVal
String const & String::operator=(String const & origVal)
{
   if (this != &origVal) 
   {
      delete[] stringArray;

      stringLength = origVal.stringLength; 
      stringArray = new char[stringLength+1]; 
      for (int i = 0; i <= stringLength; i++)
         stringArray[i] = origVal.stringArray[i];
   }
   return *this;
}




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
char String::operator[](int index) const
{
    Assert(((index >= 0) && (index <= stringLength)),
             "Index to string is out of bounds.");
    return stringArray[index];
}




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
char & String::operator[](int index) 
{
    Assert(((index >= 0) && (index <= stringLength)), 
             "Index to string is out of bounds.");
    return stringArray[index];
}





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
String String::substring(int startIndex, int substringLength) const
{
   Assert((startIndex >= 0) && (startIndex < stringLength), 
                 "Start of substring not in string bounds.");  
   Assert((substringLength >= 0), 
                 "Length of substring cannot be negative."); 

   // if substringLength is too big for end of string, reduce
   //   it accordingly. stringLength - 1 is last non-null index
   //   of string, and startIndex + substringLength - 1 is
   //   index of last character of proposed substring.
   if (startIndex + substringLength - 1 > stringLength - 1)
      substringLength = stringLength - startIndex;


   // copy relevant characters into new array 
   char* substringArray = new char[substringLength + 1];   
   for (int i = startIndex; i < startIndex + substringLength; i++)
      substringArray[i - startIndex] = (*this)[i];
   substringArray[substringLength] = '\0';


   // use array to initialize String object
   String finalSubstring(substringArray); 
   delete[] substringArray;
   return finalSubstring;
}



 

// concat
//    - parameters : secondString - reference to another String object;
//                      that String object cannot be changed through
//                      the parameter reference variable
//    - return value : a String object
//    - creates a String object, initialized to the concatenation
//         of this String object and the parameter String object, 
//         and returns a copy of that newly-created String object
String String::concat(String const & secondString) const
{
   int firstLength = stringLength; 
   int concatStringLength = stringLength + secondString.stringLength; 
   char* concatArray = new char[concatStringLength + 1]; 

   for (int i = 0; i < firstLength; i++)
      concatArray[i] = (*this)[i]; 
   for (int i = firstLength; i < concatStringLength; i++)
      concatArray[i] = secondString[i - firstLength];  
   concatArray[concatStringLength] = '\0'; 

   String finalConcat(concatArray); 
   delete[] concatArray;
   return finalConcat;
}
 



// length
//    - return value : integer stringLengthgth of string
//    - returns the number of characters in the String
//         (not counting terminating null character)
//    - this function cannot change this String
int String::length() const
{
   return stringLength;
}




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
bool String::operator==(String const & secondString) const
{
   return strcmp(stringArray, secondString.stringArray) == 0;
}




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
bool String::operator!=(String const & secondString) const
{
   return strcmp(stringArray, secondString.stringArray) != 0;
}



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
bool String::operator<(String const & secondString) const
{
   return strcmp(stringArray, secondString.stringArray) < 0;
}




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
bool String::operator>(String const & secondString) const
{
   return strcmp(stringArray, secondString.stringArray) > 0;
}




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
bool String::operator<=(String const & secondString) const
{
   return strcmp(stringArray, secondString.stringArray) <= 0;
}



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
bool String::operator>=(String const & secondString) const
{
   return strcmp(stringArray, secondString.stringArray) >= 0;
}




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
std::ostream & operator<<(std::ostream & Out, 
                                 String const & outputString)
{
    Out << outputString.stringArray;
    return Out;
}
 
 
