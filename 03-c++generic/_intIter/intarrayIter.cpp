// ********************************************************
// *                                                      *
// *   intarrayIter.cpp                                   *
// *                                                      *
// *   Implementation for an integer array class that     *
// *    has a simple iterator available                   *
// *                                                      *
// *   Modified from the integer array class file         *
// *    intarray.cpp January 2005 by Jason Zych           *
// *                                                      *
// ********************************************************

#include <cstddef>    // for definition of NULL

#include "asserts.h"
#include "intarrayIter.h"


   
// **************************************************
// *      member functions for iterator class       *
// **************************************************   


// iterator
//    - constructor
//    - initializes this iterator to NULL
IntArrayIter::iterator::iterator() 
{
   ptr = NULL;
}


// operator*
//    - return type : a reference to the element type
//    - returns by reference the element (or rather, element 
//         cell) that this iterator points to. No error
//         checking is done to make sure iterator points to
//         a legitimate location first.
int & IntArrayIter::iterator::operator*()
{
   return *ptr;
}



// operator++ (prefix version)
//    - return type : reference to an iterator
//    - moves this iterator one position forward, and then 
//         returns the iterator (holding the new value). No
//         error checking is done to make sure this operation
//         is legitimate first.
IntArrayIter::iterator & IntArrayIter::iterator::operator++()
{
   ptr = ptr + 1;  // pointer arithmetic, not integer addition
   return *this;
}


// operator-- (prefix version)
//    - return type : reference to an iterator
//    - moves this iterator one position backward, and then 
//         returns the iterator (holding the new value). No
//         error checking is done to make sure this operation
//         is legitimate first. 
IntArrayIter::iterator & IntArrayIter::iterator::operator--()
{
   ptr = ptr - 1;  // pointer arithmetic, not integer addition
   return *this;
}


// operator==
//    - parameters : origVal - previously created iterator
//    - return value : boolean with true indicating equality
//    - returns true if this iterator and the parameter 
//         iterator point to the same location, else returns false
bool IntArrayIter::iterator::operator==(
                       IntArrayIter::iterator const & origVal) const
{
   return (ptr == origVal.ptr);
}



   
// **************************************************
// *     member functions for IntArrayIter class    *
// **************************************************   




// IntArrayIter
//    - constructor
//    - initializes object to be a zero-element array; low and high
//        indices will be 0 and -1, respectively
IntArrayIter::IntArrayIter()
{
   lowerBound = 0;
   upperBound = -1;
   data = NULL;
   onePastLast = NULL;
}




// IntArrayIter
//    - constructor
//    - parameters : low - desired lower bound of array
//                 : high - desired higher bound of array
//    - high is required to be greater than or equal to low - 1; if it
//       is not, an assertion is triggered. Assuming high >= low - 1,
//        initializes object to be a (high - low + 1)-element array; cells
//        themselves are uninitialized. Note that if high == low - 1, then 
//        the value of the expression high - low + 1 is 0 and we create an 
//        IntArrayIter object without any legal indices
IntArrayIter::IntArrayIter(int low, int high)
{
   Assert(high >= low - 1, 
                "IntArrayIter: illegal bounds in IntArrayIter(int, int)");
   lowerBound = low;
   upperBound = high;

   // When we create array below, all values in array cells are 
   // automatically initialized using no-argument constructor of
   // int -- which does nothing, so cells hold garbage
   data = new int[upperBound - lowerBound + 1]; 

   onePastLast = data + (upperBound - lowerBound + 1);
}




// IntArrayIter
//    - constructor
//    - parameters : origVal - reference to previously-created IntArrayIter
//                    object; that IntArrayIter object cannot be changed through
//                    the parameter reference
//    - initializes array to be a copy of origVal
IntArrayIter::IntArrayIter(IntArrayIter const & origVal)
{
   // set the bounds of the array
   lowerBound = origVal.lowerBound;  
   upperBound = origVal.upperBound;   

   if (lowerBound <= upperBound)
   {
      data = new int[upperBound - lowerBound + 1];  
      for (int i = lowerBound; i <= upperBound; ++i)
         data[i - lowerBound] = (origVal.data)[i - lowerBound];
      onePastLast = data + (upperBound - lowerBound + 1);
   }
   else    // lowerBound > upperBound ===> lowerBound - 1 == upperBound
   {
      data = NULL;
      onePastLast = NULL;
   }
}


 
// ~IntArrayIter
//    - destructor
//    - deletes dynamically allocated memory
IntArrayIter::~IntArrayIter() 
{
   delete[] data;
}




