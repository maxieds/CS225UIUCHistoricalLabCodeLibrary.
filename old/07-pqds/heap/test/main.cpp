// ******************************************************
// *                                                    *
// *  heapTest.cpp                                      *
// *                                                    *
// *  Test file for kheap class                         *
// *                                                    *
// *  Written July 2004 by Jason Zych                   *
// *                                                    *
// ******************************************************

#include <stddef.h>
#include <iostream.h>
#include "kheap.h"


int main()
{

   KeyHeap<int, int> theHeap(100);

   for (int i = 25; i >= 1; i = i - 2)
      theHeap.Insert(i, 5*i);
   for (int i = 24; i >= 2; i = i - 2)
      theHeap.Insert(i, 5*i);

   while (!theHeap.IsEmpty())
      cout << theHeap.DeleteMin() << endl;


   return 0;
}


