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

#include <iostream.h>
#include "skiplist.h"


 // ************** Creation/Destruction/Mass Update


// SkipList
//    - default constructor
//    - parameters : userMaxLevel - the maximum allowed level of a
//                      skiplist node in this skiplist
//    - creates an empty skiplist
template <class Etype>
SkipList<Etype>::SkipList(int userMaxLevel) : head(0, userMaxLevel),
         currentPtr(NULL), maxLevel(userMaxLevel), size(0)
{
   head.Initialize(NULL);
}





// SkipList
//    - copy constructor
//    - parameters : origVal - a previously allocated SkipList object
//    - initializes the list to be a copy of origVal
template <class Etype>
SkipList<Etype>::SkipList(const SkipList<Etype>& origVal) : 
   head(0, origVal.maxLevel), maxLevel(origVal.maxLevel), size(origVal.size)
{
   head.Initialize(NULL);

   if (size == 0)
      currentPtr = NULL;
   else
   {
      // update is an array that, for each level in the new list, will
      //   point to the rightmost node in that level that we've created
      //   so far.
      Array<SkipNode*> update(0, maxLevel);
      update.Initialize(NULL);

      // origTravPtr starts pointing to first node
      SkipNode* origTravPtr = origVal.head[0];
      SkipNode* copyTravPtr;

      while (origTravPtr != NULL)
      {
         // create a new node that has the same height as the current node
	 //   in the origVal, and copy into it the origVal node's element
         copyTravPtr = new SkipNode(origTravPtr->nodeTopLevel, maxLevel); 
         copyTravPtr->element = origTravPtr->element; 

         // for all the levels that this node has...
         for (int level = 0; level <= copyTravPtr->nodeTopLevel; level++)
         {
            // if this is the first node on this level, then head should
            //  point to it; otherwise, the most recent prior node on this
            //  level should point to it
            if (update[level] == NULL)
               head[level] = copyTravPtr; 
            else
               (update[level]->ptrArray)[level] = copyTravPtr; 
 
            // and now this is the "most recent node" for this level
            update[level] = copyTravPtr; 
         }
    
         if (origVal.currentPtr == origTravPtr)
            currentPtr = copyTravPtr;

         // move origTravPtr to the next node in the parameter skiplist
         origTravPtr = (origTravPtr->ptrArray)[0]; 
      }
   }
}

      


// ~SkipList
//    - destructor
//    - deallocates all dynamically allocated memory 
//          associated with the skiplist
template <class Etype>
SkipList<Etype>::~SkipList()
{
   Clear(); 
}




// operator=
//    - parameters: origVal - a previously allocated SkipList object
//    - return value: reference to this SkipList object,
//                       after the object has been assigned
//    - sets this list to be a copy of origVal
template <class Etype>
const SkipList<Etype>& 
SkipList<Etype>::operator=(const SkipList<Etype>& origVal)
{
   if (this!=&origVal)
   {
      Clear(); 

      head.Initialize(NULL);
      maxLevel = origVal.maxLevel;
      size = origVal.size;

      if (size == 0)
         currentPtr = NULL;
      else
      {
         // update is an array that, for each level in the new list, will
         //   point to the rightmost node in that level that we've created
         //   so far.
         Array<SkipNode*> update(0, maxLevel);
         update.Initialize(NULL);

         // origTravPtr starts pointing to first node
         SkipNode *origTravPtr = origVal.head[0];
         SkipNode    *copyTravPtr;

         while (origTravPtr != NULL)
         {
            // create a new node that has the same height as the current node
            //   in the origVal, and copy into it the origVal node's element
            copyTravPtr = new SkipNode(origTravPtr->nodeTopLevel, maxLevel); 
            copyTravPtr->element = origTravPtr->element; 

            // for all the levels that this node has...
            for (int level = 0; level <= copyTravPtr->nodeTopLevel; level++)
            {
               // if this is the first node on this level, then head should
               //  point to it; otherwise, the most recent prior node on this
               //  level should point to it
               if (update[level] == NULL)
                  head[level] = copyTravPtr; 
               else
                  (update[level]->ptrArray)[level] = copyTravPtr; 
 
               // and now this is the "most recent node" for this level
               update[level] = copyTravPtr; 
            }
    
            if (origVal.currentPtr == origTravPtr)
               currentPtr = copyTravPtr;

            // move origTravPtr to the next node in the parameter skiplist
            origTravPtr = (origTravPtr->ptrArray)[0]; 
         }
      }
   }
   return *this; 
}



