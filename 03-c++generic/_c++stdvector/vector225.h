// *******************************************************************
// *                                                                 *
// *   vector225.h                                                   *    
// *                                                                 *
// *   Interface for a generalized vector class; intended to         *
// *    mostly duplicate the C++ STL vector class, just in a         *
// *    well-commented form that students can learn from a bit       *
// *    more easily                                                  *     
// *                                                                 *
// *   Written June 1998 by Jason Zych                               * 
// *                                                                 *
// *    - changes by Jason Zych July 1999:                           *
// *       - four iterator classes added                             *
// *                                                                 *
// *    - changes by Jason Zych September 2003:                      *
// *       - "typename" added to iterator functions in .cpp file     *    
// *       - old MP function stubs and #include of list225.h removed *
// *       - #ifndef macro changed in .h                             *  
// *                                                                 *
// *   - changes by Jason Zych September 2004:                       *
// *       - standard header includes fixed                          *
// *       - iterator implementation moved to .cpp                   *
// *       - enhanced description of this class in file header       *
// *            and other comments                                   *
// *                                                                 *
// *   - changes made by Jason Zych January 2005:                    *
// *       - fixed bug in implementation of "assign"                 *
// *       - replaced int with bool as comparison return type        *
// *       - no longer using typedef-created types as types          *
// *              elsewhere in this file                             *
// *       - const standardized on right side of modified item       *
// *       - standardized usage of nested-class scoping, the         *
// *              typename keyword, and template params in header    *
// *       - assorted comment maintenance                            *
// *                                                                 *
// *******************************************************************


/*  
   TO THE CS225 STUDENT:


   This file will at first look large and difficult
   to understand. It will make more sense if you realize
   that it is grouped into four sections as follows:


     (1) typedefs

         This first section is not terribly important to you
         right now and you can skip over it if you like. We've
         designed the file so that it can be ignored until you
         specifically want to use these tools. 

         A "typedef" is a type definition. You are taking an
         existing type, and assigning it an additional name. 
         For example, if you wanted to use the name "foo" to
         create integers, you could use the following line:
 
                     typedef int foo;
         
         and from that point on, these two lines:

                     int x;
                     foo x;

         are indentical, i.e. the name "foo" is equivalent to
         the name "int".

         In the case of the vector class, these typedefs --
         -- these "new type names" -- are standard names that exist 
         for every STL class. The idea is that if you are given
         some container object myObj, and you don't know whether 
         it is a vector, or a list, or whatever, you can still say
         myObj::value_type, and that expression will give you
         the type of the value held in this container.


     (2) iterators

         Four kinds of iterators are defined, all of which are
         pretty similar, so once you understand one, you're not
         too far from understanding them all:
 
             iterator 

             const_iterator  
                  same as iterator except you can only read
                  the container through this iterator, not alter it.
                  So, for example, the operator*() function 
                  returns a const reference, so that:

                            cout << *it1 << endl;
   
                  would work, but:

                            *it1 = someValue;

                  would not work. The return value of *it1
                  is const, so you cannot assign to it as with
                  a variable.
                            
             reverse_iterator  
                  same as iterator except that it works in reverse;
                  that is, ++it1 moves the reverse_iterator toward the 
                  front of the container, and --it1 moves the iterator 
                  toward the end of the container, rather than vice-versa 
                  as with (regular) iterators

             const_reverse_iterator
                  same as reverse_iterator except you can only read 
                  the container through this iterator, not alter it, 
                  i.e. const_reverse_iterator is to reverse_iterator
                  as const_iterator is to iterator


     (3) the declarations for the vector member functions themselves


     (4) private data and private member functions 
*/


#ifndef VECTOR_225_H
#define VECTOR_225_H

#include <iostream>


// some forward declarations; we tell the compiler these classes
// and functions exist, so that the compiler knows about their
// existence, but we have more info about them later on.  
template <class Etype> class vector;
template <class Etype> std::ostream& 
      operator<<(std::ostream& Out, vector<Etype> const & theVec);



template <typename Etype>
class vector
{
public:


   // ************************
   // *                      *
   // *  typedefs            *
   // *                      *
   // ************************


   // C++ STL classes have 12 type definitions, so that every class 
   //   defines the following type names as nested types:
   //      
   //     value_type, pointer, reference, const_pointer, const_reference
   //     iterator, const_iterator, reverse_iterator, const_reverse_iterator
   //     allocator_type, size_type, difference_type


