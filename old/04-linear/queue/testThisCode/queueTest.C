// ******************************************************
// *                                                    *
// *  queueTest.C                                       *
// *                                                    *
// *  Test file for queue classes                       *
// *                                                    *
// *  Written July 2001 by Jason Zych                   *
// *                                                    *
// ******************************************************

#include <stddef.h>
#include <iostream.h>

// #include "array-implemented-queue.h"  
// #include "list-implemented-queue.h"   
// #include "singly-linked-queue.h"


int main()
{
   // quick-n-dirty array, here so that we can pass something
   // into the pass-by-referenceList functions without triggering
   // compiler warnings
   int numbers[17];
   for (int i = 0; i <= 16; i++)
      numbers[i] = i;


   // basic default creation
   Queue<int> tester1;
   cout << "Size of tester1 is: " << tester1.Size() << endl;
   cout << "tester 1 is: "; 
   tester1.Print();
   if (tester1.IsEmpty())
      cout << "tester1 is empty" << endl;
   else
      cout << "tester1 is not empty" << endl;
   cout << endl;


   // testing copy constructor and operator= on empty list
   Queue<int> tester2(tester1);
   cout << "Size of tester2 is: " << tester2.Size() << endl;
   cout << "tester 2 is: "; 
   tester2.Print();
   if (tester2.IsEmpty())
      cout << "tester2 is empty" << endl;
   else
      cout << "tester2 is not empty" << endl;
   cout << endl;

   Queue<int> tester3;
   tester3.Enqueue(numbers[3]);  
   tester3 = tester2;
   cout << "Size of tester3 is: " << tester3.Size() << endl;
   cout << "tester 3 is: "; 
   tester3.Print();
   if (tester3.IsEmpty())
      cout << "tester3 is empty" << endl;
   else
      cout << "tester3 is not empty" << endl;
   cout << endl;


   // throwing values into tester1 via Enqueue
   tester1.Enqueue(numbers[7]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[2]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[9]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[11]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[4]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[8]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[3]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[1]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[10]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[5]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[0]);
   cout << "Current front element is: " << tester1.Front() << endl;
   tester1.Enqueue(numbers[6]);
   cout << "Current front element is: " << tester1.Front() << endl;
   cout << endl;

   cout << "Size of tester1 is: " << tester1.Size() << endl;
   cout << "tester 1 is: "; 
   tester1.Print();
   if (tester1.IsEmpty())
      cout << "tester1 is empty" << endl;
   else
      cout << "tester1 is not empty" << endl;
   cout << endl;


   // testing copy constructor and operator= on non-empty list
   Queue<int> tester4(tester1);
   cout << "Size of tester4 is: " << tester4.Size() << endl;
   cout << "tester 4 is: "; 
   tester4.Print();
   if (tester4.IsEmpty())
      cout << "tester4 is empty" << endl;
   else
      cout << "tester4 is not empty" << endl;
   cout << endl;

   Queue<int> tester5;
   tester5.Enqueue(numbers[3]);
   tester5 = tester1;
   cout << "Size of tester5 is: " << tester5.Size() << endl;
   cout << "tester 5 is: "; 
   tester5.Print();
   if (tester5.IsEmpty())
      cout << "tester5 is empty" << endl;
   else
      cout << "tester5 is not empty" << endl;
   cout << endl;

   // testing a Dequeue-until-empty loop
   int dequeuedElem;
   while (!(tester4.IsEmpty()))
   {
      dequeuedElem = tester4.Dequeue();
      cout << "Just dequeued " << dequeuedElem << " from queue." << endl;
      cout << "Size of tester4 is: " << tester4.Size() << endl;
      cout << "tester 4 is: ";
      tester4.Print();
      if (tester4.IsEmpty())
         cout << "tester4 is empty" << endl;
      else
         cout << "tester4 is not empty" << endl;
      cout << endl;
   }


   // assorted enqueues and dequeues on tester4
   tester4.Enqueue(numbers[7]);
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Enqueue(numbers[2]);
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Enqueue(numbers[9]);
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Dequeue();
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Enqueue(numbers[4]);
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Dequeue();
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Dequeue();
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Enqueue(numbers[1]);
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Enqueue(numbers[10]);
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Dequeue();
   cout << "Current front element is: " << tester4.Front() << endl;
   tester4.Dequeue();
   cout << "Current front element is: " << tester4.Front() << endl;
   cout << endl;

   cout << "Size of tester4 is: " << tester4.Size() << endl;
   cout << "tester 4 is: ";
   tester4.Print();
   if (tester4.IsEmpty())
      cout << "tester4 is empty" << endl;
   else
      cout << "tester4 is not empty" << endl;
   cout << endl;

    

   return 0;
}


