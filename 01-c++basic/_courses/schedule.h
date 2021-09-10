// ************************************************************
// *                                                          *
// *  schedule.h                                              *
// *                                                          *
// *  The interface for a class whose instances represent     *
// *   course schedules holding a maximum of five courses     *
// *                                                          *
// *  Written January 2005 by Jason Zych                      *
// *                                                          *
// ************************************************************

#ifndef SCHEDULE_225_H
#define SCHEDULE_225_H

#include "courseInfo.h"

class Schedule
{
public:

   // Schedule
   //    - constructor
   //    - initializes object to be an empty schedule
   Schedule();



   // addCourse
   //    - parameters : theCourse - the course to add to the schedule
   //    - return value : a boolean indicating whether or not the 
   //         course was added
   //    - if there have already been five courses added previously, return
   //        false; otherwise, add this course to schedule and return true
   bool addCourse(CourseInfo theCourse);



   // print
   //    - prints out schedule information -- specifically, the number
   //         of courses and the ID and credit for each course
   void print();


private:

    CourseInfo courses[5];
    int numCourses;

};

#endif

