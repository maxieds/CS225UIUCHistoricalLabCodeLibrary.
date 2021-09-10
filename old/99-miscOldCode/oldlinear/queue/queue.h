// **********************************************
// *                                            *
// *  queue.h                                   *
// *                                            *
// *  Interface for a queue class               * 
// *                                            *
// *  Written 2/98 by Jason Zych                * 
// *                                            *
// **********************************************
 
#ifndef _QUEUE_H
#define _QUEUE_H

#include <stddef.h>
#include "linklist.h"

template <class Etype>
class Queue : private List<Etype>
{
public:

   // Queue
   //    - default constructor
   //    - parameters : none
   //    - initializes object  
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
   //    - parameters : oldVal - previously allocated Queue object
   //    - return value : a queue object 
   //    - sets object to be equal to oldVal 
   Queue& operator=(const Queue& oldVal); 


   // Enqueue
   //    - parameters : newElem - an element to be added to the queue
   //    - places newElem on top of queue 
   void Enqueue(Etype newElem);


   // Dequeue
   //    - parameters : none
   //    - return value : a value of the type held in queue
   //    - removes and returns top element of queue   
   Etype Dequeue(); 


   // Front
   //    - parameters : none
   //    - return value : a value of the type held in queue
   //    - returns top element of queue, without removing it
   Etype Front() const; 


   // Is_Empty
   //    - parameters : none
   //    - return value : boolean integer
   //    - returns 1 if queue is empty, 0 otherwise
   int Is_Empty() const; 

}; 



#endif 

