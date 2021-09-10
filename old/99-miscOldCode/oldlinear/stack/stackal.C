// ***************************************************
// *                                                 *
// *  stackal.C                                      *
// *                                                 *
// *  Implementation for a stack class (stand-alone) *
// *                                                 *
// *  Written 2/98 by Jason Zych                     * 
// *                                                 *
// ***************************************************

#include "asserts.h"
#include "stackal.h" 

// Stack
//    - default constructor
//    - parameters : none
//    - initializes object  
template <class Etype>
Stack<Etype>::Stack()
{
   head = NULL; 
}


   
// Stack
//    - copy constructor
//    - parameters : origVal - previously allocated Stack object
//    - initializes object to be a copy of origVal
template <class Etype>
Stack<Etype>::Stack(const Stack& origVal)
{
   Node *origValPtr = origVal.head,
        *newStackPtr; 
 
   if (origValPtr == NULL)  // then origList is empty
   {
      head = NULL; 
   }
   else   // origVal is not empty; copy it node for node
   {
      // at least one node in origVal; create that node
      newStackPtr = new Node; 
      newStackPtr->element = origValPtr->element; 
      head = newStackPtr; 
      origValPtr = origValPtr->next; 
 
      while (origValPtr !=NULL) // keep creating nodes as long as there
      {                         //  are nodes in origVal
         newStackPtr->next = new Node; 
         newStackPtr = newStackPtr->next; 
         newStackPtr->element = origValPtr->element; 
         origValPtr = origValPtr->next; 
      }
      newStackPtr->next = NULL;   // last node points to NULL 
   }
} 



// ~Stack
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Stack<Etype>::~Stack()
{
   Node *deletionPtr = head;
   Node* restOfList = head;
 
   while (restOfList != NULL)
   {
      restOfList = restOfList->next;
      delete deletionPtr;
      deletionPtr = restOfList;  
   }

   head = NULL;
}

 


// operator=
//    - parameters : oldVal - previously allocated Stack object
//    - return value : a stack object 
//    - sets object to be equal to oldVal 
template <class Etype>
Stack<Etype>& Stack<Etype>::operator=(const Stack<Etype>& oldVal)
{
   if (this!=&oldVal)
   {
      Node *oldValPtr = head; 
      Node *newStackPtr = head; 
 
      while (newStackPtr != NULL)
      {
         newStackPtr = newStackPtr->next;
         delete oldValPtr;  
  	 oldValPtr = newStackPtr; 
      }

      oldValPtr = oldVal.head; 
 
      if (oldValPtr == NULL)  // then origList is empty
      {
         head = NULL;
      }
      else   // oldVal is not empty; copy it node for node
      {
         // at least one node in oldVal; create that node
         newStackPtr = new Node;
         newStackPtr->element = oldValPtr->element;
         head = newStackPtr;
         oldValPtr = oldValPtr->next;
 
         while (oldValPtr !=NULL) // keep creating nodes as long as there
         {                         //  are nodes in origVal
            newStackPtr->next = new Node;
            newStackPtr = newStackPtr->next;
            newStackPtr->element = oldValPtr->element;
            oldValPtr = oldValPtr->next;
         }
         newStackPtr->next = NULL;   // last node points to NULL
      }
   }
   return *this; 
}

 


// Push
//    - parameters : newElem - an element to be added to the stack
//    - places newElem on top of stack 
template <class Etype>
void Stack<Etype>::Push(Etype newElem)
{
   if (head==NULL)
   {
      head = new Node(); 
      head->element = newElem; 
   }
   else
   {
      Node* tempPtr = new Node(); 
      tempPtr->element = newElem; 
      tempPtr->next = head; 
      head = tempPtr; 
   }
}




// Pop
//    - parameters : none
//    - return value : a value of the type held in stack
//    - removes and returns top element of stack   
template <class Etype>
Etype Stack<Etype>::Pop()
{
   Assert(head != NULL, "Trying to remove top element from empty stack!"); 
   Etype temp = head->element; 
   Node* tempPtr = head; 
   head = head->next; 
   delete tempPtr; 
   return temp; 
}

 


// Top
//    - parameters : none
//    - return value : a value of the type held in stack
//    - returns top element of stack, without removing it
template <class Etype>
Etype Stack<Etype>::Top() const
{
   Assert (head != NULL, "Trying to read top element of empty stack!"); 
   return head->element; 
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

