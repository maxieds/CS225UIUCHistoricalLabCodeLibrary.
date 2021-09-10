// *****************************************************
// *                                                   *
// *   array.h                                         *
// *                                                   *
// *   Interface for a generalized array class         *
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

/*  
   TO THE CS225 STUDENT:

   See the vector225.h file for a full description of the
   standard container class typedefs and iterators.

*/


#ifndef ARRAY_225_H
#define ARRAY_225_H

template <typename Etype>
class Array
{
public:


   // ************************
   // *                      *
   // *  typedefs            *
   // *                      *
   // ************************

   typedef Etype value_type;      
   typedef Etype * pointer;        
   typedef Etype & reference;     
   typedef Etype const * const_pointer;
   typedef Etype const & const_reference;



   // *********************************************
   // *                                           *
   // *  Array<>::iterator                        *
   // *                                           *
   // *  iterator for our Array class.            *
   // *                                           *
   // *********************************************

   class iterator 
   {
   public:

      // typedefs
      typedef Etype value_type;
      typedef Etype * pointer;
      typedef Etype & reference;


      // iterator
      //    - constructor
      //    - initializes this iterator to point to NULL
      iterator();


      // operator*
      //    - return type : a reference to the element type
      //    - returns by reference the cell storing the element
      //         to which this iterator points.  There is no
      //          error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      Etype & operator*();

     
      // operator->
      //    - return type : a pointer to the element type
      //    - returns a pointer to the cell storing the element
      //         to which this iterator points.  There is no
      //          error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      Etype * operator->();

      
      // operator++ (prefix version)
      //    - return type : reference to an iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      typename Array<Etype>::iterator & operator++();

 
      // operator-- (prefix version)
      //    - return type: reference to an iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename Array<Etype>::iterator & operator--();


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
      typename Array<Etype>::iterator operator++(int ignore);


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
      typename Array<Etype>::iterator operator--(int ignore); 


      // operator==
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean with true indicating inequality
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(typename Array<Etype>::iterator const & origVal) const;


      // operator!=
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean with true indicating inequality
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(typename Array<Etype>::iterator const & origVal) const;


   private:

      Etype * ptr;   // pointer to whatever type of value this
                     // iterator is meant to point to; the entire 
                     // iterator object is basically a wrapper for 
                     // this pointer.


      // iterator
      //    - constructor
      //    - parameters : assignPtr - a pointer to the same type
      //           that this iterator points to
      //    - initializes iterator to point to the same place as
      //         the parameter pointer points to
      iterator(Etype * assignPtr);


      // these lines give the Array class and the const_iterator class
      //   access to the above private members of iterator
      friend class Array<Etype>;
      friend class Array<Etype>::const_iterator;
   };




   // *********************************************
   // *                                           *
   // *  Array<>::const_iterator                  *
   // *                                           *
   // *  const_iterator for our Array class.      *
   // *                                           *
   // *********************************************

   class const_iterator
   {
   public:

      // typedefs
      typedef Etype value_type;
      typedef Etype const * const_pointer;
      typedef Etype const & const_reference;


      // const_iterator
      //    - constructor
      //    - initializes this iterator to point to NULL
      const_iterator();


      // const_iterator
      //    - constructor
      //    - parameters : theIter - an iterator
      //    - initializes this const_iterator to point to the same
      //           location as the parameter iterator
      const_iterator(typename Array<Etype>::iterator const & theIter);


      // operator*
      //    - return type : a reference to a value of the element type,
      //        a value that cannot be altered through this reference
      //    - returns by reference the element to which this
      //         const_iterator points; it will not be possible to change
      //         that value through the returned reference. There is no 
      //         error checking done to ensure that this is a legal cell on 
      //         which to perform this operation.
      Etype const & operator*() const;


