// *****************************************************
// *                                                   *
// *   memmgr.h  (MP6)                                 *
// *                                                   *
// *   Interface for a memory manager class            * 
// *                                                   *
// *   Written 7/24/98 by Jason Zych                   *
// *                                                   *
// *****************************************************


#ifndef _MEMMGR_H
#define _MEMMGR_H

#include "memory.h"


class MemoryManager
{
public:

   // MemoryManager
   //    - default constructor
   //    - parameters : memSize - size of memory to have within the manager
   //                 : blockSize - size of minimum block we will allow
   //    - initializes object
   MemoryManager(int memSize = 1024, int blockSize = 16); 


   // MemoryManager
   //    - copy constructor
   //    - parameters : origVal - pre-existing memory manager
   //    - initializes object to be a copy of existing manager
   MemoryManager(const MemoryManager& origVal); 


   // ~MemoryManager
   //    - destructor
   //    - deletes dynamically allocated memory
   ~MemoryManager(); 


   // operator=
   //    - parameters : origVal - pre-existing memory manager
   //    - return value : reference to memory manager
   //    - sets object to be a copy of existing manager
   MemoryManager& operator=(const MemoryManager& origVal);


   // Clear
   //    - initializes memory to initial state
   void Clear(); 


   // Allocate
   //    - parameters : blockSize - minimum size of block needed
   //    - return value  
   int Allocate(int blockSize); 
  

   // Deallocate
   //    - parameters : memAddress - address of memory block to be deleted
   //    - deallocates block at given address
   void Deallocate(int memAddress);  

 
   // MemoryDump 
   //    - displays the allocation/deallocation status of each
   //         existing block of memory
   void MemoryDump(); 


private:

   Memory* systemMem; 
   Array<int>* freeLists; 
   int blockSize; 
   int lowBound;  
   int highBound; 
};  

#endif


 
