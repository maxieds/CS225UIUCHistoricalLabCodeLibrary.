// ***************************************************
// *                                                 *
// *  queueal.C                                      *
// *                                                 *
// *  Implementation for a queue class (stand-alone) *
// *                                                 *
// *  Written 2/98 by Jason Zych                     * 
// *                                                 *
// ***************************************************

#include "asserts.h"
#include "queueal.h" 

// Queue
//    - default constructor
//    - parameters : none
//    - initializes object  
template <class Etype>
Queue<Etype>::Queue()
{
   head = tail = NULL; 
}


   
// Queue
//    - copy constructor
//    - parameters : origVal - previously allocated Queue object
//    - initializes object to be a copy of origVal
template <class Etype>
Queue<Etype>::Queue(const Queue& origVal)
{
   Node *origValPtr = origVal.head,
        *newQueuePtr; 
 
   if (origValPtr == NULL)  // then origList is empty
   {
      head = NULL; 
   }
   else   // origVal is not empty; copy it node for node
   {
      // at least one node in origVal; create that node
      newQueuePtr = new Node; 
      newQueuePtr->element = origValPtr->element; 
      head = newQueuePtr; 
      origValPtr = origValPtr->next; 
 
      while (origValPtr !=NULL) // keep creating nodes as long as there
      {                         //  are nodes in origVal
         newQueuePtr->next = new Node; 
         newQueuePtr = newQueuePtr->next; 
         newQueuePtr->element = origValPtr->element; 
         origValPtr = origValPtr->next; 
      }
      newQueuePtr->next = NULL;   // last node points to NULL 
      tail = newQueuePtr; 
   }
} 



// ~Queue
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Queue<Etype>::~Queue()
{
   Node *deletionPtr = head;
   tail = head; 
 
   while (tail != NULL)
   {
      tail = tail->next;
      delete deletionPtr;
      deletionPtr = tail;  
   }

   head = tail = NULL;
}

 


// operator=
//    - parameters : oldVal - previously allocated Queue object
//    - return value : a queue object 
//    - sets object to be equal to oldVal 
template <class Etype>
Queue<Etype>& Queue<Etype>::operator=(const Queue<Etype>& oldVal)
{
   if (this!=&oldVal)
   {
      Node *oldValPtr = head; 
      Node *newQueuePtr = head; 
 
      while (newQueuePtr != NULL)
      {
         newQueuePtr = newQueuePtr->next;
         delete oldValPtr;  
  	 oldValPtr = newQueuePtr; 
      }

      oldValPtr = oldVal.head; 
 
      if (oldValPtr == NULL)  // then origList is empty
      {
         head = NULL;
      }
      else   // oldVal is not empty; copy it node for node
      {
         // at least one node in oldVal; create that node
         newQueuePtr = new Node;
         newQueuePtr->element = oldValPtr->element;
         head = newQueuePtr;
         oldValPtr = oldValPtr->next;
 
         while (oldValPtr !=NULL) // keep creating nodes as long as there
         {                         //  are nodes in origVal
            newQueuePtr->next = new Node;
            newQueuePtr = newQueuePtr->next;
            newQueuePtr->element = oldValPtr->element;
            oldValPtr = oldValPtr->next;
         }
         newQueuePtr->next = NULL;   // last node points to NULL
         tail = newQueuePtr; 
      }
   }
   return *this; 
}

 


// Enqueue
//    - parameters : newElem - an element to be added to the queue
//    - places newElem on back of queue 
template <class Etype>
void Queue<Etype>::Enqueue(Etype newElem)
{
   if (head==NULL)
   {
     head = new Node(); 
     head->element = newElem; 
     tail = head; 
   }
   else
   {
     Node* tempPtr = new Node();
     tempPtr->element = newElem;  
     tail->next = tempPtr;  
     tail = tempPtr; 
   }
}




// Dequeue
//    - parameters : none
//    - return value : a value of the type held in queue
//    - removes and returns front element of queue   
template <class Etype>
Etype Queue<Etype>::Dequeue()
{
   Assert(head!=NULL, "Trying to remove front element from empty queue!"); 
   Etype temp = head->element; 
   Node* tempPtr = head;  
   head = head->next; 
   delete tempPtr; 
   return temp; 
}

 


// Front
//    - parameters : none
//    - return value : a value of the type held in queue
//    - returns front element of queue, without removing it
template <class Etype>
Etype Queue<Etype>::Front() const
{
   Assert (head != NULL, "Trying to read front element of empty queue!"); 
   return head->element; 
}

 


// Is_Empty
//    - parameters : none
//    - return value : boolean integer
//    - returns 1 if queue is empty, 0 otherwise
template <class Etype>
int Queue<Etype>::Is_Empty() const
{
   return (head == NULL); 
} 

