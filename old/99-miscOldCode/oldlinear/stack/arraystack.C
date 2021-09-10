/***************************************************
 * arraystack.C                                    *
 *                                                 *
 *  Implementation of an array-based Stack class.  *
 *   adapted from Weiss, 1994                      *
 *                                                 *
 *  Author: Wendy L. Terry                         *
 *    Date: 8 Feb 1997                             *
 *  Update: 6 Oct 1997 by Wendy L. Terry           *
 *             -- expanded some comments           *
 *                                                 *
 ***************************************************/

#include <iostream.h>
#include <stdlib.h>
#include "asserts.h"
#include "stack.h"

// Constructor
template <class Etype>
Stack<Etype>::Stack(unsigned int maxsize)
{
  full_stack = maxsize;
  top_of_stack = -1;
  contents = new Etype[ maxsize ];
  Assert( contents != NULL, "Out of space in constructor.");
}

// Assignment operator
template <class Etype>
const Stack<Etype>& Stack<Etype>::operator= (const Stack& value)
{
  if (this != &value) {

    delete [] contents;
    contents = new Etype[ value.full_stack ];

    for (int i=0; i <= value.top_of_stack; i++) {
      contents[i] = value.contents[i];
    }

    top_of_stack = value.top_of_stack;
    full_stack = value.full_stack;
  }

  return *this;
}

// Member functions
//------------------

// Push
//   Pushes X onto the stack.  If stack is full, issues a warning,
//     and no changes are made to the stack.
template <class Etype>
void Stack<Etype>::Push(const Etype& X)
{
  if ( IsFull() ) {
    Warn(0, "Attempt to push on full stack.");
  }else {
    contents[ ++ top_of_stack ] = X;
  }
}


// Pop
//   Pops a value from the stack.  If stack is empty, issues a
//    warning, and forgoes the change.
template <class Etype>
void Stack<Etype>::Pop()
{
  if ( IsEmpty() ) {
    Warn(0, "Attempt to pop from empty stack.");
  }else {
    --top_of_stack;
  }
}


// Pop_n_top
//   Pops from the stack, returning the value that
//    was popped.  If stack is empty, reports the
//    error and aborts.
template <class Etype>
const Etype& Stack<Etype>::Pop_n_top()
{
  Etype top_elmt;

  if ( IsEmpty() ) {
    Assert(0, "Empty stack");
  }else {
    return contents[top_of_stack--];
  }
}


// Top
//   Returns the top value of the stack, without changing the
//    stack contents.  If the stack is empty, reports the
//    error and aborts.
template <class Etype>
const Etype& Stack<Etype>::Top() const
{
  if ( IsEmpty() ) {
    Assert(0, "Empty stack.");
  }else {
    return contents[ top_of_stack ];
  }
}


// MakeEmpty
//   Empties the stack.
template <class Etype>
void Stack<Etype>::MakeEmpty()
{
  top_of_stack = -1;
}
