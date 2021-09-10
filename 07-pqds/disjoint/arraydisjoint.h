// **********************************************
// *                                            *
// *  disjoint.h                                * 
// *                                            *
// *  Interface file for a disjoint set class.  *
// *   Implements a simple Union and Find.      *
// *                                            *
// *  Based on class in Weiss, 1994             *
// *                                            *
// *  Author:  Wendy L. Terry                   *
// *    Date:  25 Oct 1997                      *
// **********************************************

#ifndef _DISJSETS_H
#define _DISJSETS_H

#include "array.h"

class DisjointSets
{
public:

  // Constructors
  DisjointSets(unsigned int numElems = 10); 
  DisjointSets(DisjointSets const & origDS); 
 
  // Destructor
  ~DisjointSets() { delete SetArray; }

  // Assignment operator -- sets the invoking object to be a
  //   new copy of origDS
  const DisjointSets& operator=(DisjointSets const & origDS); 

  // SetUnion creates a union of the sets containing elem1 and
  //   elem2.  Note that elem1 and elem2 need not be the roots
  //   of their sets. 
  virtual void SetUnion(unsigned int elem1, unsigned int elem2); 

  // Find returns the "name" of the set containing elem.
  virtual unsigned int Find(unsigned int elem); 

protected:

  Array<int> *SetArray; 
  int SetSize;
}; 

#endif 



