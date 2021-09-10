// *****************************************************
// *                                                   *
// *   btree.C (MP7)                                   *
// *                                                   *
// *   Implementation for a BTree class                *
// *                                                   *
// *   Written October 1999 by Jason Zych              *
// *                                                   *
// *****************************************************

#include <iostream.h>
#include "asserts.h"
#include "btree.h"




// ********************* public BTree functions


// BTree
//    - default constructor
//    - initializes values to represent empty BTree
template <class Etype, int b>
BTree<Etype, b>::BTree()
{
   root = NULL;
   numKeys = 0;
}




// Find
//    - parameters : key - the key for the info we want
//    - return value : pointer to info, or to NULL
//    - searches tree for key; If key is found, return pointer
//        to info stored with that key. If key is not found,  
//        return NULL;  
template <class Etype,int b>
Etype* BTree<Etype,b>::Find(int key)
{
   BTreeNode* foundLeaf = FindPtrToLeaf(key, root);
   if (foundLeaf == NULL)  // root is NULL
      return NULL;
   else if (foundLeaf->key == key)
      return foundLeaf->info;
   else  // foundLeaf->key != key)
      return NULL; 
}


// Insert
//    - parameters : key - the key for the info we are inserting
//                 : info - the information record we are inserting
//    - inserts the key into the appropriate place in the tree,
//         and inserts the info record into that key's leaf as
//         well. The info itself won't be used, but rather,
//         a *copy* of the info record will be inserted into the
//         tree. Once that is done, however, the info is always
//         extracted by returning its address (see Find) so
//         we will be able to make changes to the actual info
//         stored in this tree. We just can't *store* the
//         original that we have here...instead we must store a
//         copy. This could be changed by having the user pass in
//         an Etype* instead of an Etype, but we'll do it this way
//         for now.
template <class Etype, int b>
void BTree<Etype,b>::Insert(int key, Etype info)
{
   // if tree has no keys, then this is the first node
   if (numKeys == 0)
   {
      Assert(root == NULL, "Root not NULL in empty tree!");
      root = new BTreeNode(1);
      root->info = new Etype(info);
      root->key = key;
      numKeys++;
   }
   // if tree has 1 key, then we must insert second node -- either
   // to right or left of first node -- and connect the two with a new
   // internal node
   else if (numKeys == 1)
      InsertIntoOneNodeTree(key, info);
   else // insert as leaf into a regular, non-special-case B-Tree
      InsertIntoManyNodeTree(key, info);
}





// Remove
//    - parameters: key - the key for the <key, info> pair we
//                          want to remove
//    - removes the key and its associated info record from the
//               tree. 
template <class Etype, int b>
void BTree<Etype,b>::Remove(int key)
{
   if (numKeys == 0)  // nothing to remove
      return;
   else if (numKeys == 1)
   {
      delete root;
      root = NULL;
      numKeys = 0;
   }
   else if (numKeys == 2)
      RemoveFromTwoNodeTree(key);
   else 
      RemoveFromManyNodeTree(key);
}





// Print
//    - prints out tree details using a pre-order traversal
template <class Etype, int b>
void BTree<Etype,b>::Print()
{
   RecursivePrint(root, 0);
}




// ************************* private BTree functions


// ***** Insert Helper functions


