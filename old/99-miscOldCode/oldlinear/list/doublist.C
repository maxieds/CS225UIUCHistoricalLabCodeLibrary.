// ***********************************************************
// *                                                         *
// *  doublist.C                                             * 
// *                                                         *
// *  Implementation for a list class, implemented via       *
// *        doubly-linked memory                             * 
// *                                                         *
// *  Written 5/97 by Jason Zych                             *
// *                                                         *
// *********************************************************** 

#include "doublist.h"


// List
//    - default constructor
template <class Etype>
List<Etype>::List()
{
   head = current = tail = NULL; 
   size=0; 
}


// List
//    - copy constructor
//    - parameters : origList - a previously allocated List object
//    - initializes the list to be a copy of origList
template <class Etype>
List<Etype>::List(const List<Etype>& origList)
{
   ListNode<Etype> *origListPtr = origList.head,
        *newListPtr; 

   if (origListPtr == NULL)  // then origList is empty
   {
      current = head = tail = NULL; 
      size=0; 
   }
   else   // origList is not empty; copy it node for node
   {
      // at least one node in origList; create that node
      newListPtr = new ListNode<Etype>; 
      newListPtr->element = origListPtr->element; 
      if (origListPtr == origList.current)  // place current pointer at 
         current = newListPtr;            // same spot in new list
      head = newListPtr; 
      head->prev = NULL; 
      origListPtr = origListPtr->next; 

      while (origListPtr !=NULL) // keep creating nodes as long as there
      {                         //  are nodes in origList
         newListPtr->next = new ListNode<Etype>; 
         newListPtr->next->prev = newListPtr; 
         newListPtr = newListPtr->next; 
         if (origListPtr == origList.current)
            current = newListPtr; 
         newListPtr->element = origListPtr->element; 
         origListPtr = origListPtr->next; 
      }
      newListPtr->next = NULL;   // last node points to NULL 
      tail = newListPtr; 
      size = origList.size;       
   }
}




// ~List
//    - destructor
//    - deallocates all dynamically allocated memory inside the list
template <class Etype>
List<Etype>::~List()
{
   Clear(); 
}



// Clear
//    - deletes all values from list, resulting in an empty list
template <class Etype>
void List<Etype>::Clear()
{

   ListNode<Etype> *deletionPtr = head; 
   current = head; 
   
   while (current != NULL)
   {
      current = current->next; 
      delete deletionPtr; 
      deletionPtr = current; 
   }

   head = current = tail = NULL; 
   size=0; 
}




// operator=
//    - parameters: origList - a previously allocated List object
//    - sets the the list to be a copy of origList
template <class Etype>
List<Etype>& List<Etype>::operator=(const List<Etype>& origList)
{

   if (this!=&origList)
   {
      Clear(); 
     
      ListNode<Etype> *origListPtr = origList.head,
           *newListPtr;
 
      if (origListPtr == NULL)  // then origList is empty
      {
         current = head = tail = NULL;
         size=0;
      }
      else
      {
         newListPtr = new ListNode<Etype>;
         newListPtr->element = origListPtr->element;
         if (origListPtr == origList.current)
            current = newListPtr;
         head = newListPtr;
         head->prev = NULL; 
         origListPtr = origListPtr->next;
 
         while (origListPtr !=NULL)
         {
            newListPtr->next = new ListNode<Etype>; 
            newListPtr->next->prev = newListPtr; 
            newListPtr = newListPtr->next; 
            if (origListPtr == origList.current)
               current = newListPtr; 
            newListPtr->element = origListPtr->element; 
            origListPtr = origListPtr->next; 
         }
         newListPtr->next = NULL; 
         tail = newListPtr; 
         size = origList.size; 
      }
   }  // end if

   return *this;

} 




// InsertAfter
//    - parameters : newElem - an element of the list's type, to be inserted
//    - inserts newElem after current position in list
template <class Etype>
void List<Etype>::InsertAfter(Etype newElem)
{
   ListNode<Etype> *tempPtr = new ListNode<Etype>; 
   tempPtr->element = newElem; 
    
   if (size==0)
   {
      tempPtr->next=NULL; 
      current = head = tail = tempPtr;  
   }
   else
   {
      tempPtr->next = current->next;
      tempPtr->prev = current;  
      if (current->next != NULL)
         current->next->prev = tempPtr; 
      current->next = tempPtr; 
      if (current == tail)
         tail = tempPtr; 
      current = tempPtr;
   }
   size++; 
}



