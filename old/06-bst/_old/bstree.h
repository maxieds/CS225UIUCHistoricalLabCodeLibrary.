// *****************************************************
// *                                                   *
// *   bstree.h (MP5)                                  *   
// *                                                   *
// *   Interface for a BST class                       * 
// *                                                   *
// *   Written by Mark Allen Weiss                     *
// *     Altered by Jason Zych                         * 
// *                                                   * 
// *****************************************************

#ifndef _BS_TREE 
#define _BS_TREE 

#include <iostream.h>
#include <stdlib.h>


// **************************************************************
// *                                                            *
// *  Class : TreeNode                                          *
// *                                                            *
// *  A node class for the BST implementation                   *
// *                                                            *
// **************************************************************

template <class Etype>
class TreeNode 
{
protected:
   
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
   TreeNode(Etype elmt, TreeNode* leftPtr = NULL, TreeNode* rightPtr= NULL ) :
            element(elmt), left(leftPtr), right(rightPtr) {}


   Etype element;          // element of node
   TreeNode* left;         // pointer to left subtree
   TreeNode* right;        // pointer to right subtree

   // BSTree is a friend class so that the BSTree has access to 
   // the protected node data
   friend class BSTree<Etype>;


   // operator<<
   //    - parameters : Out - a reference to an output stream
   //                 : outBSTPtr - pointer to the TreeNode we wish
   //                     to print 
   //    - return value : the output stream
   //    - writes the TreeNode data to the output stream
   friend ostream& operator<<(ostream& Out, TreeNode<Etype>*& outBSTPtr);

};




// **************************************************************
// *                                                            *
// *  Class : Tree                                              *
// *                                                            *
// *  The interface class for the BST implementation            * 
// *                                                            *
// **************************************************************

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
   BSTree(const BSTree& origVal); 


   // ~BSTree
   //    - destructor
   //    - deletes dynamically allocated memory
   virtual ~BSTree(); 


   // operator=
   //    - parameters : origVal - previously allocated BSTree object
   //    - return value - const reference to this object  
   //    - sets object to be a copy of origVal
   const BSTree& operator=(const BSTree& origVal);



   // Make_Empty
   //    - clears the tree 
   void Make_Empty() 
      { Make_Empty(root); root = lastFound = NULL; size=0; }



   // PreOrder
   //    - prints tree in preorder format; assumes Etype has operator<<
   //       defined
   void PreOrder() const
        { PreOrder(root); }


 
   // InOrder
   //    - prints tree in inorder format; assumes Etype has operator<<
   //       defined
   void InOrder() const
        { InOrder(root); }



   // PostOrder
   //    - prints tree in postorder format; assumes Etype has operator<<
   //       defined
   void PostOrder() const
        { PostOrder(root); }


   // Find
   //    - parameters : searchElem - element to be found
   //    - return value : boolean integer
   //    - returns 1 if searchElem is found in tree, 0 else
   //        also, if found, points internal pointer to that node 
   virtual int Find(const Etype& searchElem)
        { recentComp = 0; return int(lastFound = Find(searchElem, root)); }

   // **** Note  ^^^^^^^^ the setting of the "recent comparisons"
   //      to 0 before running the algorithm. 




   // Find_Min
   //    - return value : boolean integer
   //    - returns 1 if there is a minimum element, 0 else;
   //        also, if there is one, internal pointer points
   //        to it
   virtual int Find_Min()
        { return int(lastFound = Find_Min(root)); }


   // Find_Max
   //    - return value : boolean integer
   //    - returns 1 if there is a maximum element, 0 else;
   //        also, if there is one, internal pointer points
   //        to it
   virtual int Find_Max()
        { return int(lastFound = Find_Max(root)); }



   // Insert
   //    - parameters : insElem - element to be inserted
   //    - inserts insElem into tree (does nothing if it is 
   //         already there
   virtual void Insert(const Etype& insElem)
        { recentComp = 0; Insert(insElem, root); }

   // **** Note  ^^^^^^^^ the setting of the "recent comparisons"
   //      to 0 before running the algorithm. 





   // Remove
   //    - parameters : remElem - element to be removed 
   //    - removes remElem from tree if it is in tree
   virtual void Remove(const Etype& remElem)
        { recentComp = 0; Remove(remElem, root); }

   // **** Note  ^^^^^^^^ the setting of the "recent comparisons"
   //      to 0 before running the algorithm. 





   // IsEmpty
   //    - return value : boolean integer
   //    - returns 1 if tree is empty, 0 otherwise
   virtual int IsEmpty() const
        { return (root == NULL); }


   // Size
   //    - return value : size of tree
   //    - returns number of elements in tree
   int Size() const 
        { return size;}

 
   // Last
   //    - return value : object of the generic type
   //    - returns copy of element in the last node looked up;
   //         if no node to return, return default object 
   virtual Etype Last() const;


   // ClearStats
   //    - clears statistics
   void ClearStats() 
        { recentComp = totalComp = 0; }
 

   // ReturnTotal
   //    - return type : integer value
   //    - returns value in total comparisons field
   int ReturnTotal() const
        {  return totalComp; }


   // ReturnRecent
   //    - return type : integer value
   //    - returns value in recent comparisons field
   int ReturnRecent() const
       { return recentComp; }


   
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

 

protected:

   // Copy
   //    - parameters : TN - a treenode pointer
   //    - return value : a treenode pointer
   //    - makes a new TreeNode which is a copy of the
   //        parameter node, and returns it
   TreeNode<Etype>* Copy(const TreeNode<Etype>* TN);



   // Make_Empty
   //    - parameters : TN - reference to a tree node pointer
   //    - recursively clears the tree 
   void Make_Empty(TreeNode<Etype>*& TN);



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
