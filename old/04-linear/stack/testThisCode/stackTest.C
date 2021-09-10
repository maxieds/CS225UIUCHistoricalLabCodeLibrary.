// ******************************************************
// *                                                    *
// *  stackTest.C                                       *
// *                                                    *
// *  Test file for stack classes                       *
// *                                                    *
// *  Written July 2001 by Jason Zych                   *
// *                                                    *
// ******************************************************

#include <stddef.h>
#include <iostream.h>

// #include "array-implemented-stack.h"  
// #include "list-implemented-stack.h"   
// #include "singly-linked-stack.h"


int main()
{
   // quick-n-dirty array, here so that we can pass something
   // into the pass-by-referenceList functions without triggering
   // compiler warnings
   int numbers[17];
   for (int i = 0; i <= 16; i++)
      numbers[i] = i;


   // basic default creation
   Stack<int> tester1;
   cout << "Size of tester1 is: " << tester1.Size() << endl;
   cout << "tester 1 is: "; 
   tester1.Print();
   if (tester1.IsEmpty())
      cout << "tester1 is empty" << endl;
   else
      cout << "tester1 is not empty" << endl;
   cout << endl;


   // testing copy constructor and operator= on empty list
   Stack<int> tester2(tester1);
   cout << "Size of tester2 is: " << tester2.Size() << endl;
   cout << "tester 2 is: "; 
   tester2.Print();
   if (tester2.IsEmpty())
      cout << "tester2 is empty" << endl;
   else
      cout << "tester2 is not empty" << endl;
   cout << endl;

   Stack<int> tester3;
   tester3.Push(numbers[3]);  
   tester3 = tester2;
   cout << "Size of tester3 is: " << tester3.Size() << endl;
   cout << "tester 3 is: "; 
   tester3.Print();
   if (tester3.IsEmpty())
      cout << "tester3 is empty" << endl;
   else
      cout << "tester3 is not empty" << endl;
   cout << endl;


   // throwing values into tester1 via Push
   tester1.Push(numbers[7]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[2]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[9]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[11]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[4]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[8]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[3]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[1]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[10]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[5]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[0]);
   cout << "Current top element is: " << tester1.Top() << endl;
   tester1.Push(numbers[6]);
   cout << "Current top element is: " << tester1.Top() << endl;
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
   Stack<int> tester4(tester1);
   cout << "Size of tester4 is: " << tester4.Size() << endl;
   cout << "tester 4 is: "; 
   tester4.Print();
   if (tester4.IsEmpty())
      cout << "tester4 is empty" << endl;
   else
      cout << "tester4 is not empty" << endl;
   cout << endl;

   Stack<int> tester5;
   tester5.Push(numbers[3]);
   tester5 = tester1;
   cout << "Size of tester5 is: " << tester5.Size() << endl;
   cout << "tester 5 is: "; 
   tester5.Print();
   if (tester5.IsEmpty())
      cout << "tester5 is empty" << endl;
   else
      cout << "tester5 is not empty" << endl;
   cout << endl;

   // testing a Pop-until-empty loop
   int poppedElem;
   while (!(tester4.IsEmpty()))
   {
      poppedElem = tester4.Pop();
      cout << "Just popped " << poppedElem << " from stack." << endl;
      cout << "Size of tester4 is: " << tester4.Size() << endl;
      cout << "tester 4 is: ";
      tester4.Print();
      if (tester4.IsEmpty())
         cout << "tester4 is empty" << endl;
      else
         cout << "tester4 is not empty" << endl;
      cout << endl;
   }


   // assorted pushes and pops into tester4
   tester4.Push(numbers[7]);
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Push(numbers[2]);
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Push(numbers[9]);
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Pop();
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Push(numbers[4]);
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Pop();
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Pop();
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Push(numbers[1]);
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Push(numbers[10]);
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Pop();
   cout << "Current top element is: " << tester4.Top() << endl;
   tester4.Pop();
   cout << "Current top element is: " << tester4.Top() << endl;
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


