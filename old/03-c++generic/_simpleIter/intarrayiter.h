// *****************************************************
// *                                                   *
// *   intarray.h                                      *   
// *                                                   *
// *   Interface for an integer array class            * 
// *                                                   *
// *   Modified from the generalized array class in    *
// *    array.h September 2004 by Jason Zych           * 
// *                                                   * 
// *****************************************************

#ifndef INTARRAYITER_H
#define INTARRAYITER_H

#include <iostream>

class IntArrayIter
{
public:

   class iterator
   {
   public:


      // iterator
      //    - constructor
      //    - initializes this iterator to NULL
      iterator();


      // operator*
      //    - return type : a reference to the element type
      //    - returns by reference the element (or rather, element
      //         cell) that this iterator points to. No error
      //         checking is done to make sure iterator points to
      //         a legitimate location first.
      int& operator*();

  
      // operator++ (prefix version)
      //    - return type : reference to an iterator
      //    - moves this iterator one position forward, and then
      //         returns the iterator (holding the new value). No
      //         error checking is done to make sure this operation
      //         is legitimate first.
      iterator& operator++();


      // operator-- (prefix version)
      //    - return type : reference to an iterator
      //    - moves this iterator one position backward, and then
      //         returns the iterator (holding the new value). No
      //         error checking is done to make sure this operation
      //         is legitimate first.
      iterator& operator--();


      // operator==
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter
      //         iterator point to the same location, 0 else
      int operator==(const iterator& origVal) const;


      // operator!=
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter
      //         iterator point different locations, 0 else
      int operator!=(const iterator& origVal) const;

   private:

      int* ptr;
      friend class IntArrayIter;

   };




   // IntArrayIter
   //    - default constructor
   //    - initializes a zero-element array
   IntArrayIter();


   // IntArrayIter
   //    - constructor
   //    - parameters : low - lower bound of array
   //                 : hi - higher bound of array
   //    - initializes a hi-low+1 element array
   IntArrayIter(int low, int hi); 


   // IntArrayIter
   //    - copy constructor
   //    - parameters : origVal - previously declared IntArrayIter object
   //    - initializes array to be a copy of origVal	
   IntArrayIter(const IntArrayIter& origVal);

 
   // ~IntArrayIter
   //    - destructor
   //    - deletes dynamically allocated memory	
   ~IntArrayIter(); 


   // operator=
   //    - parameters : origVal - previously allocated IntArrayIter object
   //    - return value : reference to this IntArrayIter object
   //    - sets object to be a copy of origVal
   const IntArrayIter& operator=(const IntArrayIter& origVal);
 

   // operator[]
   //    - parameters : index - integer index
   //    - return type : constant reference to value in array cell; 
   //    - returns constant reference to array value at location 
   //         indicated by index. Since the return value is constant,
   //         this means that the returned cell cannot be used as an
   //         lvalue. This function is the operator[] that will be 
   //         invoked on const objects and references to const objects. 
   const int& operator[](int index) const;					



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
   int& operator[](int index);



   // Initialize
   //    - parameters : initElement - element to initialize array with
   //    - sets each cell in the array equal to initElement
   void Initialize(int initElement);



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


   // begin
   //    - return type : iterator
   //    - returns an iterator that points to first
   //        cell of vector
   IntArrayIter::iterator begin();


   // end
   //    - return type : iterator
   //    - returns an iterator that points to "after the last cell"
   //        so we know we are "off the vector".
   IntArrayIter::iterator end();



private:

   int lower;  // lower bound
   int upper;  // upper bound
   int* first;        // pointer to the array elements. 
   int* onePastLast;  // pointer to the memory one after the array 

};


#endif
