// ***************************************************
// *                                                 *
// *  skiplist.cpp                                   *
// *                                                 *
// *  Implementation for a skip list class           *
// *                                                 *
// *  Written July 1997 by Jason Zych                *
// *    - slight edits done July 2001 by Jason Zych  *
// *                                                 *
// ***************************************************

#include <cstddef>      // for definition of NULL
#include <cmath>        // for definition of pow()
#include <cstdlib>      // for definition of rand() and srand()
#include <iostream>
using namespace std;

#include "asserts.h"
#include "skiplist.h"


// *** Creation/Destruction/Mass Update

// Skiplist 
//    - default constructor
//    - initializes skiplist to be empty
template <typename Etype>
Skiplist<Etype>::Skiplist() : headArray(0, 0), current(NULL),  
                                            size(0), maxLevel(0)
{
   headArray.initialize(NULL);
   // srand(time(NULL));
}
 
 
// Skiplist 
//    - copy constructor
//    - parameters : origVal - a previously allocated Skiplist object 
//    - initializes the skiplist to be a copy of origVal 
template <typename Etype>
Skiplist<Etype>::Skiplist(Skiplist<Etype> const & origVal)
{
   copy(origVal);
}


// ~Skiplist
//    - destructor 
//    - deallocates all dynamically allocated memory associated 
//        with the skiplist  
template <typename Etype>
Skiplist<Etype>::~Skiplist()
{
   clear();
}


// operator=
//    - parameters: origVal - a previously allocated Skiplist object
//    - return value: reference to this Skiplist object, after it's 
//         been assigned to be a copy of the parameter
//    - sets this Skiplist to be a copy of origVal
template <typename Etype>
Skiplist<Etype> const & Skiplist<Etype>::operator=(
                       Skiplist<Etype> const & origVal)
{
   if (this != &origVal)
   {
      clear();
      copy(origVal);
   }
   return *this;
}


