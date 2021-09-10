// *******************************************************
// *                                                     *
// *  array-implemented-queue.h                          *
// *                                                     *
// *  Interface for a queue class, implemented via       *
// *    an Array                                         *
// *                                                     *
// *  Written February 2005 by Jason Zych                *
// *                                                     *
// *******************************************************
 
#ifndef QUEUE_225_H
#define QUEUE_225_H

#include "array.h"

template <typename Etype>
class Queue 
{
public:

   // *** C++-based additions to core ADT; default constructor and Big Three

   // Queue
   //    - default constructor
   //    - initializes object to be an empty queue  
   Queue();

   // We will not directly allocate dynamic memory so we can 
   // use the compiler-supplied versions of the Big Three. Remember
   // that they *are* here, even though we didn't write them in. 

 
 
   // *** Functions in the core Queue ADT


   // enqueue
   //    - parameters : insElem - an element to be added to the queue
   //    - places insElem at rear of queue 
   void enqueue(Etype const & insElem);


   // dequeue
   //    - return value : a value of the type held in queue
   //    - removes and returns front element of queue. Assumes 
   //        queue is not empty; if the queue is indeed empty,
   //        an assertion is triggered.   
   Etype dequeue(); 


   // front
   //    - return value : a reference to a value in the queue; we 
   //                     cannot change that value through this
   //                     reference
   //    - returns front element of queue, without removing it. Assumes
   //        queue is not empty; if the queue is indeed empty, an
   //        assertion is triggered. 
   Etype const & front() const; 


   // isEmpty
   //    - return value : boolean with true indicating an empty queue
   //    - returns true if queue is empty; else returns false
   bool isEmpty() const; 

private:

   Array<Etype> collection;     // Array used to implement queue
   int numElements;             // number of elements in queue
   int frontIndex;              // index of front element
   int rearIndex;               // index of rear element;
}; 


#endif 



