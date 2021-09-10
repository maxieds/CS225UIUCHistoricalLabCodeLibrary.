// ***********************************************************
// *                                                         *
// *  disjoint.C  (MP7)                                      *
// *                                                         *
// *  Implementation for a disjoint set class                *
// *                                                         *
// *  Written 30 October 1998 by Jason Zych                  *
// *                                                         *
// ***********************************************************

#include "disjoint.h"


// DisjointSets
//    - default constructor
//    - initializes object to be an empty universe
template <class Etype>
DisjointSets<Etype>::DisjointSets()
{
   keyLookup = new SetLookup<UpTreeNode<Etype>*>(); 
   orderList = new List<UpTreeNode<Etype>*>(); 
}



// DisjointSets
//    - copy constructor
//    - parameters : origVal - previously allocated DisjointSets object
//    - initializes object to be a copy of origVal
template <class Etype>
DisjointSets<Etype>::DisjointSets(const DisjointSets<Etype>& origVal)
{
   Copy(origVal);  
}



// DisjointSets
//    - destructor
template <class Etype>
DisjointSets<Etype>::~DisjointSets()
{
   Clear(); 
}



// operator=
//    - parameters : origVal - previously allocated DisjointSets object
//    - return value : reference to this DisjointSets object
//    - sets this object to be a copy of origVal
template <class Etype>
DisjointSets<Etype>& 
DisjointSets<Etype>::operator=(const DisjointSets<Etype>& origVal)
{
   if (this != &origVal)
   {
      Clear(); 
      Copy(origVal); 
   }
   return *this; 
}



// MakeSet
//    - parameters : theKey - the key for a new set element
//                 : theInfo - the info record for a new set element
//    - add a new set to the universe, consisting of one element
//         that has the parameter values as its values
template <class Etype>
void DisjointSets<Etype>::MakeSet(int theKey, Etype theInfo)
{
   UpTreeNode<Etype>* uptr = new UpTreeNode<Etype>(); 
   uptr->key = theKey; 
   uptr->info = theInfo; 
   keyLookup->Insert(theKey, uptr);
   orderList->Tail(); 
   orderList->InsertAfter(uptr); 
}




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
template <class Etype>
int DisjointSets<Etype>::Union(int key1, int key2)
{
   UpTreeNode<Etype> *uptr1, *uptr2; 

   if (keyLookup->Find(key1))
      uptr1 = keyLookup->Retrieve(); 
   else
      return 0; 
   if (keyLookup->Find(key2))
      uptr2 = keyLookup->Retrieve(); 
   else
      return 0; 

   while (uptr1->ptr != NULL) 
      uptr1 = uptr1->ptr; 
   while (uptr2->ptr != NULL)
      uptr2 = uptr2->ptr; 
   
   if (uptr1->count >= uptr2->count)
   {
      uptr1->count += uptr2->count; 
      uptr2->ptr = uptr1; 
   }
   else
   {
      uptr2->count += uptr1->count; 
      uptr1->ptr = uptr2; 
   }
   
   return 1; 

}



// Find
//    - parameters : theKey - the key of the node we want
//    - return value : integer element key
//    - finds what set the element with key theKey is a member
//         of, and returns the key of the representative element
//         of that set. If the key is not found, return 0. (Usage
//         of this class requires that 0 is not an element key.)
template <class Etype>
int DisjointSets<Etype>::Find(int theKey) 
{
   UpTreeNode<Etype>* uptr1; 
   if (keyLookup->Find(theKey))
      uptr1 = keyLookup->Retrieve(); 
   else
      return 0; 
   
   while (uptr1->ptr != NULL)
      uptr1=uptr1->ptr; 
   return uptr1->key; 
}



// Lookup
//    - parameters : theKey - key of the node we want
//                 : result - reference where we will hold the
//                      info record of the node we want
//    - return value: boolean integer
//    - find node with given key. If such a node exists, store its
//         info record in "result" and return 1. Otherwise, return 0.
template <class Etype>
int DisjointSets<Etype>::Lookup(int theKey, Etype& result) 
{
   if (keyLookup->Find(theKey))
   {
      result = keyLookup->Retrieve()->info; 
      return 1; 
   }
   else
      return 0; 
}



// Copy
//    - parameters : origVal - previously allocated DisjointSets object
//    - copies origVal into this object
template <class Etype>
void DisjointSets<Etype>::Copy(const DisjointSets& origVal)
{
   keyLookup = new SetLookup<UpTreeNode<Etype>*>();
   orderList = new List<UpTreeNode<Etype>*>();

   ListIterator<UpTreeNode<Etype>*> iterator1(*(origVal.orderList));
   while (!iterator1.AtEnd())
   {
      MakeSet(iterator1.Retrieve()->key, iterator1.Retrieve()->info);
      iterator1.Forward();
   }

   orderList->Head();
   ListIterator<UpTreeNode<Etype>*> iterator2(*(origVal.orderList));
   while (!iterator2.AtEnd())
   {
      if (iterator2.Retrieve()->ptr == NULL)
         orderList->Retrieve()->ptr = NULL;
      else
      {
         keyLookup->Find(iterator2.Retrieve()->ptr->key);
         orderList->Retrieve()->ptr = keyLookup->Retrieve();
      }
      iterator2.Forward();
      (*orderList)++;
   }

}



// Clear
//    - deletes all internal dynamically allocated memory
template <class Etype>
void DisjointSets<Etype>::Clear()
{
   UpTreeNode<Etype>* deletePtr;
   delete keyLookup;
   orderList->Head();
   for (int i=1; i<=orderList->Length(); i++)
   {
      deletePtr = orderList->Retrieve();
      delete deletePtr;
      (*orderList)++;
   }
   delete orderList;

}

