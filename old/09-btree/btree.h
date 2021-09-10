// *****************************************************
// *                                                   *
// *   btree.h                                         *   
// *                                                   *
// *   Interface for a BTree class                     *                       
// *                                                   *
// *   Written October 1999 by Jason Zych              * 
// *                                                   * 
// *****************************************************

#ifndef _BTREE_H
#define _BTREE_H

#include <iostream.h>
#include "array.h"

// **************************************************************
// *                                                            *
// *  Class : BTree                                             *
// *                                                            *
// *  The interface class for the BTree implementation          * 
// *                                                            *
// *                                                            *
// **************************************************************

template<class Etype, int b>
class BTree 
{
private:
   // forward declaration...but we don't want it public.
   class BTreeNode;


public:

   // BTree
   //    - default constructor
   //    - initializes values to represent empty BTree
   BTree();


   // Find
   //    - parameters : key - the key for the info we want
   //    - return value : pointer to info, or to NULL
   //    - searches tree for key; If key is found, return pointer
   //        to info stored with that key. If key is not found, 
   //        return NULL;   
   Etype* Find(int key);


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
   void Insert(int key, Etype info);


   // Remove
   //    - parameters: key - the key for the <key, info> pair we
   //                          want to remove
   //    - removes the key and its associated info record from the
   //               tree. 
   void Remove(int key);
   

   // Print
   //    - prints out tree details using a pre-order traversal  
   void Print();



private:

   // ***** Insert Helper functions


   // InsertIntoOneNodeTree
   //    - parameters : key - the key for the info we are inserting
   //                 : info - the information record we are inserting
   //    - does the insert work to insert the new key and info into
   //        a B-Tree that is currently size 1 (meaning the regular
   //        B-Tree rules don't completely apply yet.
   void InsertIntoOneNodeTree(int key, Etype info);


   // InsertIntoManyNodeTree
   //    - parameters : key - the key for the info we are inserting
   //                 : info - the information record we are inserting
   //    - does the insert work to insert the new key and info into
   //        a B-Tree that currently has size greater than 1 (meaning the 
   //        regular B-Tree rules are now in effect.
   void InsertIntoManyNodeTree(int key, Etype info);



   // InsertAsLeaf
   //    - parameters : leafPtr - pointer to the leaf location where
   //                     key *should* go
   //                 : key - the key we are inserting
   //                 : info - the info paired with that key
   //    - return value : pointer to leafPtr's parent
   //    - Assumes that the node pointed to by leafPtr is
   //       in the correct location for key. If that leaf node
   //       already contains key, then we don't want to insert
   //       this (key, info) pair (it is a duplicate key), so
   //       return NULL. Otherwise, a second leaf should go into
   //       this conceptual location -- i.e. the parent of leafPtr gains
   //       another child -- and new index value gets inserted into 
   //       parent of the two leaves as well. Then, return a pointer to 
   //       the parent of the two leaves.
   BTreeNode* InsertAsLeaf(BTreeNode* leafPtr, int key, Etype info);




   // SplitNode
   //    - parameters : leftHalf - a pointer to a node we want to
   //                     split in half
   //    - return value : pointer to right half of split
   //    - Assumes node is in state of overflow. Creates new 
   //        node, moves the right half of values into new node and 
   //        leaves the left half of values (and extra index) in 
   //        the node "leftHalf", and returns a pointer to the new node.
   BTreeNode* SplitNode(BTreeNode* leftHalf);





   // ***** Remove Helper functions


   // RemoveLeafFromNode
   //    - parameters : leafPtr - pointer to the leaf location where
   //                           key is potentially located
   //                 : key - the key we are removing
   //    - return value : pointer to leafPtr's parent
   //    - Assumes that the node pointed to by leafPtr is
   //       in the correct *location* for key. If that leaf node
   //       does not contain key, then key is not in the tree
   //       and there is nothing to do except return NULL. Otherwise,
   //       the leaf should be removed from this location -- and with
   //       it an index value should be removed from the leaf's parent
   //       (the index to the right of deleted leaf unless not possible).
   //       Then return a pointer to that parent.
   BTreeNode* RemoveLeafFromNode(BTreeNode* leafPtr, int key);

  
   // RemoveFromTwoNodeTree
   //    - parameters : key - the key for the info we are inserting
   //                 : info - the information record we are inserting
   //    - does the removal work to remove the key and info from a B-Tree
   //        that is currently size 2 (meaning the tree after this removal
   //        will no longer be under the control of the B-Tree rules)
   void RemoveFromTwoNodeTree(int key);