   // Here is the first set of five type definitions
   typedef Etype value_type;       // the client can use 
                                   // vector<...>::value_type to access
                                   // whatever type this vector holds

   typedef Etype * pointer;        // vector<...>::pointer is now the same
                                   //  type as a pointer to whatever type
                                   //  the vector holds
 
   typedef Etype & reference;      // vector<...>::reference is now the
                                   //  type as a reference to whatever
                                   //  type the vector holds

   // these two types give you a pointer to a constant item, 
   //  and a reference to a constant item, respectively
   typedef Etype const * const_pointer;
   typedef Etype const & const_reference;


   // Declarations for
   //    iterator
   //    const_iterator
   //    reverse_iterator
   //    const_reverse_iterator
   // appear below.


   // The declarations  
   //    allocator_type
   //    size_type
   //    difference_type
   //  will not be used in CS225 and thus do not appear in this vector class.



   // *********************************************
   // *                                           *
   // *  vector<>::iterator                       *
   // *                                           *
   // *  iterator for our vector class.           *
   // *                                           *
   // *********************************************

   class iterator 
   {
   public:

      // same typedefs as for vector, only now they are in the
      //  iterator class, so (for example), if you want the type
      //  an iterator points to, not only would vector<...>::value_type
      //  work, but so would vector<...>::iterator::value_type.
      //  This is especially helpful once you pass iterator objects
      //  as arguments to generic functions.
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
      typename vector<Etype>::iterator & operator++();

 
      // operator-- (prefix version)
      //    - return type: reference to an iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename vector<Etype>::iterator & operator--();


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
      typename vector<Etype>::iterator operator++(int ignore);


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
      typename vector<Etype>::iterator operator--(int ignore); 


      // operator==
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean with true indicating inequality
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(typename vector<Etype>::iterator const & origVal) const;


      // operator!=
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean with true indicating inequality
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(typename vector<Etype>::iterator const & origVal) const;


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


      // these lines give the vector class and the const_iterator class
      //   access to the above private members of iterator
      friend class vector<Etype>;
      friend class vector<Etype>::const_iterator;
   };




   // *********************************************
   // *                                           *
   // *  vector<>::const_iterator                 *
   // *                                           *
   // *  const_iterator for our vector class.     *
   // *                                           *
   // *********************************************

   class const_iterator
   {
   public:

      // Same typedefs as for vector, only now they are in the
      // const_iterator class, so (for example), if you want the 
      // type an const_iterator points to, not only would 
      // vector<...>::value_type work, but so would 
      // vector<...>::const_iterator::value_type. This is especially 
      // helpful once you pass iterator objects as arguments to generic 
      // functions.
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
      const_iterator(typename vector<Etype>::iterator const & theIter);


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
      typename vector<Etype>::const_iterator & operator++();


      // operator-- (prefix version)
      //    - return type: reference to a const_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename vector<Etype>::const_iterator & operator--();


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
      typename vector<Etype>::const_iterator operator++(int ignore);


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
      typename vector<Etype>::const_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created const_iterator
      //    - return value : boolean with true indicating equality
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(
              typename vector<Etype>::const_iterator const & origVal) const;


      // operator!=
      //    - parameters : origVal - previously created const_iterator
      //    - return value : boolean with true indicating inequality 
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(
              typename vector<Etype>::const_iterator const & origVal) const;



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



      // these lines give the vector class access to the above
      // private members of iterator
      friend class vector<Etype>;
   };





   // ***********************************************
   // *                                             *
   // *  vector<>::reverse_iterator                 *
   // *                                             *
   // *  Reverse iterator for our vector class.     *
   // *                                             *
   // ***********************************************

   class reverse_iterator
   {
   public:

      // Same typedefs as for vector, only now they are in the
      // reverse_iterator class, so (for example), if you want the 
      // type an reverse_iterator points to, not only would 
      // vector<...>::value_type work, but so would 
      // vector<...>::reverse_iterator::value_type. This is especially 
      // helpful once you pass iterator objects as arguments to generic 
      // functions.
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
      typename vector<Etype>::reverse_iterator & operator++();


