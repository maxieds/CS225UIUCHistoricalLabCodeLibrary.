// *******************************************************
// *                                                     *
// *  avltree.C                                          *
// *                                                     *
// *  Interface for an AVL tree, which was designed      *
// *  in the spirit of the C++ STL interfaces and        *
// *  which can (among other things) be used to          *
// *  implement the map class.                           *
// *                                                     *
// *  Current version written July 2001 by Jason Zych    *
// *  Adapted from previous work done by Wendy L. Terry  *
// *    and Jason Zych from 1997 - 2001.                 *
// *                                                     *
// *  Still needs some work here and there with const    *
// *  correctness; this should be completed by the end   *
// *  of July 2001.                                      *
// *                                                     *
// *******************************************************

#include <stdlib.h>
#include "avltree.h"
#include "asserts.h"
#include <iostream.h>


// ****************** Constructors, etc.


// avl_tree
//    - default constructor
//    - initializes tree to be empty
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::avl_tree() : treeSize(0), headerNode(new avl_tree_node()) 
{
   // If there are no "real" nodes in the tree, then there are no
   // "leftmost" or "rightmost" nodes for the header to point to. 
   // In this case, we'll make the header point to itself with those
   // pointers.

   // Why? Well, we want a way for iterators to be able to tell when
   // they are on the header node instead of a real node, since they
   // don't have access to the "headerNode" pointer to compare to. We
   // can keep the "height" field of this node at 0 (since we don't have
   // any real height data to store there, as it's not a node that 
   // actually counts as part of the tree), but that is not enough, since
   // real tree leaves will have a height of 0 as well. 

   // However, real tree leaves *must* have null left and right pointers. 
   // So, if we make sure the header node always has non-NULL left and
   // right pointers, then the header node is uniquely identifiable --
   // it (1) always has a height of 0 and non-null left and right pointers,
   // and (2) is the only node in the tree that can ever satisfy both
   // conditions. Now, an iterator can *always* tell when it is
   // pointing to the header node rather than a leaf or root or some other
   // "real" tree node. 

   headerNode->left = headerNode->right = headerNode;
}



// avl_tree
//    - copy constructor
//    - parameters : origVal - previously allocated avl_tree object
//    - initializes object to be a copy of origVal
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::avl_tree(const avl_tree<Ktype, Etype>& origVal)
{
   // first, copy the real nodes of tree
   headerNode = new avl_tree_node(); 
   root() = copy(origVal.root());
   root()->parent = headerNode;
   treeSize = origVal.treeSize;


   // Then, make headerNode->left point to leftmost in tree
   //    and headerNode->right point to rightmost in tree

   avl_tree_node* temp;
   temp = root();
   if (temp != NULL)
   {
      while (temp->left != NULL)
         temp = temp->left;
      headerNode->left = temp;

      temp = root();
      while (temp->right != NULL)
         temp = temp->right;
      headerNode->right = temp;
   }
   else // headerNode points to self if no other nodes
      headerNode->left = headerNode->right = headerNode;
}



// ~avl_tree
//    - destructor
//    - deletes dynamically allocated memory
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::~avl_tree()
{ 
   clear(root()); 
   delete headerNode;
}



// operator=
//    - parameters : origVal - previously allocated avl_tree object
//    - return value - const reference to this object  
//    - sets object to be a copy of origVal
template <class Ktype, class Etype>
const avl_tree<Ktype, Etype>& avl_tree<Ktype, Etype>::operator=(const avl_tree<Ktype, Etype>& origVal)
{
   if(this != &origVal) 
   {
      clear(root());

      // first, copy the real nodes of tree
      root() = copy(origVal.root());
      root()->parent = headerNode;
      treeSize = origVal.treeSize;

      // Then, make headerNode->left point to leftmost in tree
      //    and headerNode->right point to rightmost in tree
      avl_tree_node* temp;
      
      temp = root();
      if (temp != NULL)
      {
         while (temp->left != NULL)
            temp = temp->left;
         headerNode->left = temp;

         temp = root();
         while (temp->right != NULL)
            temp = temp->right;
         headerNode->right = temp;
      }
      else // headerNode points to self if no other nodes
         headerNode->left = headerNode->right = headerNode;
   }
   return *this;
}



 // **************** iterator functions


