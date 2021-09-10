// ***********************************************************
// *                                                         *
// *  singly-linked-list.cpp                                 *
// *                                                         *
// *  Implementation for a list class, implemented via       *
// *        singly-linked memory                             * 
// *                                                         *
// *  Written May 1997 by Jason Zych                         *
// *   - slight edits done July 2001 by Jason Zych           *
// *                                                         *
// *   - Changes made September 2004 by Jason Zych           *
// *      - removed .h from standard header includes         *
// *      - scoped all instances of typename ListNode to     *
// *             parent class                                * 
// *      - changed #ifndef macro name                       * 
// *      - moved node implementation to .cpp                *
// *      - standardized const to right of what it modifies  *
// *      - changed return type of ForwardOne and            *
// *              BackwardOne to void                        *
// *                                                         *
// *   - changes made January 2005 by Jason Zych             *
// *      - changed "class Etype" to "typename Etype"        *
// *      - put <Etype> qualifier for the name of            *
// *             type into header file                       *
// *      - used initializer list in constructors            *
// *      - assorted bug fixes                               *
// *      - changed most function names to lowercase         *
// *                                                         *
// ***********************************************************

#include <cstddef>
#include <iostream>
using namespace std; 

#include "asserts.h"
#include "singly-linked-list.h"


 // **************** Creation/Destruction/Mass Update


// List
//    - default constructor
//    - initializes list to be empty
template <typename Etype>
List<Etype>::List() : head(NULL), current(NULL), tail(NULL), size(0) 
{
   // initializer list used above; no code needed here
}



// List
//    - copy constructor
//    - parameters : origVal - a previously allocated List object
//    - initializes the list to be a copy of origVal
template <typename Etype>
List<Etype>::List(List<Etype> const & origVal)
{
   copy(origVal);
}



// ~List
//    - destructor
//    - deallocates all dynamically allocated memory associated 
//        with the list
template <typename Etype>
List<Etype>::~List()
{
   clear(); 
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
      clear();           // clear out old dynamic memory

      copy(origVal);     // copy parameter list
   }  

   return *this;
} 



