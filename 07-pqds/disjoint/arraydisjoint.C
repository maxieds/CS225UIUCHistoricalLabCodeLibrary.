// **********************************************
// *                                            *
// *  disjoint.c                                * 
// *                                            *
// *  Implementation of a disjoint set class.   *
// *   Implements a simple Union and Find.      *
// *                                            *
// *  Based on class in Weiss, 1994             *
// *                                            *
// *  Author:  Wendy L. Terry                   *
// *    Date:  25 Oct 1997                      *
// **********************************************

#include <stdio.h>
#include <stdlib.h>
#include "disjoint.h"

// Constructor
DisjointSets::DisjointSets(unsigned int numElems)
{
  SetSize = numElems; 
  SetArray = new Array<int>(SetSize, 1);
  for (int i = 1; i <= SetSize; i++)
    (*SetArray)[i] = 0; 
}


// Copy constructor
//  Creates a new disjoint sets object that is a copy of
//  origDS
DisjointSets::DisjointSets(DisjointSets const & origDS)
{
  SetSize = origDS.SetSize; 
  SetArray = new Array<int>( *(origDS.SetArray) );
}


// Assignment operator -- sets the invoking object to be a
//   new copy of origDS
const DisjointSets& DisjointSets::operator=(DisjointSets const & origDS) 
{
  if (this != &origDS)
    {
      delete SetArray;
      SetSize = origDS.SetSize; 
      SetArray = new Array<int>( *(origDS.SetArray) ); 
    }
  return *this; 
}


// SetUnion creates a union of the sets containing elem1 and
//   elem2.  Note that elem1 and elem2 need not be the roots
//   of their sets. 
void DisjointSets::SetUnion(unsigned int elem1, unsigned int elem2)
{
  unsigned int root1, root2;

  // check if elem1 is root, if not, find the root
  if ( (*SetArray)[elem1] > 0 ) {
    root1 = Find(elem1);
  }else {
    root1 = elem1;
  }

  // same for elem2
  if ( (*SetArray)[elem2] > 0 ) {
    root2 = Find(elem2);
  }else {
    root2 = elem2;
  }

  // set root2 to be child of root1
  (*SetArray)[root2] = root1; 
}


// Find returns the "name" of the set containing elem.
unsigned int DisjointSets::Find(unsigned int elem)
{
  if ( (*SetArray)[elem] <= 0 ) {
    return elem; 
  }else {
    return Find((*SetArray)[elem]);
  }
}

