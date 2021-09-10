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

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H


template <typename Etype>
class List
{
public:

   // *** Creation/Destruction/Mass Update

   // List 
   //    - default constructor
   //    - initializes list to be empty
   List();
 
 
   // List 
   //    - copy constructor
   //    - parameters : origVal - a previously allocated List object 
   //    - initializes the list to be a copy of origVal 
   List(List<Etype> const & origVal);


   // ~List
   //    - destructor 
   //    - deallocates all dynamically allocated memory associated 
   //        with the list  
   ~List();


   // operator=
   //    - parameters: origVal - a previously allocated List object
   //    - return value: reference to this List object, after it's 
   //         been assigned to be a copy of the parameter
   //    - sets this list to be a copy of origVal
   List<Etype> const & operator=(List<Etype> const & origVal);


   // clear
   //    - deletes all values from list, resulting in an empty list 
   void clear(); 



   // *** Singular Update

   // insertAfter
   //    - parameters : newElem - an element of the list's type, 
   //                       to be inserted
   //    - inserts newElem after current position in list (or as
   //        the only element in the list, if the list is currently
   //        empty), and sets that new element as the current 
   //        position. Code does not check to prevent duplicates. 
   void insertAfter(Etype const & newElem); 



   // insertBefore
   //    - parameters : newElem - an element of the list's type, 
   //                       to be inserted
   //    - inserts newElem before current position in list (or as
   //        the only element in the list, if the list is currently
   //        empty), and sets that new element as the current 
   //        position. Code does not check to prevent duplicates. 
   void insertBefore(Etype const & newElem); 


   // remove
   //    - removes the element at the current position of the list.
   //       Upon completion of the removal, the current position
   //       will be the next element in the list, or if there is no
   //       next element, then the first position (or no position at
   //       all, if the list is empty). Attempting to remove using a
   //       meaningless current position (which for this class can
   //       only happen when the list is empty) will result in a warning.
   void remove();


   // update
   //    - parameters : updateElem - an element of the list's type
   //    - replaces the value at the current position with updateElem 
   //      Attempting to update using a meaningless current position
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning.
   void update(Etype const & updateElem); 



   // *** Control of Current Position

   // front
   //    - makes the first position in the list the current position 
   //      Attempting to do this when there is no first position in the 
   //      list (which for this class can only happen when the list is 
   //      empty) will result in a warning.
   void front();



   // back
   //    - makes the last position in the list the current position
   //      Attempting to do this when there is no last position in the 
   //      list (which for this class can only happen when the list is
   //      empty) will result in a warning.
   void back();


   // forwardOne
   //    - moves the current position one position forward in the list.
   //      Attempting to move forward from a meaningless current position 
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning. Attempting to move forward from the 
   //      last position in the list will result in a warning and the
   //      current position remaining unchanged. 
   void forwardOne();


   // backwardOne
   //    - moves the current position one position backward in the list.
   //      Attempting to move backward from a meaningless current position 
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning. Attempting to move backward from the 
   //      first position in the list will result in a warning and the
   //      current position remaining unchanged. 
   void backwardOne();


   // *** Information Access 

   // retrieve
   //    - returns the element at the current list position
   //      Attempting to retrieve from a meaningless current position
   //      (which for this class can only happen when the list is empty)
   //      will result in an error message and termination of program.
   Etype const & retrieve() const; 

   
   // find 
   //    - parameters : queryElem - an element of the list's type, 
   //                       to be searched for
   //    - return value : boolean with true indicating value was found
   //    - searches list for queryElem...if found, make that position 
   //         the current position and return true; otherwise, return false 
   //         Assumes existence of operator!= for generic type.
   bool find(Etype const & queryElem);


   // length
   //    - return value : an integer representing the list's length 
   //    - returns the length of the list 
   int length() const; 


   // print
   //    - prints out the list values
   void print() const;
       
private:

   // copy
   //    - parameters : origVal - a previously allocated List object
   //    - sets the list to be a copy of origVal; assumes there is no
   //         dynamic memory that needs to be cleaned out of the list
   void copy(List<Etype> const & origVal);  


   class ListNode
   {
   public:

      // ListNode
      //    - constructor
      //    - initializes element to default Etype, and next to NULL
      ListNode();


      // ListNode
      //    - constructor
      //    - parameters : value - the value to store in the element field
      //    - initializes node to hold value and NULL
      ListNode(Etype const & value);


      Etype element;   // holds element of node
      ListNode* next; // pointer to next node in list
   };


   // you actually could just use ListNode* here; you don't need to
   // fully scope the type since you are in the List class declaration

   typename List<Etype>::ListNode* head; // points to first node of list

   typename List<Etype>::ListNode* current; // points to node at
                                            //   current position

   typename List<Etype>::ListNode* tail;   // points to last node of list

   int size;                                // number of nodes in list
};


#endif



