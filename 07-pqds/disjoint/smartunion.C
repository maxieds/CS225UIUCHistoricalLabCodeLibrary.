// **********************************************
// *                                            *
// *  smartunion.C                              * 
// *                                            *
// *  Contains the function definitions for the *
// *   set classes that perform smart unions.   *
// *                                            *
// *  Author:  Wendy L. Terry                   *
// *    Date:  25 Oct 1997                      *
// **********************************************

#include "smartunion.h"

//-------------------------
// DSetsByHeight functions
//-------------------------

// SetUnion does a union by height for the sets that contain
//   elem1 and elem2.  IE, the shorter set's tree will become
//   the child of the taller set's tree.  Note that elem1 and
//   elem2 need not be the roots of their sets.
void DSetsByHeight::SetUnion(unsigned int elem1, unsigned int elem2)
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

  if ( (*SetArray)[root2] < (*SetArray)[root1] ) {
    // root2 has greater height, since height is given as
    //  the negation of the actual height
    (*SetArray)[root1] = root2;

  }else {
    // root1 has greater height or they have equal heights

    if ( (*SetArray)[root1] == (*SetArray)[root2] ) {
      // increase root1's height
      (*SetArray)[root1]--;
    }

    (*SetArray)[root2] = root1;
  }
}


//-------------------------
// DSetsBySize functions
//-------------------------

// Constructor
//   Rewritten so all sets start off with size -1 rather than 0.
DSetsBySize::DSetsBySize(unsigned int numElems)
{
  SetSize = numElems;
  SetArray = new Array<int>(SetSize, 1);
  for ( int i = 1; i <= SetSize; i++ ) {
    (*SetArray)[i] = -1;
  }
}


// SetUnion does a union by size for the sets that contain
//   elem1 and elem2.  IE, the smaller set's tree will become
//   the child of the larger set's tree.  Note that elem1 and
//   elem2 need not be the roots of their sets.
void DSetsBySize::SetUnion(unsigned int elem1, unsigned int elem2)
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

  if ( (*SetArray)[root2] < (*SetArray)[root1] ) {
    // root2 has greater size, since size is given as
    //  the negation of actual size

    // find the size of the union, and make root1 the child of root2
    (*SetArray)[root2] += (*SetArray)[root1];
    (*SetArray)[root1] = root2;

  }else {  // root1 has greater height or they have equal heights

    // find the size of the union, and make root2 the child of root1
    (*SetArray)[root1] += (*SetArray)[root2];
    (*SetArray)[root2] = root1;
  }
}


// Find returns the "name" of the set containing elem.
//   The tree containing elem will be compressed. 
unsigned int DSetsBySize::Find(unsigned int elem)
{
  if ( (*SetArray)[elem] <= 0 ) {
    return elem; 
  }else {
    // Recursively set array to whatever Find returns.  Find will
    //  return the root, thus each node from this one up is set to root.
    return ((*SetArray)[elem] = Find( (*SetArray)[elem] ));
  }
}
