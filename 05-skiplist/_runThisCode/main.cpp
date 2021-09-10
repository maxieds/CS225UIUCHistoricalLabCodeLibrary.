// ******************************************************
// *                                                    *
// *  main.cpp                                          *
// *                                                    *
// *  Test file for list classes                        *
// *                                                    *
// *  Written July 2001 by Jason Zych                   *
// *                                                    *
// ******************************************************

#include <cstddef>
#include <iostream>
using namespace std;


#include "skiplist.h"


int main()
{
   // quick-n-dirty array, here so that we can pass something
   // into the pass-by-referenceSkiplist functions without triggering
   // compiler warnings
   int numbers[17];
   for (int i = 0; i <= 16; i++)
      numbers[i] = i;


   // basic default list creation
   Skiplist<int> tester1;
   cout << "Length of tester1 is: " << tester1.length() << endl;
   cout << "tester 1 is: "; 
   tester1.print();
   cout << endl;

   // testing empty list warnings
   tester1.front();
   tester1.back();
   tester1.forwardOne();
   tester1.backwardOne();
   tester1.remove();


   // testing copy constructor and operator= on empty list
   Skiplist<int> tester2(tester1);
   cout << "Length of tester2 is: " << tester2.length() << endl;
   cout << "tester 2 is: "; 
   tester2.print();
   cout << endl;
   Skiplist<int> tester3;
   tester3.insert(numbers[3]);  
   tester3 = tester2;
   cout << "Length of tester3 is: " << tester3.length() << endl;
   cout << "tester 3 is: "; 
   tester3.print();
   cout << endl;
   cout << endl;

   // throwing values into tester1 via Insert
   tester1.insert(numbers[7]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[2]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[9]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[11]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[4]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[8]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[3]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[1]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[10]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[5]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[0]);
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.insert(numbers[6]);
   cout << "Current element is: " << tester1.retrieve() << endl;

   // doing some traversing around tester1
   tester1.front();
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.backwardOne();
   tester1.forwardOne();
   tester1.forwardOne();
   tester1.forwardOne();
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.back();
   cout << "Current element is: " << tester1.retrieve() << endl;
   tester1.forwardOne();
   tester1.backwardOne();
   tester1.backwardOne();
   tester1.backwardOne();
   cout << "Current element is: " << tester1.retrieve() << endl;
   cout << "Length of tester1 is: " << tester1.length() << endl;
   cout << "tester 1 is: "; 
   tester1.print();
   cout << endl;


   // testing copy constructor and operator= on non-empty list
   Skiplist<int> tester4(tester1);
   cout << "Length of tester4 is: " << tester4.length() << endl;
   cout << "tester 4 is: "; 
   tester4.print();
   cout << endl;
   Skiplist<int> tester5;
   tester5.insert(numbers[3]);
   tester5 = tester1;
   cout << "Length of tester5 is: " << tester5.length() << endl;
   cout << "tester 5 is: "; 
   tester5.print();
   cout << endl;
   

   // throwing values into tester2 via Insert
   tester2.insert(numbers[7]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[2]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[9]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[11]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[4]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[8]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[3]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[1]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[10]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[5]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[0]);
   cout << "Current element is: " << tester2.retrieve() << endl;
   tester2.insert(numbers[6]);
   cout << "Current element is: " << tester2.retrieve() << endl;

   cout << "Length of tester2 is: " << tester2.length() << endl;
   cout << "tester 2 is: ";
   tester2.print();
   cout << endl;


   // Removing various values from tester2
   tester2.front();
   tester2.remove();
   tester2.front();
   tester2.forwardOne();
   tester2.forwardOne();
   tester2.remove();
   tester2.back();
   tester2.backwardOne();
   tester2.backwardOne();
   tester2.backwardOne();
   tester2.remove();
   tester2.back();
   tester2.remove();
   tester2.back();
   cout << "new last value in tester2 is: " << tester2.retrieve() << endl;
   tester2.forwardOne();
   cout << "Length of tester2 is: " << tester2.length() << endl;
   cout << "tester 2 is: ";
   tester2.print();
   cout << endl;
   tester2.clear();
   cout << "Length of tester2 is: " << tester2.length() << endl;
   cout << "tester 2 is: ";
   tester2.print();
   cout << endl;
   cout << endl;


   // throwing values into tester3 via Insert
   tester3.insert(numbers[7]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[2]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[9]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.backwardOne();
   tester3.insert(numbers[11]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[4]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[8]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[3]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[1]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.forwardOne();
   tester3.insert(numbers[10]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[5]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.insert(numbers[0]);
   cout << "Current element is: " << tester3.retrieve() << endl;
   tester3.backwardOne();
   tester3.insert(numbers[6]);
   cout << "Current element is: " << tester3.retrieve() << endl;

   cout << "Length of tester3 is: " << tester3.length() << endl;
   cout << "tester 3 is: ";
   tester3.print();
   cout << endl;


   // performing some searches on tester3
   if (tester3.find(numbers[6]))
      cout << "6 is in tester3" << endl;
   else
      cout << "6 is not in tester3" << endl;
   if (tester3.find(numbers[9]))
      cout << "9 is in tester3" << endl;
   else
      cout << "9 is not in tester3" << endl;
   if (tester3.find(numbers[4]))
      cout << "4 is in tester3" << endl;
   else
      cout << "4 is not in tester3" << endl;
   if (tester3.find(numbers[14]))
      cout << "14 is in tester3" << endl;
   else
      cout << "14 is not in tester3" << endl;


   // some updating on tester3
   tester3.find(numbers[4]);
   tester3.forwardOne();
   tester3.forwardOne();
   tester3.forwardOne();
   tester3.back();
   for (int k = 1; k <= 6; k++)
      tester3.backwardOne();
   tester3.find(numbers[16]);

   cout << "Length of tester3 is: " << tester3.length() << endl;
   cout << "tester 3 is: ";
   tester3.print();
   cout << endl;


   // those same searches again
   if (tester3.find(numbers[6]))
      cout << "6 is in tester3" << endl;
   else
      cout << "6 is not in tester3" << endl;
   if (tester3.find(numbers[9]))
      cout << "9 is in tester3" << endl;
   else
      cout << "9 is not in tester3" << endl;
   if (tester3.find(numbers[4]))
      cout << "4 is in tester3" << endl;
   else
      cout << "4 is not in tester3" << endl;
   if (tester3.find(numbers[14]))
      cout << "14 is in tester3" << endl;
   else
      cout << "14 is not in tester3" << endl;

   return 0;
}


