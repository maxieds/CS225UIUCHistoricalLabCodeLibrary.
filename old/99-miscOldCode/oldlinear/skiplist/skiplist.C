// ******************************************
// *                                        *
// *  skiplist.C                            *
// *                                        *
// *  Implementation for a skip list class  *
// *                                        *
// *  Written 7/97 by Jason Zych            *
// *                                        *
// ******************************************

#include "skiplist.h"
#include "asserts.h"

// SkipList()
//    - (default) constructor
//    - parameters : userMaxLevel - an integer indicating maximum height
//                      of ptr Tower (defaults to 5) 
template <class Etype>
SkipList<Etype>::SkipList(int userMaxLevel)
{
   maxLevel = userMaxLevel; 
   head = new Array<SNode*>(maxLevel, 0);  // allocate new header node
   currentPtr = NULL;                     // list is empty; hence no current node 
   size = 0; 
}



// SkipList - Copy Constructor 
//    - parameters : origList - a SkipList object 
//    - operation : creates a new skiplist that is a copy of origList
template <class Etype>
SkipList<Etype>::SkipList(const SkipList<Etype>& origList)
{
   maxLevel = origList.maxLevel; 
   size = origList.size; 

   // origTravPtr starts pointing to first node
   SNode* origTravPtr = (*(origList.head))[0]; 

   SNode* copyPtr; 

   // Update is an array that will point to the rightmost node of each level 
   Array<SNode*> Update(maxLevel); 
   for (int i=0; i<=maxLevel; i++)
      Update[i]=NULL;

   head = new Array<SNode*>(maxLevel);  
  
   // if there is at least one element in origList
   if (origTravPtr!=NULL)
   {
      // as long as origTravPtr has not reached the end of origList 
      while (origTravPtr!=NULL)
      {
         // create a new node that has the same height as the current node
	 //   in the origList
         copyPtr = new SNode(maxLevel, origTravPtr->nodeTopLevel); 

         // give them the same element
         copyPtr->element = origTravPtr->element; 

         // for all the levels that this node has...
         for (i=0; i<=copyPtr->nodeTopLevel; i++)
         {
            // the pointer on that level is NULL
            (*(copyPtr->ptrArray))[i]=NULL; 

            // if Update on that level is NULL, then this is the first node of
	    //   that level in the list, and so point to the node from head...
            if (Update[i]==NULL)
               (*head)[i] = copyPtr; 
            else
               // otherwise, point to the node from the node recorded by Update,
	       //   i.e. the most recent node of that level in the list
               (*(Update[i]->ptrArray))[i] = copyPtr; 

            // Finally, for each level of the node, the most recent node of that
	    //   level should be reset to this node
            Update[i] = copyPtr; 
         }
    
         // if current pointer happens to point to this node in the origList, 
         //  then this list's current pointer should point to this node 
         if (origList.currentPtr == origTravPtr)
            currentPtr = copyPtr;

         // increment origTravPtr in the origList
         origTravPtr = (*(origTravPtr->ptrArray))[0]; 
      }
   }
}

      


// ~SKipList - Destructor 
//    - operation : deallocates all dynamically allocated memory inside 
//         the list 
template <class Etype>
SkipList<Etype>::~SkipList()
{
   Clear(); 
   delete head; 
}



// Clear
//    - operation : Deletes all values from list, resulting in an empty list 
template <class Etype>
void SkipList<Etype>::Clear()
{
   currentPtr = (*head)[0]; 
   SNode* travPtr; 

   // traverse down the list, deleting each node
   while (currentPtr!=NULL)
   {
      travPtr = currentPtr; 
      currentPtr = (*(currentPtr->ptrArray))[0]; 
      delete travPtr; 
   }

   // set all header pointers to NULL
   for (int i=0; i<=maxLevel; i++)
      (*head)[i] = NULL; 
}




