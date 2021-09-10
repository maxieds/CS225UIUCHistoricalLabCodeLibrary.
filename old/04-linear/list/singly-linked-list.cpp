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
// ***********************************************************

#include "singly-linked-list.h"


 // **************** Creation/Destruction/Mass Update


// List
//    - default constructor
//    - creates an empty list
template <class Etype>
List<Etype>::List()
{
   head = NULL;
   current = NULL;
   tail = NULL; 
   size = 0; 
}



// List
//    - copy constructor
//    - parameters : origVal - a previously allocated List object
//    - initializes the list to be a copy of origVal
template <class Etype>
List<Etype>::List(List<Etype> const& origVal)
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
   else 
   {
      while (paramListPtr != NULL)
      {
         newestNode = new ListNode(paramListPtr->element);

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
         if (paramListPtr == origVal.current)
            current = thisListPtr;
         paramListPtr = paramListPtr->next;
      }
      tail = thisListPtr;
      size = origVal.size;
   }
}



// ~List
//    - destructor
//    - deallocates all dynamically allocated memory associated 
//        with the list
template <class Etype>
List<Etype>::~List()
{
   Clear(); 
}




// operator=
//    - parameters: origVal - a previously allocated List object
//    - return value: reference to this List object, after it's 
//         been assigned to be a copy of the parameter
//    - sets this list to be a copy of origVal
template <class Etype>
List<Etype> const& List<Etype>::operator=(List<Etype> const& origVal)
{
   if (this != &origVal)
   {
      Clear(); 

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
      else 
      {
         while (paramListPtr != NULL)
         {
            newestNode = new ListNode(paramListPtr->element);

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
            if (paramListPtr == origVal.current)
               current = thisListPtr;
            paramListPtr = paramListPtr->next;
         }
         tail = thisListPtr;
         size = origVal.size;
      }
   }  

   return *this;
} 



// Clear
//    - deletes all values from list, resulting in an empty list
template <class Etype>
void List<Etype>::Clear()
{
   typename List<Etype>::ListNode* deletionPtr = head;
   current = head;

   while (current != NULL)
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



// InsertAfter
//    - parameters : newElem - an element of the list's type, 
//                       to be inserted
//    - inserts newElem after current position in list (or as
//        the only element in the list, if the list is currently
//        empty), and sets that new element as the current 
//        position. Code does not check to prevent duplicates. 
template <class Etype>
void List<Etype>::InsertAfter(Etype const& newElem)
{
   typename List<Etype>::ListNode* tempNode;

   // the allocation line repeated twice
   //  below could go here once instead
 
   if (size == 0)
   {
      tempNode = new ListNode(newElem);
      head = tempNode;
      current = tempNode;
      tail = tempNode;
   }
   else
   {
      tempNode = new ListNode(newElem);

      tempNode->next = current->next; 
      current->next = tempNode; 
      if (tail == current)
         tail = tempNode; 

      current = tempNode;
   }
   size++; 
}




// InsertBefore
//    - parameters : newElem - an element of the list's type, 
//                       to be inserted
//    - inserts newElem before current position in list (or as
//        the only element in the list, if the list is currently
//        empty), and sets that new element as the current 
//        position. Code does not check to prevent duplicates. 
template <class Etype>
void List<Etype>::InsertBefore(Etype const& newElem)
{
   // code is same as InsertAfter except where indicated
   typename List<Etype>::ListNode* tempNode;

   if (size == 0)
   {
      tempNode = new ListNode(newElem);
      head = tempNode;
      current = tempNode;
      tail = tempNode;
   }
   else
   {
      tempNode = new ListNode(current->element); // different in InsertAfter

      tempNode->next = current->next;
      current->next = tempNode;
      if (tail == current)
         tail = tempNode;
     
      current->element = newElem;   // different in InsertAfter
   }
   size++;
}




// Remove
//    - removes the element at the current position of the list.
//       Upon completion of the removal, the current position  
//       will be the next element in the list, or if there is no
//       next element, then the first position (or no position at
//       all, if the list is empty). Attempting to remove using a 
//       meaningless current position (which for this class can 
//       only happen when the list is empty) will result in a warning.
template <class Etype> 
void List<Etype>::Remove()
{
   typename List<Etype>::ListNode* removePtr;
   
   if (size == 0)
   {
      Warn("Attempt to remove an element from an empty list."); 
      return; 
   }   
   else if (size == 1)
   {
      delete current; 
      head = current = tail = NULL;
   }
   else if (current->next == NULL)   // deleting last element
   {
      removePtr = head; 
      while (removePtr->next != current)
         removePtr = removePtr->next; 
      removePtr->next = NULL; 
      delete current; 
      tail = removePtr;  
      current = head;
   }
   else   // this is the case you would expect to reach most often
   {
      removePtr = current->next; 
      current->element = removePtr->element; 
      current->next = removePtr->next; 
      if (tail == removePtr)
         tail = current; 
      delete removePtr; 
   }
   size--; 
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
      current->element = updateElem;
   else
      Warn("Cannot update an element in an empty list."); 
}



 // ********************* Control of Current Position



// Head
//    - makes the first position in the list the current position
//      Attempting to do this when there is no first position in the 
//      list which for this class can only happen when the list is
//      empty) will result in a warning.
template <class Etype>
void List<Etype>::Head()
{
   if (size > 0)
      current = head;
   else
      Warn("Cannot move current to head of an empty list.");
}




// Tail
//    - makes the last position in the list the current position
//      Attempting to do this when there is no last position in the 
//      list (which for this class can only happen when the list is
//      empty) will result in a warning.
template <class Etype>
void List<Etype>::Tail()
{
   if (size > 0)
      current = tail; 
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
      if (current->next != NULL)  // and we are not at the last one
         current = current->next;   // increment the current pointer 
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
      if (current != head)  // and we are not at the first one
      {
         ListNode* beforePtr = head; 
         while (beforePtr->next != current)
            beforePtr = beforePtr->next; 
         current = beforePtr; 
      } 
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
   return current->element;    
}




// Find
//    - parameters : queryElem - an element of the list's type,
//                       to be searched for
//    - return value : an integer serving as a boolean
//    - searches list for queryElem...if found, make that position 
//         the current position and return 1; otherwise, return 0
template <class Etype>
int List<Etype>::Find(Etype const& queryElem)
{
   typename List<Etype>::ListNode* searchPtr = head;
   int result;

   while ((searchPtr !=NULL) && (searchPtr->element != queryElem))
      searchPtr = searchPtr->next; 
   if (searchPtr == NULL)
      result = 0;
   else
   {
      current = searchPtr; 
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



// ListNode
//    - constructor
//    - initializes element to default Etype, and next to NULL
template <class Etype>
List<Etype>::ListNode::ListNode() : element(), next(NULL)
{
   // no code needed here due to initializer list above
}



// ListNode
//    - constructor
//    - parameters : value - the value to store in the element field
//    - initializes node to hold value and NULL
template <class Etype>
List<Etype>::ListNode::ListNode(Etype const& value) : 
                                          element(value), next(NULL)
{
   // no code needed here due to initializer list above
}