// InsertIntoOneNodeTree
//    - parameters : key - the key for the info we are inserting
//                 : info - the information record we are inserting
//    - does the insert work to insert the new key and info into
//        a B-Tree that is currently size 1 (meaning the regular
//        B-Tree rules don't completely apply yet.
template <class Etype, int b>
void BTree<Etype, b>::InsertIntoOneNodeTree(int key, Etype info)
{
   Assert(root->isLeaf, "Root is not leaf in one-node tree!");
   BTreeNode *leftLeaf, *rightLeaf;
   if (key == root->key)
      return;   // ignore duplicates
   else if (key < root->key)
   {
      rightLeaf = root;
      leftLeaf = new BTreeNode(1);
      leftLeaf->info = new Etype(info);
      leftLeaf->key = key;
   }
   else if (key > root->key)
   {
      leftLeaf = root;
      rightLeaf = new BTreeNode(1);
      rightLeaf->info = new Etype(info);
      rightLeaf->key = key;
   }
   else
      Assert(0, "Somehow there is a fourth case in 2nd-leaf insertion!");

   root = new BTreeNode();
   leftLeaf->parent = root;
   rightLeaf->parent = root;
   (*(root->subtrees))[1] = leftLeaf;
   (*(root->subtrees))[2] = rightLeaf;
   (*(root->indices))[1] = leftLeaf->key;
   root->numChildren = 2;
   numKeys++;
}




// InsertIntoManyNodeTree
//    - parameters : key - the key for the info we are inserting
//                 : info - the information record we are inserting
//    - does the insert work to insert the new key and info into
//        a B-Tree that currently has size greater than 1 (meaning the 
//        regular B-Tree rules are now in effect.
template <class Etype, int b>
void BTree<Etype, b>::InsertIntoManyNodeTree(int key, Etype info)
{
      // travPtr will be set to the parent node of the new leaf
      BTreeNode* travPtr = InsertAsLeaf(FindPtrToLeaf(key, root), key, info);


      // as long as this node overflows and is not the root...
      while ((travPtr->numChildren > b) && (travPtr != root))
      {
         // split the node and point both halves to their common parent
         BTreeNode *rightHalf, *leftHalf;
         leftHalf = travPtr;
         rightHalf = SplitNode(leftHalf);
         rightHalf->parent = leftHalf->parent;


         // insert rightHalf node into their common parent
         int index = leftHalf->parent->MatchThisPointer(leftHalf);
         rightHalf->parent->FreeSubtreeCell(index+1);
         (*(rightHalf->parent->subtrees))[index+1] = rightHalf;

         // insert appropriate index value into common parent
         rightHalf->parent->FreeIndexCell(index);
         (*(rightHalf->parent->indices))[index] =
                         (*(leftHalf->indices))[travPtr->numChildren];

         (travPtr->parent->numChildren)++;
         travPtr = travPtr->parent;
      }

      // if this node overflows and *is* the root
      if ((travPtr == root) && (travPtr->numChildren > b))
      {
         // split the node into two
         BTreeNode *rightHalf, *newNode;
         rightHalf = SplitNode(travPtr);

         // create new node to serve as new parent to split halves and
         //  also to serve as new root of entire tree
         newNode = new BTreeNode();
         newNode->numChildren = 2;

         // connect split halves to new node, and also add appropriate index
         (*(newNode->subtrees))[1] = travPtr;
         (*(newNode->subtrees))[2] = rightHalf;
         (*(newNode->indices))[1] = (*(travPtr->indices))[travPtr->numChildren];

         rightHalf->parent = travPtr->parent = newNode;
         root = newNode;
      }

      /*
         if the node we were at overflowed, we would still be
          in the loop if it was not the root, and therefore
          could not be here, or we would have just gone through the
          root case if it *was* the root, and thus can stop when we
          reach this point. And, of course, if there was no overflow,
          then we would be here because of that. At any rate, if we are
          at this point, it means there is no longer any overflow to
          correct and thus we can stop.
      */
      // end of insert as leaf case

}