// clear
//    - deletes all values from list, resulting in an empty list 
template <typename Etype>
void Skiplist<Etype>::clear()
{
   // set current to point to first node
   current = headArray[0];             
   typename Skiplist<Etype>::SkipNode* deletionPtr = current;

   // traverse down the list, deleting each node
   while (deletionPtr != NULL)
   {
      // move current to next level-0 node
      current = (current->nextArray)[0]; 
      delete deletionPtr;
      deletionPtr = current;
   }

   // set all pointers to NULL
   headArray.setBounds(0, 0);
   headArray.initialize(NULL);

   current = NULL;
   size = 0;
   maxLevel = 0;
} 




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
//    - parameters : insElem - an element of the list's type, to be
//                       inserted into the skiplist in sorted order
//    - inserts insElem into skiplist in sorted order, and sets
//        the current position to be that newly-inserted value.
//        Code does not check to prevent duplicates. 
template <typename Etype>
void Skiplist<Etype>::insert(Etype const & insElem)
{
   Array<Skiplist<Etype>::SkipNode*> stateArray;
   stateArray = internalPrevSearch(insElem);

/*
   for (int i = stateArray.lower(); i <= stateArray.upper(); i++)
      cout << stateArray[i] << endl;
*/


   // stateArray points to the node "previous to the insElem value"
   // on every level

   // create new node, with node's top level chosen via skiplist
   // randomized algorithm
   typename Skiplist<Etype>::SkipNode* insNodePtr;
   insNodePtr = new Skiplist<Etype>::SkipNode(insElem, maxLevel);
   int currentNodeLevel = insNodePtr->nodeTopLevel;

   while (currentNodeLevel >= 0)
   {
      typename Skiplist<Etype>::SkipNode* prevAtThisLevel;
      prevAtThisLevel = stateArray[currentNodeLevel];
   
      // prevAtThisLevel points to the node prior to 
      // our new node, on this level

      if (prevAtThisLevel == NULL)  // new node is first on this level
      {
         (insNodePtr->nextArray)[currentNodeLevel] = 
                                   headArray[currentNodeLevel];
         headArray[currentNodeLevel] = insNodePtr;
      }
      else  // we are inserting after node that prevAtThisLevel points to
      {
         (insNodePtr->nextArray)[currentNodeLevel] = 
                  (prevAtThisLevel->nextArray)[currentNodeLevel];

         (prevAtThisLevel->nextArray)[currentNodeLevel] = insNodePtr;
      }

      currentNodeLevel--;
   }

   // now the new node has been attached to the list on all relevant levels

   current = insNodePtr;
   size++;


   // insertion is done! However, we might need to add a new level
   //  on top of the existing levels
   if (size >= pow(2, maxLevel + 1))
   {
      headArray.setBounds(0, maxLevel + 1);
      headArray[maxLevel + 1] = NULL;




      typename Skiplist<Etype>::SkipNode* travPtr;
      typename Skiplist<Etype>::SkipNode* prevPtr;

      travPtr = headArray[maxLevel];
      prevPtr = NULL;

      while (travPtr != NULL)
      {
         // if there's another node after this one, move to that
         // and increase it
         if ((travPtr->nextArray)[maxLevel] != NULL)
         {
            travPtr = (travPtr->nextArray)[maxLevel];
            (travPtr->nextArray).setBounds(0, maxLevel + 1);
            (travPtr->nodeTopLevel)++;
            (travPtr->nextArray)[maxLevel + 1] = NULL;

            if (prevPtr == NULL)
               headArray[maxLevel + 1] = travPtr;
            else
               (prevPtr->nextArray)[maxLevel + 1] = travPtr;
            prevPtr = travPtr;
         }
         travPtr = (travPtr->nextArray)[maxLevel];
      }
      maxLevel++;
   }
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
void Skiplist<Etype>::remove()
{
   Array<Skiplist<Etype>::SkipNode*> stateArray;
   stateArray = internalPrevSearch(current->element);



   // set nexts
   // delete node
}




// *** Control of Current Position

// front
//    - makes the first position in the list the current position 
//      Attempting to do this when there is no first position in the 
//      list (which for this class can only happen when the list is 
//      empty) will result in a warning.
template <typename Etype>
void Skiplist<Etype>::front()
{
   if (size > 0)
      current = headArray[0];
   else
      Warn("Cannot move current to head of an empty list.");
}



// back
//    - makes the last position in the list the current position
//      Attempting to do this when there is no last position in the 
//      list (which for this class can only happen when the list is
//      empty) will result in a warning.
template <typename Etype>
void Skiplist<Etype>::back()
{
   if (size > 0)
   {
      // we want to go as far as we can along the top level, then 
      // as far as we can along 2nd from top, and so on. This gets 
      // us to the end in the fewest increments possible. 

      int currentNodeLevel = maxLevel; 
      Skiplist<Etype>::SkipNode* travPtr; 

      // It is possible that we had a string of remove operations that
      // removed out all the level-n nodes, where n is the maxLevel.
      // Therefore, we cannot safely assume every level's list is 
      // non-empty. So, we need to find the first list (counting from
      // the top) that is non-empty.  
      // 
      // At least *some* list is non-empty, or else size would be 0.
      // While the current level is empty, move down a level.
      while (headArray[currentNodeLevel] == NULL)
         currentNodeLevel--; 

      // we assume travPtr does not point to NULL after this assignment 
      travPtr = headArray[currentNodeLevel]; 
      
      // Go until the next ptr on this level is NULL, then drop down
      while (currentNodeLevel >= 0)
      {
         while ((travPtr->nextArray)[currentNodeLevel] != NULL)
            travPtr = (travPtr->nextArray)[currentNodeLevel]; 
         currentNodeLevel--; 
      }
      current = travPtr; 
   }
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
void Skiplist<Etype>::forwardOne()
{
   if (size > 0)   // if there are nodes in the list
   {
      if ((current->nextArray)[0] != NULL)  // and we are not at the last one
         current = (current->nextArray)[0];   // increment the current pointer 
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
void Skiplist<Etype>::backwardOne()
{
   if (size > 0)   // if there are nodes in the list
   {
      if (current != headArray[0])  // and we are not at the first one
      {
         Array<Skiplist<Etype>::SkipNode*> stateArray;
         stateArray = internalPrevSearch(current->element);

         Skiplist<Etype>::SkipNode* prevPtr = stateArray[0];
         if ((prevPtr != NULL) && ((prevPtr->nextArray)[0] != NULL) &&
                       ((prevPtr->nextArray)[0]->element == current->element))
            current = prevPtr;
         else
            Assert("BACK ONE SUCKS!!");
      } 
      else
         Warn("Cannot decrement current position when at first element.");
   }
   else
      Warn("Cannot move to previous position of an empty list.");
}



// *** Information Access 

// retrieve
//    - returns the element at the current list position
//      Attempting to retrieve from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in an error message and termination of program.
template <typename Etype>
Etype const & Skiplist<Etype>::retrieve() const
{
   Assert(size > 0, "Cannot retrieve an element from an empty skiplist."); 
   return current->element; 
}


// find 
//    - parameters : queryElem - an element of the skiplist's type, 
//                       to be searched for
//    - return value : boolean with true indicating value was found
//    - searches skiplist for queryElem...if found, make that position 
//         the current position and return true; otherwise, return false 
//         Assumes existence of operator== for generic type.
template <typename Etype>
bool Skiplist<Etype>::find(Etype const & queryElem)
{
   Array<Skiplist<Etype>::SkipNode*> stateArray;
   stateArray = internalPrevSearch(queryElem);

   Skiplist<Etype>::SkipNode* prevPtr = stateArray[0];
   if ((prevPtr != NULL) && ((prevPtr->nextArray)[0] != NULL) &&
                   ((prevPtr->nextArray)[0]->element == queryElem))
   {
      current = (prevPtr->nextArray)[0];
      return true;
   }
   else
      return false;
}

   



// length
//    - return value : an integer representing the skiplist's length 
//    - returns the length of the skiplist 
template <typename Etype>
int Skiplist<Etype>::length() const
{
   return size;
}


// print
//    - prints out the skiplist values, in sorted order
template <typename Etype>
void Skiplist<Etype>::print() const
{
   typename Skiplist<Etype>::SkipNode* outPtr = headArray[0];

   if (size == 0)
      cout << "< empty list >";  
   else
   { 
      while (outPtr != NULL)  
      {
         cout << "(" << outPtr->element << ", ";
         cout << outPtr->nodeTopLevel << ")" << endl;
         outPtr = (outPtr->nextArray)[0];
      } 
   } 
}


// copy
//    - parameters : origVal - a previously allocated Skiplist object
//    - sets the skiplist to be a copy of origVal; assumes there is no
//         dynamic memory that needs to be cleaned out of the skiplist
template <typename Etype>
void Skiplist<Etype>::copy(Skiplist<Etype> const & origVal)
{
   headArray.setBounds(origVal.headArray.lower(), 
                          origVal.headArray.upper());
   headArray.initialize(NULL);

   size = origVal.size;
   maxLevel = origVal.maxLevel;

   if (size == 0)
      current = NULL;
   else 
   {
      // update is an array that, for each level in the new list, will
      //   point to the rightmost node in that level that we've created
      //   so far.
      Array<Skiplist<Etype>::SkipNode*> update(0, maxLevel);
      update.initialize(NULL);

      // origTravPtr starts pointing to first node
      typename Skiplist<Etype>::SkipNode* origTravPtr;
      typename Skiplist<Etype>::SkipNode* copyTravPtr;

      origTravPtr = (origVal.headArray)[0];
      
      while (origTravPtr != NULL)
      {
         copyTravPtr = new SkipNode(*origTravPtr);
         
         // for all the levels that this node has...
         for (int level = 0; level <= copyTravPtr->nodeTopLevel; level++)
         {
            // if this is the first node on this level, then head should
            //  point to it; otherwise, the most recent prior node on this
            //  level should point to it
            if (update[level] == NULL)
               headArray[level] = copyTravPtr; 
            else
               (update[level]->nextArray)[level] = copyTravPtr; 
 
            // and now this is the "most recent node" for this level
            update[level] = copyTravPtr; 
         }
    
         if (origVal.current == origTravPtr)
            current = copyTravPtr;

         // move origTravPtr to the next node in the parameter skiplist
         origTravPtr = (origTravPtr->nextArray)[0]; 
      }
   }
}



// internalPrevSearch
template <typename Etype>
Array<typename Skiplist<Etype>::SkipNode*> 
            Skiplist<Etype>::internalPrevSearch(Etype const & searchVal)
{
   Array<Skiplist<Etype>::SkipNode*> stateArray(0, maxLevel);
   stateArray.initialize(NULL);

   if (size > 0)
   {
      int currentNodeLevel = maxLevel;
  
      Skiplist<Etype>::SkipNode* trav = headArray[currentNodeLevel];

      while ((currentNodeLevel >= 0) && (headArray[currentNodeLevel] == NULL))
      {
         stateArray[currentNodeLevel] = NULL;
         currentNodeLevel--;
      }

      if (currentNodeLevel > -1)
      {
         Skiplist<Etype>::SkipNode* trav = headArray[currentNodeLevel];
 
         while (currentNodeLevel >= 0)
         {
            while (((trav->nextArray)[currentNodeLevel] != NULL) &&
                   ((trav->nextArray)[currentNodeLevel]->element < searchVal))
                trav = (trav->nextArray)[currentNodeLevel]; 
            stateArray[currentNodeLevel] = trav;
            currentNodeLevel--;  
         }
      }
   }
   
   return stateArray;
}

    


// SkipNode
//    - constructor
//    - parameters : theValue - value to store in node
//                 : nodeMaxLevel - the maximum level that can
//                     be chosen for this node. This value should
//                     be non-negative and should not exceed the
//                     current value of the enclosing skiplist's
//                     "maxLevel" member variable, though that
//                     latter condition is something the client of
//                     this function must confirm themselves.
//    - initializes the node to have parameter value and a 
//        pre-set level chosen according to the skiplist randomized 
//        level-selection algorithm. This level will be at least zero 
//        and will not exceed the given nodeMaxLevel value. In
//        addition, all node pointers stored by this node will be 
//        set to NULL.
template <typename Etype>
Skiplist<Etype>::SkipNode::SkipNode(Etype theValue, int nodeMaxLevel)
{
   Assert(nodeMaxLevel >= 0,
                       "Cannot create a node with negative level!");
   element = theValue;
   nodeTopLevel = 0;
   while ((rand() % 2 == 0) && (nodeTopLevel < nodeMaxLevel))
      nodeTopLevel++;
   nextArray.setBounds(0, nodeTopLevel);
   nextArray.initialize(NULL);
}