      // operator-- (prefix version)
      //    - return type: reference to a reverse_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename vector<Etype>::reverse_iterator & operator--();


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
      typename vector<Etype>::reverse_iterator operator++(int ignore);


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
      typename vector<Etype>::reverse_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created reverse_iterator
      //    - return value : boolean with true indicating equality
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(
              typename vector<Etype>::reverse_iterator const & origVal) const;

 
      // operator!=
      //    - parameters : origVal - previously created reverse_iterator
      //    - return value : boolean with true indicating inequality 
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(
              typename vector<Etype>::reverse_iterator const & origVal) const;

    
   private:

      // reverse iterators are implemented by using an iterator to 
      // the position to the right of where we want the reverse 
      // iterator to be. Then when dereferencing the reverse_iterator,
      // we return the value to the left of current
      typename vector<Etype>::iterator current;  



      // reverse_iterator
      //    - constructor
      //    - parameters : assignIter - iterator to the same type of
      //         data to which this reverse_iterator points 
      //    - initializes this reverse_iterator to point to the same
      //       place that the parameter iterator points to
      reverse_iterator(typename vector<Etype>::iterator assignIter);


      // these lines give the vector class and the const_reverse_iterator
      //   class access to the above private members of reverse_iterator
      friend class vector<Etype>;
      friend class vector<Etype>::const_reverse_iterator;
   };


   // ************************************************
   // *                                              *
   // *  vector<>::const_reverse_iterator            *
   // *                                              *
   // *  const_reverse_iterator for our vector class *
   // *                                              *
   // ************************************************

   class const_reverse_iterator
   {
   public:

      // Same typedefs as for vector, only now they are in the
      // const_reverse_iterator class, so (for example), if you want
      // the type an const_reverse_iterator points to, not only would 
      // vector<...>::value_type work, but so would 
      // vector<...>::const_reverse_iterator::value_type. This is 
      // especially helpful once you pass iterator objects as arguments 
      // to generic functions.
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
            typename vector<Etype>::reverse_iterator const & theIter);


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
      typename vector<Etype>::const_reverse_iterator & operator++();


      // operator-- (prefix version)
      //    - return type: reference to a const_reverse_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      typename vector<Etype>::const_reverse_iterator & operator--();


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
      typename vector<Etype>::const_reverse_iterator operator++(int ignore);


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
      typename vector<Etype>::const_reverse_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created const_reverse_iterator
      //    - return value : boolean with true indicating equality 
      //    - returns true if this iterator and the parameter 
      //         iterator point to the same location; else returns false
      bool operator==(
         typename vector<Etype>::const_reverse_iterator const & origVal) const;


      // operator!=
      //    - parameters : origVal - previously created const_reverse_iterator
      //    - return value : boolean with true indicating inequality
      //    - returns true if this iterator and the parameter 
      //         iterator point different locations; else returns false
      bool operator!=(
         typename vector<Etype>::const_reverse_iterator const & origVal) const;



   private:

      // reverse iterators are implemented by using an iterator to 
      // the position to the right of where we want the reverse 
      // iterator to be. Then when dereferencing the reverse_iterator,
      // we return the value to the left of current
      typename vector<Etype>::iterator current;  


