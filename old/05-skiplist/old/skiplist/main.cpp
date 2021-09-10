// ******************************************************
// *                                                    *
// *  listTest.C                                        *
// *                                                    *
// *  Test file for list classes                        *
// *                                                    *
// *  Written July 2001 by Jason Zych                   *
// *                                                    *
// ******************************************************

#include <stddef.h>
#include <iostream.h>
#include "skiplist.h"


int main()
{
   // quick-n-dirty array, here so that we can pass something
   // into the pass-by-referenceSkipList functions without triggering
   // compiler warnings
   int numbers[17];
   for (int i = 0; i <= 16; i++)
      numbers[i] = i;


   // basic default list creation
   SkipList<int> tester1;
   cout << "Length of tester1 is: " << tester1.Length() << endl;
   cout << "tester 1 is: "; 
   tester1.Print();
   cout << endl;

   // testing empty list warnings
   tester1.Head();
   tester1.Tail();
   tester1++;
   tester1--;
   tester1.Remove();


   // testing copy constructor and operator= on empty list
   SkipList<int> tester2(tester1);
   cout << "Length of tester2 is: " << tester2.Length() << endl;
   cout << "tester 2 is: "; 
   tester2.Print();
   cout << endl;
   SkipList<int> tester3;
   tester3.Insert(numbers[3]);  
   tester3 = tester2;
   cout << "Length of tester3 is: " << tester3.Length() << endl;
   cout << "tester 3 is: "; 
   tester3.Print();
   cout << endl;
   cout << endl;

   // throwing values into tester1 via Insert
   tester1.Insert(numbers[7]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[2]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[9]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[11]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[4]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[8]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[3]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[1]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[10]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[5]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[0]);
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Insert(numbers[6]);
   cout << "Current element is: " << tester1.Retrieve() << endl;

   // doing some traversing around tester1
   tester1.Head();
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1--;
   tester1++;
   tester1++;
   tester1++;
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1.Tail();
   cout << "Current element is: " << tester1.Retrieve() << endl;
   tester1++;
   tester1--;
   tester1--;
   tester1--;
   cout << "Current element is: " << tester1.Retrieve() << endl;
   cout << "Length of tester1 is: " << tester1.Length() << endl;
   cout << "tester 1 is: "; 
   tester1.Print();
   cout << endl;


   // testing copy constructor and operator= on non-empty list
   SkipList<int> tester4(tester1);
   cout << "Length of tester4 is: " << tester4.Length() << endl;
   cout << "tester 4 is: "; 
   tester4.Print();
   cout << endl;
   SkipList<int> tester5;
   tester5.Insert(numbers[3]);
   tester5 = tester1;
   cout << "Length of tester5 is: " << tester5.Length() << endl;
   cout << "tester 5 is: "; 
   tester5.Print();
   cout << endl;
   

   // throwing values into tester2 via Insert
   tester2.Insert(numbers[7]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[2]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[9]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[11]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[4]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[8]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[3]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[1]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[10]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[5]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[0]);
   cout << "Current element is: " << tester2.Retrieve() << endl;
   tester2.Insert(numbers[6]);
   cout << "Current element is: " << tester2.Retrieve() << endl;

   cout << "Length of tester2 is: " << tester2.Length() << endl;
   cout << "tester 2 is: ";
   tester2.Print();
   cout << endl;


   // Removing various values from tester2
   tester2.Head();
   tester2.Remove();
   tester2.Head();
   tester2++;
   tester2++;
   tester2.Remove();
   tester2.Tail();
   tester2--;
   tester2--;
   tester2--;
   tester2.Remove();
   tester2.Tail();
   tester2.Remove();
   tester2.Tail();
   cout << "new last value in tester2 is: " << tester2.Retrieve() << endl;
   tester2++;
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


   // throwing values into tester3 via Insert
   tester3.Insert(numbers[7]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[2]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[9]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3--;
   tester3.Insert(numbers[11]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[4]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[8]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[3]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[1]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3++;
   tester3.Insert(numbers[10]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[5]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3.Insert(numbers[0]);
   cout << "Current element is: " << tester3.Retrieve() << endl;
   tester3--;
   tester3.Insert(numbers[6]);
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
   tester3++++++;       // this is bad coding style
   tester3.Tail();
   tester3------------;     // so is this
   tester3.Find(numbers[16]);

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


