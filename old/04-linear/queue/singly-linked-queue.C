// *******************************************************
// *                                                     *
// *  singly-linked-queue.C                              *
// *                                                     *
// *  Implementation for a queue class, implemented via  *
// *    a singly-linked-list                             *
// *                                                     *
// *  Written February 1998 by Jason Zych                * 
// *    - slight edits done July 2001 by Jason Zych      *
// *                                                     *
// *******************************************************

#include <iostream.h> 
#include "asserts.h"
#include "singly-linked-queue.h"


 // *** Constructors and other assorted additions to core ADT

 
// Queue
//    - default constructor
//    - initializes object to be an empty queue  
template <class Etype>
Queue<Etype>::Queue() : head(NULL), tail(NULL), size(0)
{
   // no code needed here
}




// Queue
//    - copy constructor
//    - parameters : origVal - previously allocated Queue object
//    - initializes object to be a copy of origVal
template <class Etype>
Queue<Etype>::Queue(const Queue& origVal)
{
   QueueNode *paramListPtr, *thisListPtr, *newestNode;

   paramListPtr = origVal.head;
   if (paramListPtr == NULL)  // then origList is empty
   {
      head = NULL;
      size=0; 
   }
   else 
   {
      while (paramListPtr != NULL)
      {
         newestNode = new QueueNode(paramListPtr->element);

         if (paramListPtr == origVal.head)
         {
            thisListPtr = newestNode;
            head = thisListPtr;
         }
         else
         {
            thisListPtr->next = newestNode;
            thisListPtr = thisListPtr->next;
         }
         paramListPtr = paramListPtr->next;
      }
      tail = thisListPtr;
      size = origVal.size;
   }
}




// ~Queue
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Queue<Etype>::~Queue()
{
   QueueNode* deletionPtr = head;

   while (head != NULL)
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
template <class Etype>
const Queue<Etype>& Queue<Etype>::operator=(const Queue<Etype>& origVal)
{
   if (this != &origVal)
   {
      QueueNode* deletionPtr = head;

      while (head != NULL)
      {
         head = head->next;
         delete deletionPtr;
         deletionPtr = head;
      }

      QueueNode *paramListPtr, *thisListPtr, *newestNode;

      paramListPtr = origVal.head;
      if (paramListPtr == NULL)  // then origList is empty
      {
         head = NULL;
         size=0; 
      }
      else 
      {
         while (paramListPtr != NULL)
         {
            newestNode = new QueueNode(paramListPtr->element);

            if (paramListPtr == origVal.head)
            {
               thisListPtr = newestNode;
               head = thisListPtr;
            }
            else
            {
               thisListPtr->next = newestNode;
               thisListPtr = thisListPtr->next;
            }
            paramListPtr = paramListPtr->next;
         }
         tail = thisListPtr;
         size = origVal.size;
      }
   }
   return *this;
}






// Size
//    - return value : non-negative integer
//    - returns the number of elements in the queue
template <class Etype>
int Queue<Etype>::Size() const
{
   return size;
}







// Print
//    - prints the values in the queue in order, starting
//         from the front element
template <class Etype>
void Queue<Etype>::Print() const
{
   QueueNode* outPtr = head; 

   if (size==0)
      cout << "< empty queue >" << endl;
   else
   { 
      cout << "< "; 
      while (outPtr != NULL)  
      {
         cout << outPtr->element << " ";
         outPtr = outPtr->next; 
      } 
      cout << ">" << endl;
   } 
}






 // *** Functions in the core Queue ADT


// Enqueue
//    - parameters : newElem - an element to be added to the queue
//    - places newElem at rear of queue 
template <class Etype>
void Queue<Etype>::Enqueue(const Etype& newElem)
{
   if (size == 0)
      head = tail = new QueueNode(newElem);
   else
   {
      QueueNode* newNode = new QueueNode(newElem);
      tail->next = newNode;
      tail = tail->next;
   }  
   size++;
}






// Dequeue
//    - return value : a value of the type held in queue
//    - removes and returns front element of queue. Assumes 
//        queue is not empty; if the queue is indeed empty,
//        an assertion is triggered.   
template <class Etype>
Etype Queue<Etype>::Dequeue()
{
   Assert(size > 0, "Cannot remove front element of an empty queue!");
   QueueNode* deletePtr = head;
   Etype temp = head->element;
   head = head->next;
   delete deletePtr;
   size--;
   return temp;
}



// Front
//    - return value : a reference to a value in the queue
//    - returns front element of queue, without removing it. Assumes
//        queue is not empty; if the queue is indeed empty, an
//        assertion is triggered. 
template <class Etype>
const Etype& Queue<Etype>::Front() const
{
   Assert(size > 0, "Cannot read front element of an empty queue!");
   return head->element;   
}


// Is_Empty
//    - return value : boolean integer
//    - returns 1 if queue is empty, 0 otherwise
template <class Etype>
int Queue<Etype>::IsEmpty() const
{
   return (head == NULL);
}


