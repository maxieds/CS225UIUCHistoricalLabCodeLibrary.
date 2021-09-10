// *****************************************************
// *                                                   *
// *   array.cpp                                       *
// *                                                   *
// *   Implementation for a generalized array class    *
// *                                                   *
// *   Written June 1998 by Jason Zych                 *
// *                                                   *
// *     - changes by Jason Zych October 1999          *
// *        - added constructor to create an array     *
// *           of size 0                               *
// *       - altered other functions so that an array  *
// *           of size 0 is supported                  *
// *                                                   *
// *     - changes by Jason Zych October 2004          *
// *        - #ifndef macro name changed               *
// *        - const standardized on right of item      *
// *        - comments enhanced                        *
// *        - some code clean-up done                  *
// *        - class changed to typename for generic    *
// *             variable                              *
// *                                                   *
// *     - changes by Jason Zych January 2005          *
// *        - iterators and iterator support functions *
// *             added to class                        *
// *        - put <Etype> qualifier for the name of    *
// *             type into header file                 *
// *                                                   *
// *****************************************************

#include <cstddef>    // for definition of NULL

#include "asserts.h"
#include "array.h"




// ***********************************************************
// *        member functions for the iterator class          *
// ***********************************************************



// iterator
//    - constructor
//    - initializes this iterator to point to NULL
template <typename Etype>
Array<Etype>::iterator::iterator() : ptr(NULL)
{
   // initializer list used above; no code needed here
}


// operator*
//    - return type : a reference to the element type
//    - returns by reference the cell storing the element
//         to which this iterator points.  There is no 
//          error checking done to ensure that this is 
//          a legal cell on which to perform this operation. 
template <typename Etype>
Etype & Array<Etype>::iterator::operator*() 
{ 
   return *ptr;  
}


// operator->
//    - return type : a pointer to the element type
//    - returns a pointer to the cell storing the element
//         to which this iterator points.  There is no 
//          error checking done to ensure that this is 
//          a legal cell on which to perform this operation. 
template <typename Etype>
Etype * Array<Etype>::iterator::operator->()  
{ 
   return ptr; 
}



// operator++ (prefix version)
//    - return type : reference to an iterator
//    - moves this iterator one position forward in the
//          collection it points to, and then returns
//          this iterator after moving it. There is no
//          error checking done to ensure that this is 
//          a legal position at which to perform this 
//          operation.
template <typename Etype>
typename Array<Etype>::iterator & Array<Etype>::iterator::operator++() 
{ 
   ptr = ptr + 1;  // pointer arithmetic, not integer addition
   return *this; 
}


// operator-- (prefix version)
//    - return type: reference to an iterator
//    - moves this iterator one position backward in the
//          collection it points to, and then returns
//          this iterator after moving it. There is no
//          error checking done to ensure that this is 
//          a legal position at which to perform this 
//          operation.
template <typename Etype>
typename Array<Etype>::iterator & Array<Etype>::iterator::operator--() 
{ 
   ptr = ptr - 1;   // pointer arithmetic, not integer addition
   return *this; 
}



// operator++ (postfix version)
//    - parameters : ignore - argument always the integer 1, to 
//                       distinguish this from prefix version
//    - return type : an iterator
//    - moves this iterator one position forward in the 
//          collection it points to, and then returns an
//          iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation. 
template <typename Etype>
typename Array<Etype>::iterator 
                     Array<Etype>::iterator::operator++(int ignore) 
{
   typename Array<Etype>::iterator temp = *this;
   ptr = ptr + 1;   // pointer arithmetic, not integer addition
   return temp;
}


// operator-- (postfix version)
//    - parameters : ignore - argument always the integer 1, to 
//                       distinguish this from prefix version
//    - return type : an iterator
//    - moves this iterator one position backward in the 
//          collection it points to, and then returns an
//          iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation. 
template <typename Etype>
typename Array<Etype>::iterator 
                     Array<Etype>::iterator::operator--(int ignore) 
{
   typename Array<Etype>::iterator temp = *this;
   ptr = ptr - 1;  // pointer arithmetic, not integer addition
   return temp;
}


