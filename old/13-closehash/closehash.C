/*********************************************
 *                                           *
 * closehash.C                               *
 *                                           *
 * Member function definitions for classes   *
 *  inherited from the HashBase class.       *
 *                                           *
 *  Author:  Wendy L. Terry                  *
 *    Date:  15 Oct 1997                     *
 *  Update:  25 Feb 1998 by Wendy L. Terry   *
 *            -- added copy constructor and  *
 *                 operator= to each class   *
 *                                           *
 *********************************************/

#include "closehash.h"

//==================================//
// Functions for LinHashTable class //
//==================================//

// operator=
//  - parameters: origTable - the table to copy from
//  - modifies the invoking hash table so it has the same values
//      stored in it as origTable does
//  - assuming that operator= is defined for Ktype and Etype,
//      the resulting copy will be a deep copy
template<class Ktype, class Etype>
LinHashTable<Ktype, Etype>&
LinHashTable<Ktype, Etype>::
operator=(const LinHashTable<Ktype, Etype> &origTable)
{
  if (this != &origTable) {
    HashBase<Ktype, Etype>::operator=(origTable);
  }
  return *this;
}


// Find
//   - parameters : Key - the value we are looking up
//   - finds Key in the table, and sets the current index to that index
//   - returns 1 if successful, 0 otherwise
template<class Ktype, class Etype>
int LinHashTable<Ktype, Etype>::Find(Ktype Key)
{
  int numtries = 0;
  int found = 0;
  int done = 0;
  int index;
  int hvalue;

  // compute initial hash value
  hvalue = HashFunction(Key); // This is a virtual function overwritten
                              //   in subclasses. 


  // look until have found Key or empty space
  while ( (numtries < hashTableSize) && (!done) ) {

    // find index to try
    index = (hvalue + numtries) % hashTableSize;

    // check the index
    if ((*hashTable)[index]->status == 'E') {

      // Key is not in table
      currentIndex = index;
      done = 1;

    }else if ((*hashTable)[index]->tKey == Key) {

      if ((*hashTable)[index]->status == 'V') {

        // Key is found here
        currentIndex = index;
        found = 1;
        done = 1;

      }else if ((*hashTable)[index]->status == 'D') {

        // we've found Key, but it has been deleted,
        //  and so is nowhere else in the table
        currentIndex = index;
        done = 1;
      }

    }else {

      // try again
      numtries = numtries + 1;

    }
  } // end while

  return found;
}



//===================================//
// Functions for QuadHashTable class //
//===================================//

// operator=
//  - parameters: origTable - the table to copy from
//  - modifies the invoking hash table so it has the same values
//      stored in it as origTable does
//  - assuming that operator= is defined for Ktype and Etype,
//      the resulting copy will be a deep copy
template<class Ktype, class Etype>
QuadHashTable<Ktype, Etype>&
QuadHashTable<Ktype, Etype>::
operator=(const QuadHashTable<Ktype, Etype> &origTable)
{
  if (this != &origTable) {
    HashBase<Ktype, Etype>::operator=(origTable);
  }
  return *this;
}


// Find
//   - parameters : Key - the value we are looking up
//   - finds Key in the table, and sets the current index to that index
//   - returns 1 if successful, 0 otherwise
template<class Ktype, class Etype>
int QuadHashTable<Ktype, Etype>::Find(Ktype Key)
{
  int numtries = 0;
  int found = 0;
  int done = 0;
  int index;
  int hvalue;

  // compute initial hash value
  hvalue = index = HashFunction(Key);

  // look until have found Key or empty space
  while ( (numtries < hashTableSize) && (!done) ) {

    // find index to try
    index = (hvalue + (numtries*numtries)) % hashTableSize;

    // check the index
    if ((*hashTable)[index]->status == 'E') {

      // Key is not in table
      currentIndex = index;
      done = 1;

    }else if ((*hashTable)[index]->tKey == Key) {

      if ((*hashTable)[index]->status == 'V') {

        // Key is found here
        currentIndex = index;
        found = 1;
        done = 1;

      }else if ((*hashTable)[index]->status == 'D') {

        // we've found Key, but it has been deleted,
        //  and so is nowhere else in the table
        currentIndex = index;
        done = 1;
      }

    }else {

      // try again
      numtries = numtries + 1;

    }
  } // end while

  return found;
}



//===================================//
// Functions for DoubHashTable class //
//===================================//

// operator=
//  - parameters: origTable - the table to copy from
//  - modifies the invoking hash table so it has the same values
//      stored in it as origTable does
//  - assuming that operator= is defined for Ktype and Etype,
//      the resulting copy will be a deep copy
template<class Ktype, class Etype>
DoubHashTable<Ktype, Etype>&
DoubHashTable<Ktype, Etype>::
operator=(const DoubHashTable<Ktype, Etype> &origTable)
{
  if (this != &origTable) {
    HashBase<Ktype, Etype>::operator=(origTable);
  }
  return *this;
}


// Find
//   - parameters : Key - the value we are looking up
//   - finds Key in the table, and sets the current index to that index
//   - returns 1 if successful, 0 otherwise
template<class Ktype, class Etype>
int DoubHashTable<Ktype, Etype>::Find(Ktype Key)
{
  int numtries = 0;
  int found = 0;
  int done = 0;
  int index;
  int hvalue;

  // compute initial hash value
  hvalue = index = HashFunction(Key);

  // look until have found Key or empty space
  while ( (numtries < hashTableSize) && (!done) ) {

    // find index to try
    index = (hvalue + (numtries * SecondHash(Key))) % hashTableSize;
//SecondHash ?? :( 

    // check the index
    if ((*hashTable)[index]->status == 'E') {

      // Key is not in table
      currentIndex = index;
      done = 1;

    }else if ((*hashTable)[index]->tKey == Key) {

      if ((*hashTable)[index]->status == 'V') {

        // Key is found here
        currentIndex = index;
        found = 1;
        done = 1;

      }else if ((*hashTable)[index]->status == 'D') {

        // we've found Key, but it has been deleted,
        //  and so is nowhere else in the table
        currentIndex = index;
        done = 1;
      }

    }else {

      // try again
      numtries = numtries + 1;

    }
  } // end while

  return found;
}
