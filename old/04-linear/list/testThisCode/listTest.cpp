// ******************************************************
// *                                                    *
// *  listTest.cpp                                      *
// *                                                    *
// *  Test file for list classes                        *
// *                                                    *
// *  Written July 2001 by Jason Zych                   *
// *                                                    *
// *   - Changes made September 2004 by Jason Zych      *
// *      - removed .h from standard header includes    *
// *                                                    *
// ******************************************************


#include <iostream>
#include <cstddef>
using namespace std;

// #include "contiguous-list.h"
// #include "singly-linked-list.h"
// #include "doubly-linked-list.h"

int main()
{
   // quick-n-dirty array, here so that we can pass something
   // into the pass-by-reference List functions without triggering
   // compiler warnings
   int numbers[17];
   for (int i = 0; i <= 16; i++)
      numbers[i] = i;


   // basic default list creation
   List<int> tester1;
   cout << "Length of tester1 is: " << tester1.Length() << endl;
   cout << "tester 1 is: "; 
   tester1.Print();
   cout << endl;

   // testing empty list warnings
   tester1.Head();
   tester1.Tail();
   tester1.ForwardOne();
   tester1.BackwardOne();
   tester1.Update(numbers[3]);
   tester1.Remove();


   // testing copy constructor and operator= on empty list
   List<int> tester2(tester1);
   cout << "Length of tester2 is: " << tester2.Length() << endl;
   cout << "tester 2 is: "; 
   tester2.Print();
   cout << endl;
   List<int> tester3;
   tester3.InsertAfter(numbers[3]);  
   tester3 = tester2;
   cout << "Length of tester3 is: " << tester3.Length() << endl;
   cout << "tester 3 is: "; 
   tester3.Print();
   cout << endl;
   cout << endl;

   // throwing values into tester1 via InsertAfter
   tester1.InsertAfter(numbers[7]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[2]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[9]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[11]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[4]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[8]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[3]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[1]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[10]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[5]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[0]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.InsertAfter(numbers[6]);
   cout << "Current element is: " << tester1.Retrieve() << endl;

   // doing some traversing around tester1
   tester1.Head();
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.BackwardOne();
   tester1.ForwardOne();
   tester1.ForwardOne();
   tester1.ForwardOne();
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Tail();
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.ForwardOne();
   tester1.BackwardOne();
   tester1.BackwardOne();
   tester1.BackwardOne();
   cout << "Current element is: " << tester1.Retrieve() << endl;
   cout << "Length of tester1 is: " << tester1.Length() << endl;
   cout << "tester 1 is: "; 
   tester1.Print();
   cout << endl;


   // testing copy constructor and operator= on non-empty list
   List<int> tester4(tester1);
   cout << "Length of tester4 is: " << tester4.Length() << endl;
   cout << "tester 4 is: "; 
   tester4.Print();
   cout << endl;
   List<int> tester5;
   tester5.InsertAfter(numbers[3]);
   tester5 = tester1;
   cout << "Length of tester5 is: " << tester5.Length() << endl;
   cout << "tester 5 is: "; 
   tester5.Print();
   cout << endl;
   

   // throwing values into tester2 via InsertAfter
   tester2.InsertBefore(numbers[7]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[2]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[9]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[11]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[4]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[8]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[3]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[1]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[10]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[5]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[0]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.InsertBefore(numbers[6]);
   cout << "Current element is: " << tester2.Retrieve() << endl;

   cout << "Length of tester2 is: " << tester2.Length() << endl;
   cout << "tester 2 is: ";
   tester2.Print();
   cout << endl;


   // Removing various values from tester2
   tester2.Head();
   tester2.Remove();
   tester2.Head();
   tester2.ForwardOne();
   tester2.ForwardOne();
   tester2.Remove();
   tester2.Tail();
   tester2.BackwardOne();
   tester2.BackwardOne();
   tester2.BackwardOne();
   tester2.Remove();
   tester2.Tail();
   tester2.Remove();
   tester2.Tail();
   cout << "new last value in tester2 is: " << tester2.Retrieve() << endl;
   tester2.ForwardOne();
   cout << "Length of tester2 is: " << tester2.Length() << endl;
   cout << "tester 2 is: ";
   tester2.Print();
   cout << endl;
   tester2.Clear();
   cout << "Length of tester2 is: " << tester2.Length() << endl;
   cout << "tester 2 is: ";
   tester2.Print();
   cout << endl;
   cout << endl;


   // throwing values into tester3 via both insertion methods
   tester3.InsertBefore(numbers[7]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertAfter(numbers[2]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertAfter(numbers[9]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.BackwardOne();
   tester3.InsertBefore(numbers[11]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertBefore(numbers[4]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertAfter(numbers[8]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertBefore(numbers[3]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertBefore(numbers[1]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.ForwardOne();
   tester3.InsertAfter(numbers[10]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertAfter(numbers[5]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.InsertBefore(numbers[0]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.BackwardOne();
   tester3.InsertBefore(numbers[6]);
   cout << "Current element is: " << tester3.Retrieve() << endl;

   cout << "Length of tester3 is: " << tester3.Length() << endl;
   cout << "tester 3 is: ";
   tester3.Print();
   cout << endl;


   // performing some searches on tester3
   if (tester3.Find(numbers[6]))
      cout << "6 is in tester3" << endl;
   else
      cout << "6 is not in tester3" << endl;
   if (tester3.Find(numbers[9]))
      cout << "9 is in tester3" << endl;
   else
      cout << "9 is not in tester3" << endl;
   if (tester3.Find(numbers[4]))
      cout << "4 is in tester3" << endl;
   else
      cout << "4 is not in tester3" << endl;
   if (tester3.Find(numbers[14]))
      cout << "14 is in tester3" << endl;
   else
      cout << "14 is not in tester3" << endl;


   // some updating on tester3
   tester3.Find(numbers[4]);
   tester3.Update(numbers[13]);
   tester3.ForwardOne();
   tester3.ForwardOne();
   tester3.ForwardOne();
   tester3.Update(numbers[14]);
   tester3.Tail();
   tester3.Update(numbers[12]);
   for (int k = 1; k <= 6; k++)
      tester3.BackwardOne();
   tester3.Update(numbers[15]);
   tester3.Find(numbers[16]);
   tester3.Update(numbers[4]);

   cout << "Length of tester3 is: " << tester3.Length() << endl;
   cout << "tester 3 is: ";
   tester3.Print();
   cout << endl;


   // those same searches again
   if (tester3.Find(numbers[6]))
      cout << "6 is in tester3" << endl;
   else
      cout << "6 is not in tester3" << endl;
   if (tester3.Find(numbers[9]))
      cout << "9 is in tester3" << endl;
   else
      cout << "9 is not in tester3" << endl;
   if (tester3.Find(numbers[4]))
      cout << "4 is in tester3" << endl;
   else
      cout << "4 is not in tester3" << endl;
   if (tester3.Find(numbers[14]))
      cout << "14 is in tester3" << endl;
   else
      cout << "14 is not in tester3" << endl;

   return 0;
}


