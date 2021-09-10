// *******************************************************
// *                                                     *
// *  array-implemented-stack.C                          *
// *                                                     *
// *  Implementation for a stack class, implemented via  * 
// *    an Array                                         *
// *                                                     *
// *  Written July 2001 by Jason Zych                    *
// *                                                     *
// *******************************************************

#include <iostream.h> 
#include "asserts.h"
#include "array-implemented-stack.h"


 // *** Constructors and other assorted additions to core ADT

 
// Stack
//    - default constructor
//    - initializes object to be an empty stack  
template <class Etype>
Stack<Etype>::Stack() : collection(1, 10), size(0)
{
   // no code needed here
}

        // Note that the big three were not actually
        // necessary for this implementation, since there
        // is no dynamic memory. We put them in just so that
        // all three stack header files have the same interface,
        // for educational purposes, but the defaults for the
        // big three could have used for this particular implementation.

   
// Stack
//    - copy constructor
//    - parameters : origVal - previously allocated Stack object
//    - initializes object to be a copy of origVal
template <class Etype>
Stack<Etype>::Stack(const Stack<Etype>& origVal) : 
             collection(origVal.collection), size(origVal.size)
{
   // no code needed here
}



// ~Stack
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Stack<Etype>::~Stack()
{
   // no code needed here
}



// operator=
//    - parameters : origVal - previously allocated Stack object
//    - return value : this Stack object, after assignment 
//    - sets object to be equal to origVal 
template <class Etype>
const Stack<Etype>& Stack<Etype>::operator=(const Stack<Etype>& origVal)
{
   if (this != &origVal)
   {
      collection = origVal.collection;
      size = origVal.size;
   }
   return *this;
}



// Size
//    - return value : non-negative integer
//    - returns the number of elements in the stack
template <class Etype>
int Stack<Etype>::Size() const
{
   return size;
}


// Print
//    - prints the values in the stack in order, starting
//         from the top element
template <class Etype>
void Stack<Etype>::Print() const
{
   if (size == 0)
      cout << "< empty stack >" << endl;
   else
   {
      cout << "< ";
      for (int i = size; i >= 1; i--)
         cout << collection[i] << " ";
      cout << ">" << endl;
   }
}




 
 // *** Functions in the core Stack ADT


// Push
//    - parameters : newElem - an element to be added to the stack
//    - places newElem on top of stack 
template <class Etype>
void Stack<Etype>::Push(const Etype& newElem)
{
   // increase size of array if necessary
   if (size == collection.Size())
      collection.SetBounds(1, 2*collection.Size());  

   size++;
   collection[size] = newElem;
}


// Pop
//    - return value : a value of the type held in stack
//    - removes and returns top element of stack. Assumes 
//        stack is not empty; if the stack is indeed empty,
//        an assertion is triggered.   
template <class Etype>
Etype Stack<Etype>::Pop()
{
   Assert(size > 0, "Cannot remove top element of an empty stack!");
   size--;
   return collection[size+1];  // former top value
}


// Top
//    - return value : a reference to a value in the stack
//    - returns top element of stack, without removing it. Assumes
//        stack is not empty; if the stack is indeed empty, an
//        assertion is triggered. 
template <class Etype>
const Etype& Stack<Etype>::Top() const
{
   Assert(size > 0, "Cannot read top element of an empty stack!");
   return collection[size];
}


// Is_Empty
//    - return value : boolean integer
//    - returns 1 if stack is empty, 0 otherwise
template <class Etype>
int Stack<Etype>::IsEmpty() const
{
   return (size == 0);
}