// begin
//    - return type : iterator
//    - returns iterator to first location in container 
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::iterator avl_tree<Ktype, Etype>::begin()
{
   // if the structure is empty, then we just return 
   //   an iterator to the "null location" 
   if (root() == NULL)
      return end(); 
   else
      return iterator(leftmost());
}


// begin
//    - return type : iterator
//    - returns iterator to first location in container
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::const_iterator avl_tree<Ktype, Etype>::begin() const
{
   // if the structure is empty, then we just return
   //   an iterator to the "null location"
   if (root() == NULL)
      return end();
   else
      return const_iterator(leftmost());
}



// end
//    - return type: iterator
//    - returns iterator to "just after container" location
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::iterator avl_tree<Ktype, Etype>::end()
{ 
   // The header node is, among other things, the implementation
   //   for our "null location". That is one reason it is so 
   //   important for an iterator to be able to recognize when it
   //   is pointing to this header node. 
   return iterator(headerNode); 
}



// end
//    - return type: iterator
//    - returns iterator to "just after container" location
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::const_iterator avl_tree<Ktype, Etype>::end() const
{
   // The header node is, among other things, the implementation
   //   for our "null location". That is one reason it is so
   //   important for an iterator to be able to recognize when it
   //   is pointing to this header node.
   return const_iterator(headerNode);
}


// rbegin
//    - return type : reverse iterator
//    - returns iterator to first reverse location in container
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::reverse_iterator avl_tree<Ktype, Etype>::rbegin()
{
   return reverse_iterator(end());
}




// rbegin
//    - return type : reverse iterator
//    - returns iterator to first reverse location in container
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::const_reverse_iterator avl_tree<Ktype, Etype>::rbegin() const
{
   return const_reverse_iterator(end());
}



// rend
//    - return type: reverse iterator
//    - returns iterator to "just after container" reverse location
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::reverse_iterator avl_tree<Ktype, Etype>::rend()
{
   return reverse_iterator(begin());
}



// rend
//    - return type: reverse iterator
//    - returns iterator to "just after container" reverse location
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::const_reverse_iterator avl_tree<Ktype, Etype>::rend() const
{
   return const_reverse_iterator(begin());
}





// ********** Element collection editing


// insert
//    - parameters : insElem - value to be inserted
//    - return value : a pair that contains an iterator to
//                      the inserted element and a boolean
//                      integer telling us if the insertion
//                      was performed (1) or if we instead
//                      were trying to insert a duplicate key
//                      and thus stopped (0). 
//    - inserts insElem into tree (does nothing if key is
//         already there
template <class Ktype, class Etype>
pair<avl_tree<Ktype, Etype>::iterator, int> 
        avl_tree<Ktype, Etype>::insert(const pair<Ktype, Etype>& insElem)
{ 
   if (count(key(insElem)) == 1)  // this key already appears
      return pair<avl_tree<Ktype, Etype>::iterator, int>
                                     (find(key(insElem)), 0);
   else
      return pair<avl_tree<Ktype, Etype>::iterator, int>
                                (insert(insElem, root(), headerNode), 1); 
}




// insert
//    - parameters : position - an iterator possibly nearby where
//                     we want to make our insertion
//                 : insElem - value to be inserted
//    - return type : iterator to an element
//    - inserts insElem into tree (does nothing if key is
//         already there). The iterator position is supposed
//         to provide us with an insertion "hint", though
//         right now that feature is not implemented and instead
//         the iterator is simply ignored.
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::iterator avl_tree<Ktype, Etype>::insert(iterator position, const pair<Ktype, Etype>& insElem)
{ 
   // We will ignore position for now, as stated in above comment.
   //  A later revision of code *might* make use of this iterator to
   //  speed up searching, but ignoring it does not affect code 
   //  correctness.  
   return insert(insElem, root(), headerNode);  
}




// erase
//    - parameters : position - iterator to a particular value
//    - remove the value indicated by position
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::erase(avl_tree<Ktype, Etype>::iterator position)
{ 
   remove(*position, root(), headerNode); 
}


// erase
//    - parameters : eraseKey - the key of the value we wish to erase
//    - return value : boolean integer
//    - remove the value with key eraseKey, if such a value exists
//         in the tree. Return 1 if you performed a removal, 0 else. 
template <class Ktype, class Etype>
int avl_tree<Ktype, Etype>::erase(const Ktype& eraseKey)
{
   iterator temp = find(eraseKey);
   if (temp == end())
      return 0;
   else
   {
      erase(temp);
      return 1; 
   }
}


