// *******************************************************
// *                                                     *
// *  array-implemented-queue.cpp                        *
// *                                                     *
// *  Implementation for a queue class, implemented via  * 
// *    an Array                                         *
// *                                                     *
// *  Written February 2005 by Jason Zych                *
// *                                                     *
// *******************************************************

#include "asserts.h"
#include "array-implemented-queue.h"


// *** C++-based additions to core ADT; default constructor and Big Three

 
// Queue
//    - default constructor
//    - initializes object to be an empty queue  
template <typename Etype>
Queue<Etype>::Queue() : collection(0, 9), numElements(0), 
                               frontIndex(0), rearIndex(9)
{
   // initializer list used above; no code needed here
}


// We will not directly allocate dynamic memory so we can
// use the compiler-supplied versions of the Big Three. Remember
// that they *are* here, even though we didn't write them in.


 
// *** Functions in the core Queue ADT


// enqueue
//    - parameters : insElem - an element to be added to the queue
//    - places insElem at rear of queue
template <typename Etype>
void Queue<Etype>::enqueue(Etype const & insElem)
{
   // increase size of array if necessary
   if (numElements == collection.size())
   {
      collection.setBounds(0, 2 * collection.size() - 1);  

      // If prior to the expansion, rear was the last cell,
      //  then the queue is in one piece in the array --- that is,
      //  front == 0, rearl == numElements - 1, and the circular
      //  array capability is not currently in direct use. So, we
      //  after the array expansion, the queue still sits in cells
      //  0 through numElements - 1 and all is well, just as when
      //  we expand the array implementing a stack.
      //
      // Otherwise, the queue is in two parts -- front is some non-zero
      // index, and the queue consists of all cells from front to
      // numElements - 1, followed by all cells from 0 to rear. In 
      // that case, all cells from front to numElements - 1 need to 
      // be shifted to the end of the new, expanded array.
      if (rearIndex != numElements - 1)  
      {
         int indexToRead = numElements - 1; // index of rightmost real value
         int indexToWrite = collection.size() - 1;  // index of rightmost cell
         while (indexToRead >= frontIndex)
         {
            collection[indexToWrite] = collection[indexToRead];
            indexToRead--;
            indexToWrite--;
         } 
      
         // set front to the last value we copied
         frontIndex = indexToWrite + 1;  
      }
   }

   rearIndex = (rearIndex + 1) % (collection.size());
   collection[rearIndex] = insElem;
   numElements++;
}




// dequeue
//    - return value : a value of the type held in queue
//    - removes and returns front element of queue. Assumes
//        queue is not empty; if the queue is indeed empty,
//        an assertion is triggered.
template <typename Etype>
Etype Queue<Etype>::dequeue()
{
   Assert(numElements > 0, "Cannot remove front element of an empty queue!");
 
   Etype temp = collection[frontIndex];
  
   frontIndex = (frontIndex + 1) % (collection.size());   
   numElements--;

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
   Assert(numElements > 0, "Cannot read front element of an empty queue!");
   return collection[frontIndex];
}




// isEmpty
//    - return value : boolean with true indicating an empty queue
//    - returns true if queue is empty; else returns false
template <typename Etype>
bool Queue<Etype>::isEmpty() const
{
   return (numElements == 0);
}