// operator==
//    - parameters : origVal - previously created iterator
//    - return value : boolean with true indicating equality
//    - returns true if this iterator and the parameter
//         iterator point to the same location; else returns false
template <typename Etype>
bool Array<Etype>::iterator::operator==(
                 typename Array<Etype>::iterator const & origVal) const
{ 
   return (ptr == origVal.ptr); 
}


// operator!=
//    - parameters : origVal - previously created iterator
//    - return value : boolean with true indicating inequality
//    - returns true if this iterator and the parameter
//         iterator point different locations; else returns false
template <typename Etype>
bool Array<Etype>::iterator::operator!=(
                 typename Array<Etype>::iterator const & origVal) const
{ 
   return (ptr != origVal.ptr); 
}




// iterator
//    - constructor
//    - parameters : assignPtr - a pointer to the same type
//           that this iterator points to
//    - initializes iterator to point to the same place as
//         the parameter pointer points to
template <typename Etype>
Array<Etype>::iterator::iterator(Etype * assignPtr) : ptr(assignPtr)
{ 
   // initializer list used above; no code needed here
}




// ***********************************************************
// *     member functions for the const_iterator class       *
// ***********************************************************



// const_iterator
//    - constructor
//    - initializes this const_iterator to point to NULL
template <typename Etype>
Array<Etype>::const_iterator::const_iterator() : ptr(NULL)
{
   // initializer list used above; no code needed here
}



// const_iterator
//    - constructor
//    - parameters : theIter - an iterator
//    - initializes this const_iterator to point to the same
//           location as the parameter iterator
template <typename Etype>
Array<Etype>::const_iterator::const_iterator(
        typename Array<Etype>::iterator const & theIter) : ptr(theIter.ptr)
{
   // initializer list used above; no code needed here
}




// operator*
//    - return type : a reference to a value of the element type,
//        a value that cannot be altered through this reference
//    - returns by reference the element to which this
//         const_iterator points; it will not be possible to change
//         that value through the returned reference. There is no 
//         error checking done to ensure that this is a legal cell on 
//         which to perform this operation.
template <typename Etype>
Etype const & Array<Etype>::const_iterator::operator*() const
{ 
   return *ptr;  
}


// operator->
//    - return type : a pointer to a value of the element type,
//        a value that cannot be altered through this pointer
//    - returns a pointer to the element to which this 
//        const_iterator points; it will not be possible to change
//        that value through the returned pointer. There is no error
//        checking done to ensure that this is a legal cell on which
//        to perform this operation.
template <typename Etype>
Etype const * Array<Etype>::const_iterator::operator->() const
{ 
   return ptr; 
}



// operator++ (prefix version)
//    - return type : reference to an const_iterator
//    - moves this const_iterator one position forward in the
//          collection it points to, and then returns
//          this const_iterator after moving it. There is no
//          error checking done to ensure that this is 
//          a legal position at which to perform this 
//          operation.
template <typename Etype>
typename Array<Etype>::const_iterator & 
                      Array<Etype>::const_iterator::operator++() 
{ 
   ptr = ptr + 1;  // pointer arithmetic, not integer addition
   return *this; 
}



// operator-- (prefix version)
//    - return type: reference to an const_iterator
//    - moves this const_iterator one position backward in the
//          collection it points to, and then returns
//          this const_iterator after moving it. There is no
//          error checking done to ensure that this is 
//          a legal position at which to perform this 
//          operation.
template <typename Etype>
typename Array<Etype>::const_iterator & 
                      Array<Etype>::const_iterator::operator--() 
{ 
   ptr = ptr - 1;   // pointer arithmetic, not integer addition
   return *this; 
}



// operator++ (postfix version)
//    - parameters : ignore - argument always the integer 1, to 
//                       distinguish this from prefix version
//    - return type : a const_iterator
//    - moves this const_iterator one position forward in the 
//          collection it points to, and then returns an
//          const_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation. 
template <typename Etype>
typename Array<Etype>::const_iterator 
                      Array<Etype>::const_iterator::operator++(int ignore) 
{
   typename Array<Etype>::const_iterator temp = *this;
   ptr = ptr + 1;    //  pointer arithmetic, not integer addition
   return temp;
}