// erase
//    - parameters : first - an iterator to the start of a range
//                              in this tree
//                 : last - the end iterator for a range in this 
//                             tree
//    - remove the values in the range [first,last)
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::erase(avl_tree<Ktype, Etype>::iterator first, 
                                      avl_tree<Ktype, Etype>::iterator last)
{
   iterator temp = first;
   while (first != last)
   {
      ++temp;
      erase(first);
      first = temp;
   }
}



// clear
//    - clears the tree
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::clear()
{ 
   clear(root()); 
   root() = NULL; 
   treeSize = 0;
}






 // ********************* Information retrieval



// find
//    - parameters : searchKey - key we are searching for 
//    - return value : an iterator 
//    - if key is the key of a node value pair, return an   
//         iterator to that node. Otherwise, return end(); 
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::iterator 
avl_tree<Ktype, Etype>::find(const Ktype& searchKey)
{
   pair<Ktype, Etype> searchpair; 
   searchpair.first = searchKey;
   avl_tree_node* tempNodePtr = find(searchpair, root()); 
   if (tempNodePtr == NULL)
      return end();
   else
      return iterator(tempNodePtr);
}




// find
//    - parameters : searchKey - key we are searching for
//    - return value : an iterator
//    - if key is the key of a node value pair, return an
//         iterator to that node. Otherwise, return end();
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::const_iterator
avl_tree<Ktype, Etype>::find(const Ktype& searchKey) const
{
   pair<Ktype, Etype> searchpair;
   searchpair.first = searchKey;
   avl_tree_node* tempNodePtr = find(searchpair, root());
   if (tempNodePtr == NULL)
      return end();
   else
      return const_iterator(tempNodePtr);
}




// count
//    - parameters : searchKey - key we are searching for
//    - return value : boolean integer
//    - returns 1 if key is part of a node value pair in
//          tree, 0 else
template <class Ktype, class Etype>
int avl_tree<Ktype, Etype>::count(const Ktype& searchKey) const
{
   const_iterator temp = find(searchKey);
   if (temp == end())
      return 0; 
   else
      return 1;
}



// lower_bound
//    - parameters : searchKey - key we are searching for
//    - return value : an iterator
//    - if key is part of a node value pair in tree, return
//         an iterator to the first node with that searchKey
//         as key. Otherwise, return end().
//            NOTE - for Map, this function is equivalent to
//            Find. However, for Multimap -- also in the STL --
//            you can have many nodes with the same key and
//            so this function would return an iterator to the 
//            first such node. 
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::iterator avl_tree<Ktype, Etype>::lower_bound(const Ktype& searchKey)
{
   return find(searchKey); 
}



// lower_bound
//    - parameters : searchKey - key we are searching for
//    - return value : an iterator
//    - if key is part of a node value pair in tree, return
//         an iterator to the first node with that searchKey
//         as key. Otherwise, return end().
//            NOTE - for Map, this function is equivalent to
//            Find. However, for Multimap -- also in the STL --
//            you can have many nodes with the same key and
//            so this function would return an iterator to the
//            first such node.
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::const_iterator 
avl_tree<Ktype, Etype>::lower_bound(const Ktype& searchKey) const
{
   return find(searchKey);
}




// upper_bound
//    - parameters : searchKey - key we are searching for
//    - return value : an iterator
//         return an iterator to the first node with key greater
//         than searchKey. If there is no such node, return end().
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::iterator 
avl_tree<Ktype, Etype>::upper_bound(const Ktype& searchKey)
{
   avl_tree<Ktype, Etype>::iterator temp = find(searchKey); 
   if (temp != end())
      temp++;
   return temp;
}




// upper_bound
//    - parameters : searchKey - key we are searching for
//    - return value : an iterator
//         return an iterator to the first node with key greater
//         than searchKey. If there is no such node, return end().
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::const_iterator 
avl_tree<Ktype, Etype>::upper_bound(const Ktype& searchKey) const
{
   avl_tree<Ktype, Etype>::const_iterator temp = find(searchKey);
   if (temp != end())
      temp++;
   return temp;
}




