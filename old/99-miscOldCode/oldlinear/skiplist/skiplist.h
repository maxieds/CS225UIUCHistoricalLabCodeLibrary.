// ************************
// *
// *  skiplist.h
// *
// *  Interface for a skip list class
// *
// *  Written 7/97 by Jason Zych
// *
// ****************

#ifndef _SKIPLIST_H
#define _SKIPLIST_H

#include <stdlib.h>
#include "array.h"
#include "asserts.h"

template <class Etype>
class SkipList
{
public:

 // *** Allocation/Deallocation
 
   // SkipList - Default Constructor 
   //    - operation : creates an empty list;
   SkipList(int userMaxLevel=5);
 
 
   // SkipList - Copy Constructor 
   //    - parameters : origList - a SkipList object 
   //    - operation : creates a new skiplist that is a copy of origList
   SkipList(const SkipList<Etype>& origList);
 
 
   // ~SKipList - Destructor 
   //    - operation : deallocates all dynamically allocated memory inside 
   //         the list 
   ~SkipList();
 
 
 // *** Mass Update
 
   // Clear
   //    - operation : Deletes all values from list, resulting in an empty list 
   void Clear(); 
 
   
   // operator=
   //    - parameters: origList - a List object
   //    
   //    - operation : Makes the list a copy of origList 
   SkipList<Etype>& operator= (const SkipList<Etype>& origlist);
 

 
 // *** Singular Update


   // Insert
   //    - parameters : insElem - element of the template type that we 
   //                            want to insert
   //    - inserts the element insElem into the skiplist
   void Insert(Etype elem);

   
   // Remove
   //    - removes the element pointed to by the current pointer 
   void Remove();


 // *** Traversal

   // Head
   //    - moves current pointer to first node in list
   void Head();

  
   // Tail
   //    - moves current pointer to last node in list 
   void Tail();


   // operator++
   //    - moves current pointer one forward in list
   SkipList<Etype>& operator++ (int);


   // operator-- 
   //    - moves current pointer one backward in list
   SkipList<Etype>& operator-- (int); 

   
 
 // *** Information Access 

   // Retrieve
   //    - returns element at current pointer 
   Etype Retrieve() const; 


   // Includes
   //    - parameters : queryElem - an element that we are searching for 
   //    - returns 1 if queryElem is in skiplist, 0 else
   int Includes(Etype queryElem);

  
   // Length
   //    - returns length of skiplist 
   int Length() const;

  
// *** Output

   // operator<<
   //    - parameters: Out - stream operator
   //                : outlist - a list to be printed 
   //    - prints data of list to the screen
   friend ostream& operator<< (ostream& Out, const SkipList& outList); 


private:

   class SNode
   {
   public:
      // SNode
      //    - default constructor
      //    - creates a random-level node
      SNode(int maxLevel)
      {
         int lev = 0; 
         while ((rand()%2==0) && (lev < maxLevel))
            lev++;
         nodeTopLevel = lev;     
         ptrArray = new Array<SNode*>(nodeTopLevel); 
      }

 
      // SNode
      //    - constructor
      //    - parameters : levelBound - the level for this node
      //    - creates a new node with this specific level 
      SNode(int maxLevel, int levelBound)
      {
         Assert(levelBound<=maxLevel, "Error in set bound constructor!"); 
         nodeTopLevel = levelBound; 
         ptrArray = new Array<SNode*>(nodeTopLevel); 
      }    
      
       // ~SNode
       //    - destructor 
      ~SNode()
      {
         delete ptrArray; 
      }     

      int nodeTopLevel; 
      Array<SNode*>* ptrArray; 
      Etype element; 
   }; 

   Array<SNode*>* head;    // array of pointers to first element in each
			   //     level of skiplist
   SNode* currentPtr;      // pointer to current element of skiplist 
   int maxLevel;           // the maximum allowable level of a skiplist node 
   int size;               // the number of nodes in the skiplist
 
   ostream& PrintList(ostream& Out) const; // printing helper function 
}; 

#endif


