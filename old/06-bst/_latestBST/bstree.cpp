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
template <class Etype>
int BSTree<Etype>::IsEmpty() const
{
   return (root == NULL);
}


// Size
//    - return value : size of tree
//    - returns number of elements in tree
template <class Etype>
int BSTree<Etype>::Size() const
{
   return size;
}


// ***************** private functions


// Copy
//    - parameters : ptr - a treenode pointer
//    - return value : a treenode pointer
//    - makes a new TreeNode which is a copy of the
//        parameter node, and returns it
template <class Etype>
typename BSTree<Etype>::TreeNode* 
        BSTree<Etype>::Copy(typename BSTree<Etype>::TreeNode const * ptr)
{
   if (ptr != NULL)
   {
      typename BSTree<Etype>::TreeNode * temp =
              new typename BSTree<Etype>::TreeNode(ptr->element);
      temp->left = Copy(ptr->left);
      temp->right = Copy(ptr->right);
      return temp;
   }
   else
      return NULL;
}




// Clear
//    - parameters : ptr - reference to a tree node pointer
//    - recursively clears the tree
template <class Etype>
void BSTree<Etype>::Clear(typename BSTree<Etype>::TreeNode * & ptr)
{
   if (ptr != NULL) 
   {
      Clear(ptr->left);
      Clear(ptr->right);
      delete ptr;
      ptr = NULL;
   }
}




// PreOrder
//    - parameters : ptr - reference to a tree node pointer
//    - recursively prints tree in preorder format; assumes Etype has
//       has operator<< defined
template <class Etype>
void BSTree<Etype>::PreOrder(
                 typename BSTree<Etype>::TreeNode const * ptr) const
{
   if (ptr != NULL)
   {
      cout << ptr->element << endl;
      PreOrder(ptr->left);
      PreOrder(ptr->right);
   }
}



// InOrder
//    - parameters : ptr - reference to a tree node pointer
//    - recursively prints tree in inorder format; assumes Etype has
//       has operator<< defined
template <class Etype>
void BSTree<Etype>::InOrder(
                 typename BSTree<Etype>::TreeNode const * ptr) const
{
   if (ptr != NULL)
   {
      InOrder(ptr->left);
      cout << ptr->element << endl;
      InOrder(ptr->right);
   }
}



// PostOrder
//    - parameters : ptr - reference to a tree node pointer
//    - recursively prints tree in postorder format; assumes Etype has
//       has operator<< defined
template <class Etype>
void BSTree<Etype>::PostOrder(
               typename BSTree<Etype>::TreeNode const * ptr) const
{
   if (ptr != NULL)
   {
      PostOrder(ptr->left);
      PostOrder(ptr->right);
      cout << ptr->element << endl;
   }
}




// Find
//    - parameters : searchElem - element to be found
//                 : ptr - a treenode pointer
//    - return value : TreeNode pointer
//    - returns 1 if searchElem is found in tree, 0 else
template <class Etype>
int BSTree<Etype>::Find(typename BSTree<Etype>::TreeNode const * ptr,
                                   Etype const & searchElem) const
{
   if (ptr == NULL)
      return 0;
   else if (searchElem == ptr->element)
      return 1;
   else if (searchElem < ptr->element)
      return Find(ptr->left, searchElem);
   else //   searchElem > ptr->element
      return Find(ptr->right, searchElem);
}






// Insert
//    - parameters : insElem - element to be inserted
//                 : ptr - a treenode pointer
//    - recursively inserts insElem into tree (does nothing if
//         it is already there
template <class Etype>
void BSTree<Etype>::Insert(typename BSTree<Etype>::TreeNode * & ptr,
                                             Etype const & insElem)
{
   if (ptr == NULL)
   {
      ptr = new typename BSTree<Etype>::TreeNode(insElem);
      size++;
   }
   else if (insElem < ptr->element)
      Insert(ptr->left, insElem);
   else if (insElem > ptr->element)
      Insert(ptr->right, insElem);
   // Else insElem is in the tree already.  We'll do nothing.
}



// Remove
//    - parameters : remElem - element to be removed
//                 : ptr - a treenode pointer
//    - recursively removes remElem from tree if it is in tree
template <class Etype>
void BSTree<Etype>::Remove(typename BSTree<Etype>::TreeNode * & ptr,
                                          Etype const & remElem)

{
   if (ptr == NULL)
      return;
   else if (remElem < ptr->element )    // Go left.
      Remove(ptr->left, remElem);
   else if (remElem > ptr->element)     // Go right.
      Remove(ptr->right, remElem);
   else	                                // Found element to be removed.
   {
      typename BSTree<Etype>::TreeNode* tempPtr;

      if ((ptr->left != NULL) && (ptr->right != NULL))  // Two children.
      {	
         // Replace with smallest in right subtree.
         tempPtr = ptr->right;
         while (tempPtr->left != NULL)
            tempPtr = tempPtr->left;
         ptr->element = tempPtr->element;
         Remove(ptr->right, ptr->element);
      }
      else if ((ptr->left == NULL) && (ptr->right == NULL))  // no children.
      {
         delete ptr;
         ptr = NULL;
      }
      else // one child
      {
         tempPtr = ptr;
         if (ptr->left == NULL)	     // only a right child 
            ptr = ptr->right;
         else // ptr->right == NULL  // only a left child
            ptr = ptr->left;
         delete tempPtr;
      }
     
      size--;
   }
}