// equal_range 
//    - parameters : searchKey - key we are searching for
//    - return value : a pair if iterators
//    - return (1) the iterator which points to searchKey's node, 
//        and (2) the iterator which points to the key *after*
//        searchKey
template <class Ktype, class Etype>
pair<avl_tree<Ktype, Etype>::iterator, avl_tree<Ktype, Etype>::iterator> 
avl_tree<Ktype, Etype>::equal_range(const Ktype& searchKey)
{
   return pair<avl_tree<Ktype, Etype>::iterator, 
                       avl_tree<Ktype, Etype>::iterator>(lower_bound(searchKey), 
						    upper_bound(searchKey)); 

}




// equal_range
//    - parameters : searchKey - key we are searching for
//    - return value : a pair if iterators
//    - return (1) the iterator which points to searchKey's node,
//        and (2) the iterator which points to the key *after*
//        searchKey
template <class Ktype, class Etype>
pair<avl_tree<Ktype, Etype>::const_iterator, 
                                 avl_tree<Ktype, Etype>::const_iterator>
avl_tree<Ktype, Etype>::equal_range(const Ktype& searchKey) const
{
   return pair<avl_tree<Ktype, Etype>::const_iterator,
                       avl_tree<Ktype, Etype>::const_iterator>
                                                   (lower_bound(searchKey),
                                                    upper_bound(searchKey));

}



 
 // ************* Binary search tree functions



// copy
//    - parameters : TN - a treenode pointer
//    - return value : a treenode pointer
//    - makes a new treenode which is a copy of the
//        parameter node -- including subtrees -- and returns it
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::avl_tree_node* 
avl_tree<Ktype, Etype>::copy(const avl_tree_node* TN)
{
    if( TN != NULL )
    {
        avl_tree_node* tempNode = new avl_tree_node
                  (TN->element, (avl_tree_node*) copy(TN->left), 
			(avl_tree_node*) copy(TN->right), NULL, TN->height);
        if (tempNode->left != NULL)
           tempNode->left->parent = tempNode;
        if (tempNode->right != NULL)
           tempNode->right->parent = tempNode;
        return tempNode;
    }
    else
        return NULL;
}



// clear
//    - parameters : TN - reference to a treenode pointer
//    - recursively clears the tree
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::clear(avl_tree_node*& TN)
{
   if (TN != NULL)
   {
      clear(TN->left);
      clear(TN->right);
      delete TN;
      TN = NULL;
   }
}





// insert
//    - parameters : insElem - element to be inserted
//                 : TN - a treenode pointer
//    - recursively inserts insElem into tree (does nothing if
//         it is already there), and corrects balances
template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::iterator 
avl_tree<Ktype, Etype>::insert(const pair<Ktype, Etype>& insElem, 
                          avl_tree_node*& TN, avl_tree_node* parentOfTN)
{
   if (TN == NULL) 
   {
      // Create and insert the node with value insElem
      TN = new avl_tree_node();
      TN->element = insElem;
      TN->height = 0; 
      TN->parent = parentOfTN;
  
      // new code
      if ((treeSize==0) || (key(insElem) < key(headerNode->left->element)))
         headerNode->left = TN;
      if ((treeSize==0) || (key(insElem) > key(headerNode->right->element)))
         headerNode->right = TN;


      treeSize++;
      return iterator(TN);
   }
   else if (key(insElem) < key(TN->element) )
   {
      // insert in the left subtree
      iterator tempIt = insert(insElem, TN->left, TN);

      // check balance condition
      if ( node_height(TN->left) - node_height(TN->right) == 2) 
      {

         // if unbalanced, determine type of rotation
         if (key(insElem)< key(TN->left->element) ) 
         {
            // if inserted in left-most subtree, do single
            single_right_rotation(TN);
         }
         else 
         {
           // if inserted in interior subtree, do double
           double_right_rotation(TN);
         }

      }
      else 
      {
         // if balanced, recalculate height (because an
         //   insertion occured further down the tree)
         calculate_height(TN);
      }
      return tempIt; 
   }
   else if (key(insElem) > key(TN->element) ) 
   {
      // insert in the right subtree
      iterator tempIt = insert(insElem, TN->right, TN);

      // check balance condition
      if ( node_height(TN->right) - node_height(TN->left) == 2) 
      {
         // if unbalanced, determine type of rotation
         if (key(insElem) > key(TN->right->element)) 
         {
            // if inserted in right-most subtree, do single
            single_left_rotation(TN);
         }
         else 
         {
            // if inserted in interior subtree, do double
            double_left_rotation(TN);
         }
      }
      else 
      {
         // if balanced, recalculate height (because an
         //   insertion occured further down the tree)
         calculate_height(TN);
      } 
      return tempIt; 
   }
   // else insElem is in the tree already--do nothing
   else
      return end();
}




