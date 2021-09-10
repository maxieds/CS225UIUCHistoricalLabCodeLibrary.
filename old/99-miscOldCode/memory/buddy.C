// *****************************************************
// *                                                   *
// *   memmgr.C  (MP6)                                 *
// *                                                   *
// *   Implementation for a memory manager class       * 
// *                                                   *
// *   Written 7/24/98 by Jason Zych                   *
// *                                                   *
// *****************************************************

#include <math.h>
#include "asserts.h"
#include "memmgr.h"


// MemoryManager
//    - default constructor
//    - parameters : memSize - size of memory to have within the manager
//    - initializes object
MemoryManager::MemoryManager(int memSize, int theBlockSize) 
{
   blockSize = theBlockSize; 
   lowBound = log(blockSize)/log(2);   // lowest freelist index
   highBound = log(memSize)/log(2);   // highest freelist index

   systemMem = new Memory(memSize); 
   freeLists = new Array<int>(lowBound, highBound);  
  
   for (int i=lowBound; i<highBound; i++)
      (*freeLists)[i] = -1;     // set free lists to be empty, i.e. -1

   // each block has four cells of overhead, which are
   // the first four cells in the block. Mark, at the actual
   // address of the block, stores 1 if allocated and 0 if free.
   // Size, at address + 1, holds the size of the block (or, for
   // some students, maybe the log() of the size). Next, at
   // address + 2, holds the address of the next cell that is
   // in the same, doubly-linked free list as this cell. If this
   // this cell is *not* in a free list, then Next can be set to
   // whatever you want, or set to nothing. It won't be read, so it
   // doesn't matter. Prev, at address + 3, holds the address of the
   // previous cell in the free list. As with Next, this field
   // is useless in allocated blocks. Think of Next and Prev
   // as doubly-linked list pointers, but instead of being 2 of 
   // the three fields in a doubly-linked node (along with an
   // element field for field #3), the pointers here are 
   // *built into the actual element*, the actual memory block,
   // as part of the overhead of the block. 
    

   // To start, we have one block, size 1024, starting at address
   // 0. So, we have a circular doubly-linked list of 1 block, 
   // so Next and Prev should point to 0, since in a circular
   // doubly-linked list of one block, both pointers of that block
   // point to itself. 
    
   systemMem->WriteCell(0, 0);        // Mark(0) = 0 
   systemMem->WriteCell(1, memSize);  // Size(0) = memSize 
   systemMem->WriteCell(2, 0);        // Next(0) = 0  
   systemMem->WriteCell(3, 0);        // Prev(0) = 0  

   (*freeLists)[highBound] = 0;        // Free(m) = 0;   
} 


// MemoryManager
//    - copy constructor
//    - parameters : origVal - pre-existing memory manager
//    - initializes object to be a copy of existing manager
MemoryManager::MemoryManager(const MemoryManager& origVal)
{
   freeLists = new Array<int>(*(origVal.freeLists)); 
   systemMem = new Memory(*(origVal.systemMem)); 
   blockSize = origVal.blockSize; 
   highBound = origVal.highBound; 
   lowBound = origVal.lowBound; 
} 


// ~MemoryManager
//    - destructor
//    - deletes dynamically allocated memory
MemoryManager::~MemoryManager()
{
   delete systemMem; 
   delete freeLists; 
} 


// operator=
//    - parameters : origVal - pre-existing memory manager
//    - return value : reference to memory manager
//    - sets object to be a copy of existing manager
MemoryManager& MemoryManager::operator=(const MemoryManager& origVal)
{
   if (this!=&origVal)
   {
      freeLists = new Array<int>(*(origVal.freeLists)); 
      systemMem = new Memory(*(origVal.systemMem)); 
      blockSize = origVal.blockSize; 
      highBound = origVal.highBound;  
      lowBound = origVal.lowBound; 
   }
   return *this;
}


// Clear
//    - initalizes memory to inital state
void MemoryManager::Clear()
{
 
   for (int i=lowBound; i<highBound; i++)
      (*freeLists)[i] = -1;
 
   systemMem->WriteCell(0, 0);        // Mark(0) = 0
   systemMem->WriteCell(1, systemMem->Size());  // Size(0) = memSize
   systemMem->WriteCell(2, 0);        // Next(0) = 0
   systemMem->WriteCell(3, 0);        // Prev(0) = 0
 
   (*freeLists)[highBound] = 0;        // Free(m) = 0;
}


