/***********************************************
 * arraystack.h                                *
 *                                             *
 *  Interface for an array-based Stack class.  *
 *   adapted from Weiss, 1994                  *
 *                                             *
 *  Author: Wendy L. Terry                     *
 *    Date: 6 Feb 1997                         *
 *  Update: 6 Oct 1997 by Wendy L. Terry       *
 *             -- expanded some comments       *
 *                                             *
 ***********************************************/

#ifndef ASTACK_H
#define ASTACK_H

static const default_size = 100;

template <class Etype>
class Stack
{
private:

  int top_of_stack;
  unsigned int full_stack;
  Etype *contents;

public:

  // Constructor
  Stack(unsigned int maxsize = default_size);

  // Copy constructor
  Stack(const Stack & value) { operator=(value); }

  // Destructor
  ~Stack() { delete [] contents; }

  // Assignment operator
  const Stack& operator= (const Stack& value);

  // Member functions
  //------------------

  void Push(const Etype& X);
  //   Pushes X onto the stack.  If stack is full, issues a warning,
  //     and no changes are made to the stack.

  void Pop();
  //   Pops a value from the stack.  If stack is empty, issues a
  //    warning, and forgoes the change.

  const Etype& Pop_n_top();
  // Pops from the stack, returning the value that
  //    was popped.  If stack is empty, reports the
  //    error and aborts.

  const Etype& Top() const;
  // Returns the top value of the stack, without changing the
  //    stack contents.  If the stack is empty, reports the
  //    error and aborts.

  void MakeEmpty();
  // Empties the stack.

  int IsEmpty() const
    { return top_of_stack == -1; }
  // Returns TRUE if the stack is empty, FALSE otherwise.

  int IsFull() const
    { return top_of_stack == full_stack-1; }
  // Returns TRUE if the stack is full, FALSE otherwise.

};

#endif
