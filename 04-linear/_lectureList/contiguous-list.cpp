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
// *   - changes made January 2005 by Jason Zych             *
// *      - changed "class Etype" to "typename Etype"        *
// *      - put <Etype> qualifier for the name of            *
// *           type into header file                         *
// *      - used initializer list in constructors            *
// *      - assorted bug fixes                               *
// *      - changed most function names to lowercase         *
// *                                                         *
// ***********************************************************

#include <iostream>
using namespace std;

#include "asserts.h"
#include "contiguous-list.h"


 // **************** Creation/Destruction/Mass Update



// List
//    - default constructor
//    - initializes list to be empty
template <typename Etype>
List<Etype>::List() : listArray(1, 10), current(0), numElements(0)
{
   // initializer list used above; no code needed here
}



// List
//    - copy constructor
//    - parameters : origVal - a previously allocated List object
//    - initializes the list to be a copy of origVal
template <typename Etype>
List<Etype>::List(List<Etype> const & origVal) : listArray(origVal.listArray), 
                    current(origVal.current), numElements(origVal.numElements)
{
   // initializer list used above; no code needed here
}



// ~List
//    - destructor
//    - deallocates all dynamically allocated memory associated
//        with the list
template <typename Etype>
List<Etype>::~List()
{
   // nothing needed here
}




// operator=
//    - parameters: origVal - a previously allocated List object
//    - return value: reference to this List object, after it's
//         been assigned to be a copy of the parameter
//    - sets this list to be a copy of origVal
template <typename Etype>
List<Etype> const & List<Etype>::operator=(List<Etype> const & origVal)
{
  if (this != &origVal)
  {
      // no clearing out of old memory is needed here
  
      listArray = origVal.listArray;
      current = origVal.current;
      numElements = origVal.numElements;
  }
  return *this;
}




// clear
//    - deletes all values from list, resulting in an empty list
template <typename Etype>
void List<Etype>::clear()
{
   listArray.setBounds(1, 10);
   current = 0; 
   numElements = 0;
}




 // ************************ Singular Update



// insertAfter
//    - parameters : newElem - an element of the list's type,
//                       to be inserted
//    - inserts newElem after current position in list (or as
//        the only element in the list, if the list is currently
//        empty), and sets that new element as the current
//        position. Code does not check to prevent duplicates.
template <typename Etype>
void List<Etype>::insertAfter(Etype const & newElem)
{
   if (numElements == listArray.size())  // need to expand size of array
      listArray.setBounds(1, 2 * listArray.size());

   // Shift all values to the right of current, to the right
   // one cell. (If there are no values to the right of current --
   // including if the list is empty -- then this loop exits
   // immediately.)
   for (int i = numElements; i > current; i--)
         listArray[i + 1] = listArray[i]; 

   current++; 
   listArray[current] = newElem;

   numElements++;
}




// insertBefore
//    - parameters : newElem - an element of the list's type,
//                       to be inserted
//    - inserts newElem before current position in list (or as
//        the only element in the list, if the list is currently
//        empty), and sets that new element as the current
//        position. Code does not check to prevent duplicates.
template <typename Etype>
void List<Etype>::insertBefore(Etype const & newElem)
{
   if (numElements == listArray.size())  // need to expand size of the array
      listArray.setBounds(1, 2 * listArray.size());
 
   if (numElements > 0)   // if the list has values
   {
      // shift current and all vaues to its right, to the right
      // one cell; this loop assumes that the current position
      // exists and thus should not run if the list is empty 
      for (int i = numElements; i >= current; i--)
         listArray[i + 1] = listArray[i]; 
   }
   else  // list is empty
      current = 1;

   listArray[current] = newElem; 

   numElements++;
}




