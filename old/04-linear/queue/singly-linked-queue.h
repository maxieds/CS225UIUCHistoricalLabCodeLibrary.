// *******************************************************
// *                                                     *
// *  singly-linked-queue.h                              *
// *                                                     *
// *  Interface for a queue class, implemented via       *
// *    a singly-linked-list                             *
// *                                                     *
// *  Written February 1998 by Jason Zych                * 
// *    - slight edits done July 2001 by Jason Zych      *
// *                                                     *
// *******************************************************
 
#ifndef _QUEUE_H
#define _QUEUE_H

#include <stddef.h>

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

   class QueueNode
   {
   public:

      // QueueNode
      //    - constructor
      //    - initializes element to default Etype, and next to NULL
      QueueNode()  { next = NULL; }
  
      
      // QueueNode
      //    - constructor
      //    - parameters : value - the value to store in the element field
      //    - initializes node to hold value and NULL
      QueueNode(Etype value) { element = value; next = NULL; } 


      Etype element;       // holds element of node
      QueueNode* next;     // pointer to the next node in the 
                           //   singly-linked list that will be built
   }; 

   QueueNode* head;     // points to first (front) node of queue
   QueueNode* tail;     // points to last (rear) node of queue
   int size;            // number of elements in stack

}; 



#endif 

