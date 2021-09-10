// *****************************************************
// *                                                   *
// *   bstree.cpp                                      *
// *                                                   *
// *   Implementation for a binary search tree class   *
// *                                                   *
// *   Written October 2004 by Jason Zych              *
// *                                                   *
// *****************************************************


#include "bstree.h"


// ******************* public functions


// BSTree
//    - default constructor
//    - initializes tree to be empty
template <class Etype>
BSTree<Etype>::BSTree() : root(NULL), size(0)
{
   // no additional code needed
}



// BSTree
//    - copy constructor
//    - parameters : origVal - previously allocated BSTree object
//    - initializes object to be a copy of origVal
template <class Etype>
BSTree<Etype>::BSTree(BSTree<Etype> const& origVal)
{
   root = Copy(origVal.root); 
   size = origVal.size;
}



// ~BSTree
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
BSTree<Etype>::~BSTree()
{ 
   Clear(root);
}



// operator=
//    - parameters : origVal - previously allocated BSTree object
//    - return value - const reference to this object  
//    - sets object to be a copy of origVal
template <class Etype>
BSTree<Etype> const& BSTree<Etype>::operator=(BSTree<Etype> const& origVal)
{
   if(this != &origVal) 
   {
      Clear(root);
      root = Copy(origVal.root);
      size = origVal.size;
   }
   return *this;
}



// Clear
//    - clears the tree
template <class Etype>
void BSTree<Etype>::Clear() 
{ 
   Clear(root); 
   root = NULL;
   size = 0;
}


// PreOrder
//    - prints tree in preorder format; assumes Etype has operator<<
//       defined
template <class Etype>
void BSTree<Etype>::PreOrder() const
{
   PreOrder(root);
}


// InOrder
//    - prints tree in inorder format; assumes Etype has operator<<
//       defined
template <class Etype>
void BSTree<Etype>::InOrder() const
{
   InOrder(root);
}




// PostOrder
//    - prints tree in postorder format; assumes Etype has operator<<
//       defined
template <class Etype>
void BSTree<Etype>::PostOrder() const
{
   PostOrder(root);
}



// Find
//    - parameters : searchElem - element to be found
//    - return value : boolean integer
//    - returns 1 if searchElem is found in tree, 0 else
//        also, if found, points internal pointer to that node
template <class Etype>
int BSTree<Etype>::Find(Etype const& searchElem)
{
   return Find(root, searchElem);
}




// Insert
//    - parameters : insElem - element to be inserted
//    - inserts insElem into tree (does nothing if it is
//         already there
template <class Etype>
void BSTree<Etype>::Insert(Etype const& insElem)
{
   Insert(root, insElem);
}




// Remove
//    - parameters : remElem - element to be removed
//    - removes remElem from tree if it is in tree
template <class Etype>
void BSTree<Etype>::Remove(Etype const& remElem)
{
   Remove(root, remElem);
}


// IsEmpty
//    - return value : boolean integer
//    - returns 1 if tree is empty, 0 otherwise
int BSTree<Etype>::IsEmpty() const
{
   return (root == NULL);
}


// Size
//    - return value : size of tree
//    - returns number of elements in tree
int BSTree<Etype>::Size() const
{
   return size;
}


// ***************** private functions


// Copy
//    - parameters : nodePtr - a treenode pointer
//    - return value : a treenode pointer
//    - makes a new TreeNode which is a copy of the
//        parameter node, and returns it
template <class Etype>
   typename BSTree<Etype>::TreeNode* Copy(
               typename BSTree<Etype>::TreeNode const* nodePtr)
{
   if (nodePtr != NULL)
      return new TreeNode<Etype>
           (nodePtr->element, Copy(nodePtr->left), Copy(nodePtr->right));
   else
      return NULL;
}




// Clear
//    - parameters : nodePtr - reference to a tree node pointer
//    - recursively clears the tree
template <class Etype>
void BSTree<Etype>::Clear(typename BSTree<Etype>::TreeNode*& nodePtr)
{
   if (nodePtr != NULL) 
   {
      Clear(nodePtr->left);
      Clear(nodePtr->right);
      delete nodePtr;
      nodePtr = NULL;
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
TreeNode<Etype>* BSTree<Etype>::Find(TreeNode<Etype>* TN, 
                                   const Etype& searchElem)

{
   if (TN == NULL)
      return NULL;
   else if (searchElem < TN->element)
      return Find(searchElem, TN->left);
   else if (searchElem > TN->element)
      return Find(searchElem, TN->right);
   else
      return TN;
}





// Insert
//    - parameters : insElem - element to be inserted
//                 : TN - a treenode pointer
//    - recursively inserts insElem into tree (does nothing if
//         it is already there
template <class Etype>
void BSTree<Etype>::Insert(TreeNode<Etype>*& TN, Etype const & intElem)
{
   if (TN == NULL)
   {
      TN = new TreeNode<Etype>(insElem);
      size++;
   }
   else if (insElem < TN->element)
      Insert(insElem, TN->left);
   else if (insElem > TN->element)
      Insert(insElem, TN->right);
   // Else insElem is in the tree already.  We'll do nothing.
}


// Remove
//    - parameters : remElem - element to be removed
//                 : TN - a treenode pointer
//    - recursively removes remElem from tree if it is in tree
template <class Etype>
void BSTree<Etype>::Remove(TreeeNode<Etype>*& TN, Etype const & X,
{
    TreeNode<Etype> *Tmp_Cell;

   if (TN == NULL)
      return;
   else if (X < TN->element )	// Go left.
      Remove(X, TN->left );
   else if(X > TN->element)	// Go right.
      Remove(X, TN->right);
   else			// Found element to be removed.
   {
      
      if((TN->left != NULL) && (TN->right != NULL))  // Two children.
      {	
         // Replace with smallest in right subtree.
        Tmp_Cell = Find_Min(TN->right);
        TN->element = Tmp_Cell->element;
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