// operator-- (postfix version)
//    - parameters : ignore - argument always the integer 1, to 
//                       distinguish this from prefix version
//    - return type : a const_iterator
//    - moves this const_iterator one position backward in the 
//          collection it points to, and then returns an
//          const_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation. 
template <typename Etype>
typename Array<Etype>::const_iterator 
                      Array<Etype>::const_iterator::operator--(int ignore) 
{
   typename Array<Etype>::const_iterator temp = *this;
   ptr = ptr - 1;   // pointer arithmetic, not integer addition
   return temp;
}


// operator==
//    - parameters : origVal - previously created const_iterator
//    - return value : boolean with true indicating equality
//    - returns true if this const_iterator and the parameter
//         const_iterator point to the same location; else returns false
template <typename Etype>
bool Array<Etype>::const_iterator::operator==(
          typename Array<Etype>::const_iterator const & origVal) const
{ 
   return (ptr == origVal.ptr); 
}


// operator!=
//    - parameters : origVal - previously created const_iterator
//    - return value : boolean with true indicating inequality
//    - returns true if this const_iterator and the parameter
//         const_iterator point different locations; else returns false
template <typename Etype>
bool Array<Etype>::const_iterator::operator!=(
            typename Array<Etype>::const_iterator const & origVal) const
{ 
   return (ptr != origVal.ptr); 
}



// const_iterator
//    - constructor
//    - parameters : assignPtr - a const_pointer to the same type
//           that this const_iterator points to
//    - initializes const_iterator to point to the same place as
//         the parameter pointer points to
template <typename Etype>
Array<Etype>::const_iterator::const_iterator(
                               Etype const * assignPtr) : ptr(assignPtr)
{ 
   // initializer list used above; no code needed here
}




// ***********************************************************
// *     member functions for the reverse_iterator class     * 
// ***********************************************************


// reverse_iterator
//    - constructor
//    - initializes this reverse_iterator to point to NULL
template <typename Etype>
Array<Etype>::reverse_iterator::reverse_iterator() : current()
{
   // initializer list used above; no code needed here
}


// operator*
//    - return type : a reference to the element type
//    - returns by reference the cell storing the element
//         to which this reverse_iterator points.  There is
//          no error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <typename Etype>
Etype & Array<Etype>::reverse_iterator::operator*()
{
   iterator temp = current;
   --temp;
   return *temp;
}


// operator->
//    - return type : a pointer to the element type
//    - returns a pointer to the cell storing the element
//         to which this reverse_iterator points.  There is
//          no error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <typename Etype>
Etype * Array<Etype>::reverse_iterator::operator->() 
{ 
   return &(this->operator*()); 
}


// operator++ (prefix version)
//    - return type : reference to a reverse_iterator
//    - moves this iterator one position forward in the
//          collection it points to, and then returns
//          this iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <typename Etype>
typename Array<Etype>::reverse_iterator &
             Array<Etype>::reverse_iterator::operator++() 
{ 
   --current; 
   return *this; 
}


// operator-- (prefix version)
//    - return type: reference to a reverse_iterator
//    - moves this iterator one position backward in the
//          collection it points to, and then returns
//          this iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <typename Etype>
typename Array<Etype>::reverse_iterator &
             Array<Etype>::reverse_iterator::operator--()
{ 
   ++current; 
   return *this; 
}



// operator++ (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : a reverse_iterator
//    - moves this iterator one position forward in the
//          collection it points to, and then returns an
//          iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <typename Etype>
typename Array<Etype>::reverse_iterator 
                      Array<Etype>::reverse_iterator::operator++(int ignore)
{
   typename Array<Etype>::reverse_iterator temp = *this;
   --current;
   return temp;
}


// operator-- (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : a reverse_iterator
//    - moves this iterator one position backward in the
//          collection it points to, and then returns an
//          iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <typename Etype>
typename Array<Etype>::reverse_iterator
                      Array<Etype>::reverse_iterator::operator--(int ignore)
{
   typename Array<Etype>::reverse_iterator temp = *this;
   ++current;
   return temp;
}


