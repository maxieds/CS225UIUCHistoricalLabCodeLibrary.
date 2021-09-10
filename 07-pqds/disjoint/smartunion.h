// **********************************************
// *                                            *
// *  smartunion.h                              * 
// *                                            *
// *  Contains the interfaces for two disjoint  *
// *   set classes that perform smart unions.   *
// *   The class that does union by size also   *
// *   does find with compression.              *
// *                                            *
// *  Author:  Wendy L. Terry                   *
// *    Date:  25 Oct 1997                      *
// **********************************************

#ifndef _DSHEIGHT_H
#define _DSHEIGHT_H

#include "arraydisjoint.h"
//
// Class: DSetsByHeight
// Derived from: DisjointSets
//
// Implements a disjoint sets class that uses union by
//  height.  Overrides the SetUnion from DisjointSets,
//  but uses everything else.
//
// Height is represented by the negation of a set's actual
//  height.  Every set begins with height 0.  A union only
//  effects a height change when two sets of equal height
//  are combined.
//
class DSetsByHeight : public DisjointSets
{
public:

  // Constructor -- same as for base class
  DSetsByHeight(unsigned int numElems = 10)
    : DisjointSets(numElems) {}

  // Destructor -- same as for base class
  ~DSetsByHeight() {}

  // SetUnion does a union by height for the sets that contain
  //   elem1 and elem2.  IE, the shorter set's tree will become
  //   the child of the taller set's tree.  Note that elem1 and
  //   elem2 need not be the roots of their sets.
  void SetUnion(unsigned int elem1, unsigned int elem2); 
}; 

#endif 

#ifndef _DSSIZE_H
#define _DSSIZE_H

#include "disjoint.h"
//
// Class: DSetsBySize
// Derived from: DisjointSets
//
// Implements a disjoint sets class that uses union by
//  size.  Overrides the constructor and SetUnion functions
//  from DisjointSets.  Additionally, provides a new Find
//  that does compression.
//
// Size is represented by the negation of a set's actual size.
//  Thus, every set begins with the size -1, and then when
//  a union occurs, the new size is the sum of the two old
//  sizes.
//
class DSetsBySize : public DisjointSets
{
public:

  // Constructor -- must be redefined
  DSetsBySize(unsigned int numElems = 10); 

  // Destructor -- same as for base class
  ~DSetsBySize() {}

  // SetUnion does a union by size for the sets that contain
  //   elem1 and elem2.  IE, the smaller set's tree will become
  //   the child of the larger set's tree.  Note that elem1 and
  //   elem2 need not be the roots of their sets.
  void SetUnion(unsigned int elem1, unsigned int elem2);

  // Find returns the "name" of the set containing elem.
  //   The tree containing elem will be compressed.
  unsigned int Find(unsigned int elem); 
}; 

#endif 