// InsertAsLeaf
//    - parameters : leafPtr - pointer to the leaf location where
//                     key *should* go
//                 : key - the key we are inserting
//                 : info - the info paired with that key
//    - return value : pointer to leafPtr's, and new leaf's, parent
//    - Assumes that the node pointed to by leafPtr is
//       in the correct location for key. If that leaf node
//       already contains key, then we don't want to insert
//       this (key, info) pair (it is a duplicate key), so
//       return NULL. Otherwise, a second leaf should go into
//       this conceptual location -- i.e. the parent of leafPtr gains
//       another child -- and new index value gets inserted into
//       parent of the two leaves as well. Then, return a pointer to
//       the parent of the two leaves.
template <class Etype, int b>
BTree<Etype,b>::BTreeNode*
BTree<Etype,b>::InsertAsLeaf(BTree<Etype,b>::BTreeNode* leafPtr,
                                                  int key, Etype info)
{
   // *** Add your code here
   // ***** STEP 1: CREATING NODE
   // if this leaf already holds the value we are trying to insert,
   //  then we avoid inserting a duplicate by simply returning.
   if (leafPtr->key == key)
      return NULL;

   // otherwise, we should create a new B-Tree node which will
   //  be a sibling of this leaf and will also be attached as a
   //  child of this leaf's parent.
   BTreeNode* newNodePtr = new BTreeNode(1);
   newNodePtr->info = new Etype(info);
   newNodePtr->key = key;
   newNodePtr->parent = leafPtr->parent;

   // ***** STEP 2: INSERTING PTR TO NODE
   // find out which index in parent holds the leafPtr
   BTreeNode* parentNode = leafPtr->parent;  // parent of leafPtr and newNodePtr

   int newPtrIndex;                      // array index where newNodePtr will be
                                         //   inserted

   int leafPtrIndex;                     // array index where leafPtr is located
                                         //   currently

   leafPtrIndex = parentNode->MatchThisPointer(leafPtr);
   Assert(leafPtrIndex != -1, "Leaf pointer not found in its parent!");

   // the new node will be inserted to either the left or the right of
   //  leafPtr -- i.e. in the cell with index leafPtrIndex or the cell
   //  with index leafPtrIndex + 1. But, in either case, the new index
   //  value will be inserted between them, so that index value cell --
   //  which has index leafPtrIndex -- should be freed.
   parentNode->FreeIndexCell(leafPtrIndex);

   // if our new node should be inserted as the left sibling of leafPtr
   if (newNodePtr->key < leafPtr->key)
   {
      // then leafPtr should be moved over one and new
      // node goes in its current cell.
      parentNode->FreeSubtreeCell(leafPtrIndex);
      (*(parentNode->subtrees))[leafPtrIndex] = newNodePtr;
      newPtrIndex = leafPtrIndex;


      // now, since new node goes to left of leafPtr, then
      // the key in-between them is the new node's key
      (*(parentNode->indices))[leafPtrIndex] = newNodePtr->key;
   }


   // otherwise the new node should be inserted as the right sibling of leafPtr
   else if (leafPtr->key < newNodePtr->key)
   {
      // then leafPtr is less than the new leaf and therefore, though
      //   everything to the right of leafPtr should be shifted to make
      //   room for the new leaf node, leafPtr itself should stay where
      //   it is.
      parentNode->FreeSubtreeCell(leafPtrIndex + 1);
      (*(parentNode->subtrees))[leafPtrIndex+1] = newNodePtr;
      newPtrIndex = leafPtrIndex + 1;

      // now, since new node goes to the right of leafPtr, then
      //  the key in-between them is leafPtr's key
      (*(parentNode->indices))[leafPtrIndex] = leafPtr->key;
   }
   else
      Assert(0, "Somehow the old and new keys are equal!");


   // ***** STEP 3: MISCELLANY
   (parentNode->numChildren)++;
   numKeys++;

   return parentNode;


}