// operator==
//    - parameters : origVal - previously created reverse_iterator
//    - return value : boolean with true indicating equality
//    - returns true if this iterator and the parameter
//         iterator point to the same location; else returns false
template <typename Etype>
bool Array<Etype>::reverse_iterator::operator==(
             typename Array<Etype>::reverse_iterator const & origVal) const
{ 
   return (current == origVal.current); 
}



// operator!=
//    - parameters : origVal - previously created reverse_iterator
//    - return value : boolean with true indicating inequality
//    - returns true if this iterator and the parameter
//         iterator point different locations; else returns false
template <typename Etype>
bool Array<Etype>::reverse_iterator::operator!=(
         typename Array<Etype>::reverse_iterator const & origVal) const
{ 
   return (current != origVal.current); 
}




// reverse_iterator
//    - constructor
//    - parameters : assignIter - iterator to the same type of 
//         data to which this reverse_iterator points
//    - initializes this reverse_iterator to point to the same
//       place that the parameter iterator points to
template <typename Etype>
Array<Etype>::reverse_iterator::reverse_iterator(
          typename Array<Etype>::iterator assignIter) : current(assignIter)
{
   // initializer list used above; no code needed here
}







// ***********************************************************
// *  member functions for the const_reverse_iterator class  *
// ***********************************************************


// const_reverse_iterator
//    - constructor
//    - initializes this const_reverse_iterator to point to NULL
template <typename Etype>
Array<Etype>::const_reverse_iterator::const_reverse_iterator() : current()
{
   // initializer list used above; no code needed here
}



// const_reverse_iterator
//    - constructor
//    - parameters : theIter - a reverse_iterator which points
//           to the same time as this const_reverse_iterator
//    - initializes this const_reverse_iterator to point to the
//        same place to which the parameter reverses_iterator
//        points
template <typename Etype>
Array<Etype>::const_reverse_iterator::const_reverse_iterator(
            typename Array<Etype>::reverse_iterator const & theIter) :
                                            current(theIter.current) 
{
   // initializer list used above; no code needed here
}




// operator*
//    - return type : a reference to a value of the element type,
//        a value that cannot be altered through this reference
//    - returns by reference the element to which this
//         const_reverse_iterator points; it will not be possible to 
//         change that value through the returned reference. There is no 
//         error checking done to ensure that this is a legal cell on 
//         which to perform this operation.
template <typename Etype>
Etype const & Array<Etype>::const_reverse_iterator::operator*() const
{
   iterator temp = current;
   --temp;
   return *temp;
}


// operator->
//    - return type : a pointer to a value of the element type,
//        a value that cannot be altered through this pointer
//    - returns a pointer to the element to which this 
//        const_reverse_iterator points; it will not be possible to 
//        change that value through the returned pointer. There is no 
//        error checking done to ensure that this is a legal cell on 
//        which to perform this operation.
template <typename Etype>
Etype const * Array<Etype>::const_reverse_iterator::operator->() const
{ 
   return &(this->operator*()); 
}




// operator++ (prefix version)
//    - return type : reference to a const_reverse_iterator
//    - moves this iterator one position forward in the
//          collection it points to, and then returns
//          this iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <typename Etype>
typename Array<Etype>::const_reverse_iterator &
             Array<Etype>::const_reverse_iterator::operator++() 
{ 
   --current; 
   return *this; 
}


// operator-- (prefix version)
//    - return type: reference to a const_reverse_iterator
//    - moves this iterator one position backward in the
//          collection it points to, and then returns
//          this iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <typename Etype>
typename Array<Etype>::const_reverse_iterator &
             Array<Etype>::const_reverse_iterator::operator--()
{ 
   ++current; 
   return *this; 
}




// operator++ (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : a const_reverse_iterator
//    - moves this iterator one position forward in the
//          collection it points to, and then returns an
//          iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <typename Etype>
typename Array<Etype>::const_reverse_iterator 
            Array<Etype>::const_reverse_iterator::operator++(int ignore)
{
   const_reverse_iterator temp = *this;
   --current;
   return temp;
}


// operator-- (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : a const_reverse_iterator
//    - moves this iterator one position backward in the
//          collection it points to, and then returns an
//          iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <typename Etype>
typename Array<Etype>::const_reverse_iterator
            Array<Etype>::const_reverse_iterator::operator--(int ignore)
{
   const_reverse_iterator temp = *this;
   ++current;
   return temp;
}


