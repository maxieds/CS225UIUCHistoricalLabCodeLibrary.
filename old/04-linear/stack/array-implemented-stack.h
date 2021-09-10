// *******************************************************
// *                                                     *
// *  array-implemented-stack.h                          *
// *                                                     *
// *  Interface for a stack class, implemented via       *
// *    an Array                                         *
// *                                                     *
// *  Written July 2001 by Jason Zych                    *
// *                                                     *
// *******************************************************
 
#ifndef _STACK_H
#define _STACK_H

#include "array.h"

template <class Etype>
class Stack 
{
public:

 // *** Constructors and other assorted additions to core ADT

 
   // Stack
   //    - default constructor
   //    - initializes object to be an empty stack  
   Stack();

   
   // Stack
   //    - copy constructor
   //    - parameters : origVal - previously allocated Stack object
   //    - initializes object to be a copy of origVal
   Stack(const Stack& origVal); 


   // ~Stack
   //    - destructor
   //    - deletes dynamically allocated memory
   ~Stack(); 


   // operator=
   //    - parameters : origVal - previously allocated Stack object
   //    - return value : this Stack object, after assignment 
   //    - sets object to be equal to origVal 
   const Stack& operator=(const Stack& oldVal); 


   // Size
   //    - return value : non-negative integer
   //    - returns the number of elements in the stack
   int Size() const;


   // Print
   //    - prints the values in the stack in order, starting
   //         from the top element
   void Print() const;


 
 // *** Functions in the core Stack ADT


   // Push
   //    - parameters : newElem - an element to be added to the stack
   //    - places newElem on top of stack 
   void Push(const Etype& newElem);


   // Pop
   //    - return value : a value of the type held in stack
   //    - removes and returns top element of stack. Assumes 
   //        stack is not empty; if the stack is indeed empty,
   //        an assertion is triggered.   
   Etype Pop(); 


   // Top
   //    - return value : a reference to a value in the stack
   //    - returns top element of stack, without removing it. Assumes
   //        stack is not empty; if the stack is indeed empty, an
   //        assertion is triggered. 
   const Etype& Top() const; 


   // Is_Empty
   //    - return value : boolean integer
   //    - returns 1 if stack is empty, 0 otherwise
   int IsEmpty() const; 

private:

   Array<Etype> collection;     // Array used to implement stack
   int size;                    // number of elements in stack
}; 



#endif 