// operator=
//    - parameters: origList - a List object
//    
//    - operation : Makes the list a copy of origList 
template <class Etype>
SkipList<Etype>& SkipList<Etype>::operator=(const SkipList<Etype>& origList)
{
   if (this!=&origList)
   {
      Clear(); 
      maxLevel = origList.maxLevel;
      size = origList.size;

      // origTravPtr starts pointing to first node
      SNode* origTravPtr = (*(origList.head))[0];
      SNode* copyPtr;

      // Update is an array that will point to the rightmost node of each level 
      Array<SNode*> Update(maxLevel);
      for (int i=0; i<=maxLevel; i++)
         Update[i]=NULL;
  
       head = new Array<SNode*>(maxLevel);

      // if there is at least one element in origList
      if (origTravPtr!=NULL)
      {

         // as long as origTravPtr has not reached the end of origList 
         while (origTravPtr!=NULL)
         {

            // create a new node that has the same height as the current node
            //   in the origList
            copyPtr = new SNode(maxLevel, origTravPtr->nodeTopLevel);

            // give them the same element
            copyPtr->element = origTravPtr->element; 

            // for all the levels that this node has...
            for (i=0; i<=copyPtr->nodeTopLevel; i++)
            {
            
               // the pointer on that level is NULL
               (*(copyPtr->ptrArray))[i]=NULL;


               // if Update on that level is NULL, then this is the first node of
               //   that level in the list, and so point to the node from head...
               if (Update[i]==NULL)
                  (*head)[i] = copyPtr;
               else
                  // otherwise, point to the node from the node recorded by Update,
                  //   i.e. the most recent node of that level in the list
                  (*(Update[i]->ptrArray))[i] = copyPtr;

               // Finally, for each level of the node, the most recent node of that
               //   level should be reset to this node
               Update[i] = copyPtr;
            }

            // if current pointer happens to point to this node in the origList, 
            //  then this list's current pointer should point to this node 
            if (origList.currentPtr == origTravPtr)
               currentPtr = copyPtr;

            // increment origTravPtr in the origList
            origTravPtr = (*(origTravPtr->ptrArray))[0];
         }
      }
   }
   return *this; 
}




// Insert
//    - parameters : insElem - element of the template type that we want to insert
//    - inserts the element insElem into the skiplist
template <class Etype>
void SkipList<Etype>::Insert(Etype insElem)
{
   // Create new node and extract node's top level
   SNode* insertNode = new SNode(maxLevel); 
   insertNode->element = insElem; 
   int currentNodeLevel = insertNode->nodeTopLevel;  

   // traverse list from the top level of the new node down to level 0
   while (currentNodeLevel>=0)
   {
      // if the header points to null or an element greater than what
      //    we want to insert...
      if (((*head)[currentNodeLevel] == NULL) || 
	  ((*head)[currentNodeLevel]->element > insertNode->element))
      {
         // ...then insert directly off of header...
         (*(insertNode->ptrArray))[currentNodeLevel] = 
		(*head)[currentNodeLevel]; 
         (*head)[currentNodeLevel] = insertNode; 

         // ...and move down a level. 
         currentNodeLevel--; 
      }
      else // once we reach this point, we will remain in the while 
	   //    loop -- it indicates we begin our search forward
	   //    in the list
      {
         // we know the first node isn't greater (or we'd still be in 
         //  the if-case) so set temp to first node
         SNode* tempPtr = (*head)[currentNodeLevel]; 
         while (currentNodeLevel>=0)
         {
            // As long as the node after the one we're pointing to is
	    //  1) not NULL
	    //  2) less than where we should insert
            // move forward along this level
            while (
		  ((*(tempPtr->ptrArray))[currentNodeLevel] != NULL) && 
                  ((*(tempPtr->ptrArray))[currentNodeLevel]->element < 
				insertNode->element)
                  )
               tempPtr = (*(tempPtr->ptrArray))[currentNodeLevel]; 


            // now we point to node before where we want to insert
            (*(insertNode->ptrArray))[currentNodeLevel] = 
				(*(tempPtr->ptrArray))[currentNodeLevel]; 
	    (*(tempPtr->ptrArray))[currentNodeLevel] = insertNode; 
            currentNodeLevel--; 
         }
      }
   }
   size++; 
   currentPtr = insertNode; 
}

          