// operator==
//    - parameters : origVal - previously created const_reverse_iterator
//    - return value : boolean with true indicating equality
//    - returns true if this iterator and the parameter
//         iterator point to the same location; else returns false
template <typename Etype>
bool Array<Etype>::const_reverse_iterator::operator==(
        typename Array<Etype>::const_reverse_iterator const & origVal) const
{ 
   return (current == origVal.current); 
}



// operator!=
//    - parameters : origVal - previously created const_reverse_iterator
//    - return value : boolean with true indicating inequality
//    - returns true if this iterator and the parameter
//         iterator point different locations; else returns false
template <typename Etype>
bool Array<Etype>::const_reverse_iterator::operator!=(
        typename Array<Etype>::const_reverse_iterator const & origVal) const
{ 
   return (current != origVal.current); 
}




// ***********************************************************
// *         member functions for the Array class           *
// ***********************************************************


// ***** Constructors, etc.


// Array
//    - constructor
//    - initializes object to be a zero-element array; low and high
//        indices will be 0 and -1, respectively
template <typename Etype>
Array<Etype>::Array()
{
   lowerBound = 0;
   upperBound = -1;
   data = NULL;
   onePastLast = NULL;
}




// Array
//    - constructor
//    - parameters : low - desired lower bound of array
//                 : high - desired higher bound of array
//    - high is required to be greater than or equal to low - 1; if it
//       is not, an assertion is triggered. Assuming high >= low - 1,
//        initializes object to be a (high - low + 1)-element array; cells
//        themselves are uninitialized (for primitive types) or
//        initialized using the no-argument constructor (for non-primitive
//        types). Note that if high == low - 1, then the value of the
//        expression high - low + 1 is 0 and we create an Array object
//        without any legal indices
template <typename Etype>
Array<Etype>::Array(int low, int high)
{
   Assert(high >= low - 1, "Array: illegal bounds in Array(int, int)");
   lowerBound = low;
   upperBound = high;

   // When we create array below, all values in array cells are 
   // automatically initialized using no-argument constructor of
   // Etype (if Etype is a primitive type, this no-argument constructor 
   // does nothing, so cells hold garbage)
   data = new Etype[upperBound - lowerBound + 1]; 

   onePastLast = data + (upperBound - lowerBound + 1);
}




// Array
//    - constructor
//    - parameters : origVal - reference to previously-created Array
//                    object; that Array object cannot be changed through
//                    the parameter reference
//    - initializes array to be a copy of origVal
template <typename Etype>
Array<Etype>::Array(Array<Etype> const & origVal)
{
   // set the bounds of the array
   lowerBound = origVal.lowerBound;  
   upperBound = origVal.upperBound;   

   if (lowerBound <= upperBound)
   {
      data = new Etype[upperBound - lowerBound + 1];  
      for (int i = lowerBound; i <= upperBound; ++i)
         data[i - lowerBound] = (origVal.data)[i - lowerBound];
      onePastLast = data + (upperBound - lowerBound + 1);
   }
   else    // lowerBound > upperBound ===> lowerBound - 1 == upperBound
   {
      data = NULL;
      onePastLast = NULL;
   }
}


 
// ~Array
//    - destructor
//    - deletes dynamically allocated memory
template <typename Etype>
Array<Etype>::~Array() 
{
   delete[] data;
}




// operator=
//    - parameters : origVal - reference to previously-created Array
//                    object; that Array object cannot be changed through
//                    the parameter reference
//    - return value : reference to this Array object, after the
//        assignment operation has been performed; we cannot change this 
//        object through the returned reference
//    - assigns this object to be a copy of origVal
template <typename Etype>
Array<Etype> const & Array<Etype>::operator=(Array<Etype> const & origVal)
{
   if (this != &origVal)  // self-assignment check
   {
      delete[] data;

      // set the bounds of the array  
      lowerBound = origVal.lowerBound;
      upperBound = origVal.upperBound;

      if (lowerBound <= upperBound)
      {
         data = new Etype[upperBound - lowerBound + 1];
         for (int i = lowerBound; i <= upperBound; ++i)
            data[i - lowerBound] = (origVal.data)[i - lowerBound];
         onePastLast = data + (upperBound - lowerBound + 1);
      }
      else
      {
         data = NULL;
         onePastLast = NULL;
      }
   }	
   return *this;
}



