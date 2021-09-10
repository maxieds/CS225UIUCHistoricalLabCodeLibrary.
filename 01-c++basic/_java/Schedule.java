// ************************************************************
// *                                                          *
// *  Schedule.java                                           *
// *                                                          *
// *  A class whose instances represent course schedules      *
// *   holding a maximum of five courses                       *
// *                                                          *
// *  Written January 2005 by Jason Zych                      *
// *                                                          *
// ************************************************************

public class Schedule
{

   // Schedule
   //    - constructor
   //    - initializes object to be an empty schedule
   public Schedule()
   {
      courses = new CourseInfo[5];
      numCourses = 0;
   }


   // addCourse
   //    - parameters : theCourse - the course to add to the schedule
   //    - return value : a boolean indicating whether or not the 
   //         course was added
   //    - if there have already been five courses added previously, return
   //        false; otherwise, add this course to schedule and return true
   public boolean addCourse(CourseInfo theCourse)
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
   public void print()
   {
      System.out.println("Number of courses in schedule: " + numCourses);
      for (int i = 0; i < numCourses; i++)
      {
         System.out.print("   Course #" + (i + 1) + ": ID is ");
         System.out.println(courses[i].getID() + ", credit is " 
                                        + courses[i].getCredit());
      }
   }


   private CourseInfo[] courses;
   private int numCourses;

}