// remove
//    - parameters : remElem - element to be removed
//                 : TN - a treenode pointer
//    - recursively removes remElem from tree if it is in tree
//        and corrects balances 
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::remove(const pair<Ktype, Etype>& remElem, 
                           avl_tree_node*& TN, avl_tree_node* parentOfTN)
{
   avl_tree_node *tmp_cell, *tmpCellParent, *newCell;

   if (TN == NULL) 
      return;
   else if (key(remElem) < key(TN->element)) 
   {
      // remove from the left subtree
      remove(remElem, TN->left, TN);

      // check balance condition
      if (node_height(TN->right) - node_height(TN->left) == 2) 
      {
         // if unbalanced, determine type of rotation
         if (node_height(TN->right->right) >= node_height(TN->right->left))
            single_left_rotation(TN);
         else 
            double_left_rotation(TN);
      }
      else 
      {
         // if balanced, recalculate height (in case a removal
         //   and rotation occured further down the tree)
         calculate_height(TN);
      }
   }
   else if (key(remElem) > key(TN->element)) 
   {
      // remove from the right subtree
      remove(remElem, TN->right, TN);

      // check balance condition
      if (node_height(TN->right) - node_height(TN->left) == -2) 
      {
         // if unbalanced, determine type of rotation
         if (node_height(TN->left->left) >= node_height(TN->left->right)) 
            single_right_rotation(TN);
         else 
            double_right_rotation(TN);
      }
      else 
      {
         // if balanced, recalculate height (in case a removal
         //   and rotation occured further down the tree)
         calculate_height(TN);
      }
   }
   else  // remElem == TN->element
   { 
      // 2 child case -- replace TN with its inorder successor node
      if ((TN->left != NULL) && (TN->right != NULL) ) 
      {
         // find inorder successor
         tmp_cell = TN->right;  // we just checked, TN->right isn't NULL
         while (tmp_cell->left != NULL)
            tmp_cell = tmp_cell->left;



         // Put IOS node in TN's place, and put a new node in IOS's
	 // place. We do this because:
         // 
         // 1) moving IOS to TN's place instead of copying IOS value 
         //    to TN ensures that iterators to IOS continue to point
         //    to IOS.
         // 2) moving a new node to IOS's place allows us to recursively
         //   call Remove to remove it, and thus to take advantage of
         //   the recursive balance adjustments. 


         tmpCellParent = tmp_cell->parent;
         newCell = new avl_tree_node();

         // make newCell a copy of tmp_cell
         newCell->right = tmp_cell->right;
         newCell->left = tmp_cell->left;
         newCell->element = tmp_cell->element;
         newCell->height = tmp_cell->height;
         newCell->parent = tmp_cell->parent;
         

         // if inorder successor is left child of its parent
         if (tmpCellParent->left == tmp_cell)
            tmpCellParent->left = newCell;
         // else if inorder successor is right child of its parent
         else if (tmpCellParent->right == tmp_cell)
            tmpCellParent->right = newCell;

 
         // now, newCell has completely taken the place of
         // tmp_cell.

         // make tmp_cell a copy of TN.
         tmp_cell->right = TN->right;
         tmp_cell->parent = TN->parent;
         tmp_cell->left = TN->left;
         tmp_cell->height = TN->height;
         // not element, of course -- TN's element is what
         //  we wanted to remove in the first place!!!
         delete TN; // okay, since tmp_cell holds all data
         TN = tmp_cell;
         TN->left->parent = TN;
         TN->right->parent = TN;

         // now, finally, delete the just added new tmp_cell 
         remove(TN->element, TN->right, TN);
        


         // rebalancing work
         if ((node_height(TN->right) - node_height(TN->left)) == 2)
         {
            if (node_height(TN->right->right) >= node_height(TN->right->left))
               single_left_rotation(TN);
            else
               double_left_rotation(TN);
         }
         else if ((node_height(TN->right) - node_height(TN->left)) == -2)
         {
            if (node_height(TN->left->left) >= node_height(TN->left->right))
               single_right_rotation(TN);
            else
               double_right_rotation(TN);
         }
         else // balance okay
            calculate_height(TN);
      }
      else 
      {
         // X has 0 children or 1 child
         tmp_cell =  TN;
         if ((TN->left == NULL) && (TN->right == NULL)) // no children at all
         {
            TN = NULL;  
         }
         else if ((TN->left == NULL) && (TN->right != NULL)) // no left child
         {
	    TN = TN->right;
            TN->parent = parentOfTN;
         }
         else if ((TN->left != NULL) && (TN->right == NULL))   // no right child
         {
	    TN = TN->left;
            TN->parent = parentOfTN;
         }
         delete tmp_cell;

         // reassign leftmost/rightmost if need be. This could be
         //  more efficient, but due to time constraints I am eliminating
         //  the "if need be" and reassigning *all* the time since coding
         //  it involves merely a copy and paste from op= rather than
	 //  any actual thought and work. 

         avl_tree_node* temp;

         temp = root();
         if (temp != NULL)
         {
            while (temp->left != NULL)
               temp = temp->left;
            headerNode->left = temp;

            temp = root();
            while (temp->right != NULL)
               temp = temp->right;
            headerNode->right = temp;
         }
         else
            headerNode->left = headerNode->right = headerNode;

         treeSize--; 
      }
   }
}