// ****** information access/manipulation


// operator[]
//    - parameters : index - integer index into array
//    - return type : reference to the array cell at the parameter index;
//         value stored in array cell cannot be changed through the
//         returned reference
//    - This version of the operator[] will be called on const objects.
//       The parameter index is required to be a legal index into the
//       array, i.e. lowerBound <= index and index <= upperBound. (Note 
//       that for arrays of size 0, there *is* no legal index.) If the 
//       index is NOT legal, an assertion is triggered. Otherwise, the 
//       function returns a reference to the array cell at the given 
//       index, but the array cell is const (i.e. its value cannot be 
//       changed if accessed through the returned index.
template <typename Etype>
Etype const & Array<Etype>::operator[](int index) const
{
   Assert((lowerBound <= index) && (index <= upperBound), 
                         "Array: illegal index in operator[](int) const");
   return (data[index - lowerBound]);
}




// operator[]
//    - parameters : index - integer index into array
//    - return type : reference to the array cell at the parameter index
//    - This version of the operator[] will be called on non-const objects.
//       The parameter index is required to be a legal index into the
//       array, i.e. lowerBound <= index and index <= upperBound. (Note
//       that for arrays of size 0, there *is* no legal index.) If the
//       index is NOT legal, an assertion is triggered. Otherwise, the
//       function returns a reference to the array cell at the given index.
template <typename Etype>
Etype & Array<Etype>::operator[](int index) 
{
   Assert((lowerBound <= index) && (index <= upperBound), 
                         "Array: illegal index in operator[](int)");
   return (data[index - lowerBound]);
}





// initialize
//    - parameters : initElement - reference to object with which to
//                     initialize the array; that object cannot be
//                     changed through the parameter reference
//    - assigns each cell in the array to hold a copy of parameter value
template <typename Etype>
void Array<Etype>::initialize(Etype const & initElement)
{
   for (int i = lowerBound; i <= upperBound; ++i)
      data[i - lowerBound] = initElement;
}



// setBounds
//    - parameters : theLow - desired new lower bound of array
//                 : theHigh - desired new upper bound of array
//    - theHigh is required to be greater than or equal to theLow - 1; 
//        if it is not, an assertion is triggered. Assuming
//        theHigh >= theLow - 1,assigns object to be a 
//        (theHigh - theLow + 1)-element array. For any indices in
//        the array's new index range (theLow <= index <= theHigh) that 
//        were also in the array's old index range 
//        (lower() <= index <= upper()), the cells at those contain the
//        same values that they contained before this function was called. 
//        For any indices in the array's new index range that were NOT 
//        in the array's old index range, the cells at those indices are 
//        uninitialized (for primitive types) or initialized using the
//        no-argument constructor (for non-primitive types). For any 
//        indices in the array's old index range that are NOT indices in
//        the array's new index range, the values in the cells at those
//        indices are lost, since we no longer have cells with those 
//        indices in our array.
template <typename Etype>
void Array<Etype>::setBounds(int theLow, int theHigh)
{
   Assert(theHigh >= theLow - 1, 
                      "Array: illegal bounds in setBounds(int, int)");

   // create the new array; our member variable "data" will 
   //   ultimately point to this new array
   Etype * newData;
   int newSize = theHigh - theLow + 1;
   if (newSize == 0)
      newData = NULL; 
   else
      newData = new Etype[newSize]; // all values automatically initialized
                                    //  using no-argument constructor of Etype
                                    //  (if Etype is a primitive type, this
                                    //  no-argument constructor does nothing,
                                    //  so cells hold garbage)


   // Deal with the intersection of old and new ranges, if there is one.
   // If one or both of the ranges is size 0, there definitely isn't any
   // intersection. Otherwise, we need to check.
   int lowIntersect, highIntersect;
   if ((theHigh >= theLow) && (upperBound >= lowerBound)) // both size >= 1
   {
      // greater of two low values is low bound of intersection
      if (theLow > lowerBound)
         lowIntersect = theLow;        // new low value
      else
         lowIntersect = lowerBound;    // old low value

      // lowerBound of two high values is high bound of intersection
      if (theHigh < upperBound)
         highIntersect = theHigh;      // new high value
      else
         highIntersect = upperBound;   // old high value
  
      // Transfer data from old to new.
      for (int i = lowIntersect; i <= highIntersect; ++i)
         newData[i - theLow] = data[i - lowerBound];
   }

   delete[] data;    // deallocate old array
   data = newData;   // the new array is now this object's array
   lowerBound = theLow;      // set internal bounds to be equal
   upperBound = theHigh;     //    to the parameter bounds
   onePastLast = data + (upperBound - lowerBound + 1);  // set "end" pointer
}
 

 
 
