// ***********************************************************
// *                                                         *
// *  singly-linked-list.h                                   *
// *                                                         *
// *  Interface for a list class, implemented via            *
// *        singly-linked memory                             * 
// *                                                         *
// *  Written May 1997 by Jason Zych                         *
// *   - slight edits done July 2001 by Jason Zych           *
// *                                                         *
// *********************************************************** 

#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <iostream.h>
#include "asserts.h"

template <class Etype>
class List
{
public:

 // *** Creation/Destruction/Mass Update

   // List 
   //    - default constructor
   //    - creates an empty list
   List();
 
 
   // List 
   //    - copy constructor
   //    - parameters : origVal - a previously allocated List object 
   //    - initializes the list to be a copy of origVal 
   List(const List& origVal);


   // ~List
   //    - destructor 
   //    - deallocates all dynamically allocated memory associated with the list  
   virtual ~List();


   // operator=
   //    - parameters: origVal - a previously allocated List object
   //    - return value: reference to this List object, after it's been assigned
   //    - sets this list to be a copy of origVal
   const List& operator=(const List& origVal);


   // Clear
   //    - deletes all values from list, resulting in an empty list 
   void Clear(); 



 // *** Singular Update

   // InsertAfter
   //    - parameters : newElem - an element of the list's type, to be inserted
   //    - inserts newElem after current position in list, and sets that new
   //        element as the current position. Code does not check to prevent
   //        duplicates. 
   void InsertAfter(const Etype& newElem); 


   // InsertBefore
   //    - parameters : newElem - an element of the list's type, to be inserted
   //    - inserts newElem before current position in list, and sets that new
   //        element as the current position. Code does not check to prevent
   //        duplicates. 
   void InsertBefore(const Etype& newElem); 


   // Remove
   //    - removes the element at the current position of the list. 
   //       Attempting to remove using a meaningless current position 
   //       (which for this class can only happen when the list is empty) 
   //       will result in a warning.
   void Remove();


   // Update
   //    - parameters : updateElem - an element of the list's type
   //    - replaces the value at the current position with updateElem 
   //      Attempting to update using a meaningless current position
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning.
   void Update(const Etype& updateElem); 



 // *** Control of Current Position

   // Head
   //    - makes the first position in the list the current position 
   //      Attempting to do this when there is no first position in the list
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning.
   void Head();

   
   // Tail
   //    - makes the last position in the list the current position 
   //      Attempting to do this when there is no last position in the list
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning.
   void Tail();


   // operator++ (postfix version)
   //    - moves the current position one position forward in the list.
   //      Attempting to move forward from a meaningless current position 
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning. Attempting to move forward from the 
   //      last position in the list will result in a warning and the
   //      current position remaining unchanged. 
   List& operator++(int);


   // operator-- (postfix version)
   //    - moves the current position one position backward in the list.
   //      Attempting to move backward from a meaningless current position 
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning. Attempting to move backward from the 
   //      first position in the list will result in a warning and the
   //      current position remaining unchanged. 
   List& operator--(int); 


 // *** Information Access 

   // Retrieve
   //    - returns the element at the current list position
   //      Attempting to retrieve from a meaningless current position
   //      (which for this class can only happen when the list is empty)
   //      will result in an error message and termination of program.
   const Etype& Retrieve() const; 

   
   // Find 
   //    - parameters : queryElem - an element of the list's type, 
   //                       to be searched for
   //    - return value : a boolean yes or no
   //    - searches list for queryElem...if found, make that position the current
   //         position and return 1; otherwise, return 0 
   int Find(const Etype& queryElem);


   // Length
   //    - return value : an integer representing the list's length 
   //    - returns the length of the list 
   int Length() const; 


   // Print
   //    - prints out the list values
   void Print() const;
       


private:

   class ListNode  
   {
   public:

      // ListNode
      //    - constructor
      //    - initializes element to default Etype, and next to NULL
      ListNode()  { next = NULL; }
  
      
      // ListNode
      //    - constructor
      //    - parameters : value - the value to store in the element field
      //    - initializes node to hold value and NULL
      ListNode(Etype value) { element = value; next = NULL; } 

 
      Etype element;   // holds element of node
      ListNode* next;  // pointer to the next node in the list
   };


   ListNode    *head,        // points to first node of list
               *current,     // points to node at current list position
               *tail;        // points to last node of list

   int size;          // number of nodes in list
};


#endif 

   







