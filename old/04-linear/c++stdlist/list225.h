// *****************************************************************
// *                                                               *
// *  list225.h                                                    *
// *                                                               *
// *  This file provides the interface for our abbreviated         *
// *  version of the STL list class. The code is not               *
// *  optimized to the extent that a "real" STL                    *
// *  implementation would be, but it has much of the same         *
// *  functionality, and has more understandable source code.      *
// *                                                               *
// *  Written July 1999 by Jason Zych                              *
// *    - September 2003 : "typename" added to iterator            *
// *                                functions in .cpp              *
// *                     : old MP function stubs and #include      *
// *                          of vector225.h removed               *
// *                     : listNode permissions fixed in .h        *    
// *                     : #ifndef macro changed in .h             * 
// *                                                               *
// *   - September 2004 : changes made by Jason Zych               *
// *                     - standard header includes fixed          *
// *                     - iterator implementation moved to .cpp   *
// *                     - enhanced description of this class in   *
// *                           file header and other comments      *
// *                                                               *   
// ***************************************************************** 



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

         In the case of the list class, these typedefs --
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


     (3) the declarations for the list member functions themselves


     (4) private data and private member functions 
     
*/


#ifndef LIST_225_H
#define LIST_225_H

#include <iostream>
#include <cstddef>

// some forward declarations; we tell the compiler these classes
// and functions exist, so that the compiler knows about their
// existence, but we have more info about them later on.  
template <class Etype> class list;
template<class Etype> std::ostream& 
      operator<< (std::ostream& Out, const list<Etype>& theList);



template <class Etype>
class list
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
                                   // list<...>::value_type to access
                                   // whatever type this list holds

   typedef Etype* pointer;         // list<...>::pointer is now the same
                                   //  type as a pointer to whatever type
                                   //  the list holds
 
   typedef Etype& reference;       // list<...>::reference is now the
                                   //  type as a reference to whatever
                                   //  type the list holds

   // these two types give you a pointer to a constant item, 
   //  and a reference to a constant item, respectively
   typedef const Etype* const_pointer;
   typedef const Etype& const_reference;


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
   //  will not be used in CS225 and thus do not appear in this list class.


public:

   // forward declarations for the iterator classes; that is, we
   // proclaim their existence now, but will add more info later
   // in the file
   class iterator;
   class reverse_iterator;
   class const_iterator;
   class const_reverse_iterator;


private:
    
   // The iterators need access to listNode, which is a private
   // nested type of the list class. So, we need all four iterators
   // to be friends of the list class. If we did not forward declare
   // the iterators above, the lines below would not compile.
   friend class iterator;
   friend class reverse_iterator;
   friend class const_iterator;
   friend class const_reverse_iterator;


   // forward declaration for the listNode implementation class
   class listNode;