// Allocate
//    - parameters : blockSize - minimum size of block needed
//    - return value  
int MemoryManager::Allocate(int theBlockSize)
{
   int j, k;
   int theAddress, theBuddy, tempAddr;  

   // find lowest power of two that is greater than
   // our requested block size; that is the lowest size
   // block we can actually allocate, since we can only
   // allocate blocks of size equal to a power of 2. 
   k = ceil(log(theBlockSize)/log(2)); 


   // if our request is for less than our lowBound
   // (i.e. in this MP, if our request is for 8 or 4 
   // or 2, instead of at least 16), then round up to
   // lowBound. So, the min size is 16, and the min
   // log(size) is 4, no matter what. 
   if (k<lowBound)
      k = lowBound; 
   j = k; 


   // now, keep incrementing the block size we are
   // looking for until we actually find a block of
   // the size we need. (Again, j below is actually
   // log(blockSize).  
   while ((j<=highBound) && ((*freeLists)[j] == -1))
      j++; 

   // if we've exceeded the maximum possible blocksize, 
   // then we never found a block of an appropriate size,
   // so return a number that is not an address. (i.e.
   // NULL...but in this MP, -1 is NULL.) 
   if (j>highBound) 
      return -1;
   theAddress = (*freeLists)[j]; 


   // Now, remove this block from the free list it is on. 
   // If the "next" field of this block (address + 2) points
   // to itself, then this is the only node on the free list.
   // (since all our free lists are circular). In that
   // case, the free list will become empty, so the array value
   // should point to NULL, i.e. -1  
   if (systemMem->ReadCell(theAddress+2) == (*freeLists)[j])
      (*freeLists)[j] = -1;   
 
   // otherwise, we remove one block, but other blocks in the
   // doubly-linked list remain. Doubly-linked deletion! 
   else
   {
      // node->prev->next = node->next 
      systemMem->WriteCell(systemMem->ReadCell(theAddress+3) + 2, 
			systemMem->ReadCell(theAddress+2)); 
      // node->next->prev = node->prev 
      systemMem->WriteCell(systemMem->ReadCell(theAddress+2) + 3, 
			systemMem->ReadCell(theAddress + 3)); 
      // Free(j) = node->next; 
      (*freeLists)[j] = systemMem->ReadCell(theAddress + 2); 
   }


   // Finally, as long as our block is bigger than k, the 
   // actual requested size, we can cleave off the
   // second half and put that second half back on a free
   // list of the appropriate size.  
   while (j>k)
   {
      j--; 
      theBuddy = theAddress + pow(2, j); 
      systemMem->WriteCell(theBuddy, 0);    
      systemMem->WriteCell(theBuddy+1, pow(2, j)); 
      tempAddr = (*freeLists)[j]; 
   
      // if free list was empty, this block is the first
      // one into the free list, in which case set both the
      // next (address + 2) and previous (addresss + 3) pointers
      // in this cell to point to itself. Thus, we still have
      // a doubly-linked circular list, even if it's only one node.
      if (tempAddr == -1)
      {
         systemMem->WriteCell(theBuddy+2, theBuddy);
         systemMem->WriteCell(theBuddy+3, theBuddy); 
         (*freeLists)[j] = theBuddy; 
      }
      // otherwise, insert node into list. Doubly-linked insertion!
      else
      {
         // buddy->next = head->next; 
         systemMem->WriteCell(theBuddy+2, systemMem->ReadCell(tempAddr+2));
         // buddy->prev = head; 
         systemMem->WriteCell(theBuddy+3, tempAddr); 
         // head->next = buddy
         systemMem->WriteCell(tempAddr+2, theBuddy); 
         // buddy->next->prev = buddy
         systemMem->WriteCell(systemMem->ReadCell(theBuddy+2)+3, theBuddy); 
      }
   }

   // This block is allocated, so we write "1" in its Mark field
   // (address + 0)
   systemMem->WriteCell(theAddress, 1);     

   // Write the size of the block (2 to the k power) in the Size
   // field (address + 1)
   systemMem->WriteCell(theAddress+1, pow(2, k)); 

   // The Next and Prev fields (address + 2, address + 3)
   // are not needed until the block is deallocated and put 
   // back on a free list or merged with its buddy. So, we don't
   // care what is in those fields and don't need to set them. 

   return theAddress;  
} 


