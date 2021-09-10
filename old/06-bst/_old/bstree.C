// *****************************************************
// *                                                   *
// *   bstree.C (MP5)                                  *   
// *                                                   *
// *   Implementation for a BST class                  *
// *                                                   *
// *   Written by Mark Allen Weiss                     *
// *     Altered by Jason Zych                         *
// *                                                   *
// *****************************************************

#include "bstree.h"



// operator<<
//    - parameters : Out - a reference to an output stream
//                 : outBSTPtr - pointer to the TreeNode we wish 
//                     to print
//    - return value : the output stream
//    - writes the TreeNode data to the output stream
template <class Etype>
ostream& operator<<(ostream& Out, TreeNode<Etype>*& outBSTPtr)
{
   if (outBSTPtr != NULL)
   {
      Out << outBSTPtr->element << endl;
      Out << outBSTPtr->left;
      Out << outBSTPtr->right;
   }
   return Out;
}



  
// operator<<
//    - parameters : Out - a reference to an output stream
//                 : outBST - BSTree we wish to output
//    - return value : the output stream
//    - writes the BSTree data to the output stream
template <class Etype>
ostream& operator<<(ostream& Out, BSTree<Etype>& outBST)
{
   Out << outBST.size << "   " << endl ;
   Out << outBST.root;
   return Out;
}




// operator>>
//    - parameters : In - a reference to an input stream
//                 : inBST - the BSTree we wish to input into
//    - return value : the input stream
//    - reads the data the BSTree needs from the input stream and
//         stores it in the BSTree
template <class Etype>
istream& operator>>(istream& In, BSTree<Etype>& inBST)
{
   Etype inputValue;
   int theSize;


   In >> theSize;
   inBST.size = theSize;
   for (int i = 1; i<=theSize; i++)
   {
      In >> inputValue;
      inBST.Insert(inputValue);
   }
   return In;
}




// BSTree
//    - default constructor
//    - initializes tree to be empty
template <class Etype>
BSTree<Etype>::BSTree() : root(NULL), lastFound(NULL), size(0), 
				recentComp(0), totalComp(0) 
{
   // no additional code needed
}



// BSTree
//    - copy constructor
//    - parameters : origVal - previously allocated BSTree object
//    - initializes object to be a copy of origVal
template <class Etype>
BSTree<Etype>::BSTree(const BSTree<Etype>& origVal)
{
   root = Copy(origVal.root); 
   lastFound = root;
   size = origVal.size;
   recentComp = origVal.recentComp;
   totalComp = origVal.totalComp;
}



// ~BSTree
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
BSTree<Etype>::~BSTree()
{ 
   Make_Empty(root); 
   root = lastFound = NULL;
   size = recentComp = totalComp = 0;
}



// operator=
//    - parameters : origVal - previously allocated BSTree object
//    - return value - const reference to this object  
//    - sets object to be a copy of origVal
template <class Etype>
const BSTree<Etype>& BSTree<Etype>::operator=(const BSTree<Etype>& origVal)
{
   if(this != &origVal) 
   {
      Make_Empty(root);
      root = Copy(origVal.root);
      lastFound = root;
      size = origVal.size;
      recentComp = origVal.recentComp;
      totalComp = origVal.totalComp;
   }
   return *this;
}





// Last
//    - return value : object of the generic type
//    - returns copy of element in the last node looked up;
//         if no node to return, return default object
template <class Etype>
Etype BSTree<Etype>::Last() const
{     
   if (lastFound != NULL)
      return lastFound->element;
   else
   {
      Etype x;
      return x;   // return default Etype; user needs to be able
                  //   to tell the difference
   }
}




// Copy
//    - parameters : TN - a treenode pointer
//    - return value : a treenode pointer
//    - makes a new TreeNode which is a copy of the
//        parameter node, and returns it
template <class Etype>
TreeNode<Etype>* BSTree<Etype>::Copy(const TreeNode<Etype>* TN) 
{
   if (TN != NULL)
      return new TreeNode<Etype>
           (TN->element, Copy(TN->left), Copy(TN->right));
   else
      return NULL;
}




// Make_Empty
//    - parameters : TN - reference to a tree node pointer
//    - recursively clears the tree
template <class Etype>
void BSTree<Etype>::Make_Empty(TreeNode<Etype>*& TN) 
{
   if (TN != NULL) 
   {
      Make_Empty(TN->left);
      Make_Empty(TN->right);
      delete TN;
      TN = NULL;
   }
}



