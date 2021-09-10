// ****************************************************************
// *                                                              *
// *  CourseTest.java                                             *
// *                                                              *
// *  File for simple testing of CourseInfo and Schedule classes  *
// *                                                              *
// *  Written January 2005 by Jason Zych                          *
// *                                                              *
// ****************************************************************

public class CourseTest
{
   public static void main(String[] args)
   {
      System.out.println("*** Creating first course...");
      CourseInfo c1 = new CourseInfo(34523, 3);
      System.out.println();

      System.out.println(
               "*** Make use of no-argument constructor for second course.");
      System.out.println(
               "This doesn't give legal course values, but the point is");
      System.out.println(
               "to demonstrate the no-argument constructor, not to have");
      System.out.println("a legitimate pair of course values.");

      CourseInfo c2 = new CourseInfo();
      System.out.println();


      System.out.println("*** Creating third course via user input...");
      int inputID, inputCredit;

      System.out.print("Enter ID value: ");
      inputID = Keyboard.readInt();
      System.out.println();

      System.out.print("Enter credit value: ");
      inputCredit = Keyboard.readInt();
      System.out.println();

      CourseInfo c3 = new CourseInfo(inputID, inputCredit);
      System.out.println();


      System.out.println("*** Creating empty schedule...");
      Schedule listing = new Schedule();
      listing.print();
      System.out.println();

      System.out.println("*** Add first three courses to schedule...");
      boolean result;
      result = listing.addCourse(c1);
      System.out.println("First addition result: " + result);
      System.out.println();

      System.out.print("Second addition result: ");
      System.out.println(listing.addCourse(c2));
      System.out.println();


      System.out.print("Third addition result: ");
      System.out.println(listing.addCourse(c3));
      System.out.println();


      System.out.println("*** Print schedule so far...");
      listing.print();
      System.out.println();


      System.out.println("*** Create new object for c1 to refer to...");
      // Java does not have local objects and thus does not have
      // temporary local objects
      c1 = new CourseInfo(11234, 5);

      System.out.println("*** Adding c1 (with new values) to schedule...");
      System.out.print("Fourth addition result: ");
      System.out.println(listing.addCourse(c1));
      System.out.println();


      System.out.println("*** Add new object directly to schedule...");
      // Java does not have local objects and thus does not have
      // temporary local objects; 
      System.out.print("Fifth addition result: ");
      System.out.println(listing.addCourse(new CourseInfo(45463, 3)));
      System.out.println();

      System.out.println("*** Printing out schedule after five additions...");
      listing.print();
      System.out.println();


      System.out.println("*** Trying to add a sixth course...");
      CourseInfo excessCourse = new CourseInfo(78343, 1);

      System.out.print("Sixth addition result: ");
      System.out.println(listing.addCourse(excessCourse));
      System.out.println();

      System.out.println("*** Final print of schedule...");
      listing.print();
      System.out.println();
   }
}