// SplitNode
//    - parameters : leftHalf - a pointer to a node we want to
//                     split in half
//    - return value : pointer to right half of split
//    - Assumes node is in state of overflow. Creates new
//        node, moves the right half of values into new node and
//        leaves the left half of values (and extra index) in
//        the node "leftHalf", and returns a pointer to the new node.
template <class Etype, int b>
BTree<Etype,b>::BTreeNode* BTree<Etype,b>::SplitNode(
                        BTree<Etype,b>::BTreeNode* leftHalf)
{
   BTreeNode* rightHalf = new BTreeNode();

   // Copy a certain number of subtrees to the right node so that
   //   they can be removed from the left node
   for (int i = ((b+1)/2)+1; i<=b+1; i++)
      (*(rightHalf->subtrees))[i-((b+1)/2)] = (*(leftHalf->subtrees))[i];

   // Copy a certain number of index values to the right node
   //   so that they can be removed from the left node
   for (int i = ((b+1)/2)+1; i<=b; i++)
      (*(rightHalf->indices))[i-((b+1)/2)] = (*(leftHalf->indices))[i];

   // the number of children is reset in both nodes, to indicate
   //  the changed number of chilren
   //     left:  b+1  ->  (b+1)/2
   //     right:   0  ->  (b+1)/2
   rightHalf->numChildren = leftHalf->numChildren = (b+1)/2;

   // and finally, the parents of the moved subtrees must be re-set
   for (int i = 1; i <= rightHalf->numChildren; i++)
      (*(rightHalf->subtrees))[i]->parent = rightHalf;

   return rightHalf;
}



// ***** Remove Helper functions


// RemoveLeafFromNode
//    - parameters : leafPtr - pointer to the leaf location where
//                           key is potentially located
//                 : key - the key we are removing
//    - return value : pointer to leafPtr's parent
//    - Assumes that the node pointed to by leafPtr is
//       in the correct location for key. If that leaf node
//       does not contain key, then key is not in the tree
//       and there is nothing to do except return NULL. Otherwise, 
//       the leaf should be removed from this location -- and with 
//       it an index value should be removed from the leaf's parent.
//       Then return a pointer to that parent. 
template <class Etype, int b>
BTree<Etype,b>::BTreeNode*
BTree<Etype,b>::RemoveLeafFromNode(BTree<Etype,b>::BTreeNode* leafPtr, int key)
{
   // ***** STEP 1: CHECK IF LEAF CONTAINS KEY
   // If this leaf 
  
   if (leafPtr->key != key)
      return NULL;


   // **** STEP 2: DELETE LEAF AND INDEX

   BTreeNode* parentNode = leafPtr->parent;

   int leafPtrIndex = parentNode->MatchThisPointer(leafPtr);
   Assert(leafPtrIndex != -1, "Leaf pointer not found in its parent!");

 
   // if we are removing the rightmost leaf of the node, then
   // remove the most index, which is to the left of this leaf 
   if (leafPtrIndex == parentNode->numChildren)
   {  
      parentNode->FillIndexCell(leafPtrIndex-1);
      delete (*(parentNode->subtrees))[leafPtrIndex];
      parentNode->FillSubtreeCell(leafPtrIndex);
   }

   // in all other cases, we know there is an index to the right
   // of the leaf and we should remove that index. Removing the
   // right index instead of the left index whenever the right index
   // exists means that we are shifting fewer nodes to the left to
   // fill the gap.
   else
   {
      parentNode->FillIndexCell(leafPtrIndex);
      delete (*(parentNode->subtrees))[leafPtrIndex];
      parentNode->FillSubtreeCell(leafPtrIndex);
   }



   // ***** STEP 3: MISCELLANY 
   (parentNode->numChildren)--;
   numKeys--;
   
   return parentNode;
}



// RemoveFromTwoNodeTree
//    - parameters : key - the key for the info we are inserting
//                 : info - the information record we are inserting
//    - does the removal work to remove the key and info from a B-Tree
//        that is currently size 2 (meaning the tree after this removal
//        will no longer be under the control of the B-Tree rules)
template <class Etype, int b>
void BTree<Etype,b>::RemoveFromTwoNodeTree(int key)
{
   BTreeNode *leftLeaf, *rightLeaf;
   leftLeaf = (*(root->subtrees))[1];
   rightLeaf = (*(root->subtrees))[2];

   if ((leftLeaf->key == key) || (rightLeaf->key == key)) 
   {
      delete root->subtrees;
      delete root->indices;
      delete root->info;
      delete root;
      numKeys--;

      if (leftLeaf->key == key)
      {
         delete leftLeaf;
         root = rightLeaf;
      }
      else if (rightLeaf->key == key)
      {
         delete rightLeaf;
         root = leftLeaf;
      }
      root->parent = NULL;
   }
   // else key is not in tree
}




