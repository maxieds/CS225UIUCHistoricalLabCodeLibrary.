// *****************************************************
// *                                                   *
// *   simpleArray.cpp                                 *
// *                                                   *
// *   Implementation for a generalized array class    *
// *                                                   *
// *   Written June 1998 by Jason Zych                 *
// *                                                   *
// *     - changes by Jason Zych October 1999          *
// *        - added constructor to create an array     *
// *           of size 0                               *
// *       - altered other functions so that an array  *
// *           of size 0 is supported                  *
// *                                                   *
// *     - changes by Jason Zych October 2004          *
// *        - #ifndef macro name changed               *
// *        - const standardized on right of item      *
// *        - comments enhanced                        *
// *        - some code clean-up done                  *
// *        - class changed to typename for generic    *
// *             variable                              *
// *                                                   *
// *     - changes by Jason Zych January 2005          *
// *        - name of type changed to SimpleArray,     * 
// *              along with related changes to        *
// *              comments, #ifndef macro, etc.        *
// *        - put <Etype> qualifier for the name of    *
// *             type into header file                 *
// *                                                   *
// *****************************************************

#include <cstddef>    // for definition of NULL

#include "asserts.h"
#include "simpleArray.h"


// SimpleArray
//    - constructor
//    - initializes object to be a zero-element array; low and high
//        indices will be 0 and -1, respectively
template <typename Etype>
SimpleArray<Etype>::SimpleArray()
{
   lowerBound = 0;
   upperBound = -1;
   data = NULL;
}




// SimpleArray
//    - constructor
//    - parameters : low - desired lower bound of array
//                 : high - desired higher bound of array
//    - high is required to be greater than or equal to low - 1; if it
//       is not, an assertion is triggered. Assuming high >= low - 1,
//        initializes object to be a (high - low + 1)-element array; cells
//        themselves are uninitialized (for primitive types) or
//        initialized using the no-argument constructor (for non-primitive
//        types). Note that if high == low - 1, then the value of the
//        expression high - low + 1 is 0 and we create an SimpleArray
//        object without any legal indices
template <typename Etype>
SimpleArray<Etype>::SimpleArray(int low, int high)
{
   Assert(high >= low - 1, 
                  "SimpleArray: illegal bounds in SimpleArray(int, int)");
   lowerBound = low;
   upperBound = high;

   // When we create array below, all values in array cells are 
   // automatically initialized using no-argument constructor of
   // Etype (if Etype is a primitive type, this no-argument constructor 
   // does nothing, so cells hold garbage)
   data = new Etype[upperBound - lowerBound + 1]; 
}




// SimpleArray
//    - constructor
//    - parameters : origVal - reference to previously-created SimpleArray
//                    object; that SimpleArray object cannot be changed 
//                    through the parameter reference
//    - initializes array to be a copy of origVal
template <typename Etype>
SimpleArray<Etype>::SimpleArray(SimpleArray<Etype> const & origVal)
{
   // set the bounds of the array
   lowerBound = origVal.lowerBound;  
   upperBound = origVal.upperBound;   

   if (lowerBound <= upperBound)
   {
      data = new Etype[upperBound - lowerBound + 1];  
      for (int i = lowerBound; i <= upperBound; ++i)
         data[i - lowerBound] = (origVal.data)[i - lowerBound];
   }
   else    // lowerBound > upperBound ===> lowerBound - 1 == upperBound
      data = NULL;
}


 
// ~SimpleArray
//    - destructor
//    - deletes dynamically allocated memory
template <typename Etype>
SimpleArray<Etype>::~SimpleArray() 
{
   delete[] data;
}




// operator=
//    - parameters : origVal - reference to previously-created SimpleArray
//                    object; that SimpleArray object cannot be changed 
//                    through the parameter reference
//    - return value : reference to this SimpleArray object, after the
//        assignment operation has been performed; we cannot change this 
//        object through the returned reference
//    - assigns this object to be a copy of origVal
template <typename Etype>
SimpleArray<Etype> const & 
           SimpleArray<Etype>::operator=(SimpleArray<Etype> const & origVal)
{
   if (this != &origVal)  // self-assignment check
   {
      delete[] data;

      // set the bounds of the array  
      lowerBound = origVal.lowerBound;
      upperBound = origVal.upperBound;

      if (lowerBound <= upperBound)
      {
         data = new Etype[upperBound - lowerBound + 1];
         for (int i = lowerBound; i <= upperBound; ++i)
            data[i - lowerBound] = (origVal.data)[i - lowerBound];
      }
      else
         data = NULL;
   }	
   return *this;
}





// operator[]
//    - parameters : index - integer index into array
//    - return type : reference to the array cell at the parameter index;
//         value stored in array cell cannot be changed through the
//         returned reference
//    - This version of the operator[] will be called on const objects.
//       The parameter index is required to be a legal index into the
//       array, i.e. lowerBound <= index and index <= upperBound. (Note 
//       that for arrays of size 0, there *is* no legal index.) If the 
//       index is NOT legal, an assertion is triggered. Otherwise, the 
//       function returns a reference to the array cell at the given 
//       index, but the array cell is const (i.e. its value cannot be 
//       changed if accessed through the returned index.
template <typename Etype>
Etype const & SimpleArray<Etype>::operator[](int index) const
{
   Assert((lowerBound <= index) && (index <= upperBound), 
                    "SimpleArray: illegal index in operator[](int) const");
   return (data[index - lowerBound]);
}




