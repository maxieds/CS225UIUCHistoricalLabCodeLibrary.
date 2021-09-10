// **********************************************
// *                                            *
// *  queue.C                                   *
// *                                            *
// *  Implementation for a queue class          * 
// *                                            *
// *  Written 2/98 by Jason Zych                * 
// *                                            *
// **********************************************

#include "asserts.h"
#include "queue.h"

 
// Queue
//    - default constructor
//    - parameters : none
//    - initializes object  
template <class Etype>
Queue<Etype>::Queue() : List<Etype>()
{
}


   
// Queue
//    - copy constructor
//    - parameters : origVal - previously allocated Queue object
//    - initializes object to be a copy of origVal
template <class Etype>
Queue<Etype>::Queue(const Queue& origVal) : List<Etype>(origVal)
{
}
 


// ~Queue
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Queue<Etype>::~Queue()
{
} 



// operator=
//    - parameters : oldVal - previously allocated Queue object
//    - return value : a queue object 
//    - sets object to be equal to oldVal 
template <class Etype>
Queue<Etype>& Queue<Etype>::operator=(const Queue<Etype>& oldVal)
{
   if (this!=&oldVal)
      List<Etype>::operator=(oldVal); 
   return *this; 
} 



// Enqueue
//    - parameters : newElem - an element to be added to the queue
//    - places newElem on back of queue 
template <class Etype>
void Queue<Etype>::Enqueue(Etype newElem)
{
   InsertAfter(newElem); 
}



// Dequeue
//    - parameters : none
//    - return value : a value of the type held in queue
//    - removes and returns front element of queue   
template <class Etype>
Etype Queue<Etype>::Dequeue()
{
   Assert (head != NULL, "Trying to remove front element of empty queue!"); 
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
   Assert (head != NULL, "Trying to read top element from empty queue!"); 
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