      // operator->
      //    - return type : a pointer to a value of the element type,
      //        a value that cannot be altered through this pointer
      //    - returns a pointer to the element to which this 
      //        const_iterator points; it will not be possible to change
      //        that value through the returned pointer. There is no error
      //        checking done to ensure that this is a legal cell on which
      //        to perform this operation.
      Etype const * operator->() const;


      // operator++ (prefix version)
      //    - return type : reference to a const_iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      typename Array<Etype>::const_iterator & operator++();


      // operator-- (prefix version)
      //    - return type: reference to a const_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename Array<Etype>::const_iterator & operator--();


      // operator++ (postfix version)
      //    - parameters : ignore - argument always the integer 1, to 
      //                       distinguish this from prefix version
      //    - return type : a const_iterator
      //    - moves this iterator one position forward in the 
      //          collection it points to, and then returns an
      //          iterator to the position this iterator pointed
      //          to before this function was run. There is no
      //          error checking done to ensure that this is a
      //          legal position at which to perform this operation. 
      typename Array<Etype>::const_iterator operator++(int ignore);


      // operator-- (postfix version)
      //    - parameters : ignore - argument always the integer 1, to 
      //                       distinguish this from prefix version
      //    - return type : a const_iterator
      //    - moves this iterator one position backward in the 
      //          collection it points to, and then returns an
      //          iterator to the position this iterator pointed
      //          to before this function was run. There is no
      //          error checking done to ensure that this is a
      //          legal position at which to perform this operation. 
      typename Array<Etype>::const_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created const_iterator
      //    - return value : boolean with true indicating equality
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(
              typename Array<Etype>::const_iterator const & origVal) const;


      // operator!=
      //    - parameters : origVal - previously created const_iterator
      //    - return value : boolean with true indicating inequality 
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(
              typename Array<Etype>::const_iterator const & origVal) const;



   private:


      Etype * ptr;   // pointer to whatever type of value this
                     // const_iterator is meant to point to; the entire 
                     // const_iterator object is basically a wrapper for 
                     // this pointer.


      // const_iterator
      //    - constructor
      //    - parameters : assignPtr - a const_pointer to the same type
      //           that this const_iterator points to
      //    - initializes const_iterator to point to the same place as
      //         the parameter pointer points to
      const_iterator(Etype const * assignPtr);



      // these lines give the Array class access to the above
      // private members of iterator
      friend class Array<Etype>;
   };





   // ***********************************************
   // *                                             *
   // *  Array<>::reverse_iterator                  *
   // *                                             *
   // *  Reverse iterator for our Array class.      *
   // *                                             *
   // ***********************************************

   class reverse_iterator
   {
   public:

      // typedefs
      typedef Etype value_type;
      typedef Etype * pointer;
      typedef Etype & reference;


      // reverse_iterator
      //    - constructor
      //    - initializes this reverse_iterator to point to NULL
      reverse_iterator();


      // operator*
      //    - return type : a reference to the element type
      //    - returns by reference the cell storing the element
      //         to which this reverse_iterator points.  There is 
      //          no error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      Etype & operator*();


      // operator->
      //    - return type : a pointer to the element type
      //    - returns a pointer to the cell storing the element
      //         to which this reverse_iterator points.  There is 
      //          no error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      Etype * operator->();


      // operator++ (prefix version)
      //    - return type : reference to a reverse_iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      typename Array<Etype>::reverse_iterator & operator++();


      // operator-- (prefix version)
      //    - return type: reference to a reverse_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename Array<Etype>::reverse_iterator & operator--();


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
      typename Array<Etype>::reverse_iterator operator++(int ignore);


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
      typename Array<Etype>::reverse_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created reverse_iterator
      //    - return value : boolean with true indicating equality
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(
              typename Array<Etype>::reverse_iterator const & origVal) const;

 
      // operator!=
      //    - parameters : origVal - previously created reverse_iterator
      //    - return value : boolean with true indicating inequality 
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(
              typename Array<Etype>::reverse_iterator const & origVal) const;

    
   private:

      // reverse iterators are implemented by using an iterator to 
      // the position to the right of where we want the reverse 
      // iterator to be. Then when dereferencing the reverse_iterator,
      // we return the value to the left of current
      typename Array<Etype>::iterator current;  


      // reverse_iterator
      //    - constructor
      //    - parameters : assignIter - iterator to the same type of
      //         data to which this reverse_iterator points 
      //    - initializes this reverse_iterator to point to the same
      //       place that the parameter iterator points to
      reverse_iterator(typename Array<Etype>::iterator assignIter);


      // these lines give the Array class and the const_reverse_iterator
      //   class access to the above private members of reverse_iterator
      friend class Array<Etype>;
      friend class Array<Etype>::const_reverse_iterator;
   };


   // ************************************************
   // *                                              *
   // *  Array<>::const_reverse_iterator             *
   // *                                              *
   // *  const_reverse_iterator for our Array class  *
   // *                                              *
   // ************************************************

   class const_reverse_iterator
   {
   public:

      // typedefs
      typedef Etype value_type;
      typedef Etype const * const_pointer;
      typedef Etype const & const_reference;


      // const_reverse_iterator
      //    - constructor
      //    - initializes this const_reverse_iterator to NULL
      const_reverse_iterator();


      // const_reverse_iterator
      //    - constructor
      //    - parameters : theIter - a reverse_iterator which points
      //           to the same time as this const_reverse_iterator
      //    - initializes this const_reverse_iterator to point to the
      //        same place to which the parameter reverses_iterator
      //        points
      const_reverse_iterator(
            typename Array<Etype>::reverse_iterator const & theIter);


      // operator*
      //    - return type : a reference to a value of the element type,
      //        a value that cannot be altered through this reference
      //    - returns by reference the element to which this
      //         const_reverse_iterator points; it will not be possible to 
      //         change that value through the returned reference. There is no 
      //         error checking done to ensure that this is a legal cell on 
      //         which to perform this operation.
      Etype const & operator*() const;


      // operator->
      //    - return type : a pointer to a value of the element type,
      //        a value that cannot be altered through this pointer
      //    - returns a pointer to the element to which this 
      //        const_reverse_iterator points; it will not be possible to 
      //        change that value through the returned pointer. There is no 
      //        error checking done to ensure that this is a legal cell on 
      //        which to perform this operation.
      Etype const * operator->() const;


      // operator++ (prefix version)
      //    - return type : reference to a const_reverse_iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      typename Array<Etype>::const_reverse_iterator & operator++();


      // operator-- (prefix version)
      //    - return type: reference to a const_reverse_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename Array<Etype>::const_reverse_iterator & operator--();


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
      typename Array<Etype>::const_reverse_iterator operator++(int ignore);


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
      typename Array<Etype>::const_reverse_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created const_reverse_iterator
      //    - return value : boolean with true indicating equality 
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(
         typename Array<Etype>::const_reverse_iterator const & origVal) const;


      // operator!=
      //    - parameters : origVal - previously created const_reverse_iterator
      //    - return value : boolean with true indicating inequality
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(
         typename Array<Etype>::const_reverse_iterator const & origVal) const;



   private:

      // reverse iterators are implemented by using an iterator to 
      // the position to the right of where we want the reverse 
      // iterator to be. Then when dereferencing the reverse_iterator,
      // we return the value to the left of current
      typename Array<Etype>::iterator current;  


      // these lines give the Array class access to the
      //   above private members of const_reverse_iterator
      friend class Array<Etype>;

   };



  

   // ************************
   // *                      *
   // *  Array functions     *
   // *                      *
   // ************************


   // ***** Constructors, etc.

   // Array
   //    - constructor
   //    - initializes object to be a zero-element array; low and high
   //        indices will be 0 and -1, respectively
   Array();


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
   Array(int low, int high); 


