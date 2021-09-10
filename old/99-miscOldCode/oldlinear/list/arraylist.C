// ***********************************************************
// *                                                         *
// *  arraylist.C                                            *
// *                                                         *
// *  Implementation for a list class, implemented via       *
// *        contiguous memory                                * 
// *                                                         *
// *  Written 5/97 by Jason Zych                             *
// *                                                         *
// *********************************************************** 

#include "arraylist.h"

// Default constructor
//   Creates an empty list.
template <class Etype>
List<Etype>::List()
{
   listArray = new Array<Etype>(1, 3);  
   current = 0; 
   size = 0;    
   space = 3; 
}


// Copy Constructor
//   Creates a new list that is a copy of origList.
template <class Etype>
List<Etype>::List(const List<Etype>& origList)
{
   listArray = new Array<Etype>(); 
   (*listArray) = (*(origList.listArray)); 
   size = origList.size; 
   space = origList.space; 
   current = origList.current; 
}


// Destructor - clears all data from the list  
template <class Etype>
List<Etype>::~List()
{
   Clear(); 
   delete listArray; 
}


// Clear
//   Clears all data from list.
template <class Etype>
void List<Etype>::Clear()
{
   current = 0; 
   size = 0; 
   space = 3; 
   delete listArray; 
   listArray = new Array<Etype>(1, 3); 
}


// Assignment operator
//   Makes the current list object a copy of origList.
template <class Etype>
List<Etype>& List<Etype>::operator=(const List<Etype>& origList)
{
  if (this!=&origList)
  {
      delete listArray;
      listArray = new Array<Etype>();  
      (*listArray) = (*(origList.listArray)); 
      size = origList.size; 
      space = origList.space; 
      current = origList.current;  
     
  }  
  return *this;
} 


// InsertAfter
//   Inserts the new element into the list immediately after the 
//    current node.
template <class Etype>
void List<Etype>::InsertAfter(Etype newElem)
{
  if (size == space)  // need to expand size of array
    {
      space = 2*space; 
      listArray->SetBounds(1, space);  
    } 
  if (size==0)
    {
      current = 1; 
      size = 1; 
      (*listArray)[1] = newElem;  
    }
  else
    {
      for (int i=size; i>current; i--)
	(*listArray)[i+1] = (*listArray)[i]; 
      size++; 
      (*listArray)[current+1] = newElem; 
      current++; 
    }
}


// InsertBefore
//   Inserts the new element into the list immediately before the
//    current node.
template <class Etype>
void List<Etype>::InsertBefore(Etype newElem)
{
  if (size == space)  // need to expand size of the array
    {
      space = 2*space; 
      listArray->SetBounds(1, space);   
    }
  if (size==0)
    {
      current = 1;  
      size = 1; 
      (*listArray)[1] = newElem; 
    }
  else
    {
      for (int i=size; i>=current; i--)
	(*listArray)[i+1] = (*listArray)[i]; 
      size++; 
      (*listArray)[current] = newElem; 
    }
}


// Remove
//   Removes the element given by current.  If the list is empty,
//    user receives a warning, and no changes are made.
template <class Etype> 
void List<Etype>::Remove()
{
   if (size==0)
   {
      Warn(size > 0, "Attempt to remove an element from an empty list."); 
      return; 
   }   
   else if (size==1)
   {
      size = current = 0; 
   }
   else
   {
      for (int i=current; i<size; i++)
         (*listArray)[i] = (*listArray)[i+1]; 
      size--; 
   }
}


// Update
//   Changes the current element to the value updateElem.  Warns
//    the user if the list is empty.
template <class Etype>
void List<Etype>::Update(Etype updateElem)
{  
   Warn(size > 0, "Cannot update an element in an empty list."); 
   if (size > 0)
      (*listArray)[current] = updateElem; 
}


// Head
//   Makes the first element of the list the current element. 
template <class Etype>
void List<Etype>::Head()
{
   current = 1; 
}


// Tail
//   Makes the last element of the list the current element.
template <class Etype>
void List<Etype>::Tail()
{
   current = size; 
}


// operator++
//   Makes the element following the current element the new
//    current element; does nothing if at end of list
template <class Etype>
List<Etype>& List<Etype>::operator++(int)
{
   if (size > 0)   // if there are nodes in the list
      if (current != size)  // and we are not on the last one
         current++;    // increment the current pointer 
   return *this; 
}


// operator--
//   Makes the element prior to the current element the new current 
//    element; does nothing if at head of list 
template <class Etype>
List<Etype>& List<Etype>::operator--(int)
{
   if (size > 0)   // if there are nodes in the list
      if (current != 1)  // and we are not on the first one
         current--;    // decrement the current pointer

   return *this; 
}


// Retrieve
//   Returns the current element of the list.  If the list is
//    empty, reports the error and aborts.
template <class Etype>
Etype List<Etype>::Retrieve() const
{
   Assert(size > 0, "Cannot Retrieve an element from an empty list."); 
   return (*listArray)[current];  
}


// Find
//   Returns 1 if queryElem is in the list, 0 otherwise .
template <class Etype>
int List<Etype>::Find(Etype queryElem)
{
   int i=1; 
   while ((i<=size) && ((*listArray)[i] != queryElem))
      i++; 
   if (i==size+1)
      return 0; 
   else
   {
      current = i; 
      return 1; 
   } 
}


// Length
//   Returns the length of the list
template <class Etype>
int List<Etype>::Length() const
{
   return size; 
}


// Print
//   Prints list contents to the screen 
template <class Etype>
void List<Etype>::Print() const
{
   int outIndex = 1; 

   if (size==0)
      cout << "< empty list >"; 
   else
   { 
      cout << "< "; 
      while (outIndex<=size)  
      {
         cout << (*listArray)[outIndex] << " ";
         outIndex++; 
      } 
      cout << ">"; 
   } 
}

















