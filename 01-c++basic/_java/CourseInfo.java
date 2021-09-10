// ************************************************************
// *                                                          *
// *  CourseInfo.java                                         *
// *                                                          *
// *  A class whose instances hold the ID and credit          *
// *    for a single course                                   *
// *                                                          *
// *  Written January 2005 by Jason Zych                      *
// *                                                          *
// ************************************************************

public class CourseInfo
{

   // CourseInfo
   //    - constructor
   //    - initializes object to meaningless default 
   //        values (-1 for both ID and credit)
   public CourseInfo()
   {
      courseID = -1;
      credit = -1;

      // these two lines:
      //    this.courseID = -1;
      //    this.credit = -1;
      // would be ok too

   }



   // CourseInfo
   //    - constructor
   //    - parameter : theID - integer storing ID for course; this
   //                   ID must be a positive integer or an assertion
   //                   will be triggered
   //                : theCredit - credit of course; this must be a positive
   //                   integer or an assertion will be triggered
   //    - initializes object to have the parameter values
   public CourseInfo(int theID, int theCredit)
   {
      Asserts.Assert(theID > 0, "CourseInfo: ID must be positive!");
      Asserts.Assert(theCredit > 0, "CourseInfo: credit must be positive!");

      courseID = theID;
      credit = theCredit;

      // these two lines:
      //    this.courseID = theID;
      //    this.credit = theCredit;
      // would be ok too

   }
  


   // getID
   //    - return value : an integer storing the ID of this course
   //    - returns the ID for this course
   public int getID()
   {
      return courseID;

      // return this.courseID;   would be ok too
   }



   // getCredit
   //    - return value : an integer holding the credit hours for this course
   //    - returns the credit hours for this course
   public int getCredit()
   {
      return credit;

      // return this.credit;   would be ok too
   }



   private int courseID;     // ID number of course
   private int credit;       // credit (in hours) of course
}