// operator[]
//    - parameters : index - integer index into array
//    - return type : reference to the array cell at the parameter index
//    - This version of the operator[] will be called on non-const objects.
//       The parameter index is required to be a legal index into the
//       array, i.e. lowerBound <= index and index <= upperBound. (Note
//       that for arrays of size 0, there *is* no legal index.) If the
//       index is NOT legal, an assertion is triggered. Otherwise, the
//       function returns a reference to the array cell at the given index.
template <typename Etype>
Etype & SimpleArray<Etype>::operator[](int index) 
{
   Assert((lowerBound <= index) && (index <= upperBound), 
                         "SimpleArray: illegal index in operator[](int)");
   return (data[index - lowerBound]);
}





// initialize
//    - parameters : initElement - reference to object with which to
//                     initialize the array; that object cannot be
//                     changed through the parameter reference
//    - assigns each cell in the array to hold a copy of parameter value
template <typename Etype>
void SimpleArray<Etype>::initialize(Etype const & initElement)
{
   for (int i = lowerBound; i <= upperBound; ++i)
      data[i - lowerBound] = initElement;
}



// setBounds
//    - parameters : theLow - desired new lower bound of array
//                 : theHigh - desired new upper bound of array
//    - theHigh is required to be greater than or equal to theLow - 1; 
//        if it is not, an assertion is triggered. Assuming
//        theHigh >= theLow - 1,assigns object to be a 
//        (theHigh - theLow + 1)-element array. For any indices in
//        the array's new index range (theLow <= index <= theHigh) that 
//        were also in the array's old index range 
//        (lower() <= index <= upper()), the cells at those contain the
//        same values that they contained before this function was called. 
//        For any indices in the array's new index range that were NOT 
//        in the array's old index range, the cells at those indices are 
//        uninitialized (for primitive types) or initialized using the
//        no-argument constructor (for non-primitive types). For any 
//        indices in the array's old index range that are NOT indices in
//        the array's new index range, the values in the cells at those
//        indices are lost, since we no longer have cells with those 
//        indices in our array.
template <typename Etype>
void SimpleArray<Etype>::setBounds(int theLow, int theHigh)
{
   Assert(theHigh >= theLow - 1, 
                  "SimpleArray: illegal bounds in setBounds(int, int)");

   // create the new array; our member variable "data" will 
   //   ultimately point to this new array
   Etype * newData;
   int newSize = theHigh - theLow + 1;
   if (newSize == 0)
      newData = NULL; 
   else
      newData = new Etype[newSize]; // all values automatically initialized
                                    //  using no-argument constructor of Etype
                                    //  (if Etype is a primitive type, this
                                    //  no-argument constructor does nothing,
                                    //  so cells hold garbage)


   // Deal with the intersection of old and new ranges, if there is one.
   // If one or both of the ranges is size 0, there definitely isn't any
   // intersection. Otherwise, we need to check.
   int lowIntersect, highIntersect;
   if ((theHigh >= theLow) && (upperBound >= lowerBound)) // both size >= 1
   {
      // greater of two low values is low bound of intersection
      if (theLow > lowerBound)
         lowIntersect = theLow;        // new low value
      else
         lowIntersect = lowerBound;    // old low value

      // lowerBound of two high values is high bound of intersection
      if (theHigh < upperBound)
         highIntersect = theHigh;      // new high value
      else
         highIntersect = upperBound;   // old high value
  
      // Transfer data from old to new.
      for (int i = lowIntersect; i <= highIntersect; ++i)
         newData[i - theLow] = data[i - lowerBound];
   }

   delete[] data;    // deallocate old array
   data = newData;   // the new array is now this object's array
   lowerBound = theLow;      // set internal bounds to be equal
   upperBound = theHigh;     //    to the parameter bounds
}
 

 
 
// size
//    - return value : non-negative integer
//    - returns size of array
template <typename Etype>
int SimpleArray<Etype>::size() const 
{
   return (upperBound - lowerBound + 1);
}



// lower
//    - return value : integer index
//    - returns "lower bound" index of array. If array has size >= 1,
//        this will be lowest legal index of array. If array is of 
//        size 0, then this will be an integer one greater than the
//        value returned by upper(), but will not be a legal index.
template <typename Etype>
int SimpleArray<Etype>::lower() const 
{ 
   return lowerBound;
}



// upper
//    - return value : integer index
//    - returns "upper bound" of array. If array has size >= 1,
//        this will be highest legal index of array. If array is of
//        size 0, then this will be an integer one less than the
//        value returned by lower(), but will not be a legal index.
template <typename Etype>
int SimpleArray<Etype>::upper() const 
{
   return upperBound;
}




