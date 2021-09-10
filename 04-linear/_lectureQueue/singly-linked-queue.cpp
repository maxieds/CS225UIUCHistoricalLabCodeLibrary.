// *******************************************************
// *                                                     *
// *  singly-linked-queue.cpp                            *
// *                                                     *
// *  Implementation for a queue class, implemented via  *
// *    a singly-linked-list                             *
// *                                                     *
// *  Written February 2005 by Jason Zych                *
// *                                                     *
// *******************************************************

#include <cstddef>

#include "asserts.h"
#include "singly-linked-queue.h"



// *** C++-based additions to core ADT; default constructor and Big Three

// Queue
//    - default constructor
//    - initializes object to be an empty queue
template <typename Etype>
Queue<Etype>::Queue() : head(NULL), tail(NULL)
{
   // initializer list used above; no code needed here
}



// Queue
//    - copy constructor
//    - parameters : origVal - previously allocated Queue object
//    - initializes object to be a copy of origVal
template <typename Etype>
Queue<Etype>::Queue(Queue<Etype> const & origVal)
{
   typename Queue<Etype>::QueueNode* paramListPtr;
   typename Queue<Etype>::QueueNode* thisListPtr;
   typename Queue<Etype>::QueueNode* newestNode;

   paramListPtr = origVal.head;
   if (paramListPtr == NULL)  // then origList is empty
   {
      head = NULL;
      tail = NULL;
   }
   else 
   {
      while (paramListPtr != NULL)
      {
         newestNode = new Queue<Etype>::QueueNode(paramListPtr->element);

         if (paramListPtr == origVal.head)
         {
            thisListPtr = newestNode;
            head = newestNode;
         }
         else
         {
            thisListPtr->next = newestNode;
            thisListPtr = thisListPtr->next;
         }
         if (origVal.tail == paramListPtr)
            tail = thisListPtr;
         paramListPtr = paramListPtr->next;
      }
   }
}




// ~Queue
//    - destructor
//    - deletes dynamically allocated memory
template <typename Etype>
Queue<Etype>::~Queue()
{
   typename Queue<Etype>::QueueNode* deletionPtr = head;

   while (deletionPtr != NULL)
   {
      head = head->next;
      delete deletionPtr;
      deletionPtr = head;
   }
}





// operator=
//    - parameters : origVal - previously allocated Queue object
//    - return value : this Queue object, after assignment 
//    - sets object to be equal to origVal 
template <typename Etype>
Queue<Etype> const & Queue<Etype>::operator=(
                            Queue<Etype> const & origVal)
{
   if (this != &origVal)
   {
      Queue<Etype>::QueueNode* deletionPtr = head;

      while (deletionPtr != NULL)
      {
         head = head->next;
         delete deletionPtr;
         deletionPtr = head;
      }

      typename Queue<Etype>::QueueNode* paramListPtr;
      typename Queue<Etype>::QueueNode* thisListPtr;
      typename Queue<Etype>::QueueNode* newestNode;

      paramListPtr = origVal.head;
      if (paramListPtr == NULL)  // then origList is empty
      {
         head = NULL;
         tail = NULL;
      }
      else
      {
         while (paramListPtr != NULL)
         {
            newestNode = new Queue<Etype>::QueueNode(paramListPtr->element);

            if (paramListPtr == origVal.head)
            {
               thisListPtr = newestNode;
               head = newestNode;
            }
            else
            {
               thisListPtr->next = newestNode;
               thisListPtr = thisListPtr->next;
            }

            if (origVal.tail == paramListPtr)
               tail = thisListPtr;

            paramListPtr = paramListPtr->next;
         }
      }
   }
   return *this;
}



// *** Functions in the core Queue ADT


// enqueue
//    - parameters : insElem - an element to be added to the queue
//    - places insElem at rear of queue 
template <typename Etype>
void Queue<Etype>::enqueue(Etype const & insElem)
{
   if (head == NULL)
   {
      head = new Queue<Etype>::QueueNode(insElem);
      tail = head;
   }
   else
   {
      tail->next = new Queue<Etype>::QueueNode(insElem);
      tail = tail->next;
   }  
}






// dequeue
//    - return value : a value of the type held in queue
//    - removes and returns front element of queue. Assumes 
//        queue is not empty; if the queue is indeed empty,
//        an assertion is triggered.   
template <typename Etype>
Etype Queue<Etype>::dequeue()
{
   Assert(head != NULL, "Cannot remove front element of an empty queue!");

   typename Queue<Etype>::QueueNode* deletePtr = head;
   Etype temp = head->element;
   head = head->next;
   delete deletePtr;
   return temp;
}




// front
//    - return value : a reference to a value in the queue; we 
//                     cannot change that value through this
//                     reference
//    - returns front element of queue, without removing it. Assumes
//        queue is not empty; if the queue is indeed empty, an
//        assertion is triggered. 
template <typename Etype>
Etype const & Queue<Etype>::front() const
{
   Assert(head != NULL, "Cannot read front element of an empty queue!");
   return head->element;   
}


// isEmpty
//    - return value : boolean with true indicating an empty queue
//    - returns true if queue is empty; else returns false
template <typename Etype>
bool Queue<Etype>::isEmpty() const
{
   return (head == NULL);
}



// QueueNode
//    - constructor
//    - initializes element to default Etype, and next to NULL
template <typename Etype>
Queue<Etype>::QueueNode::QueueNode() : element(), next(NULL)
{
   // initializer list used above; no code needed here
} 

  
      
// QueueNode
//    - constructor
//    - parameters : value - the value to store in the element field
//    - initializes node to hold value and NULL
template <typename Etype>
Queue<Etype>::QueueNode::QueueNode(Etype const & value) :
                          element(value), next(NULL)
{
   // initializer list used above; no code needed here
}


