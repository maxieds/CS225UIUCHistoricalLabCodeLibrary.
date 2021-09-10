// *******************************************************
// *                                                     *
// *  list-implemented-queue.h                           *
// *                                                     *
// *  Interface for a queue class, implemented via       *
// *    an earlier-written List class                    *
// *                                                     *
// *  Written February 1998 by Jason Zych                * 
// *    - slight edits done July 2001 by Jason Zych      *
// *                                                     *
// *******************************************************
 
#ifndef _QUEUE_H
#define _QUEUE_H

#include "singly-linked-list.h"

template <class Etype>
class Queue 
{
public:

 // *** Constructors and other assorted additions to core ADT

 
   // Queue
   //    - default constructor
   //    - initializes object to be an empty queue  
   Queue();

   
   // Queue
   //    - copy constructor
   //    - parameters : origVal - previously allocated Queue object
   //    - initializes object to be a copy of origVal
   Queue(const Queue& origVal); 


   // ~Queue
   //    - destructor
   //    - deletes dynamically allocated memory
   ~Queue(); 


   // operator=
   //    - parameters : origVal - previously allocated Queue object
   //    - return value : this Queue object, after assignment 
   //    - sets object to be equal to origVal 
   const Queue& operator=(const Queue& origVal); 


   // Size
   //    - return value : non-negative integer
   //    - returns the number of elements in the queue
   int Size() const;


   // Print
   //    - prints the values in the queue in order, starting
   //         from the front element
   void Print() const;


 
 // *** Functions in the core Queue ADT


   // Enqueue
   //    - parameters : newElem - an element to be added to the queue
   //    - places newElem at rear of queue
   void Enqueue(const Etype& newElem);


   // Dequeue
   //    - return value : a value of the type held in queue
   //    - removes and returns front element of queue. Assumes 
   //        queue is not empty; if the queue is indeed empty,
   //        an assertion is triggered.   
   Etype Dequeue(); 


   // Front
   //    - return value : a reference to a value in the queue
   //    - returns front element of queue, without removing it. Assumes
   //        queue is not empty; if the queue is indeed empty, an
   //        assertion is triggered. 
   const Etype& Front() const; 


   // Is_Empty
   //    - return value : boolean integer
   //    - returns 1 if queue is empty, 0 otherwise
   int IsEmpty() const; 

private:

   List<Etype> collection;     // list used to implement queue
}; 



#endif 