// operator=
//    - parameters : origVal - reference to previously-created IntArrayIter
//                    object; that IntArrayIter object cannot be changed through
//                    the parameter reference
//    - return value : reference to this IntArrayIter object, after the
//        operation has been performed; we cannot change this object
//        through the returned reference
//    - assigns this object to be a copy of origVal
IntArrayIter const & IntArrayIter::operator=(IntArrayIter const & origVal)
{
   if (this != &origVal)  // self-assignment check
   {
      delete[] data;

      // set the bounds of the array  
      lowerBound = origVal.lowerBound;
      upperBound = origVal.upperBound;

      if (lowerBound <= upperBound)
      {
         data = new int[upperBound - lowerBound + 1];
         for (int i = lowerBound; i <= upperBound; ++i)
            data[i - lowerBound] = (origVal.data)[i - lowerBound];
         onePastLast = data + (upperBound - lowerBound + 1);
      }
      else
      {
         data = NULL;
         onePastLast = NULL;
      }
   }	
   return *this;
}





// operator[]
//    - parameters : index - integer index into array
//    - return type : copy of the value in the array cell at the   
//                        parameter index
//    - This version of the operator[] will be called on const objects.
//       The parameter index is required to be a legal index into the
//       array, i.e. lowerBound <= index and index <= upperBound. (Note
//       that for arrays of size 0, there *is* no legal index.) If the
//       index is NOT legal, an assertion is triggered. Otherwise, the
//       function returns a copy of the value in the array cell at the
//       given index. (Since you return a copy of what is in the cell, 
//       the value in the cell cannot be changed via the use of this 
//       function.)
int IntArrayIter::operator[](int index) const
{
   Assert((lowerBound <= index) && (index <= upperBound), 
                   "IntArrayIter: illegal index in operator[](int) const");
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
int & IntArrayIter::operator[](int index) 
{
   Assert((lowerBound <= index) && (index <= upperBound), 
                      "IntArrayIter: illegal index in operator[](int)");
   return (data[index - lowerBound]);
}





// initialize
//    - parameters : initElement - reference to object with which to
//                     initialize the array; that object cannot be
//                     changed through the parameter reference
//    - assigns each cell in the array to hold a copy of parameter value
void IntArrayIter::initialize(int initElement)
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
//        uninitialized. For any indices in the array's old index range 
//        that are NOT indices in the array's new index range, the values 
//        in the cells at those indices are lost, since we no longer have 
//        cells with those indices in our array.
void IntArrayIter::setBounds(int theLow, int theHigh)
{
   Assert(theHigh >= theLow - 1, 
                    "IntArrayIter: illegal bounds in setBounds(int, int)");

   // create the new array; our member variable "data" will 
   //   ultimately point to this new array
   int * newData;
   int newSize = theHigh - theLow + 1;
   if (newSize == 0)
      newData = NULL; 
   else
      newData = new int[newSize]; // all values automatically initialized
                                    //  using no-argument constructor of int
                                    //  -- which does nothing, so cells 
                                    //  hold garbage)


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
   onePastLast = data + (upperBound - lowerBound + 1); // set "end" pointer
}
 

 
 
// size
//    - return value : non-negative integer
//    - returns size of array
int IntArrayIter::size() const 
{
   return (upperBound - lowerBound + 1);
}



// lower
//    - return value : integer index
//    - returns "lower bound" index of array. If array has size >= 1,
//        this will be lowest legal index of array. If array is of 
//        size 0, then this will be an integer one greater than the
//        value returned by upper(), but will not be a legal index.
int IntArrayIter::lower() const 
{ 
   return lowerBound;
}



// upper
//    - return value : integer index
//    - returns "upper bound" of array. If array has size >= 1,
//        this will be highest legal index of array. If array is of
//        size 0, then this will be an integer one less than the
//        value returned by lower(), but will not be a legal index.
int IntArrayIter::upper() const 
{
   return upperBound;
}



// begin
//    - return type : iterator
//    - returns an iterator that points to first
//        cell of the array
IntArrayIter::iterator IntArrayIter::begin()
{
   IntArrayIter::iterator temp;
   temp.ptr = data;
   return temp;
}



// end
//    - return type : iterator
//    - returns an iterator that points to the position "just after
//        the last cell of the array" so we know we are "off the
//        end of the array"
IntArrayIter::iterator IntArrayIter::end()
{
   IntArrayIter::iterator temp;
   temp.ptr = onePastLast;
   return temp;
}