// RemoveFromManyNodeTree
//    - parameters : key - the key for the info we are inserting
//    - does the removal work to remove the new key and info from
//        a B-Tree that currently has size greater than 2 (meaning the
//        regular B-Tree rules are now in effect.
template <class Etype, int b>
void BTree<Etype,b>::RemoveFromManyNodeTree(int key)
{
   // travPtr will be set to the parent node of the to-be-removed leaf
   BTreeNode* travPtr = RemoveLeafFromNode(FindPtrToLeaf(key, root), key);

   BTreeNode *immediateLeft, *immediateRight;


   // if the node is not the root and yet underflows
   while ((travPtr != root) && (travPtr->numChildren < (b+1)/2))
   {
      // index of travPtr in parent
      int index = travPtr->parent->MatchThisPointer(travPtr);

      // get ptrs to immediate left and right siblings, if they
      //    exist 
      if (index > 1) 
         immediateLeft = (*(travPtr->parent->subtrees))[index-1];
      else 
         immediateLeft = NULL;
      if (index < travPtr->parent->numChildren)
         immediateRight =  (*(travPtr->parent->subtrees))[index+1];
      else
         immediateRight = NULL;  


      // if you can steal from left
      if ((immediateLeft != NULL) && (immediateLeft->numChildren>(b+1)/2)) 
         StealChild(travPtr, immediateLeft);

      // else if you can steal from right
      else if ((immediateRight != NULL) && 
                                   (immediateRight->numChildren>(b+1)/2))
         StealChild(travPtr, immediateRight);
      
      // else if you can combine with left
      else if (immediateLeft != NULL)
      {
         // grab needed index from parent and shift-to-condense the
         //   parent's other indices, since we must drop an index from 
         //   the parent in the combine case
         int indexOfIndicesArray = index-1;
         int valueInIndicesArray = 
                  (*(travPtr->parent->indices))[indexOfIndicesArray];
         travPtr->parent->FillIndexCell(indexOfIndicesArray);

         // create new combine node
         BTreeNode* combinedNode = CombineNodes(immediateLeft, travPtr);

         // attach combine node to parent and fill in other space 
         travPtr->parent->FillSubtreeCell(index);
         (*(travPtr->parent->subtrees))[index-1] = combinedNode;
         combinedNode->parent = travPtr->parent;

         // fill index into new combine node
         (*(combinedNode->indices))[(b+1)/2] = valueInIndicesArray;

         // move upward to inspect parent
         BTreeNode* temp = travPtr;
         (travPtr->parent->numChildren)--;
         travPtr = travPtr->parent;
         delete temp;
      }

      // else combine with right
      else
      {
         // grab needed index from parent and shift-to-condense
         // the parent's other indices, since we must drop an   
         // index from the parent in the combine case
         int indexOfIndicesArray = index; 
         int valueInIndicesArray =
                  (*(travPtr->parent->indices))[indexOfIndicesArray];
         travPtr->parent->FillIndexCell(indexOfIndicesArray);

         // create new combine node
         BTreeNode* combinedNode = CombineNodes(travPtr, immediateRight);


         // attach combine node to parent and fill in other spaces
         travPtr->parent->FillSubtreeCell(index + 1);
         (*(travPtr->parent->subtrees))[index] = combinedNode;
         combinedNode->parent = travPtr->parent;

         // fill index into new combine node
         (*(combinedNode->indices))[(b+1)/2 - 1] = valueInIndicesArray;
         

         // move upward to inspect parent 
         delete immediateRight;
         (travPtr->parent->numChildren)--;
         travPtr = travPtr->parent;
      }
   }


   // if the node *is* the root and yet underflows
   if ((travPtr == root) && (travPtr->numChildren < 2))
   {
      BTreeNode* temp = (*(root->subtrees))[1];
      delete root; 
      root = temp;
      root->parent = NULL;
   }

   // if no underflow, stop!

}