// size
//    - return value : non-negative integer
//    - returns size of array
template <typename Etype>
int Array<Etype>::size() const 
{
   return (upperBound - lowerBound + 1);
}



// lower
//    - return value : integer index
//    - returns "lower bound" index of array. If array has size >= 1,
//        this will be lowest legal index of array. If array is of 
//        size 0, then this will be an integer one greater than the
//        value returned by upper(), but will not be a legal index.
template <typename Etype>
int Array<Etype>::lower() const 
{ 
   return lowerBound;
}



// upper
//    - return value : integer index
//    - returns "upper bound" of array. If array has size >= 1,
//        this will be highest legal index of array. If array is of
//        size 0, then this will be an integer one less than the
//        value returned by lower(), but will not be a legal index.
template <typename Etype>
int Array<Etype>::upper() const 
{
   return upperBound;
}




// ****************** iterator functions


// begin
//    - return type : iterator
//    - returns an iterator that points to first
//        cell of Array
template <typename Etype>
typename Array<Etype>::iterator Array<Etype>::begin()
{
   return iterator(data);
}



// begin
//    - return type : const_iterator
//    - returns a const_iterator that points to first
//        cell of Array
template <typename Etype>
typename Array<Etype>::const_iterator Array<Etype>::begin() const
{
   return iterator(data);
}




// end
//    - return type : iterator
//    - returns an iterator that points to "after the last cell"
//        so we know we are "off the Array".
template <typename Etype>
typename Array<Etype>::iterator Array<Etype>::end()
{
   // Our functions will treat finish as an iterator
   //   to the cell right after the last one filled
   return iterator(onePastLast);
}



// end
//    - return type : const_iterator
//    - returns an const_iterator that points to "after the last cell"
//        so we know we are "off the Array".
template <typename Etype>
typename Array<Etype>::const_iterator Array<Etype>::end() const
{
   // Our functions will treat finish as an iterator
   //   to the cell right after the last one filled
   return iterator(onePastLast);
}



// rbegin
//    - return type : reverse iterator
//    - returns a reverse iterator that points to
//        first cell of abstract "reverse Array", i.e.
//        last real cell of Array
template <typename Etype>
typename Array<Etype>::reverse_iterator Array<Etype>::rbegin()
{
   return reverse_iterator(onePastLast);
}



// rbegin
//    - return type : const_reverse_iterator
//    - returns a const_reverse_iterator that points to
//        first cell of abstract "reverse Array", i.e.
//        last real cell of Array
template <typename Etype>
typename Array<Etype>::const_reverse_iterator Array<Etype>::rbegin() const
{
   return reverse_iterator(onePastLast);
}




// rend
//    - return type : reverse_iterator
//    - returns a reverse iterator that points to
//        "end position" of abstract "reverse Array",
//         i.e. the abstract "before first cell"
//         spot in Array
template <typename Etype>
typename Array<Etype>::reverse_iterator Array<Etype>::rend()
{
   return reverse_iterator(data);
}



// rend
//    - return type : const_reverse_iterator
//    - returns a const_reverse_iterator that points to
//        "end position" of abstract "reverse Array",
//         i.e. the abstract "before first cell"
//         spot in Array
template <typename Etype>
typename Array<Etype>::const_reverse_iterator Array<Etype>::rend() const
{
   return reverse_iterator(data);
}



