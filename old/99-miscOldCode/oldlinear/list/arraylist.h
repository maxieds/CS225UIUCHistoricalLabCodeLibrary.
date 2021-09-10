// ***********************************************************
// *                                                         *
// *  arraylist.h                                            *
// *                                                         *
// *  Interface for a list class, implemented via            *
// *        contiguous memory                                * 
// *                                                         *
// *  Written 5/97 by Jason Zych                             *
// *                                                         *
// *********************************************************** 

#ifndef LIST_H
#define LIST_H

#include <iostream.h>
#include "asserts.h"
#include "array.h"

template <class Etype>
class List
{
public:

 // *** Allocation/Deallocation

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
   //    - deallocates all dynamically allocated memory inside the list 
   virtual ~List();


 // *** Mass Update

   // Clear
   //    - deletes all values from list, resulting in an empty list 
   void Clear(); 

   
   // operator=
   //    - parameters: origVal - a previously allocated List object
   //    - return value: reference to the List object
   //    - sets the the list to be a copy of origVal
   List& operator= (const List& origVal);


 // *** Singular Update

   // InsertAfter
   //    - parameters : newElem - an element of the list's type, to be inserted
   //    - inserts newElem after current position in list
   void InsertAfter(Etype newElem); 


   // InsertBefore
   //    - parameters : newElem - an element of the list's type, to be inserted
   //    - inserts newElem before current position in list
   void InsertBefore(Etype newElem); 


   // Remove
   //    - removes the element at the current postition of the list
   void Remove();


   // Update
   //    - parameters : updateElem - an element of the list's type
   //    - replaces the value at the current position with updateElem 
   void Update(Etype updateElem); 


 // *** Traversal

   // Head
   //    - makes the first position in the list the current position 
   void Head();

   
   // Tail
   //    - makes the last position in the list the current position 
   void Tail();


   // operator++
   //    - moves the current position one forward in the list  
   List& operator++ (int);


   // operator--
   //    - moves the current position one backward in the list
   List& operator-- (int); 

 // *** Information Access 

   // Retrieve
   //    - returns the element at the current list position
   Etype Retrieve() const; 

   
   // Find 
   //    - parameters : queryElem - an element of the list's type, to be 
   //                          searched for
   //    - return value : a boolean yes or no
   //    - searches list for queryElem...if found, make that position the current
   //         position and return 1; otherwise, return 0 
   int Find(Etype queryElem); 


   // Length
   //    - return value : an integer representing the list's length 
   //    - returns the length of the list 
   int Length() const; 

// *** Output

   // Print
   //    - Prints list contents to the screen
   void Print() const;

protected:

   Array<Etype> *listArray; 
   int current; 
   int space; 
   int size; 

};



#endif 

   

