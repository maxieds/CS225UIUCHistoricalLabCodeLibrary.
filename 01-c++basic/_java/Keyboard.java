// *******************************************************
// *                                                     *
// *  Keyboard.java                                      *
// *                                                     *
// *  Version B : redirected-input version               *
// *   - meant for use when user will redirect a file    *
// *      of input values into the program using <       *
// *                                                     *
// *  Primitive Keyboard input of integers, reals,       *
// *     strings, and characters.                        *
// *                                                     *
// *  Author: M. Dennis Mickunas, June 9, 1997           *
// *                                                     *
// *  Changes made August 2001 by Jason Zych:            *
// *     - format of file header comment changed         *
// *     - method header comments added                  *
// *     - "public" added in front of "class" keyword    *
// *     - indentation style of file changed to be       *
// *         consistent with all the other given code    *
// *         the students will see this semester         *
// *     - each method changed to print out an extra     *
// *         blank line before returning (to aid in      *
// *         dealing with formatting differences that    *
// *         result from getting input from stdin rather *
// *         than keyboard during automated testing)     *
// *                                                     *
// *  Changes made December 2001 by Jason Zych:          *
// *     - edited variables: changed some from class     *
// *         variables to local variables, changed       *  
// *         remaining class variables to private        *
// *         access, and gave some variables more        *
// *         descriptive names.                          *
// *     - changed method name of eof() to endOfFile()   *
// *     - added a few instructive comments              * 
// *                                                     *
// *******************************************************

// To the CS125 student:
// 
//   As stated in class, you don't need to understand this file in
//   order to use it. All you need to do is to put this file in the
//   same directory as the files you write, and then write expressions
//   into your code similar to the ones you have seen in lecture.
// 
//   However, in case you are interested, there are some comments below 
//   telling you in which lectures you will learn more about various code 
//   statements you see here. Some of the code statements you see here
//   will be things the CS125 course will teach you; other code statements
//   are considered "honors topics" and will be covered in CS196 for those
//   students taking the honors course.  
//
// *****************************************************************


// This line lets the compiler know we are making use of some
// pre-written Java library code -- in this case, code to allow
// some input from the keyboard. You will never need to deal with
// expressions like this in CS125, since all of the code you use
// in this class will either be provided by us or written by you. 
// However, CS196 will make use of some pre-written Java libraries, 
// so CS196 students will make use of "import" statements.

import java.io.*;



public class Keyboard 
{
   // These are "class variables"; we'll discuss what class
   //   variables are in lecture 14.

   private static boolean isEndOfFile = false;
   private static String inputString;


   // The class variable below is being initialized using an
   //   expression involving the word "new".  The keyword "new" 
   //   is something we will first see in lecture 12 when we 
   //   discuss arrays. We will discuss the more general use of
   //   "new" -- with objects other than arrays -- in lectures 
   //   13 through 15. The CS196 course will discuss the particulars
   //   of BufferedReader and InputStreamReader objects and the  
   //   System.in expression. 

   /* WARNING:  THE BUFFER VALUE IS SET TO 1 HERE TO OVERCOME
   ** A KNOWN BUG IN WIN95 (WITH JDK 1.1.3 ONWARDS)
   */
   private static BufferedReader input = 
            new BufferedReader(new InputStreamReader(System.in),1);


   // readInt(), readChar(), readDouble(), readString(), and 
   //  endOfFile() are "class methods". You will use some of
   //  these for now without knowing too much about them, but we 
   //  will discuss in more detail what methods are in lecture 10,
   //  and we will discuss the difference between "class methods"
   //  and other kinds of methods in lecture 14.


   // readInt
   //    - return value : the integer entered as input
   //    - pauses program, waiting for the user to type in an
   //        integer and hit return. Once the user does this, 
   //        that integer is returned by this method. 
   public static int readInt() 
   {
      if (isEndOfFile) 
         return 0;
      System.out.flush();

      // The keywords "try" and "catch", which appear in this
      //   and the next three methods, deal with something known
      //   as "exception handling". CS196 will explore this topic 
      //   in detail.
      try 
      { 
         inputString = input.readLine(); 
      }
      catch (IOException e) 
      {
         System.exit(-1);
      }

      if (inputString == null) 
      {
         isEndOfFile = true; 
         return 0;
      }

      int inputInteger;
      inputInteger = new Integer(inputString.trim()).intValue();
      System.out.println();
      return inputInteger;
   }



   // readChar
   //    - return value : the character entered as input 
   //    - pauses program, waiting for the user to type in a
   //          character and hit return. Once the user does this,
   //          that character is returned by this method.
   public static char readChar() 
   {
      if (isEndOfFile) 
         return (char)0;
      System.out.flush();

      try 
      { 
         inputString = input.readLine(); 
      }
      catch (IOException e) 
      {
         System.exit(-1);
      }

      if (inputString == null) 
      {
         isEndOfFile = true; 
         return (char)0;
      }

      System.out.println();
      return inputString.charAt(0);
   }



   // readDouble
   //    - return value : the floating point number entered as input 
   //    - pauses program, waiting for the user to type in a
   //        floating point number and hit return. Once the user does 
   //        this, that floating point number is returned by this method.
   public static double readDouble() 
   {
      if (isEndOfFile) 
         return 0.0;
      System.out.flush();

      try 
      { 
         inputString = input.readLine();
      }
      catch (IOException e) 
      {
         System.exit(-1);
      }

      if (inputString == null) 
      {
         isEndOfFile = true; 
         return 0.0;
      }

      double inputDouble;
      inputDouble = new Double(inputString.trim()).doubleValue();
      System.out.println();
      return inputDouble;
   }



   // readString
   //    - return value : the character string entered as input 
   //    - pauses program, waiting for the user to type in a
   //        string of characters and hit return. Once the user does 
   //        this, a String holding those characters is returned by 
   //        this method.
   public static String readString() 
   {
      if (isEndOfFile) 
         return null;
      System.out.flush();

      try 
      {
         inputString = input.readLine();
      }
      catch (IOException e) 
      {
         System.exit(-1);
      }

      if (inputString == null) 
      {
         isEndOfFile = true; 
         return null;
      }

      System.out.println();
      return inputString;
   }



   // endOfFile
   //    - return value : whether or not the file has been completely read 
   //    - returns true if the isEndOfFile flag has been previously set to
   //        true by one of the input methods above, and otherwise returns
   //        false.   
   public static boolean endOfFile() 
   {
      return isEndOfFile;
   }
}