// StealChild
//    - parameters : stealTo - a pointer to a node we want to
//                     steal to
//    - parameters : stealFrom - a pointer to a node we want to
//                     steal from
//    - Assumes that the stealTo node is in state of underflow, that
//        the stealFrom node can be stolen from without causing 
//        underflow, and that the two nodes are immedaite siblings.
//        Steals a child from the stealFrom node, and moves it to
//        the stealTo node, swapping around index values as appropriate.
template <class Etype, int b>
void BTree<Etype,b>::StealChild(BTree<Etype,b>::BTreeNode* stealTo, 
                                BTree<Etype,b>::BTreeNode* stealFrom)
{

   // stealing left to right
   if ( (*(stealFrom->indices))[1] < (*(stealTo->indices))[1])
   {
      // move rightmost child over one cell 
      (*(stealTo->subtrees))[(b+1)/2] = (*(stealTo->subtrees))[(b+1)/2 - 1];

      // move each of the other children and index values over one cell
      for (int i = (stealTo->numChildren)-1; i >=1; i--)
      {
         (*(stealTo->subtrees))[i+1] = (*(stealTo->subtrees))[i];
         (*(stealTo->indices))[i+1] = (*(stealTo->indices))[i];
      } 

      // now steal child and store in first cell
      (*(stealTo->subtrees))[1] = 
                        (*(stealFrom->subtrees))[stealFrom->numChildren];
      (*(stealTo->subtrees))[1]->parent = stealTo;

 
      // what is the index of the stealFrom node in the parent?
      int downIndex = stealFrom->parent->MatchThisPointer(stealFrom);

      (*(stealTo->indices))[1] = (*(stealTo->parent->indices))[downIndex];

      int upValue = (*(stealFrom->indices))[stealFrom->numChildren-1];
      (stealFrom->numChildren)--;
      (stealTo->numChildren)++;
      (*(stealTo->parent->indices))[downIndex] = upValue;
   }

   // stealing right to left
   else
   {
      // steal child and store in last cell
      (*(stealTo->subtrees))[(b+1)/2] = (*(stealFrom->subtrees))[1];
      (*(stealTo->subtrees))[(b+1)/2]->parent = stealTo;

      int upValue = (*(stealFrom->indices))[1];

      // move down each index and corresponding child
      for (int i = 2; i <= stealFrom->numChildren-1; i++)
      {
         (*(stealFrom->subtrees))[i-1] = (*(stealFrom->subtrees))[i];
         (*(stealFrom->indices))[i-1] = (*(stealFrom->indices))[i];
      } 
      
      // move down last subtree
      (*(stealFrom->subtrees))[stealFrom->numChildren-1] = 
                         (*(stealFrom->subtrees))[stealFrom->numChildren];

  
      // what is index of the stealTo node in the parent?
      int downIndex = stealTo->parent->MatchThisPointer(stealTo);

      (*(stealTo->indices))[stealTo->numChildren] = 
                         (*(stealTo->parent->indices))[downIndex];

      
      (stealFrom->numChildren)--;
      (stealTo->numChildren)++;
      (*(stealTo->parent->indices))[downIndex] = upValue;

   }
}