// Deallocate
//    - parameters : memAddress - address of memory block to be deleted
//    - deallocates block at given address
void MemoryManager::Deallocate(int memAddress)
{
   int k; 
   int theBuddy, tempAddr;

   // k will hold the log of the size of this block. Size is stored
   //   at address + 1, always. 
   k = log(systemMem->ReadCell(memAddress+1))/log(2); 


   // As long as the block we are freeing is not the full memory, 
   //      and the correct-sized buddy of this block is free, too, 
   while ((k<highBound) && 
	  ((systemMem->ReadCell(memAddress ^ (int) pow(2, k)) == 0) &&
	   (systemMem->ReadCell((memAddress ^ (int) pow(2, k))+1) == pow(2, k))))
   {

      // We will remove the buddy from its free list and merge it
      // with our newly-deallocated block, thus making a free block
      // twice as large. If the buddy was the only node in its free list,
      // the free list is empty and should hold NULL, i.e. -1.  
      theBuddy = memAddress ^ (int) pow(2, k);
      if (systemMem->ReadCell(memAddress+2) == (*freeLists)[k]) 
         (*freeLists)[k] = -1;   

      // Otherwise, remove the buddy from the list, leaving other elements
      //  behind. Doubly-linked delete!  
      else
      {
         // node->prev->next = node->next 
         systemMem->WriteCell(systemMem->ReadCell(theBuddy+3) + 2, 
                        systemMem->ReadCell(theBuddy+2)); 
         // node->next->prev = node->prev 
         systemMem->WriteCell(systemMem->ReadCell(theBuddy+2) + 3, 
                        systemMem->ReadCell(theBuddy + 3));
         // Free(k) = node->next; 
         (*freeLists)[k] = systemMem->ReadCell(theBuddy + 2); 
      } 

      // Finally, if our block merged with a buddy that had a
      // *lower* address, then the new address of the merged block
      // is really the buddy's address. (ex. if we merge newly 
      // deallocated block 32-63 with buddy 0-31, the address of the 
      // new 0-63 block is the former-buddy's address, 0, not our block's
      // address, 32. 
      if (theBuddy < memAddress)
         memAddress = theBuddy; 

      k++; 
   }
   systemMem->WriteCell(memAddress, 0); 
   systemMem->WriteCell(memAddress+1, pow(2, k)); 
 
   tempAddr = (*freeLists)[k];

   // Finally, this large free block must be inserted into the 
   // free list. If that free list was empty, then this is the first
   // block in the circular doubly-linked list, and as such, its
   // Next field (address + 2) and Prev field (address + 3) should
   // point to itself. 
   if (tempAddr == -1)
   {
      systemMem->WriteCell(memAddress+2, memAddress);
      systemMem->WriteCell(memAddress+3, memAddress); 
      (*freeLists)[k] = memAddress; 
   }
   // else, do a doubly-linked insertion into the list. 
   else
   {
      // P->next = head->next; 
      systemMem->WriteCell(memAddress+2, systemMem->ReadCell(tempAddr+2));  
      // P->prev = head; 
      systemMem->WriteCell(memAddress+3, tempAddr); 
      // head->next = P
      systemMem->WriteCell(tempAddr+2, memAddress); 
      // P->next->prev = P 
      systemMem->WriteCell(systemMem->ReadCell(memAddress+2)+3, memAddress); 
   }
}


// MemoryDump 
//    - displays the allocation/deallocation status of each
//         existing block of memory
void MemoryManager::MemoryDump()
{
   int travAddr = 0;
   while (travAddr<systemMem->Size())
   {
      cout << "ADDRESS: " << travAddr << endl; 
      if (systemMem->ReadCell(travAddr) == 1)
      {
         cout << "   Block is allocated." << endl;  
         cout << "   Size of block is "; 
         cout << systemMem->ReadCell(travAddr+1) << "." << endl; 
      }
      else
      {
         cout << "   Block is free." << endl;  
         cout << "   Size of block is "; 
         cout << systemMem->ReadCell(travAddr+1) << "." << endl; 
         cout << "   Next block in its list is "; 
         cout << systemMem->ReadCell(travAddr+2) << "." << endl;
         cout << "   Previous block in its list is "; 
         cout << systemMem->ReadCell(travAddr+3) << "." << endl; 
      }
      travAddr = travAddr + systemMem->ReadCell(travAddr+1); 
   } 
   cout << endl; 
}    


