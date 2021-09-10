/*********************************************
 *                                           *
 * closehash.h                               *
 *                                           *
 * Interfaces for closed hash tables derived *
 *  from the HashBase class.                 *
 * These classes are also abstract.          *
 *                                           *
 *  Author:  Wendy L. Terry                  *
 *    Date:  15 Oct 1997                     *
 *  Update:  25 Feb 1998 by Wendy L. Terry   *
 *            -- added copy constructor and  *
 *                 operator= to each class   *
 *                                           *
 *********************************************/

#include "hashbase.h"

#ifndef _LINHASH_H
#define _LINHASH_H
//
// Class:  LinHashTable
// Derived from:  HashBase
//
// Implements a hash table that uses linear probing for
//  collision resolution.  All members of HashBase are inherited,
//  and Find() is defined to use linear probing.  The hash
//  function is left undefined.
//
template<class Ktype, class Etype>
class LinHashTable : public HashBase<Ktype, Etype>
{
public:

  // Constructor
  LinHashTable(int tableSize=59)
    : HashBase<Ktype, Etype>(tableSize) {}

  // Copy constructor
  LinHashTable(const LinHashTable &origTable)
    : HashBase<Ktype, Etype>(origTable) {}
      
  // Destructor
  ~LinHashTable() {}

  // operator=
  //  - parameters: origTable - the table to copy from
  //  - modifies the invoking hash table so it has the same values
  //      stored in it as origTable does
  //  - assuming that operator= is defined for Ktype and Etype,
  //      the resulting copy will be a deep copy
  LinHashTable& operator=(const LinHashTable &origTable);

  // Find
  //   - parameters : Key - the value we are looking up
  //   - finds Key in the table, and sets the current index to that index
  //   - returns 1 if successful, 0 otherwise
  virtual int Find(Ktype Key);

};
#endif


#ifndef _QUADHASH_H
#define _QUADHASH_H
//
// Class:  QuadHashTable
// Derived from:  HashBase
//
// Implements a hash table that uses quadratic probing for
//  collision resolution.  All members of HashBase are inherited,
//  and Find() is defined to use quadratic probing.  The hash 
//  function is left undefined.
//
template<class Ktype, class Etype>
class QuadHashTable : public HashBase<Ktype, Etype>
{
public:
  // Constructor
  QuadHashTable(int tableSize=59)
    : HashBase<Ktype, Etype>(tableSize) {}

  // Copy constructor
  QuadHashTable(const QuadHashTable &origTable)
    : HashBase<Ktype, Etype>(origTable) {}
      
  // Destructor
  ~QuadHashTable() {}

  // operator=
  //  - parameters: origTable - the table to copy from
  //  - modifies the invoking hash table so it has the same values
  //      stored in it as origTable does
  //  - assuming that operator= is defined for Ktype and Etype,
  //      the resulting copy will be a deep copy
  QuadHashTable& operator=(const QuadHashTable &origTable);

  // Find
  //   - parameters : Key - the value we are looking up
  //   - finds Key in the table, and sets the current index to that index
  //   - returns 1 if successful, 0 otherwise
  virtual int Find(Ktype Key);

};
#endif


#ifndef _DOUBHASH_H
#define _DOUBHASH_H
//
// Class:  DoubHashTable
// Derived from:  HashBase
//
// Implements a hash table that uses double hashing for
//  collision resolution.  All members of HashBase are
//  inherited, and Find() is defined to use double hashing.
//  The first hash function is left undefined, and a second
//  pure virtual hash function is declared.
//
template<class Ktype, class Etype>
class DoubHashTable : public HashBase<Ktype, Etype>
{
public:

  // Constructor
  DoubHashTable(int tableSize=59)
    : HashBase<Ktype, Etype>(tableSize) {}

  // Copy constructor
  DoubHashTable(const DoubHashTable &origTable)
    : HashBase<Ktype, Etype>(origTable) {}
      
  // Destructor
  ~DoubHashTable() {}

  // operator=
  //  - parameters: origTable - the table to copy from
  //  - modifies the invoking hash table so it has the same values
  //      stored in it as origTable does
  //  - assuming that operator= is defined for Ktype and Etype,
  //      the resulting copy will be a deep copy
  DoubHashTable& operator=(const DoubHashTable &origTable);

  // Find
  //   - parameters : Key - the value we are looking up
  //   - finds Key in the table, and sets the current index to that index
  //   - returns 1 if successful, 0 otherwise
  virtual int Find(Ktype Key);

protected:

  // SecondHash
  //   - pure virtual function
  //   - computes second hash value for Key
  virtual int SecondHash(Ktype Key) = 0;

};
#endif
