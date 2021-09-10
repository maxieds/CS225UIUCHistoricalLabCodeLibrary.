// *******************************************************
// *                                                     *
// *  singly-linked-queue.h                              *
// *                                                     *
// *  Interface for a queue class, implemented via       *
// *    a singly-linked list                             *
// *                                                     *
// *  Written February 2005 by Jason Zych                *
// *                                                     *
// *******************************************************
 
#ifndef QUEUE_225_H
#define QUEUE_225_H

template <typename Etype>
class Queue 
{
public:

   // *** C++-based additions to core ADT; default constructor and Big Three

   // Queue
   //    - default constructor
   //    - initializes object to be an empty queue  
   Queue();


   // Queue
   //    - copy constructor
   //    - parameters : origVal - previously allocated Queue object
   //    - initializes object to be a copy of origVal
   Queue(Queue<Etype> const & origVal);


   // ~Queue
   //    - destructor
   //    - deletes dynamically allocated memory
   ~Queue();


   // operator=
   //    - parameters : origVal - previously allocated Queue object
   //    - return value : this Queue object, after assignment
   //    - sets object to be equal to origVal
   Queue<Etype> const & operator=(Queue<Etype> const & origVal);

 
 
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

   class QueueNode
   {
   public:

      // QueueNode
      //    - constructor
      //    - initializes element to default Etype, and next to NULL
      QueueNode();


      // QueueNode
      //    - constructor
      //    - parameters : value - the value to store in the element field
      //    - initializes node to hold value and NULL
      QueueNode(Etype const & value);


      Etype element;       // holds element of node
      QueueNode* next;     // pointer to the next node in the
                           //   singly-linked list that will be built
   };


   typename Queue<Etype>::QueueNode* head;  // pointer to front of queue
   typename Queue<Etype>::QueueNode* tail;  // pointer to rear of queue
};


#endif 



