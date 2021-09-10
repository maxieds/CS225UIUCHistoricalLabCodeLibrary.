// ******************************************************
// *                                                    *
// *  bstTest.cpp                                       *
// *                                                    *
// *  Short test file for BST class                     *
// *                                                    *
// *  Written October 2004 by Jason Zych                *
// *                                                    *
// ******************************************************


#include <iostream>
#include <cstddef>
using namespace std;

#include "bstree.h"

int main()
{
   BSTree<int> testTree;

   cout << "*** Inserting values 0-22 into the tree" << endl << endl;  
   int count = 0;
   int i = 12;
   while (count < 23)
   {
      testTree.Insert(i);
      i = i + 17;
      i = i % 23;
      count++;
   } 
   cout << endl << endl;

   cout << "*** Searching for all non-negative multiples of 3 <= 34" << endl;
   for (int j = 0; j <= 34; j = j + 3)
      cout << testTree.Find(j) << endl;
   cout << endl << endl;
 
   cout << "*** Preorder traversal of tree:" << endl; 
   testTree.PreOrder();
   cout << endl;

   cout << "*** Inorder traversal of tree:" << endl;
   testTree.InOrder();
   cout << endl;

   cout << "*** Postorder traversal of tree:" << endl;
   testTree.PostOrder();
   cout << endl;

   cout << "Size of tree is: " << testTree.Size() << endl;
   cout << endl;
   cout << "*** Testing IsEmpty" << endl;
   cout << testTree.IsEmpty() << endl;

   cout << "*** Making copies..." << endl;
   BSTree<int> copyTree(testTree);
   BSTree<int> equalTree;
   int number = 10;
   equalTree.Insert(number);
   equalTree.PreOrder();
   equalTree = testTree; 
   cout << endl;

   cout << "*** Clearing original tree:" << endl;
   testTree.Clear();

   cout << "*** Preorder traversal of original tree:" << endl;
   testTree.PreOrder();
   cout << endl;

   cout << "*** Inorder traversal of original tree:" << endl;
   testTree.InOrder();
   cout << endl;

   cout << "*** Postorder traversal of original tree:" << endl;
   testTree.PostOrder();
   cout << endl;

   cout << "*** Preorder traversal of copy tree:" << endl;
   copyTree.PreOrder();
   cout << endl;

   cout << "*** Preorder traversal of equal tree:" << endl;
   equalTree.PreOrder();
   cout << endl;

   cout << "*** Removing values from the tree" << endl << endl;
   count = 0;
   i = 1;
   while (count < 23)
   {
      copyTree.Remove(i);
      cout << "Removed the value " << i << " from copy tree." << endl;
      copyTree.PreOrder();
      cout << endl;
      i = i + 19;
      i = i % 23;
      count++;
   }
   cout << endl << endl;

   return 0;
}


