// ********************************************************
// *                                                      *
// *   string.cpp                                         *
// *                                                      *
// *   Implementation for a character string class.       *
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

#include <cstring> 
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
//    - parameters : initString - a pointer to a character array
//    - initializes object to the string stored in the character
//         array
String::String(const char* initString) 
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
//    - copy constructor
//    - parameters : origVal - previously allocated String object
//    - initializes object to be a copy of origVal
String::String(const String& origVal)
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
//    - parameters : origVal - previously allocated String object
//    - return value : reference to String object
//    - sets object to be a copy of origVal
const String& String::operator=(const String& origVal)
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
const char& String::operator[](int index) const
{
    Assert(((index >= 0) && (index <= stringLength)),
             "Index to string is out of bounds.");
    return stringArray[index];
}




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
char& String::operator[](int index) 
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
//    - parameters : secondString - the second string in the 
//                      concatenation
//    - return value : a String value
//    - creates a String formed by concatenating this string
//         and the parameter String, and returns that String
String String::concat(const String& secondString) const
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
//            (not counting terminating null character)
int String::length() const
{
   return stringLength;
}



// operator==
//    - parameters : secondString - the second string in the
//                         comparison
//    - return value : a boolean-valued integer
//    - returns 1 if this string is equal to the parameter
//        string, 0 otherwise
int String::operator==(const String& secondString) const
{
   return strcmp(stringArray, secondString.stringArray) == 0;
}



// operator!=
//    - parameters : secondString - the second string in the
//                        comparison
//    - return value : a boolean-valued integer
//    - returns 1 if this string is not equal to the parameter
//       String, 0 otherwise
int String::operator!=(const String& secondString) const
{
   return strcmp(stringArray, secondString.stringArray) != 0;
}



// operator<
//    - parameters : secondString - the second string in the
//                       comparison
//    - return value : a boolean-valued integer
//    - returns 1 if the this string comes before the second in
//         alphabetical order; 0 otherwise
int String::operator<(const String& secondString) const
{
   return strcmp(stringArray, secondString.stringArray) < 0;
}




// operator>
//    - parameters : secondString - the second string in the
//                      comparison
//    - return value : a boolean-valued integer
//    - returns 1 if the first string comes after the second in
//         alphabetical order; 0 otherwise
int String::operator>(const String& secondString) const
{
   return strcmp(stringArray, secondString.stringArray) > 0;
}




// operator<=
//    - parameters : secondString - the second string in the
//                       comparison
//    - return value : a boolean-valued integer
//    - returns 1 if the this string comes before the second in
//         alphabetical order or they are equivalent; 0 otherwise
int String::operator<=(const String& secondString) const
{
   return strcmp(stringArray, secondString.stringArray) <= 0;
}




// operator>=
//    - parameters : secondString - the second string in the
//                      comparison
//    - return value : a boolean-valued integer
//    - returns 1 if the first string comes after the second in
//         alphabetical order or they are equal; 0 otherwise
int String::operator>=(const String& secondString) const
{
   return strcmp(stringArray, secondString.stringArray) >= 0;
}




// operator<<
//    - parameters : Out - an ostream reference
//                 : outputString - a String to write to output 
//    - return value : an ostream reference
//    - writes the given String to the given output stream
std::ostream& operator<<(std::ostream& Out, 
                                 const String& outputString)
{
    Out << outputString.stringArray;
    return Out;
}
 
 