// InsertBefore
//    - parameters : newElem - an element of the list's type, to be inserted
//    - inserts newElem before current position in list
template <class Etype>
void List<Etype>::InsertBefore(Etype newElem)
{
   ListNode<Etype> *tempPtr = new ListNode<Etype>;

   if (size==0)
   {
      tempPtr->element = newElem;
      tempPtr->next = NULL;
      current = head = tail = tempPtr;
   }
   else
   {
      tempPtr->element = current->element;
      tempPtr->next = current->next;
      tempPtr->prev = current; 
      current->element = newElem;
      if (current->next != NULL)
         current->next->prev = tempPtr; 
      if (current == tail)
         tail = tempPtr; 
      current->next = tempPtr;
   }
   size++;
}



// Remove
//    - removes the element at the current postition of the list
template <class Etype> 
void List<Etype>::Remove()
{
   ListNode<Etype> *removePtr; 
   
   if (size==0)
   {
      Warn(size > 0, "Attempt to remove an element from an empty list."); 
      return; 
   }   
   else if (size==1)
   {
      delete current; 
      head = current = tail = NULL;
   }
   else if (current->next == NULL)   // deleting last element
   {
      tail = tail->prev; 
      current = tail; 
      delete current->next; 
      current->next = NULL; 
   }
   else   // this is the case you would expect to reach most often
   {
      removePtr = current->next; 
      current->element = removePtr->element; 
      current->next = removePtr->next; 
      if (removePtr->next != NULL)
         removePtr->next->prev = current;  
      if (removePtr == tail)
         tail = current; 
      delete removePtr; 
   }
   size--; 
}




// Update
//    - parameters : updateElem - an element of the list's type
//    - replaces the value at the current position with updateElem
template <class Etype>
void List<Etype>::Update(Etype updateElem)
{  
   Warn(size > 0, "Cannot update an element in an empty list."); 
   if (size > 0)
      current->element = updateElem; 
}





// Head
//    - makes the first position in the list the current position
template <class Etype>
void List<Etype>::Head()
{
   current = head; 
}




// Tail
//    - makes the last position in the list the current position
template <class Etype>
void List<Etype>::Tail()
{
   current = tail; 
}





// operator++
//    - moves the current position one forward in the list
template <class Etype>
List<Etype>& List<Etype>::operator++(int)
{
   if (size > 0)   // if there are nodes in the list
      if (current->next != NULL)  // and we are not on the last one
         current =  current->next;   // increment the current pointer 
   return *this; 
}





// operator--
//    - moves the current position one backward in the list
template <class Etype>
List<Etype>& List<Etype>::operator--(int)
{
   if (size > 0)   // if there are nodes in the list
      if (current->prev != NULL)  // and we are not on the first one
         current = current->prev;  // decrement the current pointer
   return *this; 
}




// Retrieve
//    - returns the element at the current list position
template <class Etype>
Etype List<Etype>::Retrieve() const
{
   Assert(size > 0, "Cannot Retrieve an element from an empty list."); 
   return current->element;    
}




// Find 
//    - parameters : queryElem - an element of the list's type, to be searched for
//    - return value : a boolean yes or no
//    - searches list for queryElem...if found, make that position the current
//         position and return 1; otherwise, return 0
template <class Etype>
int List<Etype>::Find(Etype queryElem)
{
   ListNode<Etype> *searchPtr = head;
   while ((searchPtr !=NULL) && (searchPtr->element != queryElem))
      searchPtr = searchPtr->next; 
   if (searchPtr == NULL)
      return 0; 
   else
   {
      current = searchPtr; 
      return 1; 
   }
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
//    - writes the individual elements of the list to the output
//         stream object, and then returns that output stream object
template <class Etype>
void List<Etype>::Print() const
{
   ListNode<Etype>* outPtr = head; 

   if (size==0)
      cout << "< empty list >";  
   else
   { 
      cout << "< "; 
      while (outPtr!=NULL)  
      {
         cout << outPtr->element << " ";
         outPtr = outPtr->next; 
      } 
      cout << ">";
   } 
}