      // these lines give the vector class access to the
      //   above private members of const_reverse_iterator
      friend class vector<Etype>;

   };



  

  // ************************
  // *                      *
  // *  vector functions    *
  // *                      *
  // ************************



   // ***** Constructors, etc.

   // vector
   //    - default constructor
   //    - initializes an empty vector
   vector();


   // vector
   //    - constructor
   //    - parameters : requestedSize - desired size of vector
   //    - creates a vector of the parameter size
   vector(int requestedSize);


   // vector
   //    - constructor
   //    - parameters : requestedSize - desired size of vector
   //                   initElem - desired initialization value
   //    - creates a vector of the given size and initializes each
   //         cell using the given initialization value
   vector(int requestedSize, Etype const & initElem); 

 

   // vector
   //    - copy constructor
   //    - parameters : origVal - previously declared vector object
   //    - initializes vector to be a copy of origVal	
   vector(vector<Etype> const & origVal);


 
   // ~vector
   //    - destructor
   //    - deletes dynamically allocated memory	
   ~vector(); 



   // operator=
   //    - parameters : origVal - previously allocated vector object
   //    - return value : reference to vector object
   //    - sets object to be a copy of origVal;  renders all iterators 
   //          to this object invalid
   vector<Etype> const & operator=(vector<Etype> const & origVal);



   // assign
   //    - parameters : vectorSize - new size of vector
   //                 : assignElem - assigning element
   //    - assigns vector to be of given size with each cell
   //        assigned to hold assignElem; renders all iterators
   //        to this object invalid
   void assign(int vectorSize, Etype const & assignElem);




   // ******* iterator functions


   // begin
   //    - return type : iterator
   //    - returns an iterator that points to first
   //        cell of vector
   typename vector<Etype>::iterator begin();


   // begin
   //    - return type : const_iterator
   //    - returns a const_iterator that points to first
   //        cell of vector
   typename vector<Etype>::const_iterator begin() const;


   // end
   //    - return type : iterator
   //    - returns an iterator that points to "after the last cell"
   //        so we know we are "off the vector".
   typename vector<Etype>::iterator end();


   // end
   //    - return type : const_iterator
   //    - returns an const_iterator that points to "after the last cell"
   //        so we know we are "off the vector".
   typename vector<Etype>::const_iterator end() const;


   // rbegin
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        first cell of abstract "reverse vector", i.e.
   //        last real cell of vector
   typename vector<Etype>::reverse_iterator rbegin();


   // rbegin
   //    - return type : const_reverse_iterator
   //    - returns a const_reverse_iterator that points to
   //        first cell of abstract "reverse vector", i.e.
   //        last real cell of vector
   typename vector<Etype>::const_reverse_iterator rbegin() const;


   // rend
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        "end position" of abstract "reverse vector",
   //         i.e. the abstract "before first cell" 
   //         spot in vector 
   typename vector<Etype>::reverse_iterator rend();


   // rend
   //    - return type : const_reverse_iterator
   //    - returns a const_reverse_iterator that points to
   //        "end position" of abstract "reverse vector",
   //         i.e. the abstract "before first cell"
   //         spot in vector
   typename vector<Etype>::const_reverse_iterator rend() const;

 


   // ****** Element Access


   // front
   //    - return type : a reference to a vector element
   //    - returns a reference to the first cell in the vector
   Etype & front();


   // front
   //    - return type : a constant reference to a vector element
   //    - returns a constant reference to the first cell in the vector
   Etype const & front() const;


   // back
   //    - return type : a reference to a vector element
   //    - returns a reference to the last cell in the vector
   Etype & back();


   // back
   //    - return type : a constant reference to a vector element
   //    - returns a constant reference to the last cell in the vector 
   Etype const & back() const;


   // operator[]
   //    - parameters : index - integer index
   //    - return type : reference to value in vector cell;
   //    - returns reference to vector value at location indicated
   //         by index. Due to  the fact that this a reference to the
   //         value and not the value itself, this effectively
   //         means we are returning the vector cell itself, which
   //         can be read for it's value, or else written to with a
   //         *new* value. This function is the operator[] invoked
   //         on non-const objects or references to non-const objects.
   //    - no range checking is done here
   Etype & operator[] (int index);


   // operator[]
   //    - parameters : index - integer index
   //    - return type : constant reference to value in vector cell; 
   //    - returns constant reference to vector value at location 
   //         indicated by index. Since the return value is constant,
   //         this means that the returned cell cannot be used as an
   //         lvalue. This function is the operator[] that will be 
   //         invoked on const objects and references to const objects. 
   //   - no range checking is done here
   Etype const & operator[] (int index) const;					


   // at
   //    - parameters : index - integer index
   //    - return type : reference to value in vector cell;
   //    - returns reference to vector value at location indicated
   //         by index. Due to  the fact that this a reference to the
   //         value and not the value itself, this effectively
   //         means we are returning the vector cell itself, which
   //         can be read for it's value, or else written to with a
   //         *new* value. This function is the operator[] invoked
   //         on non-const objects or references to non-const objects.
   //    - range checking is done here
   Etype & at(int index);


   // at
   //    - parameters : index - integer index
   //    - return type : constant reference to value in vector cell;
   //    - returns constant reference to vector value at location
   //         indicated by index. Since the return value is constant,
   //         this means that the returned cell cannot be used as an
   //         lvalue. This function is the At() that will be
   //         invoked on const objects and references to const objects.
   //    - range checking is done here
   Etype const & at(int index) const; 



   // ********************** (Stack/Queue)-type access


   // push_back
   //    - parameters : insElem - element to insert
   //    - inserts element as last element in vector; this
   //         function potentially renders all iterators
   //         to this vector invalid.
   void push_back(Etype const & insElem);


   // pop_back
   //    - removes last element of vector (but does NOT
   //        return it); assertion triggered if this function
   //        is called on an empty vector
   void pop_back(); 



   // ********************** General list operations 


   // insert
   //    - parameters : insIter - an iterator to the element we want to
   //                     insert before
   //                 : newElem - an element of the vector's type
   //    - inserts newElem before the position indicated by the iterator
   void insert(typename vector<Etype>::iterator insIter, 
                                     Etype const & newElem);



   // insert
   //    - parameters : insIter - an iterator to the element we want
   //                     to insert before
   //                 : the number of copies of our new element that
   //                     we want
   //                 : newElem - an element of the vector's type
   //    - inserts numCopies copies of newElem before the position
   //        indicated by the iterator
   void insert(typename vector<Etype>::iterator insIter, 
                     int numCopies, Etype const & insElem);



   // erase
   //    - parameters : eraseIter - iterator to element to be removed
   //    - removes the element at the current postition of the vector 
   void erase(typename vector<Etype>::iterator eraseIter);



   // erase
   //    - parameters : first - iterator to first element in sequence
   //                     to be removed
   //                 : last - iterator to element after last one to
   //                     be removed (see 3rd Insert comments for more
   //                     explanation)
   //    - removes the sequence [first, last) from this vector 
   void erase(typename vector<Etype>::iterator first, 
              typename vector<Etype>::iterator last);


   // clear
   //    - deletes all values from vector, resulting in an empty vector 
   void clear();



   // ******************* Other operations

   // size
   //    - return value : integer
   //    - returns size of vector 
   int size() const; 


   // empty
   //    - return value : boolean with true indicating emptiness
   //    - returns true if vector is empty; else returns false
   bool empty() const;


   // capacity 
   //    - return value : integer
   //    - returns capacity of vector
   int capacity() const;


   // reserve()
   //    - parameters : numCells - number of cells to reserve
   //    - return value : none
   //    - reserves future space
   void reserve(int numCells);
 
   
   // get_allocator not included
   // max_size not included
   // resize not included
   // swap not included


   // operator==
   //    - parameters : secondVal - another vector object to compare to
   //    - return type : boolean with true indicating equality
   //    - returns true if this vector is equal to secondVal; 
   //           else returns false
   bool operator==(vector<Etype> const & secondVal);
 

   // operator!=
   //    - parameters : secondVal - another vector object to compare to
   //    - return type : boolean with true indicating inequality
   //    - returns true if this vector is not equal to secondVal;
   //           else returns false
   bool operator!=(vector<Etype> const & secondVal);


   // operator<
   //    - parameters : secondVal - another vector object to compare to
   //    - return type : boolean with true indicating "less than"
   //    - returns true if this vector is less than secondVal;
   //           else returns false
   bool operator<(vector<Etype> const & secondVal);


   // operator<<
   //    - friend function of vector class
   //    - parameters : Out - the output stream to which we will write
   //                 : printvector - the vector that we will write to 
   //                                   the output stream
   //    - return value : a reference to the same output stream we passed in
   //    - writes vector values to parameter stream and returns stream
   friend std::ostream& operator<< <Etype> (std::ostream& Out, 
                                      vector<Etype> const & printvector);




private:

   // IncreaseCapacity
   //    - doubles capacity of vector (increases it
   //               by 10 if it is currently 0.
   void IncreaseCapacity(); 

   // A vector has three key points we need to be worried
   // about. You might expect two -- the beginning cell 
   // and the "end" cell. However, part of what makes a vector
   // work efficiently is the fact that we might have more
   // memory allocated than we are using right now -- thus
   // meaning we have room to grow without needing to allocate
   // more memory.
   // 
   // Thus we need to keep track of *two* "end" positions. 
   // First, we need to know the "end" of our actual allocated
   // memory -- that is, the address of the "cell" located 
   // immediately after our final allocated cell. But in addition,
   // we also need to know the "end" of the section of this memory
   // that is actually in use by our conceptual vector -- that
   // is, the address of the "cell" after the final cell the user
   // expects to have. 
  
   Etype  *start,     // pointer to first cell of vector 
          *finish,    // pointer to "end" cell of conceptual vector 
          *onePastEnd; // pointer to "end" cell of actual vector  

   int vectorSize;         // number of elements in conceptual vector
   int vectorCapacity;     // number of cells in actual vector
	 	           //   (could be greater than size, as we
                           //    generally allocate more space in advance
                           //    than we need right now

};


#endif
