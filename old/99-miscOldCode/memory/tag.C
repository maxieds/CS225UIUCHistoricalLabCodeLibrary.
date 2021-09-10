// **************************************************
// *                                                *
// *  memmanager.C                                  *
// *                                                *
// *  Implementation for a memory manager class     *
// *                                                *
// *  Written 7/97 by Jason Zych                    *
// *                                                *
// **************************************************

#include <stddef.h>
#include "asserts.h"
#include "array.h"
#include "memmanager.h"


// MemManager
//    - constructor
MemManager::MemManager(int size)
{
   memorySize = size; 
   overhead = 4; 
   manager = new Array<int>(memorySize-1, 0); 
   Assert(manager!=NULL, "memory not allocated for memory manager.");  

   (*manager)[0] = 1;    // set LowMark field of first node to "in use" 
   (*manager)[memorySize-1] = 1; // set Mark field after last node to "in use" 
  
   freelistHead = 1;

   // Mark field of lone free block is 0; 
   (*manager)[Mark(freelistHead)] = 0; 

   // size field is size - 2;
   (*manager)[Size(freelistHead)] = size - 2; 
 
   // LowMark field of "next block" is 0;  
   (*manager)[LowMark(freelistHead + (*manager)[Size(freelistHead)])] = 0; 

   // LowSize field of "next block" is size-2; 
   (*manager)[LowSize(freelistHead + (*manager)[Size(freelistHead)])] = size-2;

   // Next field of lone block is itself 
   (*manager)[Next(freelistHead)] = freelistHead; 

   // Prev field of lone block 
   (*manager)[Prev(freelistHead)] = freelistHead; 

   // begin allocations at lone block in list 
   roverPtr = freelistHead; 
}


  
// MemManager
//    - copy constructor
//    - parameters : origMemObj - an already-existing memory manager object 
//    - initializes memory manager object to be a copy of origMemObj
MemManager::MemManager(const MemManager& origMemObj)
{
   memorySize = origMemObj.memorySize; 
   manager = new Array<int>(memorySize-1, 0); 
   Assert(manager!=NULL, "memory not allocated for copy of memory manager.");

   freelistHead = origMemObj.freelistHead;   
   for (int i=0; i<memorySize; i++)
      (*manager)[i] = (*(origMemObj.manager))[i]; 
   roverPtr = origMemObj.roverPtr; 
   overhead = 4; 
}

 


// ~MemManager
//    - destructor
MemManager::~MemManager()
{
   delete manager; 
}




// operator=
//    - parameters : origMemObj - an already-existing memory manager object 
//    - sets memory manager object to be a copy of origMemObj
MemManager& MemManager::operator=(const MemManager& origMemObj)
{
   if (this!=&origMemObj)
   {
      delete manager; 
      memorySize = origMemObj.memorySize; 
      manager = new Array<int>(memorySize-1, 0); 
      Assert(manager!=NULL, "memory not allocated for copy of memory manager.");
   
      freelistHead = origMemObj.freelistHead;   
      for (int i=0; i<memorySize; i++)
         (*manager)[i] = (*(origMemObj.manager))[i]; 
      roverPtr = origMemObj.roverPtr; 
   }
   return *this; 
}




// Clear
//    - initializes the memory manager 
void MemManager::Clear() 
{
   for (int i=0; i<memorySize; i++)
      (*manager)[i] = 0; 
 
   (*manager)[0] = 1;    // set LowMark field of first node to "in use"
   (*manager)[memorySize-1] = 1; // set Mark field after last node to "in use"
 
   freelistHead = 1;
 
   (*manager)[Mark(freelistHead)] = 0;
   (*manager)[Size(freelistHead)] = memorySize - 2;
   (*manager)[LowMark(freelistHead + (*manager)[Size(freelistHead)])] = 0;
   (*manager)[LowSize(freelistHead + (*manager)[Size(freelistHead)])] = 
								memorySize-2;
   (*manager)[Next(freelistHead)] = freelistHead;
   (*manager)[Prev(freelistHead)] = freelistHead;
   roverPtr = freelistHead;
}





