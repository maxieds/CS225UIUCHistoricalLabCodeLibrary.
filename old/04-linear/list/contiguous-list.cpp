// ***********************************************************
// *                                                         *
// *  contiguous-list.cpp                                    *
// *                                                         *
// *  Implementation for a list class, implemented via       *
// *        contiguous memory                                *
// *                                                         *
// *  Written May 1997 by Jason Zych                         *
// *   - slight edits done July 2001 by Jason Zych           *
// *                                                         *
// *   - Changes made September 2004 by Jason Zych           *
// *      - removed .h from standard header includes         *
// *      - changed #ifndef macro name                       *
// *      - standardized const to right of what it modifies  *
// *      - changed return type of ForwardOne and            *
// *              BackwardOne to void                        *
// *                                                         *
// ***********************************************************


#include "contiguous-list.h"


 // **************** Creation/Destruction/Mass Update



// List
//    - default constructor
//    - creates an empty list
template <class Etype>
List<Etype>::List() : listArray(1, 10)
{
   current = 0; 
   size = 0;    
}



// List
//    - copy constructor
//    - parameters : origVal - a previously allocated List object
//    - initializes the list to be a copy of origVal
template <class Etype>
List<Etype>::List(List<Etype> const& origVal)  
{
   listArray = origVal.listArray;
   current = origVal.current;
   size = origVal.size; 
}



// ~List
//    - destructor
//    - deallocates all dynamically allocated memory associated with the list
template <class Etype>
List<Etype>::~List()
{
   Clear(); 
}




// operator=
//    - parameters: origVal - a previously allocated List object
//    - return value: reference to this List object, after it's been assigned
//    - sets this list to be a copy of origVal
template <class Etype>
List<Etype> const& List<Etype>::operator=(List<Etype> const& origVal)
{
  if (this != &origVal)
  {
      Clear();
  
      listArray = origVal.listArray;
      current = origVal.current;
      size = origVal.size;
  }
  return *this;
}




template <class Etype>
void List<Etype>::Clear()
{
   listArray.SetBounds(1, 10);
   current = 0; 
   size = 0; 
}




 // ************************ Singular Update



// InsertAfter
//    - parameters : newElem - an element of the list's type, to be inserted
//    - inserts newElem after current position in list, and sets that new
//        element as the current position. Code does not check to prevent
//        duplicates.
template <class Etype>
void List<Etype>::InsertAfter(Etype const& newElem)
{
   if (size == listArray.Size())  // need to expand size of array
      listArray.SetBounds(1, 2 * listArray.Size());

   for (int i = size; i > current; i--)
      listArray[i+1] = listArray[i]; 
   size++;
   current++; 
   listArray[current] = newElem;
}




// InsertBefore
//    - parameters : newElem - an element of the list's type, to be inserted
//    - inserts newElem before current position in list, and sets that new
//        element as the current position. Code does not check to prevent
//        duplicates.
template <class Etype>
void List<Etype>::InsertBefore(Etype const& newElem)
{
   if (size == listArray.Size())  // need to expand size of the array
      listArray.SetBounds(1, 2*listArray.Size());
 
   if (size > 0) 
      for (int i = size; i >= current; i--)
         listArray[i+1] = listArray[i]; 
   else
      current = 1;

   size++; 
   listArray[current] = newElem; 
}




// Remove
//    - removes the element at the current position of the list. 
//       Attempting to remove using a meaningless current position 
//       (which for this class can only happen when the list is empty) 
//       will result in a warning.
template <class Etype> 
void List<Etype>::Remove()
{
   if (size==0)
   {
      Warn("Attempt to remove an element from an empty list."); 
      return; 
   }   
   else if (size==1)
   {
      listArray.SetBounds(0, 10);
      size = current = 0; 
   }
   else
   {
      for (int i = current; i < size; i++)
         listArray[i] = listArray[i+1]; 
      size--; 
      if ((size < listArray.Size()/2) && (listArray.Size() > 10))
         listArray.SetBounds(1, listArray.Size()/2);
   }
}





// Update
//    - parameters : updateElem - an element of the list's type
//    - replaces the value at the current position with updateElem
//      Attempting to update using a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning.
template <class Etype>
void List<Etype>::Update(Etype const& updateElem)
{  
   if (size > 0)
      listArray[current] = updateElem;
   else
      Warn("Cannot update an element in an empty list."); 
}




 // ********************* Control of Current Position




// Head
//    - makes the first position in the list the current position
//      Attempting to do this when there is no first position in the list
//      (which for this class can only happen when the list is empty)
//      will result in a warning.
template <class Etype>
void List<Etype>::Head()
{
   if (size > 0)
      current = 1;
   else
      Warn("Cannot move current to head of an empty list.");
}




// Tail
//    - makes the last position in the list the current position
//      Attempting to do this when there is no last position in the list
//      (which for this class can only happen when the list is empty)
//      will result in a warning.
template <class Etype>
void List<Etype>::Tail()
{
   if (size > 0)
      current = size;
   else
      Warn("Cannot move current to tail of an empty list.");
}






// ForwardOne
//    - moves the current position one position forward in the list.
//      Attempting to move forward from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning. Attempting to move forward from the
//      last position in the list will result in a warning and the
//      current position remaining unchanged.
template <class Etype>
void List<Etype>::ForwardOne()
{
   if (size > 0)   // if there are nodes in the list
      if (current != size)  // and we are not on the last one
         current++;         // increment the current position
      else
         Warn("Cannot advance current position past end position.");
   else
      Warn("Cannot move to next position of an empty list.");
}






// BackwardOne
//    - moves the current position one position backward in the list.
//      Attempting to move backward from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning. Attempting to move backward from the
//      first position in the list will result in a warning and the
//      current position remaining unchanged.
template <class Etype>
void List<Etype>::BackwardOne()
{
   if (size > 0)   // if there are nodes in the list
      if (current != 1)  // and we are not at the first one
         current--;       // decrement the current position
      else
         Warn("Cannot decrement current position when at first element.");
   else
      Warn("Cannot move to previous position of an empty list.");
}




 // ******************** Information Access




// Retrieve
//    - returns the element at the current list position
//      Attempting to retrieve from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in an error message and termination of program.
template <class Etype>
Etype const& List<Etype>::Retrieve() const
{
   Assert(size > 0, "Cannot Retrieve an element from an empty list."); 
   return listArray[current];  
}





// Find 
//    - parameters : queryElem - an element of the list's type, to search for
//    - return value : a boolean yes or no
//    - searches list for queryElem...if found, make that position the current
//         position and return 1; otherwise, return 0
template <class Etype>
int List<Etype>::Find(Etype const& queryElem)
{
   int searchIndex = 1; 
   int result;

   while ((searchIndex <= size) && (listArray[searchIndex] != queryElem))
      searchIndex++; 
   if (searchIndex == size+1)
      result = 0;
   else
   {
      current = searchIndex; 
      result = 1;
   } 
   return result;
}




// Length
//    - return value : an integer representing the list's length
//    - returns the length of the list
template <class Etype>
int List<Etype>::Length() const
{
   return size; 
}




// Print
//    - prints out the list values
template <class Etype>
void List<Etype>::Print() const
{
   if (size == 0)
      cout << "< empty list >";  
   else
   {
      cout << "< ";
      for (int i = 1; i <= size; i++)
         cout << listArray[i] << " ";
      cout << ">";
   }
}