   // RemoveFromManyNodeTree
   //    - parameters : key - the key for the info we are inserting
   //    - does the removal work to remove the new key and info from
   //        a B-Tree that currently has size greater than 2 (meaning the
   //        regular B-Tree rules are now in effect.
   void RemoveFromManyNodeTree(int key);




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
   void StealChild(BTreeNode* stealTo, BTreeNode* stealFrom);



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
   BTreeNode* CombineNodes(BTreeNode* leftSide, BTreeNode* rightSide);


  

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
   //        key or not.  If subtree does not exist, return NULL.
   BTreeNode* FindPtrToLeaf(int key, BTreeNode* ptr);


   // RecursivePrint
   //    - parameters : ptr - a pointer to a node in the BTree
   //                 : depth - the depth of the node "ptr"
   //    - recursively prints this subtree in a preorder fashion.
   //       The depth parameter will be useful for detecting
   //       the end of a particular subtree traversal in the actual
   //       printed output. 
   void RecursivePrint(BTreeNode* ptr, int depth);
   

   // *********************************************
   // *                                           *
   // *  BTree<>::BTreeNode                       *
   // *                                           *
   // *  The node class for our BTree.            * 
   // *  Right now, the compiler can get funky    *
   // *  about nested class definitions in the    *
   // *   .C, so we put all the code in the .h.   *
   // *                                           *
   // *  There are a number of tasks you could    *
   // *   do on a node that are not conceptually  *
   // *   hard, but would be irritating to waste  *
   // *   time having to code yourself. So, we    *
   // *   have provided the functions we think    *
   // *   you will find useful. The comments      *
   // *   *should* be enough to allow you to      *
   // *   understand and use them without having  *
   // *   to look at their code, but the code     *
   // *   isn't too complicated, if you *do*      *
   // *    want to look at it.                    *
   // *                                           *
   // *********************************************

   class BTreeNode
   {
   public:    // public in scope of BTree
              // private to outside world
  
      // BTreeNode
      //    - default constructor
      //    - parameters : leafFlag - indicates if node is leaf or not
      //    - creates a new BTreeNode. If user passes in 0 or no value 
      //        at all, creates an internal node. If user passes in 
      //        1, creates a leaf. 
      BTreeNode(int leafFlag = 0)
      {
         if (leafFlag == 0) // non-leaf
         {
            // make them one larger in size than legal, so that
            //  we can handle temporary overflow until that overflow
            //  is fixed. 
            indices = new Array<int>(1, b);
            subtrees = new Array<BTreeNode*>(1, b+1);
            numChildren = 0; // this will, of course, get changed
            isLeaf = 0;
            parent = NULL;  // this will get changed as well

            // *** we won't use these 
            info = NULL;
            key = 0;   // just to give it a default
         }
         else
         {
            key = 0;  // this will get changed
            info = NULL;   // this will get changed
            parent = NULL;   // this will get changed
            isLeaf = 1; 
 
            // *** we won't use these
            indices = NULL;
            subtrees = NULL;
            numChildren = 0;
         }
      } 

      // SearchForSubtreeIndex
      //    - parameters : key - the integer key we are
      //                          fitting to node range
      //    - return value : integer array index
      //    - finds subtree of this node that this key
      //         belongs in, by using the index values
      //         to determine ranges and then selecting
      //         the subtree based on which range the 
      //         key falls into. The function then returns 
      //         the index of that subtree in the subtree 
      //         pointers array of this node.
      //         Should only be called on a non-leaf, but
      //         will return -1 if called on a leaf. 
      int SearchForSubtreeIndex(int searchKey)
      {
         if (isLeaf == 1)
            return -1;
         else
         { 
            // inspect index array, which is indexed from
            //  1 to b-1 at most, and in general indexed from
            //  1 to (number of children in this node - 1)
            //
            // start search at index 1 of 1...numChildren-1
            int index = 1;

            // Keep going as long as you have not exceeded 
            //   numChildren - 1 (then you would be reading 
            //   garbage values) and your key is greater than
            //   the current index value. Stop if the key is <=
            //   current index value, or else when you have 
            //   determined that your key is greater than *all*
            //   index values (meaning it is in the last subtree).
            while ((index < numChildren) && (searchKey > (*indices)[index]))
               index++;

            // Whatever index you stopped at will also be the index
            //  you want in the subtree pointer array. If you went to
            //  index == numChildren and stopped via the first while-
            //  loop condition, then your key is larger than all 
            //  indices and you do indeed want the rightmost subtree,
            //  which is of course located at the index numChildren. 
            return index; 
         }
      }


