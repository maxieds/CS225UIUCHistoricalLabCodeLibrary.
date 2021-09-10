// ***********************************************************
// *                                                         *
// *   Asserts.java                                          *
// *                                                         *
// *   Implementation for error alert functions              *
// *                                                         *
// *   Written January 2005 by Jason Zych                    *
// *                                                         *
// ***********************************************************

public class Asserts
{
   // Assert
   //    - parameters : safeCondition - value of a boolean expression
   //                 : errorMessage - a pointer to a character array 
   //                    containing an error message to print out;
   //                    we cannot change this character array through
   //                    this pointer
   //    - if safeCondition is true, do nothing. Otherwise, print
   //              errorMessage with specific formatting, and then 
   //              forcefully exit the program with error status flag.
   public static void Assert(boolean safeCondition, String errorMessage)
   {
      if (!safeCondition)
      {
         System.err.println("***Error: " + errorMessage);
         System.exit(-1);   // exits the program, sends "program 
                            // ended abnormally" flag to operating system
      }
   }



   // Assert
   //    - parameters :  errorMessage - a pointer to a character array
   //                     containing an error message to print out;
   //                     we cannot change this character array through
   //                     this pointer
   //    - print errorMessage with specific formatting, and then forcefully 
   //        exit the program with error status flag.
   public static void Assert(String errorMessage)
   {
      System.err.println("***Error: " + errorMessage);
      System.exit(-1);   // exits the program, sends "program
                         // ended abnormally" flag to operating system
   }




   // Warn
   //    - parameters : safeCondition - value of a boolean expression
   //                 : warningMessage - a pointer to a character array
   //                    containing a warning message to print out;
   //                    we cannot change this character array through
   //                    this pointer
   //    - if safeCondition is true, do nothing. Otherwise, print
   //              warningMessage with specific formatting
   public static void Warn(boolean safeCondition, String warningMessage)
   {
      if (!safeCondition)
         System.err.println("***Warning: " + warningMessage);
   }



   // Warn
   //    - parameters : warningMessage - a pointer to a character array
   //                    containing a warning message to print out;
   //                    we cannot change this character array through
   //                    this pointer
   //    - print warningMessage with specific formatting
   public static void Warn(String warningMessage)
   {
      System.err.println("***Warning: " + warningMessage);
   }
}



