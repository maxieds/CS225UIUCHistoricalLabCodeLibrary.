// *******************************************************
// *                                                     *
// *  array-implemented-queue.C                          *
// *                                                     *
// *  Implementation for a queue class, implemented via  *
// *    an Array                                         *
// *                                                     *
// *  Written July 2001 by Jason Zych                    *
// *                                                     *
// *******************************************************

#include <iostream.h> 
#include "asserts.h"
#include "array-implemented-queue.h"


 // *** Constructors and other assorted additions to core ADT

 
// Queue
//    - default constructor
//    - initializes object to be an empty queue  
template <class Etype>
Queue<Etype>::Queue() : collection(0, 9), numElements(0), front(0), rear(9)
{
   // no code needed here
}


        // Note that the big three were not actually 
        // necessary for this implementation, since there
        // is no dynamic memory. We put them in just so that
        // all three queue header files have the same interface,
        // for educational purposes, but the defaults for the
        // big three could have used for this particular implementation.


   
// Queue
//    - copy constructor
//    - parameters : origVal - previously allocated Queue object
//    - initializes object to be a copy of origVal
template <class Etype>
Queue<Etype>::Queue(const Queue<Etype>& origVal) :
             collection(origVal.collection), numElements(origVal.numElements), 
             front(origVal.front), rear(origVal.rear)
{
   // no code needed here
}


// ~Queue
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Queue<Etype>::~Queue() 
{
   // no code needed here
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
      collection = origVal.collection;
      numElements = origVal.numElements;
      front = origVal.front;
      rear = origVal.rear;
   }
   return *this;
}


// Size
//    - return value : non-negative integer
//    - returns the number of elements in the queue
template <class Etype>
int Queue<Etype>::Size() const
{
   return numElements;
}


// Print
//    - prints the values in the queue in order, starting
//         from the front element
template <class Etype>
void Queue<Etype>::Print() const
{
   if (numElements == 0)
      cout << "< empty queue >" << endl;
   else
   {
      cout << "< ";
      int i = front;
      while (i != rear)
      {
         cout << collection[i] << " ";
         i = (i + 1) % collection.Size();
      }
      cout << collection[i] << " >" << endl; 
   }
}


 
 // *** Functions in the core Queue ADT


// Enqueue
//    - parameters : newElem - an element to be added to the queue
//    - places newElem at rear of queue 
template <class Etype>
void Queue<Etype>::Enqueue(const Etype& newElem)
{
   // increase size of array if necessary
   if (numElements == collection.Size())
      collection.SetBounds(0, 2*collection.Size()-1);  

   rear = (rear + 1) % collection.Size();
   collection[rear] = newElem;
   numElements++;
}


// Dequeue
//    - return value : a value of the type held in queue
//    - removes and returns front element of queue. Assumes 
//        queue is not empty; if the queue is indeed empty,
//        an assertion is triggered.   
template <class Etype>
Etype Queue<Etype>::Dequeue()
{
   Assert(numElements > 0,
            "Cannot remove front element of an empty queue!");
   Etype temp = collection[front];
   front = (front+1) % collection.Size();
   numElements--;
   return temp;
}



// Front
//    - return value : a reference to a value in the queue
//    - returns Front element of queue, without removing it. Assumes
//        queue is not empty; if the queue is indeed empty, an
//        assertion is triggered. 
template <class Etype>
const Etype& Queue<Etype>::Front() const
{
   Assert(numElements > 0, 
            "Cannot read front element of an empty queue!");
   return collection[front];
}



// Is_Empty
//    - return value : boolean integer
//    - returns 1 if queue is empty, 0 otherwise
template <class Etype>
int Queue<Etype>::IsEmpty() const
{
   return (numElements == 0);
}