// Clear
//    - deletes all values from list, resulting in an empty list
template <class Etype>
void SkipList<Etype>::Clear()
{
   currentPtr = head[0];
   SkipNode* travPtr;

   // traverse down the list, deleting each node
   while (currentPtr != NULL)
   {
      travPtr = currentPtr;
      currentPtr = (currentPtr->ptrArray)[0];
      delete travPtr;
   }

   // set all header pointers to NULL
   head.Initialize(NULL);
   size = 0;
}



 // ******************* Singular Update



// Insert
//    - parameters : newElem - an element of the list's type, to be inserted
//    - inserts newElem into the skiplist in sorted order, and sets that
//        new element as the current position. Code does not check to prevent
//        duplicates.
template <class Etype>
void SkipList<Etype>::Insert(const Etype& insElem)
{
   // Create new node and extract node's top level
   SkipNode* insertNode = new SkipNode(maxLevel); 
   insertNode->element = insElem; 
   int currentNodeLevel = insertNode->nodeTopLevel;  

   // traverse list from the top level of the new node down to level 0
   while (currentNodeLevel>=0)
   {
      // if the header points to null or an element greater than what
      //    we want to insert, have header point to the new node
      if ((head[currentNodeLevel] == NULL) || 
	  (head[currentNodeLevel]->element > insertNode->element))
      {
         (insertNode->ptrArray)[currentNodeLevel] = head[currentNodeLevel]; 
         head[currentNodeLevel] = insertNode; 
         currentNodeLevel--; 
      }
      else // once we reach this point, we will remain in the while 
	   //    loop -- it indicates we begin our search forward
	   //    in the list
      {
         // we know the first node isn't greater (or we'd still be in 
         //  the if-case) so set temp to first node
         SkipNode* tempPtr = head[currentNodeLevel]; 
         while (currentNodeLevel>=0)
         {
            // As long as the node after the one we're pointing to is
	    //  1) not NULL
	    //  2) less than where we should insert
            // move forward along this level
            while (
		  ((tempPtr->ptrArray)[currentNodeLevel] != NULL) && 
                  ((tempPtr->ptrArray)[currentNodeLevel]->element < 
				insertNode->element)
                  )
               tempPtr = (tempPtr->ptrArray)[currentNodeLevel]; 


            // now we point to node before where we want to insert
            (insertNode->ptrArray)[currentNodeLevel] = 
				(tempPtr->ptrArray)[currentNodeLevel]; 
	    (tempPtr->ptrArray)[currentNodeLevel] = insertNode; 
            currentNodeLevel--; 
         }
      }
   }
   size++; 
   currentPtr = insertNode; 
}

          



// Remove
//    - removes the element at the current position of the list.
//       Attempting to remove using a meaningless current position
//       (which for this class can only happen when the list is empty)
//       will result in a warning.
template <class Etype>
void SkipList<Etype>::Remove()
{
   if (size == 0)
   {
      Warn("Attempt to remove an element from an empty list.");
      return;
   }
      
   int currentNodeLevel = currentPtr->nodeTopLevel; 
   SkipNode* deletePtr = currentPtr; 
   
   while (currentNodeLevel >= 0)
   {
      // if the current node is the first node in the list on this
      //    level, then header points to current's next node on this
      //    level 
      if (head[currentNodeLevel] == deletePtr)
      {
         head[currentNodeLevel] = 
		(deletePtr->ptrArray)[currentNodeLevel]; 
         currentNodeLevel--; 
      }
      else // once we reach this point, we will remain in the while 
	   //    loop -- it indicates we begin our search forward
	   //    in the list
      {
         // we know the first node isn't our current pointer (or we'd
	 //    still be in the if-case) so set travPtr to first node
         SkipNode* travPtr = head[currentNodeLevel]; 
         while (currentNodeLevel >= 0)
         { 
            while ((travPtr->ptrArray)[currentNodeLevel] != deletePtr) 
               travPtr = (travPtr->ptrArray)[currentNodeLevel]; 
            // now, on this level, we point to the node before the
	    //    one we want to remove
            (travPtr->ptrArray)[currentNodeLevel] = 
			(deletePtr->ptrArray)[currentNodeLevel]; 
            currentPtr = travPtr; 
            currentNodeLevel--; 
         }
         if ((deletePtr->ptrArray)[0] != NULL)
            currentPtr = (deletePtr->ptrArray)[0]; 
      }
   }
   delete deletePtr; 
   size--; 
}



 // **************** Control of Current Position



