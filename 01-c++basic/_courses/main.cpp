// ****************************************************************
// *                                                              *
// *  main.cpp                                                    *
// *                                                              *
// *  File for simple testing of CourseInfo and Schedule classes  *
// *                                                              *
// *  Written January 2005 by Jason Zych                          *
// *                                                              *
// ****************************************************************

#include <iostream>
using namespace std;

#include "courseInfo.h"
#include "schedule.h"


int main()
{
   cout << "*** Creating first course..." << endl;
   CourseInfo c1(34523, 3);
   cout << endl;

   cout << "*** Make use of no-argument constructor for second course.";
   cout << endl;
   cout << "This doesn't give legal course values, but the point is" << endl; 
   cout << "to demonstrate the no-argument constructor, not to have" << endl;
   cout << "a legitimate pair of course values." << endl;

   CourseInfo c2;
   // Note: do NOT do this:
   //    CourseInfo c2();
   // since that is declaring a function c2, not a variable c2. 
   cout << endl;


   cout << "*** Creating third course via user input..." << endl;
   int inputID, inputCredit;

   cout << "Enter ID value: ";
   cin >> inputID;
   cout << endl;

   cout << "Enter credit value: ";
   cin >> inputCredit;
   cout << endl;

   CourseInfo c3(inputID, inputCredit);
   cout << endl;
 
   cout << "*** Creating empty schedule..." << endl;  
   Schedule listing;
   listing.print();
   cout << endl;

   cout << "*** Add first three courses to schedule..." << endl;
   bool result;
   result = listing.addCourse(c1);
   cout << "First addition result: " << result << endl;
   cout << endl;

   cout << "Second addition result: ";
   cout << listing.addCourse(c2) << endl;
   cout << endl;

   cout << "Third addition result: ";
   cout << listing.addCourse(c3) << endl;
   cout << endl;

   cout << "*** Print schedule so far..." << endl;
   listing.print();
   cout << endl;

   cout << "*** Create temporary object to write into c1..." << endl;

   // CourseInfo(11234, 5) create a local object with no name, 
   // whose scope is only this line. Then you are running:
   //       c1 = some other CourseInfo object
   // which copies the data of the object on the right into the object
   // on the left, like any other assignment would do. 
   c1 = CourseInfo(11234, 5);

   cout << "*** Adding c1 (with new values) to schedule..." << endl;
   cout << "Fourth addition result: ";
   cout << listing.addCourse(c1) << endl;
   cout << endl;
  
   cout << "*** Add temporary object directly to schedule..." << endl;
   // Once again, CourseInfo(45463, 3) creates a local object with no
   // name whose scope is only this line. In this case, that object is
   // is passed as an argument to the addCourse function, just like
   // we previously passed other CourseInfo objects as arguments to 
   // the addCourse function.
   cout << "Fifth addition result: ";
   cout << listing.addCourse(CourseInfo(45463, 3)) << endl;
   cout << endl;

   cout << "*** Printing out schedule after five additions..." << endl;
   listing.print();
   cout << endl;

   cout << "*** Trying to add a sixth course..." << endl;
   CourseInfo excessCourse(78343, 1);
   cout << "Sixth addition result: ";
   cout << listing.addCourse(excessCourse) << endl;
   cout << endl;

   cout << "*** Final print of schedule..." << endl;
   listing.print();
   cout << endl;


   // tell operating system that the program has finished properly
   return EXIT_SUCCESS; 
}

