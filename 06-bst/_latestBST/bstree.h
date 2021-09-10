// *****************************************************
// *                                                   *
// *   bstree.h                                        *
// *                                                   *
// *   Interface for a binary search tree class        *
// *                                                   *
// *   Written October 2004 by Jason Zych              *
// *                                                   * 
// *****************************************************

#ifndef BS_TREE_225 
#define BS_TREE_225

#include <iostream>
#include <cstdlib>
using namespace std;


template <class Etype>
class BSTree
{
public:

   // BSTree
   //    - default constructor
   //    - initializes tree to be empty
   BSTree();


   // BSTree
   //    - copy constructor
   //    - parameters : origVal - previously allocated BSTree object
   //    - initializes object to be a copy of origVal
   BSTree(BSTree const & origVal); 


   // ~BSTree
   //    - destructor
   //    - deletes dynamically allocated memory
   ~BSTree(); 


   // operator=
   //    - parameters : origVal - previously allocated BSTree object
   //    - return value - const reference to this object  
   //    - sets object to be a copy of origVal
   BSTree const & operator=(BSTree const & origVal);


   // Clear
   //    - clears the tree
   void Clear();


   // PreOrder
   //    - prints tree in preorder format; assumes Etype has operator<<
   //       defined
   void PreOrder() const;

 
   // InOrder
   //    - prints tree in inorder format; assumes Etype has operator<<
   //       defined
   void InOrder() const;


   // PostOrder
   //    - prints tree in postorder format; assumes Etype has operator<<
   //       defined
   void PostOrder() const;


   // Find
   //    - parameters : searchElem - element to be found
   //    - return value : integer representing a boolean value
   //    - returns 1 if searchElem is found in tree, 0 else
   int Find(Etype const & searchElem);


   // Insert
   //    - parameters : insElem - element to be inserted
   //    - inserts insElem into tree (does nothing if it is 
   //         already there
   void Insert(Etype const& insElem);


   // Remove
   //    - parameters : remElem - element to be removed 
   //    - removes remElem from tree if it is in tree; does 
   //         nothing if remElem is not in tree 
   void Remove(Etype const & remElem);


   // IsEmpty
   //    - return value : boolean integer
   //    - returns 1 if tree is empty, 0 otherwise
   int IsEmpty() const;


   // Size
   //    - return value : size of tree
   //    - returns number of elements in tree
   int Size() const;

private:

   class TreeNode
   {
   public:

      // TreeNode
      //    - default constructor
      //    - initializes node to default values
      TreeNode() : element(), left(NULL), right(NULL) {}


      // TreeNode
      //    - constructor
      //    - parameters : elmt - initialization element
      //                 : leftPtr - initialization left pointer
      //                 : rightPtr - initialization right pointer
      //    - initializes node to parameter values
      TreeNode(Etype elmt, TreeNode* leftPtr = NULL, 
                TreeNode* rightPtr= NULL ) :
                        element(elmt), left(leftPtr), right(rightPtr) {}

      Etype element;          // element of node
      TreeNode* left;         // pointer to left subtree
      TreeNode* right;        // pointer to right subtree

   };



   // Copy
   //    - parameters : ptr - a treenode pointer
   //    - return value : a treenode pointer
   //    - makes a new TreeNode which is a copy of the
   //        parameter node, and returns it
   typename BSTree<Etype>::TreeNode* Copy(
               typename BSTree<Etype>::TreeNode const * ptr);



   // Clear
   //    - parameters : ptr - reference to a tree node pointer
   //    - recursively clears the tree 
   void Clear(typename BSTree<Etype>::TreeNode * & ptr);



   // PreOrder
   //    - parameters : ptr - reference to a tree node pointer
   //    - recursively prints tree in preorder format; assumes Etype has 
   //       has operator<< defined
   void PreOrder(typename BSTree<Etype>::TreeNode const * ptr) const;



   // InOrder
   //    - parameters : ptr - reference to a tree node pointer
   //    - recursively prints tree in inorder format; assumes Etype has 
   //       has operator<< defined
   void InOrder(typename BSTree<Etype>::TreeNode const * ptr) const;



   // PostOrder
   //    - parameters : ptr - reference to a tree node pointer
   //    - recursively prints tree in postorder format; assumes Etype has 
   //       has operator<< defined
   void PostOrder(typename BSTree<Etype>::TreeNode const * ptr) const;



   // Find
   //    - parameters : searchElem - element to be found
   //                 : ptr - a treenode pointer
   //    - return value : TreeNode pointer 
   //    - returns 1 if searchElem is found in tree, 0 else
   int Find(typename BSTree<Etype>::TreeNode const * ptr, 
                                    Etype const & searchElem) const;



   // Insert
   //    - parameters : insElem - element to be inserted
   //                 : ptr - a treenode pointer
   //    - recursively inserts insElem into tree (does nothing if 
   //         it is already there
   void Insert(typename BSTree<Etype>::TreeNode * & ptr,
                                          Etype const & insElem);


 
   // Remove
   //    - parameters : remElem - element to be removed 
   //                 : ptr - a treenode pointer
   //    - recursively removes remElem from tree if it is in tree
   void Remove(typename BSTree<Etype>::TreeNode * & ptr,
                                          Etype const & remElem);




   typename BSTree<Etype>::TreeNode* root;  // pointer to root node of tree
   int size;                              // number of nodes in tree

};



// *** needed to get templates to work
template <class Etype>
ostream& operator<<(ostream& Out, BSTree<Etype>& outBST);

template <class Etype>
istream& operator>>(istream& In, BSTree<Etype>& inBST);


#endif      