      // MatchThisPointer
      //    - parameters : ptr - a pointer to a possible subtree
      //                            of this node
      //    - return value : integer index
      //    - The parameter pointer might be a second pointer to a
      //        subtree of this node. If so, then we should be able
      //        to find a pointer with the same value in our subtree
      //        array, since two pointers to the same subtree should
      //        hold the same address.  If the parameter pointer does
      //        indeed point to a subtree of this node, return the 
      //        index in the subtree array whose cell stores the same
      //        address as the parameter pointer (i.e. if ptr *is* a 
      //        subtree, return the index where that subtree is located 
      //        in this node's subtree array). If ptr does not match 
      //        any subtree address held in this node, it means ptr
      //        does not point to a subtree of this node, and so we 
      //        return -1.
      int MatchThisPointer(BTreeNode* ptr)
      {
         int index = 1;
         
         // search the subtree array, trying to find a match for
         //   this pointer
         while ((index < numChildren+1) && (ptr != (*subtrees)[index]))
            index++;
   
         // if index == numChildren + 1, then we searched the entire
         //  array without finding a match, meaning ptr does not point
         //  to a subtree of this node. Return -1. 
         if (index == numChildren + 1)
            return -1;
         else
            return index;
      }


      // FreeSubtreeCell
      //    - parameters : indexToBeFreed : a subtree index of this node
      //    - Assumes indexToBeFreed is between 1 and numChildren for
      //        this node. Opens up a spot in this node for a new child
      //        subtree by shifting everything in this spot and 
      //        all spots to the right over one location to the right.
      //        However, it is the *user's* responsibility to 
      //        increase the numChildren value by one, since the 
      //        subtree and index arrays are handled independently
      //        and so by not increasing the numChildren value here,
      //        is won't matter whether the index array or the 
      //        subtree array is shifted first. 
      void FreeSubtreeCell(int indexToBeFreed) 
      {
         int travIndex = numChildren; 
         while (travIndex >= indexToBeFreed)
         {
            (*subtrees)[travIndex + 1] = (*subtrees)[travIndex];
            travIndex--;
         }
      }




      // FillSubtreeCell
      //    - parameters : indexToBeFilled : a subtree index of this node
      //    - Assumes indexToBeFilled is between 1 and numChildren for
      //        this node. Closes up this spot in this node by shifting 
      //        everything to the right of this spot over one location to
      //        the left.
      //        However, it is the *user's* responsibility to
      //        decrease the numChildren value by one, since the
      //        subtree and index arrays are handled independently
      //        and so by not decreasing the numChildren value here,
      //        is won't matter whether the index array or the
      //        subtree array is shifted first.
      void FillSubtreeCell(int indexToBeFilled)
      {
         int travIndex = indexToBeFilled;
         while (travIndex < numChildren)
         {
            (*subtrees)[travIndex] = (*subtrees)[travIndex + 1];
            travIndex++;
         }
      }
      




      // FreeIndexCell
      //    - parameters : indexToBeFreed : a index value index of this node
      //    - Assumes indexToBeFreed is between 1 and numChildren-1 for
      //        this node. Opens up a spot in this node for a new node
      //        index value by shifting everything in this spot and
      //        all spots to the right over one location to the right.
      //        However, it is the *user's* responsibility to 
      //        increase the numChildren value by one, since the 
      //        subtree and index arrays are handled independently
      //        and so by not increasing the numChildren value here,
      //        is won't matter whether the index array or the 
      //        subtree array is shifted first. 
      void FreeIndexCell(int indexToBeFreed)
      {
         int travIndex = numChildren-1;
         while (travIndex >= indexToBeFreed)
         {
            (*indices)[travIndex+1] = (*indices)[travIndex];
            travIndex--;
         }
      }



      // FillIndexCell
      //    - parameters : indexToBeFilled : an index value index of this node
      //    - Assumes indexToBeFilled is between 1 and numChildren-1 for
      //        this node. Closes up a spot in this node by shifting 
      //        everything to the right of this spot 
      //        over one location to the left.
      //        However, it is the *user's* responsibility to
      //        decrease the numChildren value by one, since the
      //        subtree and index arrays are handled independently
      //        and so by not decreasing the numChildren value here,
      //        is won't matter whether the index array or the
      //        subtree array is shifted first.
      void FillIndexCell(int indexToBeFilled)
      {
         int travIndex = indexToBeFilled;
         while (travIndex < numChildren - 1)
         {
            (*indices)[travIndex] = (*indices)[travIndex + 1];
            travIndex++;
         }
      }

 
      // *** these used only if node is non-leaf
      Array<int>* indices;          // ptr to array of indices
      Array<BTreeNode*>* subtrees;  // ptr to array of subtrees 
      int numChildren;              // number of children of node


      // *** these used only if node is leaf
      int key;                      // key of leaf  
      Etype* info;                  // ptr to info of leaf


      // *** these used regardless of type of node
      int isLeaf;                 // 1 if leaf, 0 if not
      BTreeNode* parent;          // ptr to parent, null if root
   };

   BTreeNode* root;           // ptr to root node of BTree
   int numKeys;               // total number of values (leaves)
                              //    in BTree

};


#endif
