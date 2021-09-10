// *************************************************
// *                                               *
// *  kheap.cpp                                    *
// *                                               *
// *  Implementation file for a KeyHeap class      *
// *                                               *
// *  Written by Mark Allen Weiss                  *
// *     Revised 10/97 by Partha Ramachandran      *
// *     Revised 31 October 1997 by Jason Zych     *
// *     Revised 10 March 1998 by David Anderson   *
// *                                               *
// *************************************************

#include "asserts.h"
#include "array.h"
#include "kheap.h"


// KeyHeap
//    - default constructor
//    - parameters: initSize - an integer that provides the size
//       of the heap that should be allocated
//    - allocated and initializes the heap
template <class Ktype, class Etype>
KeyHeap<Ktype, Etype>::KeyHeap(unsigned int initSize)
{
   numElements = 0;
   maxSize = initSize; 
   elements.SetBounds(1, maxSize);
}

// KeyHeap
//    - copy constructor
//    - parameters: origHeap - the heap to create from
//    - creates a new heap that has the same values stored in it
//       as origHeap does
//    - assuming that operator= is defined for Ktype and Etype,
//       the resulting copy will be a deep copy
template <class Ktype, class Etype>
KeyHeap<Ktype, Etype>::KeyHeap(const KeyHeap<Ktype, Etype>& origHeap)
{
   numElements = origHeap.numElements;
   maxSize = origHeap.maxSize;
   elements = origHeap.elements;
   for (int i = 1; i <= numElements; i++)
      elements[i] = new HeapNode(*(origHeap.elements[i]));

}

// ~KeyHeap
//    - destructor
//    - deletes the dynamically allocated memory
template <class Ktype, class Etype>
KeyHeap<Ktype, Etype>::~KeyHeap()
{
   for (int i=1; i<=numElements; i++)
      delete elements[i];  
}

// operator=
//    - parameters: origHeap - the heap to copy from
//    - modifies theinvoking heap so it has the same values
//      stored in it as origHeap does
//    - assuming that operator= is defined for Ktype and Etype,
//      The resulting copy will be a deep copy
template <class Ktype, class Etype>
KeyHeap<Ktype, Etype>& 
KeyHeap<Ktype, Etype>::operator=(const KeyHeap<Ktype, Etype>& origHeap)
{
   int i;

   if (this != &origHeap) {
 
      // get rid of old heap
      for (int i=1; i<=numElements; i++)
         delete elements[i];

      // copy static values
      numElements = origHeap.numElements;
      maxSize = origHeap.maxSize;
     
      // create new heap array
      elements = origHeap.elements;
      for (int i = 1; i <= numElements; i++)
         elements[i] = new HeapNode(*(origHeap.elements[i]));

   } 

   return *this;
}


// Insert
//    - parameters : insElem - the element to be inserted
//    - inserts insElem into the heap. Will exit program if
//       heap is full.
template <class Ktype, class Etype>
void KeyHeap<Ktype, Etype>::Insert(const Ktype & insKey, const Etype & X)
{
   unsigned int i; 
   
   Assert(!IsFull(), "Priority queue is full"); 

   numElements++; 
   i = numElements;
 
   while ((i != 1) && (elements[i/2]->key > insKey)) 
   {
      elements[i]=elements[i/2]; // swap bubble with number above  
      i/=2;                     
   }
   elements[i] = new HeapNode(insKey, X); 
       // bubble, which has now come to rest, is given
                        //    the new element  
}




// DeleteMin
//    - return value : the minimum element of the heap
//    - removes the minimum element from the heap, and
//         returns it. Will exit program if heap is
//         empty
template <class Ktype, class Etype>
Etype KeyHeap<Ktype, Etype>::DeleteMin()
{
   unsigned int lowChild; 
   HeapNode *minElement, *lastElement; 

   Assert(!IsEmpty(), "Priority Queue is Empty"); 

   minElement = elements[1]; 
   lastElement = elements[numElements--]; 
 
   int i;
   for (i=1; i*2 <= numElements; i=lowChild)
   {
      // Find smaller child
      lowChild = i*2;       // child is left child  
      if (lowChild != numElements)  // If this is not == Size, then right 
                                    // child exists
         if (elements[lowChild+1]->key < elements[lowChild]->key)
            lowChild++; 

      // Percolate one level
      if (lastElement->key > elements[lowChild]->key) // compare child to
					          // the element we are holding 
         elements[i] = elements[lowChild]; 
      else
         break; 
   }
   elements[i] = lastElement;   // Place holding value into the bubble 

   return (minElement->elem); 
}




// FindMin
//    - return value : the minimum element of the heap
//    - returns (without removal) the minimum element
//         of the heap. Will exit program if heap is
//         empty
template <class Ktype, class Etype>
Etype KeyHeap<Ktype, Etype>::FindMin() const
{
   Assert(!IsEmpty(), "Priority Queue is Empty"); 
   return elements[1]->elem; 
}



