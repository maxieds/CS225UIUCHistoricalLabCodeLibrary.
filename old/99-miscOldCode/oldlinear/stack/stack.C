// **********************************************
// *                                            *
// *  stack.C                                   *
// *                                            *
// *  Implementation for a stack class          * 
// *                                            *
// *  Written 2/98 by Jason Zych                * 
// *                                            *
// **********************************************

#include "asserts.h"
#include "stack.h"

 
// Stack
//    - default constructor
//    - parameters : none
//    - initializes object  
template <class Etype>
Stack<Etype>::Stack() : List<Etype>()
{
}


   
// Stack
//    - copy constructor
//    - parameters : origVal - previously allocated Stack object
//    - initializes object to be a copy of origVal
template <class Etype>
Stack<Etype>::Stack(const Stack& origVal) : List<Etype>(origVal)
{
}
 


// ~Stack
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Stack<Etype>::~Stack()
{
} 



// operator=
//    - parameters : oldVal - previously allocated Stack object
//    - return value : a stack object 
//    - sets object to be equal to oldVal 
template <class Etype>
Stack<Etype>& Stack<Etype>::operator=(const Stack<Etype>& oldVal)
{
   if (this!=&oldVal)
      List<Etype>::operator=(oldVal); 
   return *this; 
} 



// Push
//    - parameters : newElem - an element to be added to the stack
//    - places newElem on top of stack 
template <class Etype>
void Stack<Etype>::Push(Etype newElem)
{
   InsertBefore(newElem); 
}



// Pop
//    - parameters : none
//    - return value : a value of the type held in stack
//    - removes and returns top element of stack   
template <class Etype>
Etype Stack<Etype>::Pop()
{
   Assert (head != NULL, "Trying to remove top element of empty stack!"); 
   Etype temp = Retrieve();
   Remove(); 
   return temp; 
} 



// Top
//    - parameters : none
//    - return value : a value of the type held in stack
//    - returns top element of stack, without removing it
template <class Etype>
Etype Stack<Etype>::Top() const
{
   Assert (head != NULL, "Trying to read top element from empty stack!"); 
   return Retrieve(); 
} 


// Is_Empty
//    - parameters : none
//    - return value : boolean integer
//    - returns 1 if stack is empty, 0 otherwise
template <class Etype>
int Stack<Etype>::Is_Empty() const
{
   return (head == NULL); 
} 


