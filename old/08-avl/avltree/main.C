// *******************************************************
// *                                                     *
// *  main.C                                             *
// *                                                     *
// *  Demo for the avl_tree class.                       *
// *                                                     *
// *  Written July 2001 by Jason Zych                    *
// *                                                     *
// ******************************************************* 


#include <iostream.h>
#include "avltree.h"
#include "utility225.h"


void print_tree(avl_tree<int, int>&);

void print_tree(avl_tree<int, int>& tester)
{
   avl_tree<int, int>::iterator it1;
   it1 = tester.begin();
   while (it1 != tester.end())
   {
      cout << "key:  " << it1->first << "  value: "
                << (*it1).second << endl;
      it1++;
   }
}


void const_tester(const avl_tree<int, int>& hello)
{
   // won't work with it/revit
   avl_tree<int, int>::const_iterator it1 = hello.begin();
   while (it1 != hello.end())
   {
            cout << "key:  " << it1->first << "  value: "
                << (*it1).second << endl;
       it1++;
   }
   cout << endl << endl;

   avl_tree<int, int>::const_reverse_iterator rit1 = hello.rbegin();
   while (rit1 != hello.rend())
   {
      cout << "key:  " << rit1->first << "  value: "
                << (*rit1).second << endl;
      rit1++;
   }
   cout << endl << endl;

   avl_tree<int, int>::const_iterator it3;
   if (hello.find(20) != hello.end())
   {
      it3 = hello.find(20);
      cout << "found 20, pair is " << hello.find(20)->second << endl;
   }
   else
      cout << "no 20 is there!" << endl;

   if (hello.find(200) == hello.end())
      cout << "no 200 is there! " << endl;
   else
   {
      it3 = hello.find(200);
      cout << "yep!" << endl;
   } 


   cout << hello.lower_bound(20)->second << endl;
   cout << hello.upper_bound(20)->second << endl;
   if (hello.upper_bound(100) == hello.end())
      cout << "nothin' after 100 " << endl;
   else
      cout << hello.upper_bound(100)->second << endl;

   pair<avl_tree<int, int>::const_iterator, 
          avl_tree<int, int>::const_iterator> ergo;
   ergo = hello.equal_range(20);
   cout << "pair: " << ergo.first->second << ", "
        << ergo.second->second << endl;

}



int main()
{
   cout << "*** creating default avl tree" << endl;
   avl_tree<int, int> tester;
   cout << "*** printing default avl tree" << endl;
   print_tree(tester);
   cout << endl;

   cout << "*** creating a second default avl tree" << endl;
   avl_tree<int, int> tester2;
   cout << "*** inserting a value into this avl tree" << endl;
   tester2.insert(pair<int, int>(2, 200));
   cout << "*** printing this avl tree " << endl;
   print_tree(tester2);
   cout << endl;
  

   cout << "*** creating a third tree and inserting more values" << endl;
   avl_tree<int, int> tester3;
   for (int i = 100; i >= 1; i--)
      tester3.insert(pair<int, int>(i, i*i));
   print_tree(tester3);
   cout << endl;

   avl_tree<int, int>::reverse_iterator rit1 = tester3.rbegin();
   while (rit1 != tester3.rend())
   {
      cout << "key:  " << rit1->first << "  value: "
                << (*rit1).second << endl;
      rit1++;
   }
   cout << endl;

   cout << "*** testing const" << endl;
   const_tester(tester3);
   cout << "*** done testing const" << endl;
   cout << endl << endl;


   cout << "*** testing cc, assignments, etc. " << endl;  
   avl_tree<int, int> tester3copy(tester3);
   avl_tree<int, int> tester4;
   tester4.insert(pair<int, int>(2, 200));
   tester4 = tester3;
   tester3.erase(tester3.begin(), tester3.end());

   cout << "printing tester3 " << endl;
   print_tree(tester3);
   cout << endl << endl;
   cout << "printing tester3copy" << endl;
   print_tree(tester3copy);
   cout << endl << endl;
   cout << "printing tester4" << endl;
   print_tree(tester4);
   cout << endl << endl;
   tester3copy.clear();
   cout << "printing tester3copy" << endl;
   print_tree(tester3copy);
   cout << endl << endl;


   cout << "*** Testing assorted other fun stuff! " << endl;
   if (tester3.empty())
      cout << "tester3 is empty!" << endl;
   else 
      cout << "tester3 is not empty!" << endl;


   avl_tree<int, int>::iterator it3;
   if (tester4.find(20) != tester4.end())
   {
      it3 = tester4.find(20);
      cout << "found 20, pair is " << tester4.find(20)->second << endl;
   }
   else
      cout << "no 20 is there!" << endl;

   if (tester4.find(200) == tester4.end())
      cout << "no 200 is there! " << endl;
   else
   {
      it3 = tester4.find(200);
      cout << "found 200, pair is " << tester4.find(200)->second << endl;
   }

   cout << tester4.lower_bound(20)->second << endl;
   cout << tester4.upper_bound(20)->second << endl;
   pair<avl_tree<int, int>::iterator, avl_tree<int, int>::iterator> ergo;
   ergo = tester4.equal_range(20);
   cout << "20 pair: " << ergo.first->second << ", "
        << ergo.second->second << endl;
 
   cout << "count for 101 is " << tester4.count(101) << endl;
   cout << "count for 11 is " << tester4.count(11) << endl;
   cout << "size for tester4 is " << tester4.size() << endl;    
   cout << endl << endl;

   cout << "*** erasing some values" << endl;
   for (int i = 99; i>=1; i = i - 3)
      tester4.erase(i);
   print_tree(tester4);
   
   cout << "size for tester4 is " << tester4.size() << endl;
   if (tester4.empty())
      cout << "tester4 is empty!" << endl;
   else
      cout << "tester4 is not empty!" << endl;



}



