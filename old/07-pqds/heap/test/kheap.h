// *************************************************
// *                                               *
// *  kheap.h                                      *
// *                                               *
// *  Interface file for a keyed KeyHeap class     * 
// *                                               *
// *  Written 31 October 1997 by Jason Zych        *
// *    Revised 10 March 1998  by David Anderson   * 
// *                                               *
// *************************************************
 
#ifndef _KHEAP_H
#define _KHEAP_H

#include <stddef.h>
#include "array.h"

template <class Ktype, class Etype>
class KeyHeap
{
public:

   // KeyHeap
   //    - default constructor
   //    - parameters: initSize - an integer that provides the size
   //       of the heap that should be allocated
   //    - allocated and initializes the heap 
   KeyHeap(unsigned int initSize = 10);  
   
   // KeyHeap
   //    - copy constructor
   //    - parameters: origHeap - the heap to create from
   //    - creates a new heap that has the same values stored in it
   //       as origHeap does
   //    - assuming that operator= is defined for Ktype and Etype, 
   //       the resulting copy will be a deep copy
   KeyHeap(const KeyHeap& origHeap);  

   // ~KeyHeap 
   //    - destructor
   //    - deletes the dynamically allocated memory 
   ~KeyHeap(); 

   // operator=  
   //    - parameters: origHeap - the heap to copy from 
   //    - modifies theinvoking heap so it has the same values
   //      stored in it as origHeap does
   //    - assuming that operator= is defined for Ktype and Etype,
   //      The resulting copy will be a deep copy 
   KeyHeap& operator=(const KeyHeap& origHeap);  

 
   // MakeEmpty
   //    - clears the heap 
   void MakeEmpty()  { numElements=0; }


   // IsEmpty
   //    - return value : boolean info
   //    - returns 1 if the heap is empty, and 0 if it is not
   int IsEmpty() const { return numElements==0; }


   // IsFull
   //    - return value : boolean info
   //    - returns 1 if the heap is full, and 0 if it is not
   int IsFull() const { return numElements==maxSize; }


   // Insert
   //    - parameters : insKey - the key to insert by 
   //    -              insElem - the element to be inserted 
   //    - inserts insElem into the heap. Will exit program if
   //       heap is full.  
   void Insert(const Ktype & insKey, const Etype & insElem); 


   // DeleteMin
   //    - return value : the minimum element of the heap 
   //    - removes the minimum element from the heap, and 
   //         returns it. Will exit program if heap is
   //         empty 
   Etype DeleteMin(); 


   // FindMin
   //    - return value : the minimum element of the heap
   //    - returns (without removal) the minimum element
   //         of the heap. Will exit program if heap is 
   //         empty
   Etype FindMin() const;


private:

   class HeapNode
   {
   public:

      Ktype key; 
      Etype elem; 
   
      HeapNode() {}
      HeapNode(const HeapNode& origNode) 
         { key = origNode.key; elem = origNode.elem; }
      HeapNode(Ktype newKey, Etype newElem) : 
         key(newKey), elem(newElem) {}      
   }; 

   unsigned int maxSize;   // defines maximum size of the array
   unsigned int numElements;  // defines current number of elements
                             // (and thus always <= maxSize)
   Array<HeapNode*> elements; // array to hold heap data 
 
};


#endif
