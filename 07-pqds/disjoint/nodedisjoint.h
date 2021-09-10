// ***********************************************************
// *                                                         *
// *  disjoint.h                                             *
// *                                                         *
// *  Interface for a disjoint set class                     * 
// *                                                         *
// *  Written 30 October 1998 by Jason Zych                  *
// *                                                         *
// *********************************************************** 

#ifndef _DISJOINT_H
#define _DISJOINT_H

#include <stddef.h>
#include "setlookup.h"
#include "itdoublist.h"



// **************************************************************
// *                                                            *
// *  Class : UpTreeNode                                        *
// *                                                            *
// *  A node class for an up-tree disjoint set implementation   *
// *                                                            *
// *  Written 30 Oct 1998 by Jason Zych                         *
// *                                                            *
// **************************************************************

template <class Etype>
class UpTreeNode
{
private:

   // UpTreeNode
   //    - default constructor
   //    - initializes object to default values
   UpTreeNode() { count = 1; ptr = NULL; }

   int count;         // count of nodes in this set, if this
		      //    is a set root; otherwise meaningless
   UpTreeNode* ptr;   // pointer to parent in up-tree
   int key;           // integer key of node
   Etype info;        // info record of node 
 
   friend class DisjointSets<Etype>; 
};




// **************************************************************
// *                                                            *
// *  Class : DisjointSets                                      *
// *                                                            *
// *  A class implementing a disjoint set universe. Features    *
// *  include lookup by node key and element info retrieval.    * 
// *                                                            *
// *  Written 30 Oct 1998 by Jason Zych                         *
// *                                                            *
// **************************************************************

template <class Etype>
class DisjointSets
{
public:

   // DisjointSets
   //    - default constructor
   //    - initializes object to be an empty universe 
   DisjointSets(); 
  

   // DisjointSets
   //    - copy constructor
   //    - parameters : origVal - previously allocated DisjointSets object
   //    - initializes object to be a copy of origVal  
   DisjointSets(const DisjointSets& origVal); 


   // DisjointSets
   //    - destructor
   //    - deletes dynamically allocated memory
   ~DisjointSets(); 


   // operator=
   //    - parameters : origVal - previously allocated DisjointSets object
   //    - return value : reference to this DisjointSets object
   //    - sets this object to be a copy of origVal
   DisjointSets& operator=(const DisjointSets& origVal); 


   // MakeSet 
   //    - parameters : theKey - the key for a new set element
   //                 : theInfo - the info record for a new set element
   //    - add a new set to the universe, consisting of one element
   //         that has the parameter values as its values  
   void MakeSet(int theKey, Etype theInfo); 


   // Union
   //    - parameters : key1 - key of first element involved in union
   //                 : key2 - key of second element involved in union
   //    - return value : boolean integer
   //    - attempts to union the set that contains key1 and the set
   //         that contains key2. If it turns out that there is either
   //         no node with key1 as a key, or else no node with key2 as
   //         a key, then return 0. Otherwise, perform the union if
   //         the two elements are in different sets, do nothing if 
   //         the two elements are in the same set, and return 1 in 
   //         either case.
   int Union(int key1, int key2); 
  

   // Find
   //    - parameters : theKey - the key of the node we want
   //    - return value : integer element key
   //    - finds what set the element with key theKey is a member
   //         of, and returns the key of the representative element
   //         of that set. If the key is not found, return 0. (Usage
   //         of this class requires that 0 is not an element key.)  
   int Find(int theKey);  


   // Lookup
   //    - parameters : theKey - key of the node we want
   //                 : result - reference where we will hold the
   // 			   info record of the node we want
   //    - return value: boolean integer
   //    - find node with given key. If such a node exists, store its
   //         info record in "result" and return 1. Otherwise, return 0.
   int Lookup(int theKey, Etype& result);  


private:

   // Copy
   //    - parameters : origVal - previously allocated DisjointSets object
   //    - copies origVal into this object
   void Copy(const DisjointSets& origVal); 


   // Clear
   //    - deletes all internal dynamically allocated memory 
   void Clear(); 


   SetLookup<UpTreeNode<Etype>*>* keyLookup;   // pointer to internal hash 
                                               //  table that we will use to 
                                               //  look up UpTreeNodes by 
                                               //  their key

   List<UpTreeNode<Etype>*>* orderList;   // pointer to internal list that 
                                          //  we will use to keep a 
				          //  sequential ordering of all 
                                          //  allocated UpTreeNodes

}; 


#endif


