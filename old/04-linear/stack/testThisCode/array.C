// *****************************************************
// *                                                   *
// *   array.C                                         *
// *                                                   *
// *   Implementation for a generalized array class    *
// *                                                   *
// *   Written 6/16/98 by Jason Zych                   *
// *     October 14 1999 -- support added for arrays   *
// *       of size 0 by Jason Zych. The default array  *
// *       is now of size 0 rather than 1, so that you *
// *       can (for example) always create an array of *
// *       the needed size even if the needed size is  * 
// *       zero.                                       *
// *                                                   *
// *                                                   *
// *****************************************************

 
#include <iostream.h>
#include <stddef.h>
#include "array.h"
#include "asserts.h"

// Array
//    - default constructor
//    - initializes a zero-element array
template<class Etype>
Array<Etype>::Array()
{
   lower = 0;
   upper = -1;
   data = NULL;
}

// Array
//    - constructor
//    - parameters : low - lower bound of array
//                 : hi - higher bound of array
//    - initializes a up-low+1 element array
template<class Etype>
Array<Etype>::Array(int low, int hi)
{
   Assert(low <= hi+1, "Illegal bounds in constructor");
   lower = low;
   upper = hi;
   data = new Etype[upper - lower + 1];
}


// Array
//    - copy constructor
//    - parameters : origVal - previously declared Array object
//    - initializes array to be a copy of origVal   
template<class Etype>
Array<Etype>::Array(const Array<Etype>& origVal)
{
   lower = origVal.lower;  // set the bounds of array
   upper = origVal.upper;  // 
   if (lower <= upper)
   {
      data = new Etype[upper - lower + 1];  // allocate new memory for array
      for (int i = lower; i <= upper; i++)
         data[i - lower] = origVal.data[i - lower];
   }
   else 
      data = NULL;
}


 
// ~Array
//    - destructor
//    - deleted dynamically allocated memory
template <class Etype>
Array<Etype>::~Array() 
{
   delete[] data;
}



// operator=
//    - parameters : origVal - previously allocated Array object
//    - return value : reference to Array object
//    - sets object to be a copy of origVal
template<class Etype>
const Array<Etype>& Array<Etype>::operator= (const Array<Etype>& origVal)
{
   if (this != &origVal)
   {
      lower = origVal.lower;
      upper = origVal.upper;
      delete[] data;
      if (lower <= upper)
      {
         data = new Etype[upper - lower + 1];
         for (int i = lower; i <= upper; i++)
            data[i - lower] = origVal.data[i - lower];
      }
      else
         data = NULL;
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
template<class Etype>
const Etype& Array<Etype>::operator[] (int index) const
{
   Assert((index >= lower) && (index <= upper), "Illegal array index in [ ]");
   return (data[index - lower]);
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
template<class Etype>
Etype& Array<Etype>::operator[] (int index) 
{
   Assert((index >= lower) && (index <= upper), "Illegal array index in [ ]");
   return (data[index - lower]);
}





// Initialize
//    - parameters : initElement - element to initialize array with
//    - sets each cell in the array equal to initElement
template<class Etype>
void Array<Etype>::Initialize(Etype initElement)
{
   for (int i=lower; i<=upper; i++)
      data[i-lower] = initElement;
}


 
// SetBounds
//    - parameters : newlow - new lower bound
//                 : newhi - new upper bound
//    - changes upper and lower bounds to up and low and
//         copies any old values in that range to the new
//         array
template<class Etype>
void Array<Etype>::SetBounds(int newlow, int newhi)
{
   Assert(newlow <= newhi+1, "Bad bounds in SetBounds");
   Etype* newData;
   unsigned int newSize = newhi - newlow + 1;
   if (newSize == 0)
      newData = NULL; 
   else
      newData = new Etype[newSize];

   // Find the intersection of old and new ranges.
   int lowMax, upMin;
   if (newlow == newhi+1)
   {
      lowMax = newlow;
      upMin = newhi;
      delete[] data; 
      data = NULL;
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
  
         // Transfer data from old to new.
         for (int i = lowMax; i <= upMin; i++)
            newData[i - newlow] = data[i - lower];
      }
   }


   delete[] data;                       // Free up old data array,
   data = newData;                      // and use the data in the new array.
       
   lower = newlow;
   upper = newhi;
}
 

 
 
// Size
//    - parameters : none
//    - return value : integer
//    - returns size of array
template <class Etype>
int Array<Etype>::Size() const 
{
   return (upper - lower + 1);
}



// Lower
//    - parameters : none
//    - return value : integer
//    - returns lower bound of array
template <class Etype>
int Array<Etype>::Lower() const 
{ 
   return lower;
}


// Upper
//    - parameters : none
//    - return value : integer
//    - returns upper bound of array
template <class Etype>
int Array<Etype>::Upper() const 
{
   return upper;
}




