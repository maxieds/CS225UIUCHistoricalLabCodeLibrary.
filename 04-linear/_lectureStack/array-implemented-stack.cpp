// *******************************************************
// *                                                     *
// *  array-implemented-stack.cpp                        *
// *                                                     *
// *  Implementation for a stack class, implemented via  * 
// *    an Array                                         *
// *                                                     *
// *  Written February 2005 by Jason Zych                *
// *                                                     *
// *******************************************************

#include "asserts.h"
#include "array-implemented-stack.h"


// *** C++-based additions to core ADT; default constructor and Big Three

 
// Stack
//    - default constructor
//    - initializes object to be an empty stack  
template <typename Etype>
Stack<Etype>::Stack() : collection(1, 10), numElements(0)
{
   // initializer list used above; no code needed here
}


// We will not directly allocate dynamic memory so we can
// use the compiler-supplied versions of the Big Three. Remember
// that they *are* here, even though we didn't write them in.


 
// *** Functions in the core Stack ADT


// push
//    - parameters : insElem - an element to be added to the stack
//    - places insElem on top of stack
template <typename Etype>
void Stack<Etype>::push(Etype const & insElem)
{
   // increase size of array if necessary
   if (numElements == collection.size())
      collection.setBounds(1, 2 * collection.size());  

   numElements++;
   collection[numElements] = insElem;
}




// pop
//    - return value : a value of the type held in stack
//    - removes and returns top element of stack. Assumes
//        stack is not empty; if the stack is indeed empty,
//        an assertion is triggered.
template <typename Etype>
Etype Stack<Etype>::pop()
{
   Assert(numElements > 0, "Cannot remove top element of an empty stack!");
   numElements--;

   // This is safe to do because even though we have decreased
   // numElements, we have not deleted any cell of the array itself.
   // Cells with indices > numElements are not conceptually part of
   // the stack, but they are not garbage memory either. They
   // are allocated cells that exist only as part of the implementation,
   // as additional capacity into which the stack can grow. 
   return collection[numElements + 1];  // former top value
}



// top
//    - return value : a reference to a value in the stack; we
//                     cannot change that value through this
//                     reference
//    - returns top element of stack, without removing it. Assumes
//        stack is not empty; if the stack is indeed empty, an
//        assertion is triggered.
template <typename Etype>
Etype const & Stack<Etype>::top() const
{
   Assert(numElements > 0, "Cannot read top element of an empty stack!");
   return collection[numElements];
}




// isEmpty
//    - return value : boolean with true indicating an empty stack
//    - returns true if stack is empty; else returns false
template <typename Etype>
bool Stack<Etype>::isEmpty() const
{
   return (numElements == 0);
}



