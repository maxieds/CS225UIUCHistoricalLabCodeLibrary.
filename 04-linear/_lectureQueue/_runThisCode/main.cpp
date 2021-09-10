// ******************************************************
// *                                                    *
// *  main.cpp                                          *
// *                                                    *
// *  Test file for queue classes                       *
// *                                                    *
// *  Written February 2005 by Jason Zych               *
// *                                                    *
// ******************************************************

#include <iostream>
using namespace std;

// #include "array-implemented-queue.h"  
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
   if (tester1.isEmpty())
      cout << "tester1 is empty" << endl;
   else
      cout << "tester1 is not empty" << endl;
   cout << endl;


   // testing copy constructor and operator= on empty list
   Queue<int> tester2(tester1);
   if (tester2.isEmpty())
      cout << "tester2 is empty" << endl;
   else
      cout << "tester2 is not empty" << endl;
   cout << endl;

   Queue<int> tester3;
   tester3.enqueue(numbers[3]);  
   tester3.enqueue(numbers[8]);
   cout << tester3.dequeue() << endl;
   tester3 = tester2;
   if (tester3.isEmpty())
      cout << "tester3 is empty" << endl;
   else
      cout << "tester3 is not empty" << endl;
   cout << endl;


   // throwing values into tester1 via enqueue
   tester1.enqueue(numbers[7]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[2]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[9]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[11]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[4]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[8]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[3]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[1]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[10]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[5]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[0]);
   cout << "Current front element is: " << tester1.front() << endl;
   tester1.enqueue(numbers[6]);
   cout << "Current front element is: " << tester1.front() << endl;
   cout << endl;


   if (tester1.isEmpty())
      cout << "tester1 is empty" << endl;
   else
      cout << "tester1 is not empty" << endl;
   cout << endl;


   // testing copy constructor and operator= on non-empty list
   Queue<int> tester4(tester1);
   if (tester4.isEmpty())
      cout << "tester4 is empty" << endl;
   else
      cout << "tester4 is not empty" << endl;
   cout << endl;

   Queue<int> tester5;
   tester5.enqueue(numbers[3]);
   tester5.enqueue(numbers[8]);
   cout << tester5.dequeue() << endl;
   tester5 = tester1;
   if (tester5.isEmpty())
      cout << "tester5 is empty" << endl;
   else
      cout << "tester5 is not empty" << endl;
   cout << endl;

   // testing a dequeue-until-empty loop
   int dequeuedElem;
   while (!(tester4.isEmpty()))
   {
      dequeuedElem = tester4.dequeue();
      cout << "Just dequeued " << dequeuedElem << " from queue." << endl;
      if (tester4.isEmpty())
         cout << "tester4 is empty" << endl;
      else
         cout << "tester4 is not empty" << endl;
      cout << endl;
   }


   // assorted enqueues and dequeues on tester4
   tester4.enqueue(numbers[7]);
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.enqueue(numbers[2]);
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.enqueue(numbers[9]);
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.dequeue();
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.enqueue(numbers[4]);
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.dequeue();
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.dequeue();
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.enqueue(numbers[1]);
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.enqueue(numbers[10]);
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.dequeue();
   cout << "Current front element is: " << tester4.front() << endl;
   tester4.dequeue();
   cout << "Current front element is: " << tester4.front() << endl;
   cout << endl;

   if (tester4.isEmpty())
      cout << "tester4 is empty" << endl;
   else
      cout << "tester4 is not empty" << endl;
   cout << endl;

   return EXIT_SUCCESS; 
}