// Remove
//    - removes the element pointed to by the current pointer 
template <class Etype>
void SkipList<Etype>::Remove()
{
   int currentNodeLevel = currentPtr->nodeTopLevel; 
   SNode* deletePtr = currentPtr; 
   
   while (currentNodeLevel >= 0)
   {
      // if the current node is the first node in the list on this
      //    level, then header points to current's next node on this
      //    level 
      if ((*head)[currentNodeLevel] == deletePtr)
      {
         (*head)[currentNodeLevel] = 
		(*(deletePtr->ptrArray))[currentNodeLevel]; 
         currentNodeLevel--; 
      }
      else // once we reach this point, we will remain in the while 
	   //    loop -- it indicates we begin our search forward
	   //    in the list
      {
         // we know the first node isn't our current pointer (or we'd
	 //    still be in the if-case) so set travPtr to first node
         SNode* travPtr = (*head)[currentNodeLevel]; 
         while (currentNodeLevel >= 0)
         { 
            while ((*(travPtr->ptrArray))[currentNodeLevel] != deletePtr) 
               travPtr = (*(travPtr->ptrArray))[currentNodeLevel]; 
            // now, on this level, we point to the node before the
	    //    one we want to remove
            (*(travPtr->ptrArray))[currentNodeLevel] = 
			(*(deletePtr->ptrArray))[currentNodeLevel]; 
            currentPtr = travPtr; 
            currentNodeLevel--; 
         }
         if ((*(deletePtr->ptrArray))[0] != NULL)
            currentPtr = (*(deletePtr->ptrArray))[0]; 
      }
   }
   delete deletePtr; 
   size--; 
}




// Head
//    - moves current pointer to first node in list
template <class Etype>
void SkipList<Etype>::Head()
{
   currentPtr = (*head)[0]; 
}



// Tail
//    - moves current pointer to last node in list
template <class Etype>
void SkipList<Etype>::Tail()
{
   // we want to go as far as we can along the top level, then 
   // as far as we can along 2nd from top, and so on. This gets 
   // us to the end in the fewest increments possible. 

   int currentNodeLevel = maxLevel; 
   SNode* travPtr; 

   // while the current node level is an actual node level (i.e. we haven't
   //   sunk below the bottom level of the list) and the header pointer is NULL, 
   //   move down a level. 
   while ((currentNodeLevel>=0) && ((*head)[currentNodeLevel] == NULL))
      currentNodeLevel--; 
 
   // if cNL is -1, then we have an empty list 
   if (currentNodeLevel == -1)
      return;

   // otherwise, travPtr is the first node of the highest level that
   // actually has a node 
   else
   { 
      travPtr = (*head)[currentNodeLevel]; 
      
      // go until the next ptr on this level is NULL, then drop down
      while (currentNodeLevel>=0)
      {
         while ((*(travPtr->ptrArray))[currentNodeLevel]!=NULL)
            travPtr = (*(travPtr->ptrArray))[currentNodeLevel]; 
         currentNodeLevel--; 
      }
   }
   currentPtr = travPtr; 
}




// operator++
//    - moves current pointer one forward in list
template <class Etype>
SkipList<Etype>& SkipList<Etype>::operator++ (int)
{
   if ((*(currentPtr->ptrArray))[0]!=NULL)
      currentPtr = (*(currentPtr->ptrArray))[0];
   return *this; 
}