// PreOrder
//    - parameters : TN - reference to a tree node pointer
//    - recursively prints tree in preorder format; assumes Etype has
//       has operator<< defined
template <class Etype>
void BSTree<Etype>::PreOrder(const TreeNode<Etype>* TN) const 
{
   if (TN == NULL)
      return;
   else 
   {
      cout << TN->element << endl; 
      PreOrder(TN->left);
      PreOrder(TN->right);
   }
}




// InOrder
//    - parameters : TN - reference to a tree node pointer
//    - recursively prints tree in inorder format; assumes Etype has
//       has operator<< defined
template <class Etype>
void BSTree<Etype>::InOrder(const TreeNode<Etype>* TN) const 
{
   if (TN == NULL)
      return;
   else 
   {
      InOrder(TN->left);
      cout << TN->element << endl;
      InOrder(TN->right);
   }
}



// PostOrder
//    - parameters : TN - reference to a tree node pointer
//    - recursively prints tree in postorder format; assumes Etype has
//       has operator<< defined
template <class Etype>
void BSTree<Etype>::PostOrder(const TreeNode<Etype>* TN) const 
{
   if (TN == NULL)
      return;
   else 
   {
      PostOrder(TN->left);
      PostOrder(TN->right);
      cout << TN->element << endl;
   }
}
 



// Find
//    - parameters : searchElem - element to be found
//                 : TN - a treenode pointer
//    - return value : TreeNode pointer
//    - returns 1 if searchElem is found in tree, 0 else
//        also, if found, returns pointer to that node
template <class Etype>
TreeNode<Etype>* BSTree<Etype>::Find(const Etype& searchElem, 
					TreeNode<Etype>* TN)
{
   if (TN == NULL)
      return NULL;
   else if (searchElem < TN->element)
   {
      recentComp++; totalComp++;
      return Find(searchElem, TN->left);
   }
   else if (searchElem > TN->element)
   {
      recentComp++; totalComp++;
      return Find(searchElem, TN->right);
   }
   else
      return TN;
}



// Find_Min
//    - parameters : TN - a treenode pointer
//    - return value : TreeNode pointer
//    - returns pointer to the minimum value in tree
//    - (recursive)
template <class Etype>
TreeNode<Etype>* BSTree<Etype>::Find_Min(TreeNode<Etype>* TN) const 
{
   if (TN == NULL)
      return NULL;
   else if (TN->left == NULL)
      return TN;
   else
      return Find_Min(TN->left);
}



// Find_Max
//    - parameters : TN - a treenode pointer
//    - return value : TreeNode pointer
//    - returns pointer to the maximum value in tree
//    - (nonrecursive)
template <class Etype>
TreeNode<Etype>* BSTree<Etype>::Find_Max(TreeNode<Etype>* TN) const 
{
   if (TN != NULL)
      while(TN->right != NULL)
         TN = TN->right;
   return TN;
}



// Insert
//    - parameters : insElem - element to be inserted
//                 : TN - a treenode pointer
//    - recursively inserts insElem into tree (does nothing if
//         it is already there
template <class Etype>
void BSTree<Etype>::Insert(const Etype& insElem, TreeNode<Etype>*& TN) 
{
   if (TN == NULL)
   {
      TN = new TreeNode<Etype>(insElem);
      size++;
   }
   else if (insElem < TN->element)
   {
      recentComp++; totalComp++;
      Insert(insElem, TN->left);
   }
   else if (insElem > TN->element)
   {
      recentComp++; totalComp++; 
      Insert(insElem, TN->right);
   }
   // Else insElem is in the tree already.  We'll do nothing.
}


// Remove
//    - parameters : remElem - element to be removed
//                 : TN - a treenode pointer
//    - recursively removes remElem from tree if it is in tree
template <class Etype>
void BSTree<Etype>::Remove(const Etype & X, TreeNode<Etype>*& TN) 
{
    TreeNode<Etype> *Tmp_Cell;

   if (TN == NULL)
      return;
   else if (X < TN->element )	// Go left.
   {
      recentComp++; totalComp++;
      Remove(X, TN->left );
   }
   else if(X > TN->element)	// Go right.
   {
      recentComp++; totalComp++;
      Remove(X, TN->right);
   }
   else			// Found element to be removed.
   {
      
      if((TN->left != NULL) && (TN->right != NULL))  // Two children.
      {	
         // Replace with smallest in right subtree.
        Tmp_Cell = Find_Min(TN->right);
        TN->element = Tmp_Cell->element;
        recentComp++; totalComp++; 
        Remove(TN->element, TN->right);
      }
      else	// One child or zero children
      {
         Tmp_Cell = TN;
         if (TN->left == NULL )	// Only a right child or no children.
            TN = TN->right;
         else if (TN->right == NULL )	// Only a left child.
            TN = TN->left;
         delete Tmp_Cell;
         size--;
      }
   }
}



