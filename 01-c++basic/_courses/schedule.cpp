// **************************************************************
// *                                                            *
// *  schedule.cpp                                              *
// *                                                            *
// *  The implementation for a class whose instances represent  *
// *   course schedules holding a maximum of five courses        *
// *                                                            *
// *  Written January 2005 by Jason Zych                        *
// *                                                            *
// **************************************************************

#include <iostream>
using namespace std;

#include "schedule.h"


// Schedule
//    - constructor
//    - initializes object to be an empty schedule
Schedule::Schedule()
{
   // array already initialized to default courses
   numCourses = 0;
}



// addCourse
//    - parameters : theCourse - the course to add to the schedule
//    - return value : a boolean indicating whether or not the 
//         course was added
//    - if there have already been five courses added previously, return
//        false; otherwise, add this course to schedule and return true
bool Schedule::addCourse(CourseInfo theCourse)
{
   if (numCourses == 5)
      return false;
   else
   {
      courses[numCourses] = theCourse;
      numCourses++;
      return true;
   } 
}



// print
//    - prints out schedule information -- specifically, the number
//         of courses and the ID and credit for each course
void Schedule::print()
{
   cout << "Number of courses in schedule: " << numCourses << endl;
   for (int i = 0; i < numCourses; i++)
   {
      cout << "   Course #" << (i + 1) << ": ID is ";
      cout << courses[i].getID() << ", credit is " << courses[i].getCredit();
      cout << endl;
   }
}