// clear
//    - deletes all values from list, resulting in an empty list
template <typename Etype>
void List<Etype>::clear()
{
   typename List<Etype>::ListNode* deletionPtr = head;
   current = head;

   while (deletionPtr != NULL)
   {
      current = current->next;
      delete deletionPtr;
      deletionPtr = current;
   }

   head = NULL;
   current = NULL;
   tail = NULL;
   size = 0;
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
   typename List<Etype>::ListNode* tempNode;

   tempNode = new List<Etype>::ListNode(newElem);
 
   if (size == 0)
   {
      head = tempNode;
      current = tempNode;
      tail = tempNode;
   }
   else
   {
      // standard two assignments for singly-linked list insertion
      tempNode->next = current->next; 
      current->next = tempNode; 

      if (tail == current)
         tail = tempNode; 

      current = tempNode;
   }
   size++; 
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
   typename List<Etype>::ListNode* tempNode;
   
   // we have separate node allocation for each part of the 
   // conditional this time

   if (size == 0)
   {
      tempNode = new List<Etype>::ListNode(newElem);
      head = tempNode;
      current = tempNode;
      tail = tempNode;
   }
   else
   {
      // This allocation was different in InsertAfter; here,
      // we copy the old (current) value into the new node, and move
      // the new value into the old (current) node...thus we can
      // simulate an "insertBefore" by swapping the order of the
      // values in this way and then doing an "insertAfter"
      tempNode = new List<Etype>::ListNode(current->element);
      current->element = newElem;

      // standard two assignments for singly-linked list insertion
      tempNode->next = current->next;
      current->next = tempNode;

      if (tail == current)
         tail = tempNode;

      // current already points to the node into which we put the new
      // value, so current doesn't need to be reassigned to another node
   }
   size++;
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
   typename List<Etype>::ListNode* removePtr;
   
   if (size == 0)
   {
      Warn("Attempt to remove an element from an empty list."); 
   }   
   else 
   {
      if (size == 1)
      {
         delete current; 
         head = NULL;
         current = NULL;
         tail = NULL;
      }
      else if (current->next == NULL)   // deleting last element when size >= 2
      {
         // traverse from start of list to find the node before current
         removePtr = head; 
         while (removePtr->next != current)
            removePtr = removePtr->next; 
         removePtr->next = NULL; 
         delete current; 
         tail = removePtr;  
         current = head;
      }
      else   // deleting non-last element when size >= 2
      {
         // We will actually delete the node *after* current. Save that
         // node's value by storing it in current node. We don't need
         // to save current node's value because that's the one we are
         // trying to get rid of.
         current->element = current->next->element;

         removePtr = current->next;  // save to-be-deleted node so we can
                                     // delete it later

         // standard assignment for singly-linked list removal
         current->next = current->next->next;

         if (tail == removePtr)
            tail = current; 

         delete removePtr; 
      }
      size--; 
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
   if (size > 0)
      current->element = updateElem;
   else
      Warn("Cannot update an element in an empty list."); 
}



 // ********************* Control of Current Position



// front
//    - makes the first position in the list the current position
//      Attempting to do this when there is no first position in the 
//      list which for this class can only happen when the list is
//      empty) will result in a warning.
template <typename Etype>
void List<Etype>::front()
{
   if (size > 0)
      current = head;
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
   if (size > 0)
      current = tail; 
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
   if (size > 0)   // if there are nodes in the list
   {
      if (current->next != NULL)  // and we are not at the last one
         current = current->next;   // increment the current pointer 
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
   if (size > 0)   // if there are nodes in the list
   {
      if (current != head)  // and we are not at the first one
      {
         ListNode* beforePtr = head; 
         while (beforePtr->next != current)
            beforePtr = beforePtr->next; 
         current = beforePtr; 
      } 
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
   Assert(size > 0, "Cannot Retrieve an element from an empty list."); 
   return current->element;    
}




// find
//    - parameters : queryElem - an element of the list's type,
//                       to be searched for
//    - return value : an integer serving as a boolean
//    - searches list for queryElem...if found, make that position 
//         the current position and return 1; otherwise, return 0
template <typename Etype>
bool List<Etype>::find(Etype const & queryElem)
{
   typename List<Etype>::ListNode* searchPtr = head;
   bool result;

   while ((searchPtr !=NULL) && (searchPtr->element != queryElem))
      searchPtr = searchPtr->next; 

   if (searchPtr == NULL)  // stopped because ran out of values
      result = false;
   else                    // stopped because search key was found
   {
      current = searchPtr; 
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
   return size; 
}



// print
//    - prints out the list values
template <typename Etype>
void List<Etype>::print() const
{
   typename List<Etype>::ListNode* outPtr = head;

   if (size == 0)
      cout << "< empty list >";  
   else
   { 
      cout << "< "; 
      while (outPtr != NULL)  
      {
         cout << outPtr->element << " ";
         outPtr = outPtr->next; 
      } 
      cout << ">";
   } 
}


// copy
//    - parameters : origVal - a previously allocated List object
//    - sets the list to be a copy of origVal; assumes there is no
//         dynamic memory that needs to be cleaned out of the list
template <typename Etype>
void List<Etype>::copy(List<Etype> const & origVal)
{
   typename List<Etype>::ListNode* paramListPtr;
   typename List<Etype>::ListNode* thisListPtr;
   typename List<Etype>::ListNode* newestNode;

   paramListPtr = origVal.head;

   if (paramListPtr == NULL)  // then origList is empty
   {
      head = NULL;
      current = NULL;
      tail = NULL;
      size = 0;
   }
   else   // origList has at least one node
   {
      while (paramListPtr != NULL)
      {
         newestNode = new List<Etype>::ListNode(paramListPtr->element);

         if (paramListPtr == origVal.head)  // adding first node to list
         {
            thisListPtr = newestNode;
            head = newestNode;
         }
         else                  // adding some other non-first node to list
         {
            thisListPtr->next = newestNode;
            thisListPtr = thisListPtr->next;
         }

         if (paramListPtr == origVal.current)  // this runs, first or not
            current = thisListPtr;
         paramListPtr = paramListPtr->next;

      }
      tail = thisListPtr;
      size = origVal.size;
   }
}

// ListNode
//    - constructor
//    - initializes element to default Etype, and next to NULL
template <typename Etype>
List<Etype>::ListNode::ListNode() : element(), next(NULL)
{
   // no code needed here due to initializer list above
}



// ListNode
//    - constructor
//    - parameters : value - the value to store in the element field
//    - initializes node to hold value and NULL
template <typename Etype>
List<Etype>::ListNode::ListNode(Etype const & value) : 
                                          element(value), next(NULL)
{
   // no code needed here due to initializer list above
}



