// ************************************************************
// *                                                          *
// *  main.cpp                                                *
// *                                                          *
// *  File for simple testing of vector class                 *
// *                                                          *
// *  Written January 2005 by Jason Zych                      *
// *                                                          *
// ************************************************************

#include <iostream>
using namespace std;

#include "string.h"
#include "vector225.h"
#include "iterVectorFns.h"

int main()
{
   cout << "*** We are testing vector code" << endl << endl;

   cout << "*** Testing empty vectors." << endl << endl;
   vector<String> emptyVector;

   if (emptyVector.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << emptyVector.size() << endl;
   cout << "Capacity: " << emptyVector.capacity() << endl;

   emptyVector.reserve(15);
   cout << "New size: " << emptyVector.size() << endl;
   cout << "New capacity: " << emptyVector.capacity() << endl;
   cout << endl;

   cout << "*** About to test iterators on empty vector..." << endl << endl;
   ForwardIteration(emptyVector);
   ForwardConstIteration(emptyVector);
   ReverseIteration(emptyVector);
   ReverseConstIteration(emptyVector);
   cout << endl << endl;

   vector<String> emptyVector2(emptyVector);
   
   if (emptyVector2.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << emptyVector2.size() << endl;
   cout << "Capacity: " << emptyVector2.capacity() << endl;
   ForwardIteration(emptyVector2);
   ForwardConstIteration(emptyVector2);
   ReverseIteration(emptyVector2);
   ReverseConstIteration(emptyVector2);
   cout << endl << endl;

   vector<String> emptyVector3;
   emptyVector3.push_back("hello");
   cout << "We just have this for a moment: " << emptyVector3[0] << endl;
   emptyVector3 = emptyVector;     // now emptyVector3 is empty again

   if (emptyVector3.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << emptyVector3.size() << endl;
   cout << "Capacity: " << emptyVector3.capacity() << endl;
   ForwardIteration(emptyVector3);
   ForwardConstIteration(emptyVector3);
   ReverseIteration(emptyVector3);
   ReverseConstIteration(emptyVector3);
   cout << endl << endl;


   // Now we've tested creation of empty vectors, copying
   //  and assignment of them, size/empty/capacity/reserve, 
   //  and iterator code



   cout << "*** Testing a pre-assigned vector " << endl << endl;
   vector<String> preAssigned(9, "init");
   if (preAssigned.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << preAssigned.size() << endl;
   cout << "Capacity: " << preAssigned.capacity() << endl;
   preAssigned.reserve(15);
   cout << "New size: " << preAssigned.size() << endl;
   cout << "New capacity: " << preAssigned.capacity() << endl;
   cout << endl;

   cout << "First pass down that vector:" << endl;
   for (int i = 0; i < preAssigned.size(); ++i)
   {
      cout << "at index " << i << ": " << preAssigned[i] << endl;
      preAssigned[i] = preAssigned[i].concat(" append");
   }
   cout << endl;

   cout << "Second pass down that vector:" << endl;
   for (int i = 0; i < preAssigned.size(); ++i)
   {
      cout << "at index " << i << ": " << preAssigned.at(i) << endl;  
      preAssigned.at(i) = preAssigned.at(i).concat(" more");
   }
   cout << endl;

   cout << "Third pass down that vector:" << endl;
   for (int i = 0; i < preAssigned.size(); ++i)
   {
      cout << "at index " << i << ": " << preAssigned[i] << endl;
   }
   cout << endl;

   preAssigned.assign(12, "init-extra");
   cout << "Final pass after assign call:" << endl;
   for (int i = 0; i < preAssigned.size(); ++i)
   {
      cout << "at index " << i << ": " << preAssigned.at(i) << endl;
   }
   cout << endl;

   if (preAssigned.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << preAssigned.size() << endl;
   cout << "Capacity: " << preAssigned.capacity() << endl;
   cout << endl << endl;



   cout << "*** Testing pre-assigned constant vector..." << endl << endl;
   // (the three commented-out lines below will not compile
   //  due to the const-ness of this vector)
   vector<String> const setVector(preAssigned);
 
   if (setVector.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << setVector.size() << endl;
   cout << "Capacity: " << setVector.capacity() << endl;
   // setVector.reserve(15);

   cout << "First pass down that vector:" << endl;
   for (int i = 0; i < setVector.size(); ++i)
   {
      cout << "at index " << i << ": " << setVector[i] << endl;
      // setVector[i] = setVector[i].concat(" append");
   }
   cout << endl;

   cout << "Second pass down that vector:" << endl;
   for (int i = 0; i < setVector.size(); ++i)
   {
      cout << "at index " << i << ": " << setVector.at(i) << endl;
      // setVector.at(i) = setVector.at(i).concat(" more");
   }
   cout << endl << endl;


   // Now we've tested creation of vectors using another one
   //  of the constructors, as well as testing assign() and 
   //  the non-const and const versions of operator[] and at().
   //  In addition, we've tested the copy constructor on a
   //  non-empty vector. 


   cout << "*** Testing general-use vector..." << endl << endl;
   vector<String> usedVector(12);
   if (usedVector.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   usedVector.reserve(15);
   cout << "New size: " << usedVector.size() << endl;
   cout << "New capacity: " << usedVector.capacity() << endl;
   cout << endl << endl;

   cout << "Adding values to vector cells..." << endl;
   usedVector[0] = "Crichton";
   usedVector[1] = "Aeryn";
   usedVector[2] = "D'Argo";
   usedVector[3] = "Chiana";
   usedVector[4] = "Rygel";
   usedVector[5] = "Pilot";
   usedVector[6] = "Zhann";
   usedVector[7] = "Scorpius";
   usedVector[8] = "Crais";
   usedVector[9] = "Jool";
   usedVector[10] = "Sizoku";
   usedVector[11] = "Moya";
   cout << endl << endl;

   cout << "Original set of values:" << endl;
   cout << "Front is: " << usedVector.front() << endl;
   cout << "Back is: " << usedVector.back() << endl;
   cout << endl;

   usedVector.push_back("Braca");
   cout << "After a push_back() operation:" << endl;
   cout << "Front is: " << usedVector.front() << endl;
   cout << "Back is: " << usedVector.back() << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   cout << endl;

   usedVector.pop_back();
   cout << "After a pop_back() operation:" << endl;
   cout << "Front is: " << usedVector.front() << endl;
   cout << "Back is: " << usedVector.back() << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   cout << endl;

   usedVector.push_back("Braca");
   usedVector.push_back("Talyn");
   usedVector.push_back("Grayza");
   usedVector.push_back("Stark");
   cout << "After four push_back() operations:" << endl;
   cout << "Front is: " << usedVector.front() << endl;
   cout << "Back is: " << usedVector.back() << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   cout << endl;

   cout << "Non-const so swapping front and back:" << endl;
   String temp = usedVector.front();
   usedVector.front() = usedVector.back();
   usedVector.back() = temp;
   cout << "Front is: " << usedVector.front() << endl;
   cout << "Back is: " << usedVector.back() << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   cout << endl;

   cout << "*** About to test iterator functions..." << endl << endl;
   ForwardIteration(usedVector);
   ForwardConstIteration(usedVector);
   ReverseIteration(usedVector);
   ReverseConstIteration(usedVector);
   cout << endl << endl;

   cout << "*** Assignment operator and iterator-based changes:" << endl;
   preAssigned = usedVector;
   ForwardIterationWithChanges(preAssigned);
   ReverseIterationWithChanges(preAssigned);
   cout << endl << endl;

   cout << "*** Const usage of front and back:" << endl;
   vector<String> const setUsedVector(usedVector);
   // The bottom two of the commented-out three lines below, 
   // will not compile
   //    String temp2 = setUsedVector.front();
   //    setUsedVector.front() = setUsedVector.back();
   //    setUsedVector.back() = temp;
   cout << "Front is: " << setUsedVector.front() << endl;
   cout << "Back is: " << setUsedVector.back() << endl;
   cout << "Size: " << setUsedVector.size() << endl;
   cout << "Capacity: " << setUsedVector.capacity() << endl;
   cout << endl << endl;

  
   cout << "*** Testing insert and erase:" << endl;
   vector<String>::iterator it1, it2, it3;
   it1 = usedVector.begin();
   for (int i = 1; i <= 3; i++)
      ++it1;
   it2 = it1;
   for (int i = 1; i <= 4; i++)
      ++it2;
   cout << "First iterator at: " << *it1 << endl;
   cout << "Second iterator at: " << *it2 << endl;

   cout << "About to run erase of range..." << endl;
   usedVector.erase(it1, it2);
   cout << endl;
   BriefForwardIteration(usedVector);
   cout << endl;

   it1 = usedVector.begin();
   for (int i = 1; i <= 5; i++)
      ++it1;
   cout << "First iterator at: " << *it1 << endl;
   cout << "About to erase single value..." << endl;
   usedVector.erase(it1);
   cout << endl;
   BriefForwardIteration(usedVector);
   cout << endl;
   if (usedVector.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   cout << endl << endl;

   it1 = usedVector.begin();
   for (int i = 1; i <= 6; i++)
      ++it1;
   cout << "First iterator at: " << *it1 << endl;
   cout << "About to insert single value..." << endl;
   usedVector.insert(it1, "Rygel");
   cout << endl;
   BriefForwardIteration(usedVector);
   cout << endl;
   it1 = usedVector.begin();
   for (int i = 1; i <= 4; i++)
      ++it1;
   cout << "First iterator at: " << *it1 << endl;
   cout << "About to insert many duplicate values..." << endl;
   usedVector.insert(it1, 5, "Pilot");
   cout << endl;
   BriefForwardIteration(usedVector);
   cout << endl;
   if (usedVector.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   cout << endl << endl;

   cout << "Clearing vector..." << endl;
   usedVector.clear();
   cout << endl;
   BriefForwardIteration(usedVector);
   cout << endl;
   if (usedVector.empty())
      cout << "This vector is empty." << endl;
   else
      cout << "This vector is not empty." << endl;
   cout << "Size: " << usedVector.size() << endl;
   cout << "Capacity: " << usedVector.capacity() << endl;
   cout << endl << endl;

   cout << "*** Testing operators..." << endl;
   cout << (emptyVector2 == emptyVector3) << endl;
   cout << (preAssigned == setVector) << endl;
   cout << (usedVector == setUsedVector) << endl;
   cout << endl;

   cout << (emptyVector2 != emptyVector3) << endl;
   cout << (preAssigned != setVector) << endl;
   cout << (usedVector != setUsedVector) << endl;
   cout << endl;

   cout << (emptyVector2 < emptyVector3) << endl;
   cout << (usedVector < setUsedVector) << endl;
   emptyVector2.push_back("hello");
   emptyVector3.push_back("ice cream");
   cout << (emptyVector2 < emptyVector3) << endl;
   cout << endl;

   usedVector.insert(usedVector.begin(), 5, "Pilot");
   usedVector.push_back("Moya");
   cout << "emptyVector is : " << emptyVector << endl;
   cout << "usedVector is : " << usedVector << endl;
   cout << endl << endl;

   return EXIT_SUCCESS; 
}