   // Array
   //    - constructor
   //    - parameters : origVal - reference to previously-created Array
   //                    object; that Array object cannot be changed through
   //                    the parameter reference
   //    - initializes array to be a copy of origVal	
   Array(Array<Etype> const & origVal);

 
   // ~Array
   //    - destructor
   //    - deletes dynamically allocated memory	
   ~Array(); 


   // operator=
   //    - parameters : origVal - reference to previously-created Array
   //                    object; that Array object cannot be changed through
   //                    the parameter reference
   //    - return value : reference to this Array object, after the
   //        assignment operation has been performed; we cannot change this 
   //        object through the returned reference
   //    - assigns this object to be a copy of origVal
   Array<Etype> const & operator=(Array<Etype> const & origVal);


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
   Etype const & operator[](int index) const;					


   // operator[]
   //    - parameters : index - integer index into array
   //    - return type : reference to the array cell at the parameter index
   //    - This version of the operator[] will be called on non-const objects.
   //       The parameter index is required to be a legal index into the
   //       array, i.e. lowerBound <= index and index <= upperBound. (Note
   //       that for arrays of size 0, there *is* no legal index.) If the
   //       index is NOT legal, an assertion is triggered. Otherwise, the
   //       function returns a reference to the array cell at the given index.
   Etype & operator[](int index);


   // initialize
   //    - parameters : initElement - reference to object with which to 
   //                     initialize the array; that object cannot be
   //                     changed through the parameter reference
   //    - assigns each cell in the array to hold a copy of parameter value
   void initialize(Etype const & initElement);


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
   void setBounds(int theLow, int theHigh);


   // size
   //    - return value : non-negative integer
   //    - returns size of array  
   int size() const; 


   // lower
   //    - return value : integer index
   //    - returns "lower bound" index of array. If array has size >= 1,
   //        this will be lowest legal index of array. If array is of 
   //        size 0, then this will be an integer one greater than the
   //        value returned by upper(), but will not be a legal index.
   int lower() const; 


   // upper
   //    - return value : integer index
   //    - returns "upper bound" of array. If array has size >= 1,
   //        this will be highest legal index of array. If array is of
   //        size 0, then this will be an integer one less than the
   //        value returned by lower(), but will not be a legal index.
   int upper() const; 



   // ******* iterator functions

   // begin
   //    - return type : iterator
   //    - returns an iterator that points to first
   //        cell of Array
   typename Array<Etype>::iterator begin();


   // begin
   //    - return type : const_iterator
   //    - returns a const_iterator that points to first
   //        cell of Array
   typename Array<Etype>::const_iterator begin() const;


   // end
   //    - return type : iterator
   //    - returns an iterator that points to "after the last cell"
   //        so we know we are "off the Array".
   typename Array<Etype>::iterator end();


   // end
   //    - return type : const_iterator
   //    - returns an const_iterator that points to "after the last cell"
   //        so we know we are "off the Array".
   typename Array<Etype>::const_iterator end() const;


   // rbegin
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        first cell of abstract "reverse Array", i.e.
   //        last real cell of Array
   typename Array<Etype>::reverse_iterator rbegin();


   // rbegin
   //    - return type : const_reverse_iterator
   //    - returns a const_reverse_iterator that points to
   //        first cell of abstract "reverse Array", i.e.
   //        last real cell of Array
   typename Array<Etype>::const_reverse_iterator rbegin() const;


   // rend
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        "end position" of abstract "reverse Array",
   //         i.e. the abstract "before first cell" 
   //         spot in Array 
   typename Array<Etype>::reverse_iterator rend();


   // rend
   //    - return type : const_reverse_iterator
   //    - returns a const_reverse_iterator that points to
   //        "end position" of abstract "reverse Array",
   //         i.e. the abstract "before first cell"
   //         spot in Array
   typename Array<Etype>::const_reverse_iterator rend() const;


private:

   int lowerBound;       // lower bound 
   int upperBound;       // upper bound
   Etype * data;         // pointer to the start of the array elements. 
   Etype * onePastLast;  // pointer to the memory one past end of array

};


#endif
