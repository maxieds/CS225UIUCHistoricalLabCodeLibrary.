// ***********************************************************
// *                                                         *
// *  trie.C                                                 *
// *                                                         *
// *  Implementation for a string-keyed trie class           *
// *                                                         *
// *  Written July 2003 by Jason Zych                        *
// *                                                         *
// ***********************************************************

#include <stddef.h>
#include "trie.h"
#include "asserts.h"



// Find
//    - parameters : searchString - key value to search for
//                 : nodePtr - pointer to the node currently being examined
//    - return value : pair holding boolean "succesful or
//                       not" indicator and associated info
//    - returns (0, Etype()) if string is not in tree; else
//           returns (1, info) where info is the info associated
//           with the string
template <class Etype>
pair<int, Etype> Trie<Etype>::Find(String searchString, TrieNode*& nodePtr)
{
   // your code goes here
   if (nodePtr==NULL)
      return pair<int, Etype>(0, Etype());
   else if (nodePtr->nodeType == 0)
   {
      if (searchString == nodePtr->key)
         return pair<int, Etype>(1, nodePtr->storedInfo);
      else
         return pair<int, Etype>(0, Etype());
   }
   else  // nodePtr->nodeType == 1
   {
      int index = ascIndex(searchString[nodePtr->nodeLevel]);
      return Find(searchString, (*(nodePtr->subtrieArrayPtr))[index]);
   }
}






// Insert
//    - parameters : newString - new key value to add
//                 : info - new info record to add
//                 : nodePtr - pointer to the node currently being examined
//                 : prevLevel - level of the node that contains nodePtr
//    - inserts new values into the trie as a leaf node
template <class Etype>
void Trie<Etype>::Insert(String newString, Etype info, TrieNode*& nodePtr,
                            int prevLevel)
{
   // your code goes here

   if (nodePtr == NULL)    // NULL case
   {
      if (prevLevel == newString.length())
      {
         nodePtr = new TrieNode(newString, info);
         nodePtr->nodeLevel = prevLevel+1;
      }
      else
      {
         nodePtr = new TrieNode();
         nodePtr->nodeLevel = prevLevel+1;
         Insert(newString, info,
             (*(nodePtr->subtrieArrayPtr))[ascIndex(
                       newString[nodePtr->nodeLevel])], nodePtr->nodeLevel);
      }
   }
   else if (nodePtr->nodeType == 0)    // leaf case
   {
      cout << "This key already exists in the trie!" << endl;
      return;
   }
   else    // nodePtr->nodeType == 1, array node case
      Insert(newString, info,
             (*(nodePtr->subtrieArrayPtr))[ascIndex(
                       newString[nodePtr->nodeLevel])], nodePtr->nodeLevel);

}




// Print
//    - parameters : nodePtr - pointer to a subtrie root
//    - prints the leaf info of the subtree rooted at nodePtr
//           in pre-order traversal order
template <class Etype>
void Trie<Etype>::Print(TrieNode*& nodePtr)
{
   // your code goes here

   if (nodePtr == NULL)
      return;
   else if (nodePtr->nodeType == 0)  // leaf
      cout << "Leaf at level " << nodePtr->nodeLevel <<
                " --- key: " << nodePtr->key << "     elem: " <<
                 nodePtr->storedInfo << endl;
   else // nodePtr->nodeType == 1, array
   {
      cout << "Array node at level " << nodePtr->nodeLevel << ":" << endl;
      for (int i = 1; i <= 27; i++)
         if ((*(nodePtr->subtrieArrayPtr))[i] != NULL)
         {
            cout << "From level " << nodePtr->nodeLevel <<
                      " node, inspecting subtrie at cell " << i
                                      << ":" << endl;
            Print((*(nodePtr->subtrieArrayPtr))[i]);
            cout << "Just returned to level " << nodePtr->nodeLevel
                                     << " node." << endl;
         }
   }
}








// *********** public functions


// Trie
//    - default constructor
//    - initializes object to default values
template <class Etype>
Trie<Etype>::Trie()
{
   root = NULL;
}


 
// Trie
//    - copy constructor
//    - parameters : origVal - previously allocated Trie object
//    - initializes object to be a copy of origVal
template <class Etype>
Trie<Etype>::Trie(const Trie<Etype>& origVal)
{
   root = Copy(origVal.root); 
}


// ~Trie
//    - destructor
//    - deletes dynamically allocated memory
template <class Etype>
Trie<Etype>::~Trie()
{
   Clear(root); 
}


// operator=
//    - parameters : origVal - previously allocated Trie object
//    - return value : reference to TrieNode
//    - sets object to be a copy of origVal
template <class Etype>
Trie<Etype>& Trie<Etype>::operator=(const Trie<Etype>& origVal)
{
   if (this!=&origVal)
   {
      Clear(root); 
      root = Copy(origVal.root); 
   }
   return *this; 
}



// Find
//    - parameters : searchString - key value to search for
//    - return value : pair holding boolean "succesful or
//                       not" indicator and associated info
//    - returns (0, Etype()) if string is not in tree; else
//           returns (1, info) where info is the info associated
//           with the string
template <class Etype>
pair<int, Etype> Trie<Etype>::Find(String searchString)
{
   return Find(searchString, root);
}



// Insert
//    - parameters : newString - new key to add
//                 : info - associated info record to add
//    - inserts newString into the trie
template <class Etype>
void Trie<Etype>::Insert(String newString, Etype info)
{
   Insert(newString, info, root, -1); 
}



// Print
//    - prints the leaf info in pre-order traversal order
template <class Etype>
void Trie<Etype>::Print()
{
   Print(root);
}
 



// **************** private functions


// Copy
//    - parameters : origVal - pointer to a patricia tree structure
//    - return value : TrieNode pointer
//    - returns a pointer to a copy of the paramter tree
template <class Etype>
Trie<Etype>::TrieNode* Trie<Etype>::Copy(TrieNode*& nodePtr)
{
   TrieNode* tempPtr; 
   if (nodePtr == NULL)
      return NULL; 
   else if (nodePtr->nodeType == 0)
   {
      tempPtr = new TrieNode(nodePtr->key, nodePtr->storedInfo); 
      tempPtr->nodeLevel = nodePtr->nodeLevel; 
      return tempPtr; 
   }
   else   // nodePtr->nodeType == 1
   {
      tempPtr = new TrieNode(); 
      tempPtr->nodeLevel = nodePtr->nodeLevel;   
      for (int i=1; i<=27; i++)
         (*(tempPtr->subtrieArrayPtr))[i] = 
		Copy((*(nodePtr->subtrieArrayPtr))[i]); 
      return tempPtr; 
   }
   return NULL;
}




// Clear
//    - parameter : origVal - pointer to a patricia tree structure
//    - clears the entire tree
template <class Etype>
void Trie<Etype>::Clear(TrieNode*& nodePtr)
{
   if (nodePtr != NULL)
   {
      if (nodePtr->nodeType == 1)
      {
         for (int i = 1; i <= 27; i++)
            Clear((*(nodePtr->subtrieArrayPtr))[i]);
         delete nodePtr->subtrieArrayPtr;
      }
      delete nodePtr;
   }
}




// ascIndex
//    - parameters : indexChar - a character for which we want an index
//    - return value : integer index
//    - returns the index from 1 - 27 that represents this character
template <class Etype>
int Trie<Etype>::ascIndex(char indexChar)
{
   if ((indexChar>=97) && (indexChar<=122))   // lowercase letter
      return (indexChar-96);  
   else if (indexChar == 0)  // null character
      return 27;
   else
      Assert(0, "Bizarre character in string!");
}



