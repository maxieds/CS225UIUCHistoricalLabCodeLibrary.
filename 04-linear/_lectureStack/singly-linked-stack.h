// *******************************************************
// *                                                     *
// *  singly-linked-stack.h                              *
// *                                                     *
// *  Interface for a stack class, implemented via       *
// *    a singly-linked-list                             *
// *                                                     *
// *  Written February 2005 by Jason Zych                * 
// *                                                     *
// *******************************************************
 
#ifndef STACK_225_H
#define STACK_225_H

template <typename Etype>
class Stack 
{
public:


   // *** C++-based additions to core ADT; default constructor and Big Three

   // Stack
   //    - default constructor
   //    - initializes object to be an empty stack  
   Stack();

   
   // Stack
   //    - copy constructor
   //    - parameters : origVal - previously allocated Stack object
   //    - initializes object to be a copy of origVal
   Stack(Stack<Etype> const & origVal); 


   // ~Stack
   //    - destructor
   //    - deletes dynamically allocated memory
   ~Stack(); 


   // operator=
   //    - parameters : origVal - previously allocated Stack object
   //    - return value : this Stack object, after assignment 
   //    - sets object to be equal to origVal 
   Stack<Etype> const & operator=(Stack<Etype> const & origVal); 


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

   class StackNode
   {
   public:

      // StackNode
      //    - constructor
      //    - initializes element to default Etype, and next to NULL
      StackNode();
  
      
      // StackNode
      //    - constructor
      //    - parameters : value - the value to store in the element field
      //    - initializes node to hold value and NULL
      StackNode(Etype const & value);


      Etype element;       // holds element of node
      StackNode* next;     // pointer to the next node in the 
                           //   singly-linked list that will be built
   }; 


   // points to first (top) node of stack
   typename Stack<Etype>::StackNode* head; 
}; 


#endif 

