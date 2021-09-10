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

#ifndef SKIPLIST_225_H
#define SKIPLIST_225_H

#include "array.h"

template <typename Etype>
class Skiplist
{
public:

   // *** Creation/Destruction/Mass Update

   // Skiplist 
   //    - default constructor
   //    - initializes skiplist to be empty
   Skiplist();


   // Skiplist
   //    - constructor
   //    - parameters : userMaxLevel - the max level of the skiplist
   //    - initializes skiplist to be empty
   Skiplist(int userMaxLevel);
 
 
   // Skiplist 
   //    - copy constructor
   //    - parameters : origVal - a previously allocated Skiplist object 
   //    - initializes the skiplist to be a copy of origVal 
   Skiplist(Skiplist<Etype> const & origVal);


   // ~Skiplist
   //    - destructor 
   //    - deallocates all dynamically allocated memory associated 
   //        with the skiplist  
   ~Skiplist();


   // operator=
   //    - parameters: origVal - a previously allocated Skiplist object
   //    - return value: reference to this Skiplist object, after it's 
   //         been assigned to be a copy of the parameter
   //    - sets this Skiplist to be a copy of origVal
   Skiplist<Etype> const & operator=(Skiplist<Etype> const & origVal);


   // clear
   //    - deletes all values from list, resulting in an empty list 
   void clear(); 



   // *** Singular Update

   // Note : unlike the original list classes, this skiplist class is
   //   *sorted*. Thus, as with any sorted list class, this class cannot
   //   have InsertBefore and InsertAfter, but must instead have just one
   //   Insert function, because the element's insertion location is
   //   pre-determined by the sort order, rather than being a location
   //   the user can choose. Likewise, there is no Update function because
   //   such an update could conceivably create a list that was not in sorted
   //   order.


   // insert
   //    - parameters : newElem - an element of the list's type, to be
   //                       inserted into the skiplist in sorted order
   //    - inserts newElem into skiplist in sorted order, and sets
   //        the current position to be that newly-inserted value.
   //        Code does not check to prevent duplicates. 
   void insert(Etype const & newElem); 



   // remove
   //    - removes the element at the current position of the list.
   //       Upon completion of the removal, the current position
   //       will be the next element in the list, or if there is no
   //       next element, then the first position (or no position at
   //       all, if the list is empty). Attempting to remove using a
   //       meaningless current position (which for this class can
   //       only happen when the list is empty) will result in a warning.
   void remove();



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
   //    - parameters : queryElem - an element of the skiplist's type, 
   //                       to be searched for
   //    - return value : boolean with true indicating value was found
   //    - searches skiplist for queryElem...if found, make that position 
   //         the current position and return true; otherwise, return false 
   //         Assumes existence of operator== for generic type.
   bool find(Etype const & queryElem);


   // length
   //    - return value : an integer representing the skiplist's length 
   //    - returns the length of the skiplist 
   int length() const; 


   // print
   //    - prints out the skiplist values, in sorted order
   void print() const;
       

private:

   class SkipNode
   {
   public:

      // *** These constructors need a bit of redesign

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
         ptrArray.setBounds(0, nodeTopLevel);
         ptrArray.initialize(NULL);
      }

 
      // SkipNode
      //    - constructor
      //    - parameters : level - the specific desired level for this node.
      //                     This value should be non-negative and should not 
      //                     exceed the  skiplist's "maxLevel" value, though 
      //                     that latter condition is something the client of 
      //                     this function must confirm themselves. 
      //                  : nodeMaxLevel - the maximum level allowed for this
      //                     node. Aside from an Assert check, this value
      //                     is never actually used, but leaving it out
      //                     makes the two constructors have identical 
      //                     parameter lists, so since *something* had to
      //                     be thrown in as a second parameter, why not
      //                     something meaningful? 
      //    - creates a new node whose level will be equal to the parameter
      //        value. In addition, all node pointers stored by this node
      //        will be set to NULL. 
      SkipNode(int level, int nodeMaxLevel)
      {
         Assert(level <= nodeMaxLevel, "Node level cannot be that large!");
         Assert(level >= 0, "Cannot create a node with negative level!");
         nodeTopLevel = level;
         ptrArray.setBounds(0, nodeTopLevel);
         ptrArray.initialize(NULL);
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