// Allocate
//    - parameters : blockSize - an integer value referring to the memory 
//             amount needed 
//    - allocates a block of memory and returns the address  
int MemManager::Allocate(int blockSize)
{
   int saveRover = roverPtr; 
   int neededSize = blockSize + overhead;   // the size block we're actually
					    //  looking for
   int currentSize; 
   int allocatedBlockAddress; 
   int searchedWholeList = 0; 

   while(!searchedWholeList)
   {
      currentSize = (*manager)[Size(roverPtr)]; 
      if (currentSize < neededSize) 
         roverPtr = (*manager)[Next(roverPtr)]; 
      else 
      {
         if ((currentSize - neededSize) < overhead) 
         {
            allocatedBlockAddress = roverPtr; 
            DeleteBlock(roverPtr); 
         }
         else
         {
            allocatedBlockAddress = roverPtr + currentSize - neededSize; 
            (*manager)[Size(roverPtr)] = 
                (*manager)[LowSize(allocatedBlockAddress)] = 
                    currentSize - neededSize;
            (*manager)[Size(allocatedBlockAddress)] = 
	        (*manager)[LowSize(allocatedBlockAddress + neededSize)] = 
                      neededSize;
            (*manager)[LowMark(allocatedBlockAddress)] = 0; 
         }
         (*manager)[Mark(allocatedBlockAddress)] = 1; 
         (*manager)[LowMark(allocatedBlockAddress + 
		(*manager)[Size(allocatedBlockAddress)])] = 1; 
         roverPtr = (*manager)[Next(roverPtr)]; 
         return allocatedBlockAddress; 
      }
      if (roverPtr == saveRover) 
         searchedWholeList = 1; 
   }
   return 0; 
}


// Deallocate
//    - parameters : blockAddress - the address of the memory block to be 
//             dellocated
//    - deallocates block at blockAddress  
void MemManager::Deallocate(int blockAddress)
{
   int qPtr; 

   if ((*manager)[LowMark(blockAddress)] == 0)
   {
      qPtr = blockAddress; 
      blockAddress -= (*manager)[LowSize(blockAddress)];  
      (*manager)[Size(blockAddress)] += (*manager)[Size(qPtr)];
      DeleteBlock(blockAddress); 
   } 
   else
      (*manager)[Mark(blockAddress)] = 0; 

   qPtr = blockAddress + (*manager)[Size(blockAddress)];  
   if ((*manager)[Mark(qPtr)] == 0)
   {
      (*manager)[Size(blockAddress)] += (*manager)[Size(qPtr)]; 
      if (roverPtr == qPtr) 
         roverPtr = blockAddress; 
      DeleteBlock(qPtr); 
      qPtr = blockAddress + (*manager)[Size(blockAddress)]; 
   }
   
   (*manager)[LowSize(qPtr)] = (*manager)[Size(blockAddress)]; 
   (*manager)[LowMark(qPtr)] = 0; 
   InsertBlock(blockAddress); 
}


// MemoryDump
//    - prints current status of memory
void MemManager::MemoryDump() 
{
   int blockIndex = 1; 
   while (blockIndex != memorySize-1)
   {
      cout << "Block beginning at address " << blockIndex << ":" << endl; 
      cout << "   allocation status: "; 
      if ((*manager)[blockIndex] == 1)
         cout << "allocated" << endl; 
      else
         cout << "free" << endl; 
      cout << "   total size: " << (*manager)[Size(blockIndex)] << endl; 
      cout << "   data cells: " << Size(blockIndex) + 1 << " to "; 
      cout << (*manager)[Size(blockIndex)] + blockIndex - 3 << endl;  
      cout << endl; 
      blockIndex += (*manager)[Size(blockIndex)]; 
   }
   cout << endl; 
}   


void MemManager::DeleteBlock(int Ptr)
{
   if (Next(Ptr) == Ptr)
      freelistHead = -1; 
   else
   {
      (*manager)[Next((*manager)[Prev(Ptr)])] = (*manager)[Next(Ptr)]; 
      (*manager)[Prev((*manager)[Next(Ptr)])] = (*manager)[Prev(Ptr)]; 
      if (freelistHead == Ptr)
         freelistHead = (*manager)[Next(Ptr)]; 
   }
}


void MemManager::InsertBlock(int Ptr) 
{
   (*manager)[Prev(Ptr)] = (*manager)[Prev(freelistHead)]; 
   (*manager)[Next(Ptr)] = freelistHead; 
   (*manager)[Next((*manager)[Prev(freelistHead)])] = Ptr; 
   (*manager)[Prev(freelistHead)] = Ptr; 
   freelistHead = Ptr; 
}



   

