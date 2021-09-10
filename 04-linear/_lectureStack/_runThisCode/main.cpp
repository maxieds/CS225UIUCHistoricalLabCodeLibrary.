// ******************************************************
// *                                                    *
// *  main.cpp                                          *
// *                                                    *
// *  Test file for stack classes                       *
// *                                                    *
// *  Written February 2005 by Jason Zych               *
// *                                                    *
// ******************************************************

#include <iostream>
using namespace std;

// #include "array-implemented-stack.h"  
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
   if (tester1.isEmpty())
      cout << "tester1 is empty" << endl;
   else
      cout << "tester1 is not empty" << endl;
   cout << endl;


   // testing copy constructor and operator= on empty list
   Stack<int> tester2(tester1);
   if (tester2.isEmpty())
      cout << "tester2 is empty" << endl;
   else
      cout << "tester2 is not empty" << endl;
   cout << endl;

   Stack<int> tester3;
   tester3.push(numbers[3]);  
   tester3.push(numbers[8]);
   cout << tester3.pop() << endl;
   tester3 = tester2;
   if (tester3.isEmpty())
      cout << "tester3 is empty" << endl;
   else
      cout << "tester3 is not empty" << endl;
   cout << endl;


   // throwing values into tester1 via push
   tester1.push(numbers[7]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[2]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[9]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[11]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[4]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[8]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[3]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[1]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[10]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[5]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[0]);
   cout << "Current top element is: " << tester1.top() << endl;
   tester1.push(numbers[6]);
   cout << "Current top element is: " << tester1.top() << endl;
   cout << endl;

   if (tester1.isEmpty())
      cout << "tester1 is empty" << endl;
   else
      cout << "tester1 is not empty" << endl;
   cout << endl;


   // testing copy constructor and operator= on non-empty list
   Stack<int> tester4(tester1);
   if (tester4.isEmpty())
      cout << "tester4 is empty" << endl;
   else
      cout << "tester4 is not empty" << endl;
   cout << endl;


   Stack<int> tester5;
   tester5.push(numbers[3]);
   tester5.push(numbers[8]);
   cout << tester5.pop() << endl;
   tester5 = tester1;
   if (tester5.isEmpty())
      cout << "tester5 is empty" << endl;
   else
      cout << "tester5 is not empty" << endl;
   cout << endl;

   // testing a pop-until-empty loop
   int poppedElem;
   while (!(tester4.isEmpty()))
   {
      poppedElem = tester4.pop();
      cout << "Just popped " << poppedElem << " from stack." << endl;
      if (tester4.isEmpty())
         cout << "tester4 is empty" << endl;
      else
         cout << "tester4 is not empty" << endl;
      cout << endl;
   }


   // assorted pushes and pops into tester4
   tester4.push(numbers[7]);
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.push(numbers[2]);
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.push(numbers[9]);
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.pop();
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.push(numbers[4]);
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.pop();
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.pop();
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.push(numbers[1]);
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.push(numbers[10]);
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.pop();
   cout << "Current top element is: " << tester4.top() << endl;
   tester4.pop();
   cout << "Current top element is: " << tester4.top() << endl;
   cout << endl;

   if (tester4.isEmpty())
      cout << "tester4 is empty" << endl;
   else
      cout << "tester4 is not empty" << endl;
   cout << endl;


   return EXIT_SUCCESS; 
}


