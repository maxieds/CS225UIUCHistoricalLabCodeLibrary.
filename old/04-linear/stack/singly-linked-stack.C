// *******************************************************
// *                                                     *
// *  singly-linked-stack.C                              *
// *                                                     *
// *  Implementation for a stack class, implemented via  *
// *    a singly-linked-list                             *
// *                                                     *
// *  Written February 1998 by Jason Zych                * 
// *    - slight edits done July 2001 by Jason Zych      *
// *                                                     *
// *******************************************************

#include <iostream.h> 
#include "asserts.h"
#include "singly-linked-stack.h"


 // *** Constructors and other assorted additions to core ADT

 
// Stack
//    - default constructor
//    - initializes object to be an empty stack  
template <class Etype>
Stack<Etype>::Stack() : head(NULL), size(0)
{
   // no code needed here
}




// Stack
//    - copy constructor
//    - parameters : origVal - previously allocated Stack object
//    - initializes object to be a copy of origVal
template <class Etype>
Stack<Etype>::Stack(const Stack& origVal)
{
   StackNode *paramListPtr, *thisListPtr, *newestNode;

   paramListPtr = origVal.head;
   if (paramListPtr == NULL)  // then origList is empty
   {
      head = NULL;
      size=0; 
   }
   else 
   {
      while (paramListPtr != NULL)
      {
         newestNode = new StackNode(paramListPtr->element);

         if (paramListPtr == origVal.head)
         {
            thisListPtr = newestNode;
            head = thisListPtr;
         }
         else
         {
            thisListPtr->next = newestNode;
            thisListPtr = thisListPtr->next;
         }
         paramListPtr = paramListPtr->next;
      }
      size = origVal.size;
   }
}




// ~Stack
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Stack<Etype>::~Stack()
{
   StackNode* deletionPtr = head;

   while (head != NULL)
   {
      head = head->next;
      delete deletionPtr;
      deletionPtr = head;
   }
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
      StackNode* deletionPtr = head;

      while (head != NULL)
      {
         head = head->next;
         delete deletionPtr;
         deletionPtr = head;
      }

      StackNode *paramListPtr, *thisListPtr, *newestNode;

      paramListPtr = origVal.head;
      if (paramListPtr == NULL)  // then origList is empty
      {
         head = NULL;
         size=0; 
      }
      else 
      {
         while (paramListPtr != NULL)
         {
            newestNode = new StackNode(paramListPtr->element);

            if (paramListPtr == origVal.head)
            {
               thisListPtr = newestNode;
               head = thisListPtr;
            }
            else
            {
               thisListPtr->next = newestNode;
               thisListPtr = thisListPtr->next;
            }
            paramListPtr = paramListPtr->next;
         }
         size = origVal.size;
      }
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
   StackNode* outPtr = head; 

   if (size==0)
      cout << "< empty stack >" << endl;
   else
   { 
      cout << "< "; 
      while (outPtr != NULL)  
      {
         cout << outPtr->element << " ";
         outPtr = outPtr->next; 
      } 
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
   if (size == 0)
      head = new StackNode(newElem);
   else
   {
      StackNode* newNode = new StackNode(newElem);
      newNode->next = head;
      head = newNode;
   }  
   size++;
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
   StackNode* deletePtr = head;
   Etype temp = head->element;
   head = head->next;
   delete deletePtr;
   size--;
   return temp;
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
   return head->element;   
}


// Is_Empty
//    - return value : boolean integer
//    - returns 1 if stack is empty, 0 otherwise
template <class Etype>
int Stack<Etype>::IsEmpty() const
{
   return (head == NULL);
}


