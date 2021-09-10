// *******************************************************
// *                                                     *
// *  singly-linked-stack.cpp                            *
// *                                                     *
// *  Implementation for a stack class, implemented via  *
// *    a singly-linked-list                             *
// *                                                     *
// *  Written February 2005 by Jason Zych                *
// *                                                     *
// *******************************************************


#include <cstddef>

#include "asserts.h"
#include "singly-linked-stack.h"



// *** C++-based additions to core ADT; default constructor and Big Three

// Stack
//    - default constructor
//    - initializes object to be an empty stack
template <typename Etype>
Stack<Etype>::Stack() : head(NULL)
{
   // initializer list used above; no code needed here
}



// Stack
//    - copy constructor
//    - parameters : origVal - previously allocated Stack object
//    - initializes object to be a copy of origVal
template <typename Etype>
Stack<Etype>::Stack(Stack<Etype> const & origVal)
{
   typename Stack<Etype>::StackNode* paramListPtr;
   typename Stack<Etype>::StackNode* thisListPtr;
   typename Stack<Etype>::StackNode* newestNode;

   paramListPtr = origVal.head;
   if (paramListPtr == NULL)  // then origList is empty
      head = NULL;
   else 
   {
      while (paramListPtr != NULL)
      {
         newestNode = new Stack<Etype>::StackNode(paramListPtr->element);

         if (paramListPtr == origVal.head)
         {
            thisListPtr = newestNode;
            head = newestNode;
         }
         else
         {
            thisListPtr->next = newestNode;
            thisListPtr = thisListPtr->next;
         }
         paramListPtr = paramListPtr->next;
      }
   }
}




// ~Stack
//    - destructor
//    - deletes dynamically allocated memory
template <typename Etype>
Stack<Etype>::~Stack()
{
   typename Stack<Etype>::StackNode* deletionPtr = head;

   while (deletionPtr != NULL)
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
template <typename Etype>
Stack<Etype> const & Stack<Etype>::operator=(
                            Stack<Etype> const & origVal)
{
   if (this != &origVal)
   {
      Stack<Etype>::StackNode* deletionPtr = head;

      while (deletionPtr != NULL)
      {
         head = head->next;
         delete deletionPtr;
         deletionPtr = head;
      }

      typename Stack<Etype>::StackNode* paramListPtr;
      typename Stack<Etype>::StackNode* thisListPtr;
      typename Stack<Etype>::StackNode* newestNode;

      paramListPtr = origVal.head;
      if (paramListPtr == NULL)  // then origList is empty
         head = NULL;
      else
      {
         while (paramListPtr != NULL)
         {
            newestNode = new Stack<Etype>::StackNode(paramListPtr->element);

            if (paramListPtr == origVal.head)
            {
               thisListPtr = newestNode;
               head = newestNode;
            }
            else
            {
               thisListPtr->next = newestNode;
               thisListPtr = thisListPtr->next;
            }
            paramListPtr = paramListPtr->next;
         }
      }
   }
   return *this;
}



// *** Functions in the core Stack ADT


// push
//    - parameters : insElem - an element to be added to the stack
//    - places insElem on top of stack 
template <typename Etype>
void Stack<Etype>::push(Etype const & insElem)
{
   if (head == NULL)
      head = new Stack<Etype>::StackNode(insElem);
   else
   {
      typename Stack<Etype>::StackNode* temp;
      temp = new Stack<Etype>::StackNode(insElem);

      // standard two assignments to insert into a singly-linked list
      temp->next = head;
      head = temp;
   }  
}






// pop
//    - return value : a value of the type held in stack
//    - removes and returns top element of stack. Assumes 
//        stack is not empty; if the stack is indeed empty,
//        an assertion is triggered.   
template <typename Etype>
Etype Stack<Etype>::pop()
{
   Assert(head != NULL, "Cannot remove top element of an empty stack!");

   typename Stack<Etype>::StackNode* deletePtr = head;
   Etype temp = head->element;
   head = head->next;
   delete deletePtr;
   return temp;
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
   Assert(head != NULL, "Cannot read top element of an empty stack!");
   return head->element;   
}


// isEmpty
//    - return value : boolean with true indicating an empty stack
//    - returns true if stack is empty; else returns false
template <typename Etype>
bool Stack<Etype>::isEmpty() const
{
   return (head == NULL);
}



// StackNode
//    - constructor
//    - initializes element to default Etype, and next to NULL
template <typename Etype>
Stack<Etype>::StackNode::StackNode() : element(), next(NULL)
{
   // initializer list used above; no code needed here
} 

  
      
// StackNode
//    - constructor
//    - parameters : value - the value to store in the element field
//    - initializes node to hold value and NULL
template <typename Etype>
Stack<Etype>::StackNode::StackNode(Etype const & value) :
                          element(value), next(NULL)
{
   // initializer list used above; no code needed here
}


