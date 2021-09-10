// **********************************************
// *                                            *
// *  stackal.h                                 *
// *                                            *
// *  Interface for a stack class (stand-alone) *
// *                                            *
// *  Written 2/98 by Jason Zych                * 
// *                                            *
// **********************************************
 
#ifndef _STACKAL_H
#define _STACKAL_H

#include <stddef.h>

template <class Etype>
class Stack
{
public:

   // Stack
   //    - default constructor
   //    - parameters : none
   //    - initializes object  
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
   //    - parameters : oldVal - previously allocated Stack object
   //    - return value : a stack object 
   //    - sets object to be equal to oldVal 
   Stack& operator=(const Stack& oldVal); 


   // Push
   //    - parameters : newElem - an element to be added to the stack
   //    - places newElem on top of stack 
   void Push(Etype newElem);


   // Pop
   //    - parameters : none
   //    - return value : a value of the type held in stack
   //    - removes and returns top element of stack   
   Etype Pop(); 


   // Top
   //    - parameters : none
   //    - return value : a value of the type held in stack
   //    - returns top element of stack, without removing it
   Etype Top() const; 


   // Is_Empty
   //    - parameters : none
   //    - return value : boolean integer
   //    - returns 1 if stack is empty, 0 otherwise
   int Is_Empty() const; 


protected:

   struct Node
   {
      Node() { next = NULL; } 
      Etype element; 
      Node* next; 
   }; 

   Node* head; 
}; 



#endif 

