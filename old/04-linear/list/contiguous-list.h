// ***********************************************************
// *                                                         *
// *  contiguous-list.h                                      *
// *                                                         *
// *  Interface for a list class, implemented via            *
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

#ifndef CONTIGUOUS_LIST_H
#define CONTIGUOUS_LIST_H

#include <iostream>
using namespace std;

#include "asserts.h"
#include "array.h"

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
   List(List const& origVal);


   // ~List
   //    - destructor 
   //    - deallocates all dynamically allocated memory associated with the list  
   ~List();


   // operator=
   //    - parameters: origVal - a previously allocated List object
   //    - return value: reference to this List object, after it's been assigned
   //    - sets this list to be a copy of origVal
   List const& operator=(List const& origVal);


   // Clear
   //    - deletes all values from list, resulting in an empty list 
   void Clear(); 



 // *** Singular Update

   // InsertAfter
   //    - parameters : newElem - an element of the list's type, to be inserted
   //    - inserts newElem after current position in list, and sets that new
   //        element as the current position. Code does not check to prevent
   //        duplicates. 
   void InsertAfter(Etype const& newElem); 


   // InsertBefore
   //    - parameters : newElem - an element of the list's type, to be inserted
   //    - inserts newElem before current position in list, and sets that new
   //        element as the current position. Code does not check to prevent
   //        duplicates. 
   void InsertBefore(Etype const& newElem); 


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
   void Update(Etype const& updateElem); 



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


   // ForwardOne
   //    - moves the current position one position forward in the list.
   //      Attempting to move forward from a meaningless current position 
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning. Attempting to move forward from the 
   //      last position in the list will result in a warning and the
   //      current position remaining unchanged. 
   void ForwardOne();


   // BackwardOne
   //    - moves the current position one position backward in the list.
   //      Attempting to move backward from a meaningless current position 
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning. Attempting to move backward from the 
   //      first position in the list will result in a warning and the
   //      current position remaining unchanged. 
   void BackwardOne();


 // *** Information Access 

   // Retrieve
   //    - returns the element at the current list position
   //      Attempting to retrieve from a meaningless current position
   //      (which for this class can only happen when the list is empty)
   //      will result in an error message and termination of program.
   Etype const& Retrieve() const; 

   
   // Find 
   //    - parameters : queryElem - an element of the list's type, 
   //                       to be searched for
   //    - return value : a boolean yes or no
   //    - searches list for queryElem; if found, make that position the current
   //         position and return 1; otherwise, return 0 
   int Find(Etype const& queryElem);


   // Length
   //    - return value : an integer representing the list's length 
   //    - returns the length of the list 
   int Length() const; 


   // Print
   //    - prints out the list values
   void Print() const;


private:

   Array<Etype> listArray;  // array that holds our list
   int current;   // index of current position 
   int size;      // amount of space we are actually using in the array
};


#endif 

   