// remove
//    - removes the element at the current position of the list.
//       Upon completion of the removal, the current position
//       will be the next element in the list, or if there is no
//       next element, then the first position (or no position at
//       all, if the list is empty). Attempting to remove using a
//       meaningless current position (which for this class can
//       only happen when the list is empty) will result in a warning.
template <typename Etype> 
void List<Etype>::remove()
{
   if (numElements == 0)
   {
      Warn("Attempt to remove an element from an empty list."); 
   }   
   else if (numElements == 1)  // list is empty after removal
   {
      listArray.setBounds(1, 10);
      current = 0; 
      numElements = 0;
   }
   else
   {
      if (current == numElements)  // current is last value
         current = 1;
      else                         // current is NOT last value
      {
         // Move all values to the right of current, one cell to the left;
         // current holds the same index, but value that was at cell after
         // current is now in current's cell 
         for (int i = current + 1; i <= numElements; i++)
            listArray[i - 1] = listArray[i]; 
      }

      numElements--;
   }
}





// update
//    - parameters : updateElem - an element of the list's type
//    - replaces the value at the current position with updateElem
//      Attempting to update using a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning.
template <typename Etype>
void List<Etype>::update(Etype const & updateElem)
{  
   if (numElements > 0)
      listArray[current] = updateElem;
   else
      Warn("Cannot update an element in an empty list."); 
}




 // ********************* Control of Current Position




// front
//    - makes the first position in the list the current position
//      Attempting to do this when there is no first position in the
//      list (which for this class can only happen when the list is 
//      empty) will result in a warning.
template <typename Etype>
void List<Etype>::front()
{
   if (numElements > 0)
      current = 1;
   else
      Warn("Cannot move current to head of an empty list.");
}




// back
//    - makes the last position in the list the current position
//      Attempting to do this when there is no last position in the 
//      list (which for this class can only happen when the list is 
//      empty) will result in a warning.
template <typename Etype>
void List<Etype>::back()
{
   if (numElements > 0)
      current = numElements;
   else
      Warn("Cannot move current to tail of an empty list.");
}






// forwardOne
//    - moves the current position one position forward in the list.
//      Attempting to move forward from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning. Attempting to move forward from the
//      last position in the list will result in a warning and the
//      current position remaining unchanged.
template <typename Etype>
void List<Etype>::forwardOne()
{
   if (numElements > 0)   // if there are nodes in the list
   {
      if (current != numElements)  // and we are not on the last one
         current++;                // increment the current position
      else
         Warn("Cannot advance current position past end position.");
   }
   else
      Warn("Cannot move to next position of an empty list.");
}






// backwardOne
//    - moves the current position one position backward in the list.
//      Attempting to move backward from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning. Attempting to move backward from the
//      first position in the list will result in a warning and the
//      current position remaining unchanged.
template <typename Etype>
void List<Etype>::backwardOne()
{
   if (numElements > 0)   // if there are nodes in the list
   {
      if (current != 1)  // and we are not at the first one
         current--;       // decrement the current position
      else
         Warn("Cannot decrement current position when at first element.");
   }
   else
      Warn("Cannot move to previous position of an empty list.");
}




 // ******************** Information Access




// retrieve
//    - returns the element at the current list position
//      Attempting to retrieve from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in an error message and termination of program.
template <typename Etype>
Etype const & List<Etype>::retrieve() const
{
   Assert(numElements > 0, "Cannot Retrieve an element from an empty list."); 
   return listArray[current];  
}





// find
//    - parameters : queryElem - an element of the list's type,
//                       to be searched for
//    - return value : boolean with true indicating value was found
//    - searches list for queryElem...if found, make that position
//         the current position and return true; otherwise, return false.
//         Assumes existence of operator!= for generic type.
template <typename Etype>
bool List<Etype>::find(Etype const & queryElem)
{
   int index = 1;
   bool result;

   while ((index <= numElements) && (listArray[index] != queryElem))
      index++;

   if (index == numElements + 1)       // exited because no more values
      result = false;
   else                                // exited because found queryElem
   {
      current = index; 
      result = true;
   } 

   return result;
}




// length
//    - return value : an integer representing the list's length
//    - returns the length of the list
template <typename Etype>
int List<Etype>::length() const
{
   return numElements;
}




// print
//    - prints out the list values
template <typename Etype>
void List<Etype>::print() const
{
   if (numElements == 0)
      cout << "< empty list >";  
   else
   {
      cout << "< ";
      for (int i = 1; i <= numElements; i++)
         cout << listArray[i] << " ";
      cout << ">";
   }
}



