// *****************************************************
// *                                                   *
// *   intarray.cpp                                    *
// *                                                   *
// *   Implementation for an integer array class       * 
// *                                                   *
// *   Modified from the generalized array class in    *
// *    array.cpp September 2004 by Jason Zych         *
// *                                                   *
// *****************************************************

#include <iostream>
#include <cstddef>
#include "asserts.h"
#include "intarrayiter.h"


// IntArrayIter
//    - default constructor
//    - initializes a zero-element array
IntArrayIter::IntArrayIter()
{
   lower = 0;
   upper = -1;
   first = NULL;
   onePastLast = NULL;
}



// IntArrayIter
//    - constructor
//    - parameters : low - lower bound of array
//                 : hi - higher bound of array
//    - initializes a up-low+1 element array
IntArrayIter::IntArrayIter(int low, int hi)
{
   Assert(low <= hi+1, "Illegal bounds in constructor");
   lower = low;
   upper = hi;
   first = new int[upper - lower + 1];
   onePastLast = first + (upper - lower + 1);
}


// IntArrayIter
//    - copy constructor
//    - parameters : origVal - previously declared IntArrayIter object
//    - initializes array to be a copy of origVal   
IntArrayIter::IntArrayIter(const IntArrayIter& origVal)
{
   lower = origVal.lower;  // set the bounds of array
   upper = origVal.upper;  // 
   if (lower <= upper)
   {
      first = new int[upper - lower + 1];  // allocate new memory for array
      for (int i = lower; i <= upper; i++)
         first[i - lower] = origVal.first[i - lower];
      onePastLast = first + (upper - lower + 1);
   }
   else 
   {
      first = NULL;
      onePastLast = NULL;
   }
}


 
// ~IntArrayIter
//    - destructor
//    - deleted dynamically allocated memory
IntArrayIter::~IntArrayIter() 
{
   delete[] first;
}



// operator=
//    - parameters : origVal - previously allocated IntArrayIter object
//    - return value : reference to IntArrayIter object
//    - sets object to be a copy of origVal
const IntArrayIter& IntArrayIter::operator=(const IntArrayIter& origVal)
{
   if (this != &origVal)
   {
      lower = origVal.lower;
      upper = origVal.upper;
      delete[] first;
      if (lower <= upper)
      {
         first = new int[upper - lower + 1];
         for (int i = lower; i <= upper; i++)
            first[i - lower] = origVal.first[i - lower];
         onePastLast = first + (upper - lower + 1);
      }
      else
      {
         first = NULL;
         onePastLast = NULL;
      }
   }	
   return *this;
}



// operator[]
//    - parameters : index - integer index
//    - return type : constant reference to value in array cell;
//    - returns constant reference to array value at location
//         indicated by index. Since the return value is constant,
//         this means that the returned cell cannot be used as an
//         lvalue. This function is the operator[] that will be
//         invoked on const objects and references to const objects.
const int& IntArrayIter::operator[](int index) const
{
   Assert((index >= lower) && (index <= upper), "Illegal array index in [ ]");
   return (first[index - lower]);
}




// operator[]
//    - parameters : index - integer index
//    - return type : reference to value in array cell;
//    - returns reference to array value at location indicated
//         by index. Due to  the fact that this a reference to the
//         value and not the value itself, this effectively
//         means we are returning the array cell itself, which
//         can be read for it's value, or else written to with a
//         *new* value. This function is the operator[] invoked
//         on non-const objects or references to non-const objects.
int& IntArrayIter::operator[](int index) 
{
   Assert((index >= lower) && (index <= upper), "Illegal array index in [ ]");
   return (first[index - lower]);
}





// Initialize
//    - parameters : initElement - element to initialize array with
//    - sets each cell in the array equal to initElement
void IntArrayIter::Initialize(int initElement)
{
   for (int i=lower; i<=upper; i++)
      first[i-lower] = initElement;
}


 
// SetBounds
//    - parameters : newlow - new lower bound
//                 : newhi - new upper bound
//    - changes upper and lower bounds to up and low and
//         copies any old values in that range to the new
//         array
void IntArrayIter::SetBounds(int newlow, int newhi)
{
   Assert(newlow <= newhi+1, "Bad bounds in SetBounds");
   int* newData;
   unsigned int newSize = newhi - newlow + 1;
   if (newSize == 0)
      newData = NULL; 
   else
      newData = new int[newSize];

   // Find the intersection of old and new ranges.
   int lowMax, upMin;
   if (newlow == newhi+1)
   {
      lowMax = newlow;
      upMin = newhi;
      delete[] first; 
      first = NULL;
   }
   else 
   {
      if (lower < upper + 1)
      {
         if (lower < newlow)
            lowMax = newlow;
         else
            lowMax = lower;
         if (upper < newhi)
            upMin = upper;
         else
            upMin = newhi;
  
         // Transfer first from old to new.
         for (int i = lowMax; i <= upMin; i++)
            newData[i - newlow] = first[i - lower];
      }
   }


   delete[] first;                       // Free up old first array,
   first = newData;                      // and use the first in the new array.
       
   lower = newlow;
   upper = newhi;
}
 

 
 
// Size
//    - return value : integer size
//    - returns size of array
int IntArrayIter::Size() const 
{
   return (upper - lower + 1);
}



// Lower
//    - return value : integer index
//    - returns lower bound of array
int IntArrayIter::Lower() const 
{ 
   return lower;
}


// Upper
//    - return value : integer index
//    - returns upper bound of array
int IntArrayIter::Upper() const 
{
   return upper;
}


// begin
//    - return type : iterator
//    - returns an iterator that points to first
//        cell of vector
IntArrayIter::iterator IntArrayIter::begin()
{
   IntArrayIter::iterator temp;
   temp.ptr = first;
   return temp;
}




// end
//    - return type : iterator
//    - returns an iterator that points to "after the last cell"
//        so we know we are "off the vector".
IntArrayIter::iterator IntArrayIter::end()
{
   IntArrayIter::iterator temp;
   temp.ptr = onePastLast;
   return temp;
}



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
int& IntArrayIter::iterator::operator*()
{
   return *ptr;
}



// operator++ (prefix version)
//    - return type : reference to an iterator
//    - moves this iterator one position forward, and then 
//         returns the iterator (holding the new value). No
//         error checking is done to make sure this operation
//         is legitimate first.
IntArrayIter::iterator& IntArrayIter::iterator::operator++()
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
IntArrayIter::iterator& IntArrayIter::iterator::operator--()
{
   ptr = ptr - 1;  // pointer arithmetic, not integer addition
   return *this;
}


// operator==
//    - parameters : origVal - previously created iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter 
//         iterator point to the same location, 0 else
int IntArrayIter::iterator::operator==(const iterator& origVal) const
{
   return (ptr == origVal.ptr);
}


// operator!=
//    - parameters : origVal - previously created iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter 
//         iterator point different locations, 0 else
int IntArrayIter::iterator::operator!=(const iterator& origVal) const
{
   return (ptr != origVal.ptr);
}