template <class Ktype, class Etype>
avl_tree<Ktype, Etype>::avl_tree_node* 
avl_tree<Ktype, Etype>::find(const pair<Ktype, Etype>& X, 
                     avl_tree<Ktype, Etype>::avl_tree_node* TN) const
{
   if (TN == NULL)
   {
      return NULL;
   }
   else if (key(X) < key(TN->element))
      return find(X, TN->left);
   else if (key(X) > key(TN->element))
      return find(X, TN->right);
   else
      return TN;
}





 // ***************   Additional AVL-specific Helper Functions



// node_height
//    - parameters : TN - a treenode pointer
//    - return value : integer height of node
//    - returns node's height; returns -1 if pointer is NULL
template <class Ktype, class Etype>
int avl_tree<Ktype, Etype>::node_height(avl_tree_node* TN)
{ 
   return (TN ? TN->height : -1); 
}



// calculate_height
//    - parameters : TN - a treenode pointer
//    - correctly sets TN's height; assumes correct
//        subtree heights
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::calculate_height(avl_tree_node* P)
{
   if (node_height(P->left) > node_height(P->right))
      P->height = node_height(P->left) + 1;
   else
      P->height = node_height(P->right) + 1;
}




// Single left rotation
//   Performs a rotation between a node (k2) and its
//    right child, updating the heights of both.
//   Can be called only if k2 has a right child.
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::single_left_rotation( avl_tree_node* &k2 )
{
  avl_tree_node *k1 = k2->right;
  avl_tree_node *parentOfk2 = k2->parent;

  // rotate k1 up to "root" and k2 down to left
  k2->right = k1->left;
  if (k2->right != NULL)
     k2->right->parent = k2;
  k1->left = k2;
  k2->parent = k1;

  k1->parent = parentOfk2;

  calculate_height(k2);
  calculate_height(k1);

  // reset the root 
  k2 = k1;
}


// Double left rotation
//   Performs a right-left rotation, also known as a
//    double left rotation.  Can only be called if k3
//    has a right child and k3's right child has a left
//    child.
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::double_left_rotation( avl_tree_node* &k3 )
{
  single_right_rotation(k3->right);
  single_left_rotation(k3);
}



// Single right rotation
//   Performs a rotation between a node (k2) and its
//    left child, updating the heights of both.
//   Can be called only if k2 has a left child.
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::single_right_rotation( avl_tree_node* &k2 )
{
  avl_tree_node *k1 = k2->left;
  avl_tree_node *parentOfk2 = k2->parent;

  // rotate k1 up to "root" and k2 down to right
  k2->left = k1->right;
  if (k2->left != NULL)
     k2->left->parent = k2;

  k1->right = k2;
  k2->parent = k1;

  k1->parent = parentOfk2;

  // recalculate heights for rotated nodes
  calculate_height(k2);
  calculate_height(k1);

  // reset the root 
  k2 = k1;
}


// Double right rotation
//   Performs a left-right rotation, also known as a
//    double right rotation.  Can only be called if k3
//    has a left child and k3's left child has a right
//    child.
template <class Ktype, class Etype>
void avl_tree<Ktype, Etype>::double_right_rotation(avl_tree_node* &k3 )
{
  single_left_rotation(k3->left);
  single_right_rotation(k3);
}


