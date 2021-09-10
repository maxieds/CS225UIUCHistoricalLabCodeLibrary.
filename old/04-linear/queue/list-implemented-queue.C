// *******************************************************
// *                                                     *
// *  list-implemented-queue.C                           *
// *                                                     *
// *  Implementation for a queue class, implemented via  *
// *    an earlier-written List class                    *
// *                                                     *
// *  Written February 1998 by Jason Zych                * 
// *    - slight edits done July 2001 by Jason Zych      *
// *                                                     *
// *******************************************************

#include <iostream.h> 
#include "asserts.h"
#include "list-implemented-queue.h"


 // *** Constructors and other assorted additions to core ADT

 
// Queue
//    - default constructor
//    - initializes object to be an empty queue  
template <class Etype>
Queue<Etype>::Queue()  // : collection(), by default
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
              collection(origVal.collection)
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
      collection = origVal.collection;
   return *this;
}


// Size
//    - return value : non-negative integer
//    - returns the number of elements in the queue
template <class Etype>
int Queue<Etype>::Size() const
{
   return collection.Length(); 
}


// Print
//    - prints the values in the queue in order, starting
//         from the front element
template <class Etype>
void Queue<Etype>::Print() const
{
   if (collection.Length() == 0)
      cout << "< empty queue >" << endl;
   else
   {
      collection.Print();
      cout << endl;
   }
}


 
 // *** Functions in the core Queue ADT


// Enqueue
//    - parameters : newElem - an element to be added to the queue
//    - places newElem on rear of queue 
template <class Etype>
void Queue<Etype>::Enqueue(const Etype& newElem)
{
   if (collection.Length() > 0)
      collection.Tail();
   collection.InsertAfter(newElem);
   collection.Head();
}


// Dequeue
//    - return value : a value of the type held in queue
//    - removes and returns front element of queue. Assumes 
//        queue is not empty; if the queue is indeed empty,
//        an assertion is triggered.   
template <class Etype>
Etype Queue<Etype>::Dequeue()
{
   // Based on how we wrote the other functions, it is safe to
   // assume that current already points to the front of the list,
   // if there are any nodes in the list at all.
   Assert(collection.Length() > 0, 
            "Cannot remove front element of an empty queue!");
   Etype temp = collection.Retrieve();
   collection.Remove();
   if (collection.Length() > 0)
      collection.Head();
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
   // Based on how we wrote the other functions, it is safe to
   // assume that current already points to the front of the list,
   // if there are any nodes in the list at all.
   Assert(collection.Length() > 0, 
             "Cannot read front element of an empty queue!");
   return collection.Retrieve();
}



// Is_Empty
//    - return value : boolean integer
//    - returns 1 if queue is empty, 0 otherwise
template <class Etype>
int Queue<Etype>::IsEmpty() const
{
   return (collection.Length() == 0);
}


