// *********************************************
// *                                           *
// *  memmanager.h                             *
// *                                           *
// *  Interface for a memory manager class     *
// *                                           *
// *  Written 7/97 by Jason Zych               *
// *                                           *
// *********************************************


#ifndef _MEMMGR_H
#define _MEMMGR_H

#include "array.h"


class MemManager
{
public:

   // MemManager
   //    - constructor
   MemManager(int size = 64); 

  
   // MemManager
   //    - copy constructor
   //    - parameters : origMemObj - an already-existing memory manager object 
   //    - initializes memory manager object to be a copy of origMemObj
   MemManager(const MemManager& origMemObj); 


   // ~MemManager
   //    - destructor
   ~MemManager(); 


   // operator=
   //    - parameters : origMemObj - an already-existing memory manager object 
   //    - sets memory manager object to be a copy of origMemObj
   MemManager& operator=(const MemManager& origMemObj); 


   // Clear
   //    - initializes the memory manager 
   void Clear(); 


   // Allocate
   //    - parameters : blockSize - an integer value referring to the memory amount needed 
   //    - allocates a block of memory and returns the address  
   int Allocate(int blockSize); 


   // Deallocate
   //    - parameters : blockAddress - the address of the memory block to be dellocated
   //    - deallocates block at blockAddress  
   void Deallocate(int blockAddress); 


   // MemoryDump
   //    - prints current status of memory
   void MemoryDump(); 


protected:

   Array<int>* manager;  // pointer to array which will represent memory 
   int memorySize;       // size of total available memory
   int freelistHead;     // address of first block in free list;  
   int roverPtr; 
   int overhead;      // pointer overhead 

   int Mark(int Ptr) { return Ptr; } 
   int Size(int Ptr) { return Ptr + 1; } 
   int LowMark(int Ptr) { return Ptr - 1; } 
   int LowSize(int Ptr) { return Ptr - 2; }
   int Next(int Ptr)  { return Ptr + 2; } 
   int Prev(int Ptr) { return Ptr + 3; } 

   void DeleteBlock(int Ptr); 
   void InsertBlock(int Ptr); 

}; 

#endif