public:

   
   // *********************************************
   // *                                           *
   // *  list<>::iterator                         *
   // *                                           *
   // *  iterator for our list class              *
   // *                                           *
   // *********************************************

   class iterator 
   {
   public:

      // same typedefs as for list, only now they are in the
      //  iterator class, so (for example), if you want the type
      //  an iterator points to, not only would list<...>::value_type
      //  work, but so would list<...>::iterator::value_type.
      //  This is especially helpful once you pass iterator objects
      //  as arguments to generic functions.
      typedef Etype value_type;
      typedef Etype* pointer;
      typedef Etype& reference;

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
      reference operator*();

     
      // operator->
      //    - return type : a pointer to the element type
      //    - returns a pointer to the cell storing the element
      //         to which this iterator points.  There is no
      //          error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      pointer operator->();

      
      // operator++ (prefix version)
      //    - return type : reference to an iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      iterator& operator++();

 
      // operator-- (prefix version)
      //    - return type: reference to an iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      iterator& operator--();



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
      iterator operator++(int ignore);


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
      iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point to the same location, 0 else
      int operator==(const iterator& origVal) const;


      // operator!=
      //    - parameters : origVal - previously created iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point different locations, 0 else
      int operator!=(const iterator& origVal) const;



   private:

      // pointer to an internal node of the list; however, the
      // iterator, from the client's point of view, is only 
      // supposed to point to the element inside a listNode, 
      // not to the entire listNode itself. 
      // 
      // The entire iterator object is basically a wrapper for
      // this pointer.
      typename list<value_type>::listNode* ptr; 

   
   
      // iterator
      //    - constructor
      //    - parameters : assignPtr - a pointer to the same type
      //           that this iterator points to
      //    - initializes iterator to point to the same place as
      //         the parameter pointer points to
      iterator(typename list<Etype>::listNode* assignPtr);


      // these lines give the list class and the const_iterator class
      //   access to the above private members of iterator
      friend class list<value_type>;
      friend class list<value_type>::const_iterator;
   };




   // *********************************************
   // *                                           *
   // *  list<>::const_iterator                   *
   // *                                           *
   // *  const_iterator for our list class        *
   // *                                           *
   // *********************************************

   class const_iterator
   {
   public:

      // same typedefs as for list, only now they are in the
      //  iterator class, so (for example), if you want the type
      //  an iterator points to, not only would list<...>::value_type
      //  work, but so would list<...>::iterator::value_type.
      //  This is especially helpful once you pass iterator objects
      //  as arguments to generic functions.
      typedef const Etype value_type;
      typedef const Etype* const_pointer;
      typedef const Etype& const_reference;


      // const_iterator
      //    - constructor
      //    - initializes this const_iterator to point to NULL
      const_iterator();


      // const_iterator
      //    - constructor
      //    - parameters : theIter - an iterator
      //    - initializes this const_iterator to point to the same
      //           location as the parameter iterator
      const_iterator(const iterator& theIter);


      // operator*
      //    - return type : a const_reference to the element type
      //    - returns by const_reference the element to which this
      //         const_iterator points. There is no error checking 
      //         done to ensure that this is a legal cell on which
      //         to perform this operation.
      const_reference operator*() const;


      // operator->
      //    - return type : a const_pointer to the element type
      //    - returns a const_pointer to the element to which
      //        this const_iterator points. There is no error checking 
      //        done to ensure that this is a legal cell on which
      //        to perform this operation.
      const_pointer operator->() const;


      // operator++ (prefix version)
      //    - return type : const_reference to an iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      const_iterator& operator++();


      // operator-- (prefix version)
      //    - return type: const_reference to an iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      const_iterator& operator--();


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
      const_iterator operator++(int ignore);


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
      const_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created const_iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point to the same location, 0 else
      int operator==(const const_iterator& origVal) const;


      // operator!=
      //    - parameters : origVal - previously created const_iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point different locations, 0 else
      int operator!=(const const_iterator& origVal) const;


   private:

      // pointer to an internal node of the list; however, the
      // iterator, from the client's point of view, is only 
      // supposed to point to the element inside a listNode, 
      // not to the entire listNode itself. 
      // 
      // The entire iterator object is basically a wrapper for
      // this pointer.
      typename list<Etype>::listNode* ptr;

      // const_iterator
      //    - constructor
      //    - parameters : assignPtr - a const_pointer to the same type
      //           that this const_iterator points to
      //    - initializes const_iterator to point to the same place as
      //         the parameter pointer points to
      const_iterator(typename list<Etype>::listNode* assignPtr);



      // this line gives the list class access to the above
      // private members of iterator
      friend class list<Etype>;
   };




   // ***********************************************
   // *                                             *
   // *  listr<>::reverse_iterator                  *
   // *                                             *
   // *  reverse_iterator for list class            *
   // *                                             *
   // ***********************************************

   class reverse_iterator
   {
   public:

      // same typedefs as for list, only now they are in the
      //  iterator class, so (for example), if you want the type
      //  an iterator points to, not only would list<...>::value_type
      //  work, but so would list<...>::iterator::value_type.
      //  This is especially helpful once you pass iterator objects
      //  as arguments to generic functions.
      typedef Etype value_type;
      typedef Etype* pointer;
      typedef Etype& reference;



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
      reference operator*();


      // operator->
      //    - return type : a pointer to the element type
      //    - returns a pointer to the cell storing the element
      //         to which this reverse_iterator points.  There is 
      //          no error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      pointer operator->();


      // operator++ (prefix version)
      //    - return type : reference to a reverse_iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      reverse_iterator& operator++();


      // operator-- (prefix version)
      //    - return type: reference to a reverse_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      reverse_iterator& operator--();


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
      reverse_iterator operator++(int ignore);


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
      reverse_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created reverse_iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point to the same location, 0 else
      int operator==(const reverse_iterator& origVal) const;

 
      // operator!=
      //    - parameters : origVal - previously created reverse_iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point different locations, 0 else
      int operator!=(const reverse_iterator& origVal) const;



   private:

      iterator current;  // reverse iterators are implemented
                         // by using an iterator to the position
                         // to the right of where we want the
                         // reverse iterator to be. Then when 
                         // dereferencing the reverse_iterator, we
                         // return the value to the left of current 


      // reverse_iterator
      //    - constructor
      //    - parameters : assignIter - iterator to the same type of
      //         data to which this reverse_iterator points 
      //    - initializes this reverse_iterator to point to the same
      //       place that the parameter iterator points to
      reverse_iterator(iterator assignIter);


      friend class list<value_type>;
      friend class list<value_type>::const_reverse_iterator;
   };




   // ***********************************************
   // *                                             *
   // *  list<>::const_reverse_iterator             *
   // *                                             *
   // *  const_reverse iterator for our list class. *
   // *                                             *
   // ***********************************************

   class const_reverse_iterator
   {
   public:

      // same typedefs as for list, only now they are in the
      //  iterator class, so (for example), if you want the type
      //  an iterator points to, not only would list<...>::value_type
      //  work, but so would list<...>::iterator::value_type.
      //  This is especially helpful once you pass iterator objects
      //  as arguments to generic functions.
      typedef const Etype value_type;
      typedef const Etype* const_pointer;
      typedef const Etype& const_reference;



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
      const_reverse_iterator(const reverse_iterator& theIter);


      // operator*
      //    - return type : a const_reference to the element type
      //    - returns by const_reference the cell storing the element
      //         to which this const_reverse_iterator points.  There is 
      //          no error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      const_reference operator*() const;


      // operator->
      //    - return type : a const_pointer to the element type
      //    - returns a const_pointer to the cell storing the element
      //         to which this const_reverse_iterator points.  There is 
      //          no error checking done to ensure that this is 
      //          a legal cell on which to perform this operation. 
      const_pointer operator->() const;


      // operator++ (prefix version)
      //    - return type : reference to a const_reverse_iterator
      //    - moves this iterator one position forward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.  
      const_reverse_iterator& operator++();


      // operator-- (prefix version)
      //    - return type: reference to a const_reverse_iterator     
      //    - moves this iterator one position backward in the
      //          collection it points to, and then returns
      //          this iterator after moving it. There is no
      //          error checking done to ensure that this is 
      //          a legal position at which to perform this 
      //          operation.
      const_reverse_iterator& operator--();


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
      const_reverse_iterator operator++(int ignore);


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
      const_reverse_iterator operator--(int ignore);


      // operator==
      //    - parameters : origVal - previously created const_reverse_iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point to the same location, 0 else
      int operator==(const const_reverse_iterator& origVal) const;


      // operator!=
      //    - parameters : origVal - previously created const_reverse_iterator
      //    - return value : boolean integer
      //    - returns 1 if this iterator and the parameter 
      //         iterator point different locations, 0 else
      int operator!=(const const_reverse_iterator& origVal) const;



   private:

      iterator current;  // reverse iterators are implemented
                         // by using an iterator to the position
                         // to the right of where we want the
                         // reverse iterator to be. Then when 
                         // dereferencing the reverse_iterator, we
                         // return the value to the left of current 


      // these lines give the list class access to the
      //   above private members of const_reverse_iterator
      friend class list<value_type>;

   };



  // ************************
  // *                      *
  // *  list functions      *
  // *                      *
  // ************************



 // *** Constructors and Big Three

   // list
   //    - default constructor
   //    - creates an empty list
   list();



   // list
   //    - constructor
   //    - parameters : theListSize - number of elements in this list
   //    - creates a list of listSize default elements   
   list(int theListSize); 



   // list
   //    - constructor
   //    - parameters : theListSize - number of elements in this list
   //    - creates a list of listSize elements each initialized to 
   //           initElem 
   list(int theListSize, Etype initElem); 




   // list
   //    - copy constructor
   //    - parameters : origVal - a previously allocated list object
   //    - initializes the list to be a copy of origVal
   list(const list& origVal);



   // ~list
   //    - destructor
   //    - deallocates all dynamically allocated memory inside the list
   ~list();



   // operator=
   //    - parameters: origVal - a previously allocated list object
   //    - return value: reference to the list object
   //    - sets the the list to be a copy of origVal
   list& operator= (const list& origVal);




   // assign
   //    - parameters : listSize - new size of list
   //                 : assignElem - assigning element
   //    - assigns list to be of given size with each cell
   //        assigned to hold assignElem
   void assign(int listSize, Etype assignElem);




 // *** list public functions for iterators

   // begin
   //    - return type : iterator
   //    - returns an iterator that points to first
   //        node of list
   iterator begin();


   // begin
   //    - return type : iterator
   //    - returns an iterator that points to first
   //        node of list
   const_iterator begin() const;


   // end
   //    - return type : iterator
   //    - returns an iterator that points to "after the last node"
   //        so we know we are "off the list".
   iterator end();


   // end
   //    - return type : iterator
   //    - returns an iterator that points to "after the last node"
   //        so we know we are "off the list".
   const_iterator end() const;


   // rbegin
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        first node of abstract "reverse list", i.e.
   //        last real node of list
   reverse_iterator rbegin();



   // rbegin
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        first node of abstract "reverse list", i.e.
   //        last real node of list
   const_reverse_iterator rbegin() const;

 
   // rend
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        "end position" of abstract "reverse list",
   //         i.e. the abstract "before first element"
   //         spot in list  
   reverse_iterator rend();
 

   // rend
   //    - return type : reverse iterator
   //    - returns a reverse iterator that points to
   //        "end position" of abstract "reverse list",
   //         i.e. the abstract "before first element"
   //         spot in list
   const_reverse_iterator rend() const;
 


 // ******** Element access


   // front
   //    - return type : a constant reference to a list element
   //    - returns a constant reference to the first cell in the list 
   const Etype& front() const;


   // front
   //    - return type : a reference to a list element 
   //    - returns a reference to the first cell in the list 
   Etype& front();


   // back 
   //    - return type : a constant reference to a list element 
   //    - returns a constant reference to the first cell in the list 
   const Etype& back() const;


   // back 
   //    - return type : a reference to a list element 
   //    - returns a reference to the first cell in the list 
   Etype& back();



 // ********** (Stack/Queue)-type access


   // push_back
   //    - parameters : insElem - element to insert
   //    - inserts element as last element in list   
   void push_back(Etype insElem);


   // pop_back
   //    - removes last element of list (but does NOT
   //        return it)
   void pop_back(); 
  

   // push_front
   //    - parameters : insElem - element to insert
   //    - inserts element as first element in list
   void push_front(Etype insElem);


   // pop_front
   //    - removes first element of list (but does NOT 
   //        return it. 
   void pop_front(); 



 // *************** General list operations


   // insert
   //    - parameters : insIter - an iterator to the element we want to
   //                     insert before
   //                 : newElem - an element of the list's type
   //    - inserts newElem before the position indicated by the iterator
   void insert(iterator insIter, Etype newElem); 



   // insert
   //    - parameters : insIter - an iterator to the element we want 
   //                     to insert before
   //                 : the number of copies of our new element that 
   //                     we want
   //                 : newElem - an element of the list's type
   //    - inserts numCopies copies of newElem before the position 
   //        indicated by the iterator
   void insert(iterator insIter, int numCopies, Etype insElem);



   // insert
   //    - parameters : insIter - an iterator to the element we want 
   //                     to insert before
   //                 : first - an iterator to the first element in
   //                     a sequence of elements we want to insert 
   //                 : last - an iterator to the element just past
   //                     the last element in the sequence we want 
   //                     to insert (i.e. we are inserting the values
   //                     in the range [first, last) meaning first
   //                     is included, but last is not
   //    - inserts the sequence first (included) through last 
   //        (non-included) into this list before the position 
   //        indicated by insIter
   void insert(iterator insIter, iterator first, iterator last);



   // erase 
   //    - parameters : eraseIter - iterator to element to be removed
   //    - removes the element at the current postition of the list
   void erase(iterator eraseIter);



   // erase
   //    - parameters : first - iterator to first element in sequence
   //                     to be removed
   //                 : last - iterator to element after last one to
   //                     be removed (see 3rd insert comments for more
   //                     explanation) 
   //    - removes the sequence [first, last) from this list
   void erase(iterator first, iterator last);  


   // clear
   //    - deletes all values from list, resulting in an empty list
   void clear();


