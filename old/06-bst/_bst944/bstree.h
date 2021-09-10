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
   //    - return value : boolean integer
   //    - returns 1 if searchElem is found in tree, 0 else
   //        also, if found, points internal pointer to that node 
   int Find(Etype const& searchElem);





   // Insert
   //    - parameters : insElem - element to be inserted
   //    - inserts insElem into tree (does nothing if it is 
   //         already there
   void Insert(Etype const& insElem);





   // Remove
   //    - parameters : remElem - element to be removed 
   //    - removes remElem from tree if it is in tree
   void Remove(Etype const& remElem);




   // IsEmpty
   //    - return value : boolean integer
   //    - returns 1 if tree is empty, 0 otherwise
   int IsEmpty() const;


   // Size
   //    - return value : size of tree
   //    - returns number of elements in tree
   int Size() const;



 

   
   // operator<<
   //    - parameters : Out - a reference to an output stream
   //                 : outBST - BSTree we wish to output
   //    - return value : the output stream
   //    - writes the BSTree data to the output stream
   friend ostream& operator<<(ostream& Out, BSTree<Etype>& outBST); 



   // operator>>
   //    - parameters : In - a reference to an input stream
   //                 : InBST - the BSTree we wish to input into 
   //    - return value : the input stream
   //    - reads the data the BSTree needs from the input stream and
   //         stores it in the BSTree 
   friend istream& operator>>(istream& In, BSTree<Etype>& inBST); 

 

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
   //    - parameters : TN - a treenode pointer
   //    - return value : a treenode pointer
   //    - makes a new TreeNode which is a copy of the
   //        parameter node, and returns it
   typename BSTree<Etype>::TreeNode* Copy(
               typename BSTree<Etype>::TreeNode const* nodePtr);



   // Clear
   //    - parameters : TN - reference to a tree node pointer
   //    - recursively clears the tree 
   void Clear(typename BSTree<Etype>::TreeNode*& TN);



   // PreOrder
   //    - parameters : TN - reference to a tree node pointer
   //    - recursively prints tree in preorder format; assumes Etype has 
   //       has operator<< defined
   void PreOrder(const TreeNode<Etype>* TN) const;



   // InOrder
   //    - parameters : TN - reference to a tree node pointer
   //    - recursively prints tree in inorder format; assumes Etype has 
   //       has operator<< defined
   void InOrder(const TreeNode<Etype>* TN) const;



   // PostOrder
   //    - parameters : TN - reference to a tree node pointer
   //    - recursively prints tree in postorder format; assumes Etype has 
   //       has operator<< defined
   void PostOrder(const TreeNode<Etype>* TN) const;



   // Find
   //    - parameters : searchElem - element to be found
   //                 : TN - a treenode pointer
   //    - return value : TreeNode pointer 
   //    - returns 1 if searchElem is found in tree, 0 else
   //        also, if found, returns pointer to that node 
   TreeNode<Etype>* Find(const Etype& searchElem, TreeNode<Etype>* TN);



   // Find_Min
   //    - parameters : TN - a treenode pointer
   //    - return value : TreeNode pointer 
   //    - returns pointer to the minimum value in tree 
   TreeNode<Etype>* Find_Min(TreeNode<Etype>* TN) const;



   // Find_Max
   //    - parameters : TN - a treenode pointer 
   //    - return value : TreeNode pointer
   //    - returns pointer to the maximum value in tree
   TreeNode<Etype>* Find_Max(TreeNode<Etype>* TN) const;



   // Insert
   //    - parameters : insElem - element to be inserted
   //                 : TN - a treenode pointer
   //    - recursively inserts insElem into tree (does nothing if 
   //         it is already there
   void Insert(const Etype& insElem, TreeNode<Etype>*& TN);


 
   // Remove
   //    - parameters : remElem - element to be removed 
   //                 : TN - a treenode pointer
   //    - recursively removes remElem from tree if it is in tree
   void Remove(const Etype& remElem, TreeNode<Etype>*& TN);



   TreeNode<Etype>* root;          // pointer to root node of tree
   TreeNode<Etype>* lastFound;     // pointer to node that was located
                                   //   during last search
   int size;                       // number of nodes in tree


   int recentComp;          // to hold the number of comparisons
                            //   in the last operation

   int totalComp;           // to hold the total number of comparison
			    //   since the last clearing of the statistics 

};



// *** needed to get templates to work
template <class Etype>
ostream& operator<<(ostream& Out, BSTree<Etype>& outBST);

template <class Etype>
istream& operator>>(istream& In, BSTree<Etype>& inBST);


#endif      