// CombineNodes
//    - parameters : leftSide - a pointer to the left-side node of
//                      a combine operation
//    - parameters : rightSide - a pointer to the right-side node of 
//                      a combine operation
//    - Assumes that one of the two parameter nodes is in a state of 
//        underflow, and that the other has the minimum number of 
//        children allowed. Combines the two nodes into one and returns
//        a pointer to that node, leaving the correct index cell blank
//        to hold an additional index when that index is decided on.
template <class Etype, int b>
BTree<Etype,b>::BTreeNode* 
BTree<Etype, b>::CombineNodes(BTree<Etype,b>::BTreeNode* leftSide,
                                  BTree<Etype,b>::BTreeNode* rightSide)
{
  
   // move each of the right side subtrees to the left side 
   for (int i = 0; i < rightSide->numChildren; i++)
      (*(leftSide->subtrees))[b - i] = 
             (*(rightSide->subtrees))[rightSide->numChildren - i];
   
   // move each of the right side indices to the left side   
   for (int i = 0; i < (rightSide->numChildren) - 1; i++)
      (*(leftSide->indices))[b - 1 - i] = 
              (*(rightSide->indices))[(rightSide->numChildren) - 1 - i];

   // note that cell b - (rightSide->numChildren - 1) is the free
   //   cell that a future index will be placed into. It will
   //   either be (b+1)/2   or   (b+1)/2  +   1    depending
   //   on how many children the rightSide node had.

   // assign the newly-moved former-right-side children to
   //   have the left side's parent as their parent
   for (int i = 0; i < rightSide->numChildren; i++)
      (*(leftSide->subtrees))[b - i]->parent = leftSide;

   leftSide->numChildren += rightSide->numChildren; 
   return leftSide;
}




 

// ***** General Helper functions



// FindPtrToLeaf
//    - parameters : key - key we are searching for
//                 : ptr - pointer to subtree we are searching
//    - return value : leaf node pointer
//    - finds the leaf (in the subtree pointed to by ptr) where
//        key *should* be and returns pointer to that leaf. This
//        is the leaf we would find while doing a search. If this
//        leaf turns out to not contain our value, then the key is
//        not in the subtree pointed to by ptr. But we don't worry
//        about that in this function; we only search downward as
//        far as the leaf itself and then we return a pointer to
//        that leaf before inspecting it to see if it contains our
//        key or not. If subtree does not exist, return NULL.
template <class Etype, int b>
BTree<Etype, b>::BTreeNode*
BTree<Etype,b>::FindPtrToLeaf(int key, BTree<Etype, b>::BTreeNode* ptr)
{
   if (ptr == NULL)  // shouldn't happen unless a NULL root is passed in
      return NULL;
   else if (ptr->isLeaf)  // we have found a leaf; done!
      return ptr;
   else
   {
      // find where key should go among ptr's subtrees
      int index = ptr->SearchForSubtreeIndex(key);

      // recursively call FindPtrToLeaf with a subtree ptr
      return FindPtrToLeaf(key, (*(ptr->subtrees))[index]);
   }
}





// RecursivePrint 
//    - parameters : ptr - a pointer to a node in the BTree
//                 : depth - the depth of the node "ptr"  
//    - recursively prints this subtree in a preorder fashion.
//       The depth parameter will be useful for detecting
//       the end of a particular subtree traversal in the actual
//       printed output.
template <class Etype, int b>
void BTree<Etype, b>::RecursivePrint(BTree<Etype, b>::BTreeNode* ptr, int depth)
{
   if (ptr != NULL)
   {
      cout << "*** Printing a node at depth " << depth << endl;

      if (ptr->isLeaf)  // ptr points to a leaf
         cout << "   This node is a leaf with key " << ptr->key << endl;
      else  // ptr points to an internal node
      {
         cout << "   This node is an internal node." << endl;
         cout << "   Indices are: ";
         
         // print node's indices one-bu-one
         for (int i = 1; i < ptr->numChildren; i++)
            cout << (*(ptr->indices))[i] << "  ";
         cout << endl;

         cout << "   This node has " << ptr->numChildren;
         cout << " children." << endl;

         // print node's child subtrees one-by-one
         for (int i = 1; i <= ptr->numChildren; i++)
         {
            cout << "==== Child #" << i << ":" << endl;
            RecursivePrint((*(ptr->subtrees))[i], depth+1);
         }
      }
   }
   else   // this shouldn't happen unless we pass in a NULL root pointer
      cout << "*** This tree is empty!" << endl; 
}


