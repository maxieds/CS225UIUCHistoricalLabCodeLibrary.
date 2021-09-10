// *******************************************************
// *                                                     *
// *  array-implemented-stack.h                          *
// *                                                     *
// *  Interface for a stack class, implemented via       *
// *    an Array                                         *
// *                                                     *
// *  Written February 2005 by Jason Zych                *
// *                                                     *
// *******************************************************
 
#ifndef STACK_225_H
#define STACK_225_H

#include "array.h"

template <typename Etype>
class Stack 
{
public:

   // *** C++-based additions to core ADT; default constructor and Big Three

   // Stack
   //    - default constructor
   //    - initializes object to be an empty stack  
   Stack();

   // We will not directly allocate dynamic memory so we can 
   // use the compiler-supplied versions of the Big Three. Remember
   // that they *are* here, even though we didn't write them in. 

 
 
   // *** Functions in the core Stack ADT


   // push
   //    - parameters : insElem - an element to be added to the stack
   //    - places insElem on top of stack 
   void push(Etype const & insElem);


   // pop
   //    - return value : a value of the type held in stack
   //    - removes and returns top element of stack. Assumes 
   //        stack is not empty; if the stack is indeed empty,
   //        an assertion is triggered.   
   Etype pop(); 


   // top
   //    - return value : a reference to a value in the stack; we 
   //                     cannot change that value through this
   //                     reference
   //    - returns top element of stack, without removing it. Assumes
   //        stack is not empty; if the stack is indeed empty, an
   //        assertion is triggered. 
   Etype const & top() const; 


   // isEmpty
   //    - return value : boolean with true indicating an empty stack
   //    - returns true if stack is empty; else returns false
   bool isEmpty() const; 

private:

   Array<Etype> collection;     // Array used to implement stack
   int numElements;             // number of elements in stack
}; 


#endif 



