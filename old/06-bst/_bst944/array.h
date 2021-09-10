// *****************************************************
// *                                                   *
// *   array.h                                         *   
// *                                                   *
// *   Interface for a generalized array class         * 
// *                                                   *
// *   Written 6/16/98 by Jason Zych                   * 
// *                                                   * 
// *****************************************************

#ifndef _ARRAY_H
#define _ARRAY_H

#include <iostream.h>

template<class Etype>
class Array
{
public:

   // Array
   //    - default constructor
   //    - initializes a zero-element array
   Array();


   // Array
   //    - constructor
   //    - parameters : low - lower bound of array
   //                 : hi - higher bound of array
   //    - initializes a hi-low+1 element array
   Array(int low, int hi); 


   // Array
   //    - copy constructor
   //    - parameters : origVal - previously declared Array object
   //    - initializes array to be a copy of origVal	
   Array(const Array& origVal);

 
   // ~Array
   //    - destructor
   //    - deletes dynamically allocated memory	
   ~Array(); 


   // operator=
   //    - parameters : origVal - previously allocated Array object
   //    - return value : reference to this Array object
   //    - sets object to be a copy of origVal
   const Array& operator=(const Array& origVal);
 

   // operator[]
   //    - parameters : index - integer index
   //    - return type : constant reference to value in array cell; 
   //    - returns constant reference to array value at location 
   //         indicated by index. Since the return value is constant,
   //         this means that the returned cell cannot be used as an
   //         lvalue. This function is the operator[] that will be 
   //         invoked on const objects and references to const objects. 
   const Etype& operator[](int index) const;					



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
   Etype& operator[](int index);



   // Initialize
   //    - parameters : initElement - element to initialize array with
   //    - sets each cell in the array equal to initElement
   void Initialize(Etype initElement);



   // SetBounds
   //    - parameters : low - new lower bound
   //                 : hi - new upper bound
   //    - changes upper and lower bounds to up and low and
   //         copies any old values in that range to the new
   //         array
   void SetBounds(int low, int hi);



   // Size
   //    - return value : integer size
   //    - returns size of array 
   int Size() const; 


   // Lower
   //    - return value : integer index
   //    - returns lower bound of array
   int Lower() const; 


   // Upper
   //    - return value : integer index
   //    - returns upper bound of array
   int Upper() const; 


private:

   int lower;  // lower bound
   int upper;  // upper bound
   Etype *data; // Pointer to the array elements. 

};


#endif