// Head
//    - makes the first position in the list the current position
//      Attempting to do this when there is no first position in the list
//      (which for this class can only happen when the list is empty)
//      will result in a warning.
template <class Etype>
void SkipList<Etype>::Head()
{
   if (size > 0)
      currentPtr = head[0];
   else
      Warn("Cannot move current to head of an empty list.");
}



// Tail
//    - makes the last position in the list the current position
//      Attempting to do this when there is no last position in the list
//      (which for this class can only happen when the list is empty)
//      will result in a warning.
template <class Etype>
void SkipList<Etype>::Tail()
{
   if (size == 0)
      Warn("Cannot move current to tail of an empty list.");
   else
   {
      // we want to go as far as we can along the top level, then 
      // as far as we can along 2nd from top, and so on. This gets 
      // us to the end in the fewest increments possible. 

      int currentNodeLevel = maxLevel; 
      SkipNode* travPtr; 

      // while the current node level is an actual node level (i.e. we haven't
      //   sunk below the bottom level of the list) and the header pointer is NULL, 
      //   move down a level. 
      while ((currentNodeLevel>=0) && (head[currentNodeLevel] == NULL))
         currentNodeLevel--; 
 
      // if cNL is -1, then we have an empty list 
      if (currentNodeLevel == -1)
         return;

      // otherwise, travPtr is the first node of the highest level that
      // actually has a node 
      else
      { 
         travPtr = head[currentNodeLevel]; 
      
         // go until the next ptr on this level is NULL, then drop down
         while (currentNodeLevel>=0)
         {
            while ((travPtr->ptrArray)[currentNodeLevel]!=NULL)
               travPtr = (travPtr->ptrArray)[currentNodeLevel]; 
            currentNodeLevel--; 
         }
      }
      currentPtr = travPtr; 
   }
}




// ForwardOne
//    - moves the current position one position forward in the list.
//      Attempting to move forward from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning. Attempting to move forward from the
//      last position in the list will result in a warning and the
//      current position remaining unchanged.
template <class Etype>
SkipList<Etype>& SkipList<Etype>::ForwardOne()
{
   if (size > 0)   // if there are nodes in the list
      if ((currentPtr->ptrArray)[0] != NULL) // and we're not at last one
         currentPtr = (currentPtr->ptrArray)[0]; // move current forward
      else
         Warn("Cannot advance current position past end position.");
   else
      Warn("Cannot move to next position of an empty list.");
   return *this; 
}



// BackwardOne()
//    - moves the current position one position backward in the list.
//      Attempting to move backward from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in a warning. Attempting to move backward from the
//      first position in the list will result in a warning and the
//      current position remaining unchanged.
template <class Etype>
SkipList<Etype>& SkipList<Etype>::BackwardOne()
{
   if (size > 0)
   {
      if (currentPtr != head[0])
      {
         int currentNodeLevel = maxLevel;
         SkipNode* travPtr;

   
         // As long as we have not dropped below the level of the array and
         //   there is no node on the current level, drop a level 
         while ((currentNodeLevel>=0) && (head[currentNodeLevel] == NULL))
            currentNodeLevel--;

         // if currentNodeLevel = -1, list is empty; don't need to do anything  
         if (currentNodeLevel == -1)
            return *this;

         // likewise if our element is first element -- current should still be 
         //   first element 
         else if (head[0]==currentPtr)
            return *this; 

         // otherwise, search across list to find node before current node
         else
         {
            travPtr = head[currentNodeLevel];
            while (currentNodeLevel>=0)
            {
               // while the next element is less than our current element, 
               // advance
               while ((travPtr->ptrArray)[currentNodeLevel]->element < 
					currentPtr->element)
                  travPtr = (travPtr->ptrArray)[currentNodeLevel];

               // if we don't advance, drop a level
               currentNodeLevel--;
            }
         }
         if ((travPtr->ptrArray)[0]!=currentPtr)
            Assert(0, "somehow, -- screwed up");  // this assertion not 
                                                  // necessary
         else
            currentPtr = travPtr;
         return *this; 
      }
      else
         Warn("Cannot decrement current position when at first element.");
   }
   else
      Warn("Cannot move to previous position of an empty list.");
   return *this;
}





 // *************** Information Access



