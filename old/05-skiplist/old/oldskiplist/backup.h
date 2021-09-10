// ****************************************************
// *                                                  *
// *  skiplist.h                                      *
// *                                                  *
// *  Interface for a skip list class. Written to be  *
// *   as similar as possible to the interface for    *
// *   the simple List class studied earlier in the   *
// *   semester.                                      *
// *                                                  *
// *  Written July 1997 by Jason Zych                 *
// *    - slight edits done July 2001 by Jason Zych   *
// *                                                  *
// **************************************************** 

#ifndef _SKIPLIST_H
#define _SKIPLIST_H

#include <stdlib.h>
#include "asserts.h"
#include "array.h"


template <class Etype>
class SkipList
{
public:


 // *** Creation/Destruction/Mass Update

   // SkipList 
   //    - default constructor
   //    - parameters : userMaxLevel - the maximum allowed level of a
   //                      skiplist node in this skiplist
   //    - creates an empty skiplist
   SkipList(int userMaxLevel = 5);
 
 
   // SkipList 
   //    - copy constructor
   //    - parameters : origVal - a previously allocated SkipList object 
   //    - initializes the list to be a copy of origVal 
   SkipList(const SkipList& origVal);


   // ~SkipList
   //    - destructor 
   //    - deallocates all dynamically allocated memory 
   //          associated with the skiplist  
   virtual ~SkipList();


   // operator=
   //    - parameters: origVal - a previously allocated SkipList object
   //    - return value: reference to this SkipList object, 
   //                       after the object has been assigned
   //    - sets this list to be a copy of origVal
   const SkipList& operator=(const SkipList& origVal);


   // Clear
   //    - deletes all values from list, resulting in an empty list 
   void Clear(); 


 
 // *** Singular Update

 
   // Note : unlike the original list classes, this skiplist class is 
   //   *sorted*. Thus, as with any sorted list class, this class cannot
   //   have InsertBefore and InsertAfter, but must instead have just one
   //   Insert function, because the element's insertion location is 
   //   pre-determined by the sort order, rather than being a location 
   //   the user can choose. Likewise, there is no Update function because 
   //   such an update could conceivably create a list that was not in sorted 
   //   order. 


   // Insert
   //    - parameters : newElem - an element of the list's type, to be inserted
   //    - inserts newElem into the skiplist in sorted order, and sets that
   //        new element as the current position. Code does not check to prevent
   //        duplicates. 
   void Insert(const Etype& newElem); 


   // Remove
   //    - removes the element at the current position of the list. 
   //       Attempting to remove using a meaningless current position 
   //       (which for this class can only happen when the list is empty) 
   //       will result in a warning.
   void Remove();



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
   SkipList& operator++(int);


   // operator-- (postfix version)
   //    - moves the current position one position backward in the list.
   //      Attempting to move backward from a meaningless current position 
   //      (which for this class can only happen when the list is empty)
   //      will result in a warning. Attempting to move backward from the 
   //      first position in the list will result in a warning and the
   //      current position remaining unchanged. 
   SkipList& operator--(int); 




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

   static enum levelType = {MAX_ALLOWED, PRESET};

   class SkipNode
   {
   public:

      // SkipNode
      //    - constructor
      //    - parameters : nodeMaxLevel - the maximum level that can
      //                     be chosen for this node. This value should
      //                     be non-negative and should not exceed the
      //                     skiplist's "maxLevel" value, though that 
      //                     latter condition is something the client of 
      //                     this function must confirm themselves. 
      //    - initializes the node to have a pre-set level chosen 
      //        according to the skiplist randomized level-selection
      //        algorithm. This level will be at least zero and will not
      //        exceed the given nodeMaxLevel value. In addition, all 
      //        node pointers stored by this node will be set to NULL.  
      SkipNode(int nodeMaxLevel)
      {
         Assert(nodeMaxLevel >= 0, "Cannot create a node with negative level!");
         nodeTopLevel = 0;
         while ((rand() % 2 == 0) && (nodeTopLevel < nodeMaxLevel))
            nodeTopLevel++;
         ptrArray.SetBounds(0, nodeTopLevel);
         ptrArray.Initialize(NULL);
      }

 
      // SkipNode
      //    - constructor
      //    - parameters : level - the specific desired level for this node.
      //                     This value should be non-negative and should not 
      //                     exceed the  skiplist's "maxLevel" value, though 
      //                     that latter condition is something the client of 
      //                     this function must confirm themselves. 
      //    - creates a new node whose level will be equal to the parameter
      //        value. In addition, all node pointers stored by this node
      //        will be set to NULL. 
      SkipNode(int level)
      {
         Assert(level >= 0, "Cannot create a node with negative level!");
         nodeTopLevel = level;
         ptrArray.SetBounds(0, nodeTopLevel);
         ptrArray.Initialize(NULL);
      }    

  
 
      Etype element;              // value stored in this node
      Array<SkipNode*> ptrArray;  // array of "next pointers" for all
                                  //   levels this node is a part of
      int nodeTopLevel;           // top level of this node
   }; 



   Array<SkipNode*> head;    // array of pointers to first element in each
			   //     level of skiplist
   SkipNode* currentPtr;      // pointer to current element of skiplist 
   int maxLevel;           // the maximum allowable level of a skiplist node 
   int size;               // the number of nodes in the skiplist
}; 

#endif


