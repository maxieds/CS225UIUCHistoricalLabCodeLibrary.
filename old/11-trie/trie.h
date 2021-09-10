// ***********************************************************
// *                                                         *
// *  trie.h                                                 *
// *                                                         *
// *  Interface for a string-keyed trie class                *
// *                                                         *
// *  Written July 2003 by Jason Zych                        *
// *                                                         *
// *********************************************************** 

#ifndef _TRIE_H
#define _TRIE_H

#include "string.h"
#include "array.h"
#include "utility225.h"


template <class Etype>
class Trie
{
public:

   // Trie
   //    - default constructor
   //    - initializes object to default values
   Trie(); 

 
   // Trie
   //    - copy constructor
   //    - parameters : origVal - previously allocated Trie object
   //    - initializes object to be a copy of origVal
   Trie(const Trie& origVal); 


   // ~Trie
   //    - destructor
   //    - deletes dynamically allocated memory
   ~Trie(); 


   // operator=
   //    - parameters : origVal - previously allocated Trie object
   //    - return value : reference to TrieNode
   //    - sets object to be a copy of origVal
   Trie& operator=(const Trie& origVal); 

  
   // Find
   //    - parameters : searchString - key value to search for
   //    - return value : pair holding boolean "succesful or
   //                       not" indicator and associated info 
   //    - returns (0, Etype()) if string is not in tree; else 
   //           returns (1, info) where info is the info associated
   //           with the string
   pair<int,  Etype> Find(String searchString); 



   // Insert
   //    - parameters : newString - new key to add
   //                 : info - associated info record to add
   //    - inserts newString into the trie 
   void Insert(String newString, Etype info); 



   // Print
   //    - prints the leaf info in pre-order traversal order
   void Print();


private:

   class TrieNode
   {
   public:

      // TrieNode
      //    - default constructor
      //    - initializes node to default value as internal array node
      TrieNode()
      {
         nodeLevel = 0;
         nodeType = 1;   // arrayNode
         subtrieArrayPtr = new Array<TrieNode*>(1, 27);
         subtrieArrayPtr->Initialize(NULL);
      }


      // TrieNode
      //    - constructor
      //    - parameters : initString - string key initializer
      //                 : info - associated info record
      //    - initializes node to be tree leaf
      TrieNode(String initString, Etype info)
      {
         nodeLevel = 0;
         nodeType = 0;  // leaf
         subtrieArrayPtr = NULL;
         key = initString;
         storedInfo = info;
      } 


      // ~TrieNode
      //    - destructor
      //    - deletes dynamically allocated memory
      ~TrieNode()
      {
         delete subtrieArrayPtr;
      }


      int nodeLevel;                     // level of the node
      int nodeType;                      // type of the node
      Array<TrieNode*>* subtrieArrayPtr; // ptr to array in array nodes
      String key;                        // string key in leaf nodes
      Etype storedInfo;
   };


   TrieNode* root;     // pointer to root node of patricia tree


   // Copy 
   //    - parameters : origVal - pointer to a patricia tree structure
   //    - return value : TrieNode pointer
   //    - returns a pointer to a copy of the paramter tree  
   TrieNode* Copy(TrieNode*& origVal); 


   // Clear
   //    - parameter : origVal - pointer to a patricia tree structure 
   //    - clears the entire tree
   void Clear(TrieNode*& origVal); 


   // ascIndex
   //    - parameters : indexChar - a character for which we want an index
   //    - return value : integer index
   //    - returns the index from 1 - 27 that represents this character
   int ascIndex(char indexChar);



   // Find
   //    - parameters : searchString - key value to search for
   //                 : nodePtr - pointer to the node currently being examined
   //    - return value : pair holding boolean "succesful or
   //                       not" indicator and associated info
   //    - returns (0, Etype()) if string is not in tree; else
   //           returns (1, info) where info is the info associated
   //           with the string
   pair<int, Etype> Find(String searchString, TrieNode*& nodePtr);


   // Insert 
   //    - parameters : newString - new key value to add
   //                 : info - new info record to add
   //                 : nodePtr - pointer to the node currently being examined
   //                 : prevLevel - level of the node that contains nodePtr
   //    - inserts newString into the trie as a leaf node
   void Insert(String newString, Etype info, TrieNode*& nodePtr, 
                                                       int prevLevel); 


   // Print
   //    - parameters : nodePtr - pointer to a subtrie root
   //    - prints the leaf info of the subtree rooted at nodePtr
   //           in pre-order traversal order
   void Print(TrieNode*& nodePtr);


};

#endif