// Retrieve
//    - returns the element at the current list position
//      Attempting to retrieve from a meaningless current position
//      (which for this class can only happen when the list is empty)
//      will result in an error message and termination of program.
template <class Etype>
const Etype& SkipList<Etype>::Retrieve() const
{
   Assert(size > 0, "Cannot Retrieve an element from an empty list."); 
   return currentPtr->element;    
}



// Find
//    - parameters : queryElem - an element of the list's type,
//                       to be searched for
//    - return value : a boolean yes or no
//    - searches list for queryElem...if found, make that position the current
//         position and return 1; otherwise, return 0
template <class Etype>
int SkipList<Etype>::Find(const Etype& queryElem)
{

   int currentNodeLevel = maxLevel; 

   // As long as 
   // 1) we have not dropped below level 0 (the bottom level) AND
   // 2) we have no nodes on this level OR
   //       the first node is greater than what we are looking for
   while (
               (currentNodeLevel!=-1) && 
               ( (head[currentNodeLevel] == NULL) || 
		 (head[currentNodeLevel]->element > queryElem) )
         )
      currentNodeLevel--; 
       
   // now, we point to the first level that 
   //  1) has a first element...
   //  2) ...which is less than what we are looking for. 

   // if currentNodeLevel is -1, then we really aren't on a level -- every
   //   level has no node or the first node is greater than what we are looking 
   //   for. Hence, our value is not in the list.
   if (currentNodeLevel==-1)
      return 0; 

   // otherwise, if the first element in this level's list is what we want, 
   //  then we've found it!
   else if (head[0]->element == queryElem)
   {
      currentPtr = head[0]; 
      return 1; 
   }

   // otherwise...we search! 
   else
      // As long as we haven't sunk below the bottom level
      while (currentNodeLevel>=0)
      {
         SkipNode* searchPtr = head[currentNodeLevel]; 

         // search this level until the next node is either NULL or
         //   greater than what we are looking for
         while (((searchPtr->ptrArray)[currentNodeLevel]!=NULL)  &&
               ((searchPtr->ptrArray)[currentNodeLevel]->element < 
    	   						   queryElem))
            searchPtr = (searchPtr->ptrArray)[currentNodeLevel]; 

         // if the next node is NULL, we have no more nodes on this level,
	 //   but there may be some on lower levels, so we should drop a level 
         //   and continue the search
         if ((searchPtr->ptrArray)[currentNodeLevel]==NULL)
            currentNodeLevel--; 

         // otherwise, if the value we are on is correct, we're done! 
         else if ((searchPtr->ptrArray)[currentNodeLevel]->element == 
							   queryElem)
         {
            currentPtr = (searchPtr->ptrArray)[currentNodeLevel]; 
            return 1; 
         }

         // otherwise, the node after this one is too big. Just like if it
	 //  is NULL, we drop a level and continue the search
         else
            currentNodeLevel--; 
      }

   // if we get this far, then we haven't found our value 
   return 0;  
}



// Length
//    - return value : an integer representing the list's length
//    - returns the length of the list
template <class Etype>
int SkipList<Etype>::Length() const
{
   return size; 
}




// Print
//    - prints out the list values
template <class Etype>
void SkipList<Etype>::Print() const
{
   SkipNode* outPtr = head[0]; 
   if (size == 0)
      cout << "< empty list >" << endl;
   else
   { 
      while (outPtr!=NULL)  
      {
         cout << "(" << outPtr->element << ", " << outPtr->nodeTopLevel; 
         cout << ")" << endl; 
         outPtr = (outPtr->ptrArray)[0]; 
      } 
   } 
}

