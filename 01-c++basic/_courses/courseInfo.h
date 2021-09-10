// ************************************************************
// *                                                          *
// *  courseInfo.h                                            *
// *                                                          *
// *  The interface for a class whose instances hold the      *
// *   ID and credit for a single course                      *
// *                                                          *
// *  Written January 2005 by Jason Zych                      *
// *                                                          *
// ************************************************************

#ifndef COURSEINFO_225_H
#define COURSEINFO_225_H

class CourseInfo
{
public:

   // CourseInfo
   //    - constructor
   //    - initializes object to meaningless default 
   //        values (-1 for both ID and credit)
   CourseInfo();



   // CourseInfo
   //    - constructor
   //    - parameter : theID - integer storing ID for course; this
   //                   ID must be a positive integer or an assertion
   //                   will be triggered
   //                : theCredit - credit of course; this must be a positive
   //                   integer or an assertion will be triggered
   //    - initializes object to have the parameter values
   CourseInfo(int theID, int theCredit);
  


   // getID
   //    - return value : an integer storing the ID of this course
   //    - returns the ID for this course
   int getID();



   // getCredit
   //    - return value : an integer holding the credit hours for this course
   //    - returns the credit hours for this course
   int getCredit();



private:

   int courseID;     // ID number of course
   int credit;       // credit (in hours) of course
};

#endif