// operator-- 
//    - moves current pointer one backward in list
template <class Etype>
SkipList<Etype>& SkipList<Etype>::operator-- (int)
{
   int currentNodeLevel = maxLevel;
   SNode* travPtr;

   
   // As long as we have not dropped below the level of the array and
   //   there is no node on the current level, drop a level 
   while ((currentNodeLevel>=0) && ((*head)[currentNodeLevel] == NULL))
      currentNodeLevel--;

   // if currentNodeLevel = -1, list is empty; don't need to do anything  
   if (currentNodeLevel == -1)
      return *this;

   // likewise if our element is first element -- current should still be 
   //   first element 
   else if ((*head)[0]==currentPtr)
      return *this; 

   // otherwise, search across list to find node before current node
   else
   {
      travPtr = (*head)[currentNodeLevel];
      while (currentNodeLevel>=0)
      {
         // while the next element is less than our current element, advance
         while ((*(travPtr->ptrArray))[currentNodeLevel]->element < 
					currentPtr->element)
            travPtr = (*(travPtr->ptrArray))[currentNodeLevel];

         // if we don't advance, drop a level
         currentNodeLevel--;
      }
   }
   if ((*(travPtr->ptrArray))[0]!=currentPtr)
      Assert(0, "somehow, -- screwed up");  // this assertion not necessary; just my
					     // own check 
   else
      currentPtr = travPtr;
   return *this; 
}



// Retrieve
//    - returns element at current pointer
template <class Etype>
Etype SkipList<Etype>::Retrieve() const
{
   return currentPtr->element; 
}



// Includes
//    - parameters : queryElem - an element that we are searching for 
//    - returns 1 if queryElem is in skiplist, 0 else
template <class Etype>
int SkipList<Etype>::Includes(Etype queryElem)
{

   int currentNodeLevel = maxLevel; 

   // As long as 
   // 1) we have not dropped below level 0 (the bottom level) AND
   // 2) we have no nodes on this level OR
   //       the first node is greater than what we are looking for
   while (
               (currentNodeLevel!=-1) && 
               ( ((*head)[currentNodeLevel] == NULL) || 
		 ((*head)[currentNodeLevel]->element > queryElem) )
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
   else if ((*head)[0]->element == queryElem)
   {
      currentPtr = (*head)[0]; 
      return 1; 
   }

   // otherwise...we search! 
   else
      // As long as we haven't sunk below the bottom level
      while (currentNodeLevel>=0)
      {
         SNode* searchPtr = (*head)[currentNodeLevel]; 

         // search this level until the next node is either NULL or
         //   greater than what we are looking for
         while (((*(searchPtr->ptrArray))[currentNodeLevel]!=NULL)  &&
               ((*(searchPtr->ptrArray))[currentNodeLevel]->element < 
    	   						   queryElem))
            searchPtr = (*(searchPtr->ptrArray))[currentNodeLevel]; 

         // if the next node is NULL, we have no more nodes on this level,
	 //   but there may be some on lower levels, so we should drop a level 
         //   and continue the search
         if ((*(searchPtr->ptrArray))[currentNodeLevel]==NULL)
            currentNodeLevel--; 

         // otherwise, if the value we are on is correct, we're done! 
         else if ((*(searchPtr->ptrArray))[currentNodeLevel]->element == 
							   queryElem)
         {
            currentPtr = (*(searchPtr->ptrArray))[currentNodeLevel]; 
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
//    - returns length of skiplist
template <class Etype>
int SkipList<Etype>::Length() const
{
   return size; 
}



// operator<<
//    - parameters: Out - stream operator
//                : outlist - a list to be printed
//    - prints data of list to the screen
template <class Etype>
ostream& operator<< (ostream& Out, const SkipList<Etype>& outList)
{
   return outList.PrintList(Out); 
}
 


 
// Prints list to stream operator
template <class Etype>
ostream& SkipList<Etype>::PrintList(ostream& Out) const
{
   SNode* outPtr = (*head)[0]; 
   if (size==0)
      Out << "empty list" << endl;
   else
   { 
      while (outPtr!=NULL)  
      {
         Out << "(" << outPtr->element << ", " << outPtr->nodeTopLevel; 
         Out << ")" << endl; 
         outPtr = (*(outPtr->ptrArray))[0]; 
      } 
   } 
   return Out; 
}