// **************** Other general operations

   // size
   //    - parameters : none
   //    - return value : integer
   //    - returns size of list 
   int size() const; 


   // Empty
   //    - parameters : none
   //    - return value : boolean integer
   //    - returns 1 if list is empty, 0 else
   int empty() const;


   // operator==
   //    - parameters : secondVal - another list object to compare to
   //    - return type : boolean integer
   //    - returns 1 if this list is equal to secondVal, 0 else 
   int operator==(const list& secondVal);

 

   // operator!=
   //    - parameters : secondVal - another list object to compare to
   //    - return type : boolean integer
   //    - returns 1 if this list is not equal to secondVal, 0 else 
   int operator!=(const list& secondVal);


   // operator<
   //    - parameters : secondVal - another list object to compare to
   //    - return type : boolean integer
   //    - returns 1 if this list is less than secondVal, 0 else 
   int operator<(const list& secondVal);




// **************  list-class-specific operations


   // merge and splice to be added later

   // split
   // 	- parameters: pos - the position where we want to split the list
   //   - this list will be splitted into two list before pos, and the new 
   //		list will be from pos on.
   list<Etype> split(iterator pos);




   // operator<<
   //    - friend function of list class
   //    - parameters : Out - the output stream to which we will write
   //                 : printlist - the list that we will write to the 
   //                                                   output stream
   //    - return value : a reference to the same output stream we passed in
   //    - writes list values to parameter stream and returns stream
   friend std::ostream&
              operator<< <Etype> (std::ostream& Out, 
                                             const list<Etype>& printlist);


private:

   class listNode
   {
   public:    // public within context of list class
              // protected outside list class

      // listNode Constructor
      listNode() { prev = NULL; next = NULL; }
      listNode(Etype elem) { prev=NULL; next = NULL; element = elem; }

      Etype element;
      listNode* next;
      listNode* prev;
   };


private:

   listNode *headerNode;  

   int listSize;          // number of nodes in list


};

#endif 

   

