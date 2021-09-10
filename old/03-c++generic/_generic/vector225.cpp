// ******************************************************************
// *                                                                *
// *   vector.cpp                                                   *
// *                                                                *
// *   Implementation for a generalized vector class; intended to   *
// *    mostly duplicate the C++ STL vector class, just in a        *
// *    well-commented form that students can learn from a bit      *
// *    more easily                                                 *
// *                                                                *
// *   Written 6/16/98 by Jason Zych                                *
// *    - July 1999 : changes made by Jason Zych                    *
// *                     - four iterator classes added              *
// *                                                                *
// *    - September 2003 : changes made by Jason Zych               *
// *                     - "typename" added to iterator functions   *
// *                           in the vector.cpp file               *
// *                     - old MP function stubs and #include       *
// *                           of list225.h removed                 *
// *                     - #ifndef macro changed in .h              *
// *                                                                *
// *   - September 2004 : changes made by Jason Zych                *
// *                     - standard header includes fixed           *
// *                     - iterator implementation moved to .cpp    *
// *                     - enhanced description of this class in    *
// *                           file header and other comments       *
// *                                                                *
// ******************************************************************


 
#include <iostream>
#include <cstddef>
#include "vector225.h"
#include "asserts.h"


// ***********************************************************
// *        member functions for the iterator class          *
// ***********************************************************



// iterator
//    - constructor
//    - initializes this iterator to point to NULL
template <class Etype>
vector<Etype>::iterator::iterator() 
{
   ptr = NULL;
}


// operator*
//    - return type : a reference to the element type
//    - returns by reference the cell storing the element
//         to which this iterator points.  There is no 
//          error checking done to ensure that this is 
//          a legal cell on which to perform this operation. 
template <class Etype>
typename vector<Etype>::reference vector<Etype>::iterator::operator*() 
{ 
   return *ptr;  
}


// operator->
//    - return type : a pointer to the element type
//    - returns a pointer to the cell storing the element
//         to which this iterator points.  There is no 
//          error checking done to ensure that this is 
//          a legal cell on which to perform this operation. 
template <class Etype>
typename vector<Etype>::pointer vector<Etype>::iterator::operator->()  
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
template <class Etype>
typename vector<Etype>::iterator& vector<Etype>::iterator::operator++() 
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
template <class Etype>
typename vector<Etype>::iterator& vector<Etype>::iterator::operator--() 
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
template <class Etype>
typename vector<Etype>::iterator vector<Etype>::iterator::operator++(int ignore) 
{
   typename vector<Etype>::iterator temp = *this;
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
template <class Etype>
typename vector<Etype>::iterator vector<Etype>::iterator::operator--(int ignore) 
{
   typename vector<Etype>::iterator temp = *this;
   ptr = ptr - 1;  // pointer arithmetic, not integer addition
   return temp;
}


// operator==
//    - parameters : origVal - previously created iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point to the same location, 0 else
template <class Etype>
int vector<Etype>::iterator::operator==(
                 typename const vector<Etype>::iterator& origVal) const
{ 
   return (ptr == origVal.ptr); 
}


// operator!=
//    - parameters : origVal - previously created iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point different locations, 0 else
template <class Etype>
int vector<Etype>::iterator::operator!=(
                 typename const iterator& origVal) const
{ 
   return (ptr != origVal.ptr); 
}




// iterator
//    - constructor
//    - parameters : assignPtr - a pointer to the same type
//           that this iterator points to
//    - initializes iterator to point to the same place as
//         the parameter pointer points to
template <class Etype>
vector<Etype>::iterator::iterator(pointer assignPtr) 
{ 
   ptr = assignPtr; 
}




// ***********************************************************
// *     member functions for the const_iterator class       *
// ***********************************************************



// const_iterator
//    - constructor
//    - initializes this const_iterator to point to NULL
template <class Etype>
vector<Etype>::const_iterator::const_iterator() 
{
   ptr = NULL;
}



// const_iterator
//    - constructor
//    - parameters : theIter - an iterator
//    - initializes this const_iterator to point to the same
//           location as the parameter iterator
template <class Etype>
vector<Etype>::const_iterator::const_iterator(const iterator& theIter) 
{
   ptr = theIter.ptr;
}




// operator*
//    - return type : a const_reference to the element type
//    - returns by const_reference the cell storing the element
//         to which this constiterator points.  There is no 
//          error checking done to ensure that this is 
//          a legal cell on which to perform this operation. 
template <class Etype>
typename vector<Etype>::reference 
                      vector<Etype>::const_iterator::operator*() const
{ 
   return *ptr;  
}


// operator->
//    - return type : a const_pointer to the element type
//    - returns a const_pointer to the cell storing the element
//         to which this const_iterator points.  There is no 
//          error checking done to ensure that this is 
//          a legal cell on which to perform this operation. 
template <class Etype>
typename vector<Etype>::pointer 
                      vector<Etype>::const_iterator::operator->() const
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
template <class Etype>
typename vector<Etype>::const_iterator& 
                      vector<Etype>::const_iterator::operator++() 
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
template <class Etype>
typename vector<Etype>::const_iterator& 
                      vector<Etype>::const_iterator::operator--() 
{ 
   ptr = ptr - 1;   // pointer arithmetic, not integer addition
   return *this; 
}



// operator++ (postfix version)
//    - parameters : ignore - argument always the integer 1, to 
//                       distinguish this from prefix version
//    - return type : an const_iterator
//    - moves this const_iterator one position forward in the 
//          collection it points to, and then returns an
//          const_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation. 
template <class Etype>
typename vector<Etype>::const_iterator 
                      vector<Etype>::const_iterator::operator++(int ignore) 
{
   typename vector<Etype>::const_iterator temp = *this;
   ptr = ptr + 1;    //  pointer arithmetic, not integer addition
   return temp;
}


// operator-- (postfix version)
//    - parameters : ignore - argument always the integer 1, to 
//                       distinguish this from prefix version
//    - return type : an const_iterator
//    - moves this const_iterator one position backward in the 
//          collection it points to, and then returns an
//          const_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation. 
template <class Etype>
typename vector<Etype>::const_iterator 
                      vector<Etype>::const_iterator::operator--(int ignore) 
{
   typename vector<Etype>::const_iterator temp = *this;
   ptr = ptr - 1;   // pointer arithmetic, not integer addition
   return temp;
}


// operator==
//    - parameters : origVal - previously created const_iterator
//    - return value : boolean integer
//    - returns 1 if this const_iterator and the parameter
//         const_iterator point to the same location, 0 else
template <class Etype>
int vector<Etype>::const_iterator::operator==(
          typename const vector<Etype>::const_iterator& origVal) const
{ 
   return (ptr == origVal.ptr); 
}


// operator!=
//    - parameters : origVal - previously created const_iterator
//    - return value : boolean integer
//    - returns 1 if this const_iterator and the parameter
//         const_iterator point different locations, 0 else
template <class Etype>
int vector<Etype>::const_iterator::operator!=(
            typename const vector<Etype>::const_iterator& origVal) const
{ 
   return (ptr != origVal.ptr); 
}



// const_iterator
//    - constructor
//    - parameters : assignPtr - a const_pointer to the same type
//           that this const_iterator points to
//    - initializes const_iterator to point to the same place as
//         the parameter pointer points to
template <class Etype>
vector<Etype>::const_iterator::const_iterator(const_pointer assignPtr) 
{ 
   ptr = assignPtr; 
}




// ***********************************************************
// *     member functions for the reverse_iterator class     * 
// ***********************************************************


// reverse_iterator
//    - constructor
//    - initializes this reverse_iterator to point to NULL
template <class Etype>
vector<Etype>::reverse_iterator::reverse_iterator() : current()
{
   // initializer list used above; no code needed here
}


// operator*
//    - return type : a reference to the element type
//    - returns by reference the cell storing the element
//         to which this reverse_iterator points.  There is
//          no error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename vector<Etype>::reference
                      vector<Etype>::reverse_iterator::operator*()
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
template <class Etype>
typename vector<Etype>::pointer 
                      vector<Etype>::reverse_iterator::operator->() 
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
template <class Etype>
typename vector<Etype>::reverse_iterator&
             vector<Etype>::reverse_iterator::operator++() 
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
template <class Etype>
typename vector<Etype>::reverse_iterator&
             vector<Etype>::reverse_iterator::operator--()
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
template <class Etype>
typename vector<Etype>::reverse_iterator 
                      vector<Etype>::reverse_iterator::operator++(int ignore)
{
   typename vector<Etype>::reverse_iterator temp = *this;
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
template <class Etype>
typename vector<Etype>::reverse_iterator
                      vector<Etype>::reverse_iterator::operator--(int ignore)
{
   typename vector<Etype>::reverse_iterator temp = *this;
   ++current;
   return temp;
}


// operator==
//    - parameters : origVal - previously created reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point to the same location, 0 else
template <class Etype>
int vector<Etype>::reverse_iterator::operator==(
             typename const vector<Etype>::reverse_iterator& origVal) const
{ 
   return (current == origVal.current); 
}



// operator!=
//    - parameters : origVal - previously created reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point different locations, 0 else
template <class Etype>
int vector<Etype>::reverse_iterator::operator!=(
         typename const vector<Etype>::reverse_iterator& origVal) const
{ 
   return (current != origVal.current); 
}



   

// reverse_iterator
//    - constructor
//    - parameters : assignPtr - pointer to the same type of
//          data to which this reverse_iterator points 
//    - initializes this reverse_iterator to point to the same
//       place that the parameter pointer points to
template <class Etype>
vector<Etype>::reverse_iterator::reverse_iterator(
                       typename vector<Etype>::pointer assignPtr)
{
   current = assignPtr;
}




// reverse_iterator
//    - constructor
//    - parameters : assignIter - iterator to the same type of 
//         data to which this reverse_iterator points
//    - initializes this reverse_iterator to point to the same
//       place that the parameter iterator points to
template <class Etype>
vector<Etype>::reverse_iterator::reverse_iterator(
                      typename vector<Etype>::iterator assignIter)
{
   current = assignIter;
}







// ***********************************************************
// *  member functions for the const_reverse_iterator class  *
// ***********************************************************


// const_reverse_iterator
//    - constructor
//    - initializes this const_reverse_iterator to point to NULL
template <class Etype>
vector<Etype>::const_reverse_iterator::const_reverse_iterator() : current()
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
template <class Etype>
vector<Etype>::const_reverse_iterator::const_reverse_iterator(
               typename const vector<Etype>::reverse_iterator& theIter) 
{
   current = theIter.current;
}




// operator*
//    - return type : a reference to the element type
//    - returns by reference the cell storing the element
//         to which this const_reverse_iterator points.  There is
//          no error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename vector<Etype>::reference
                      vector<Etype>::const_reverse_iterator::operator*()
{
   iterator temp = current;
   --temp;
   return *temp;
}


// operator->
//    - return type : a pointer to the element type
//    - returns a pointer to the cell storing the element
//         to which this const_reverse_iterator points.  There is
//          no error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename vector<Etype>::pointer 
                      vector<Etype>::const_reverse_iterator::operator->() 
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
template <class Etype>
typename vector<Etype>::const_reverse_iterator&
             vector<Etype>::const_reverse_iterator::operator++() 
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
template <class Etype>
typename vector<Etype>::const_reverse_iterator&
             vector<Etype>::const_reverse_iterator::operator--()
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
template <class Etype>
typename vector<Etype>::const_reverse_iterator 
                      vector<Etype>::const_reverse_iterator::operator++(int ignore)
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
template <class Etype>
typename vector<Etype>::const_reverse_iterator
                      vector<Etype>::const_reverse_iterator::operator--(int ignore)
{
   const_reverse_iterator temp = *this;
   ++current;
   return temp;
}


// operator==
//    - parameters : origVal - previously created const_reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point to the same location, 0 else
template <class Etype>
int vector<Etype>::const_reverse_iterator::operator==(
             typename const vector<Etype>::const_reverse_iterator& origVal) const
{ 
   return (current == origVal.current); 
}



// operator!=
//    - parameters : origVal - previously created const_reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point different locations, 0 else
template <class Etype>
int vector<Etype>::const_reverse_iterator::operator!=(
         typename const vector<Etype>::const_reverse_iterator& origVal) const
{ 
   return (current != origVal.current); 
}





// const_reverse_iterator
//    - constructor
//    - parameters : assignPtr - const_ptr to some value 
//    - initializes this const_reverse_iterator to point
//        to same place as parameter pointer
template <class Etype>
vector<Etype>::const_reverse_iterator::const_reverse_iterator(
             typename vector<Etype>::const_pointer assignPtr)
{
   current = iterator(assignPtr);
}










// ***********************************************************
// *         member functions for the vector class           *
// ***********************************************************


// vector
//    - default constructor
//    - initializes an empty vector
template <class Etype>
vector<Etype>::vector()
{
   // default to an empty vector 

   // pointers all point to NULL
   start = NULL;
   finish = NULL;
   onePastEnd = NULL;

   // both integers are 0
   vectorCapacity = 0;
   vectorSize = 0;
}




// vector
//    - constructor
//    - parameters : requestedSize - desired size of vector
//    - creates a vector of the parameter size
template <class Etype>
vector<Etype>::vector(int requestedSize)
{
   // start holds starting address of new array
   //   i.e. address of first cell of new array
   start = new Etype[requestedSize];

   finish = &(start[requestedSize]);
   onePastEnd = (start + requestedSize);  // same place as above line
   
   vectorCapacity = requestedSize;
   vectorSize = requestedSize;
}




// vector
//    - constructor
//    - parameters : reqestedSize - desired vectorSize of vector
//                   initElem - desired initialization value
//    - creates a vector of the given size and initializes each
//         cell using the given initialization value
template <class Etype>
vector<Etype>::vector(int requestedSize, Etype initElem) 
{
   // same code as in above constructor...
   start = new Etype[requestedSize];
   finish = (start + requestedSize);
   onePastEnd = (start + requestedSize);

   // ...plus traverse array to initialize cells 
   for (int i = 0; i < requestedSize; i++)
      start[i] = initElem;

   vectorCapacity = requestedSize;
   vectorSize = requestedSize; 
}






// vector
//    - copy constructor
//    - parameters : origVal - previously declared vector object
//    - initializes array to be a copy of origVal   
template <class Etype>
vector<Etype>::vector(const vector<Etype>& origVal)
{
   vectorCapacity = origVal.vectorCapacity;
   vectorSize = origVal.vectorSize;
   
   start = new Etype[vectorCapacity];
   finish = (start + vectorSize);
   onePastEnd = (start + vectorCapacity);

   for (int i = 0; i < vectorCapacity; i++)
      start[i] = (origVal.start)[i];
}


 
// ~vector
//    - destructor
//    - deleted dynamically allocated memory
template <class Etype>
vector<Etype>::~vector() 
{
   delete[] start; 
}



// operator=
//    - parameters : origVal - previously allocated vector object
//    - return value : reference to vector object
//    - sets object to be a copy of origVal; renders all iterators 
//          to this object invalid
template <class Etype>
const vector<Etype>& vector<Etype>::operator=(const vector<Etype>& origVal)
{
   if (this != &origVal)
   {
      delete[] start;

      vectorCapacity = origVal.vectorCapacity;
      vectorSize = origVal.vectorSize;
   
      start = new Etype[vectorCapacity];
      finish = (start + vectorSize);
      onePastEnd = (start + vectorCapacity);

      for (int i = 0; i < vectorCapacity; i++)
         start[i] = (origVal.start)[i];
   }	
   return *this;
}




// assign
//    - parameters : vectorSize - new vectorSize of vector
//                 : assignElem - assigning element
//    - assigns vector to be of given vectorSize with each cell
//        assigned to hold assignElem; renders all iterators
//        to this object invalid
template <class Etype>
void vector<Etype>::assign(int requestedSize, Etype assignElem)
{
   delete[] start;

   start = new Etype[requestedSize];
   finish = (start + requestedSize);
   onePastEnd = (start + requestedSize);

   // ...plus traverse array to initialize cells
   for (int i = 0; i < requestedSize; i++)
      start[i] = initElem;

   vectorCapacity = requestedSize;
   vectorSize = requestedSize;
}






 // ****************** iterator functions

// begin
//    - return type : iterator
//    - returns an iterator that points to first
//        cell of vector
template <class Etype>
typename vector<Etype>::iterator vector<Etype>::begin() 
{
   return iterator(start);   
}



// begin
//    - return type : const_iterator
//    - returns a const_iterator that points to first
//        cell of vector
template <class Etype>
typename vector<Etype>::const_iterator vector<Etype>::begin() const
{
   return const_iterator(start);
}




// end
//    - return type : iterator
//    - returns an iterator that points to "after the last cell"
//        so we know we are "off the vector".
template <class Etype>
typename vector<Etype>::iterator vector<Etype>::end() 
{
   // Our functions will treat finish as an iterator 
   //   to the cell right after the last one filled
   return iterator(finish);
}



// end
//    - return type : const_iterator
//    - returns an const_iterator that points to "after the last cell"
//        so we know we are "off the vector".
template <class Etype>
typename vector<Etype>::const_iterator vector<Etype>::end() const
{
   // Our functions will treat finish as an iterator
   //   to the cell right after the last one filled
   return const_iterator(finish);
}




// rbegin
//    - return type : reverse iterator
//    - returns a reverse iterator that points to
//        first cell of abstract "reverse vector", i.e.
//        last real cell of vector
template <class Etype>
typename vector<Etype>::reverse_iterator vector<Etype>::rbegin() 
{
   // To create an iterator that traverses back to front
   //   instead of front to back, we would need to have the
   //   idea of an abstract "before head of vector" element
   //   so we can traverse from the last cell of the vector 
   //   to the "before head of vector" value in the same way
   //   our forward iterator traverses from the first 
   //   element in the vector to the "just after the last
   //   element" position. Since we don't want to bother 
   //   with two "special cells", the standard way to
   //   implement this is to have the reverse iterator
   //   traverse from our "after the vector" spot to the 
   //   first element, but when we access the iterator's
   //   value, we really return the location to the left
   //   of this iterator, i.e. the position one earlier 
   //   in the vector. Hence, if we abstractly want a
   //   reverse iterator to start at the last cell, then
   //   the implementation should return an iterator to the
   //   "after the vector" position.  
   // 
   //   That is, generally the rbegin() function is defined
   //   to be equivalent to end() except for the iterator 
   //   type returned. 
   return reverse_iterator(end());
}



// rbegin
//    - return type : const_reverse_iterator
//    - returns a const_reverse_iterator that points to
//        first cell of abstract "reverse vector", i.e.
//        last real cell of vector
template <class Etype>
typename vector<Etype>::const_reverse_iterator vector<Etype>::rbegin() const
{
   return const_reverse_iterator(end());
}




// rend
//    - return type : reverse_iterator
//    - returns a reverse iterator that points to
//        "end position" of abstract "reverse vector",
//         i.e. the abstract "before first cell"
//         spot in vector
template <class Etype>
typename vector<Etype>::reverse_iterator vector<Etype>::rend() 
{
   // Likewise (see the rbegin description), rend() should
   // be equivalent to begin() except for the iterator
   // returned. Abstractly, this function is returning
   // an iterator to the "just before the vector" position,
   // but since our implementation doesn't want to mess
   // with a "just before the vector" position, we instead
   // return the "first element" cell and the reverse iterator
   // knows to move one to the left for the access.
   return reverse_iterator(begin());
}



// rend
//    - return type : const_reverse_iterator
//    - returns a const_reverse_iterator that points to
//        "end position" of abstract "reverse vector",
//         i.e. the abstract "before first cell"
//         spot in vector
template <class Etype>
typename vector<Etype>::const_reverse_iterator vector<Etype>::rend() const
{
   return const_reverse_iterator(begin());
}




// ****** Element access


// front
//    - return type : a reference to a vector element
//    - returns a reference to the first cell in the vector
template <class Etype>
Etype& vector<Etype>::front()
{
   return *start;
}


// front
//    - return type : a constant reference to a vector element
//    - returns a constant reference to the first cell in the vector
template <class Etype>
const Etype& vector<Etype>::front() const
{
   return *start;
}



// back
//    - return type : a reference to a vector element
//    - returns a reference to the last cell in the vector
template <class Etype>
Etype& vector<Etype>::back()
{
   // pointer arithmetic; finish - one cell, not finish (an
   //    address value) - one value (which would give the last
   //    byte of the previous cell)
   return *(finish - 1);
}



// back
//    - return type : a constant reference to a vector element
//    - returns a constant reference to the last cell in the vector
template <class Etype>
const Etype& vector<Etype>::back() const
{
   // pointer arithmetic; finish - one cell, not finish (an 
   //    address value) - one value (which would give the last
   //    byte of the previous cell)
   return *(finish - 1);
}



// operator[]
//    - parameters : index - integer index
//    - return type : reference to value in array cell;
//    - returns reference to array value at location indicated
//         by index. Due to  the fact that this a reference to the
//         value and not the value itself, this effectively
//         means we are returning the array cell itself, which
//         can be read for it's value, or else written to with a
//         *new* value. This function is the operator[] invoked
//         on non-const objects or references to non-const objects.
//    - no range checking is done here
template <class Etype>
Etype& vector<Etype>::operator[] (int index)
{
   return start[index];
}



// operator[]
//    - parameters : index - integer index
//    - return type : constant reference to value in array cell;
//    - returns constant reference to array value at location
//         indicated by index. Since the return value is constant,
//         this means that the returned cell cannot be used as an
//         lvalue. This function is the operator[] that will be
//         invoked on const objects and references to const objects.
//   - no range checking is done here
template <class Etype>
const Etype& vector<Etype>::operator[] (int index) const
{
   return start[index];
}



// at
//    - parameters : index - integer index
//    - return type : reference to value in array cell;
//    - returns reference to array value at location indicated
//         by index. Due to  the fact that this a reference to the
//         value and not the value itself, this effectively
//         means we are returning the array cell itself, which
//         can be read for it's value, or else written to with a
//         *new* value. This function is the operator[] invoked
//         on non-const objects or references to non-const objects.
//    - range checking is done here
template <class Etype>
Etype& vector<Etype>::at(int index)
{
   Assert(((index>=0) && (index < vectorSize)), "Bad array access");
   return start[index];
}





// at 
//    - parameters : index - integer index
//    - return type : constant reference to value in array cell;
//    - returns constant reference to array value at location
//         indicated by index. Since the return value is constant,
//         this means that the returned cell cannot be used as an
//         lvalue. This function is the operator[] that will be
//         invoked on const objects and references to const objects.
//    - range checking is done here
template <class Etype>
const Etype& vector<Etype>::at(int index) const
{
   Assert(((index >=0) && (index < vectorSize)), "Bad array access"); 
   return start[index];
}




// ******************   (Stack/Queue)-type access


// push_back
//    - parameters : insElem - element to insert
//    - inserts element as last element in vector; this
//         function potentially renders all iterators
//         to this vector invalid.
template <class Etype>
void vector<Etype>::push_back(Etype insElem)
{
   if (finish==onePastEnd)
      IncreaseCapacity(); 
   *finish = insElem;
   finish = finish + 1; 
   vectorSize++; 
}



// pop_back
//    - removes last element of vector (but does NOT
//        return it); assertion triggered if this function
//        is called on an empty vector
template <class Etype>
void vector<Etype>::pop_back()
{
   Assert(finish != start, "Popped from empty vector!");
   finish = finish - 1;
   vectorSize--;
}


// ***************** General list operations



// insert
//    - parameters : insIter - an iterator to the element we want to
//                     insert before
//                 : newElem - an element of the vector's type
//    - inserts newElem before the position indicated by the iterator
template <class Etype>
void vector<Etype>::insert(iterator insIter, Etype newElem)
{
   Etype* travPtr;

   if (vectorSize==vectorCapacity)
   {  
      int pdiff = insIter.ptr - start;
      IncreaseCapacity();
      insIter.ptr = start + pdiff;
   }

   // for all cells from finish (which is the cell just past the
   //   last cell that holds a value) back to our parameter iterator,
   //   shift cell one location to the right.
   for (travPtr = finish; travPtr != (insIter.ptr); travPtr--)
   {
      // if we assume travPtr points to cell x of the array,
      //  the line below is the equivalent of
      //       start[x] = start[x-1];
      *travPtr = *(travPtr - 1);
   }


   // travPtr should now be pointing to the location where the
   //   original iterator refers to. Thus, again if travPtr points
   //   to cell x, the below line becomes start[x] = insElem;
   *travPtr = newElem;

   vectorSize++;
   finish++; 
}


// insert
//    - parameters : insIter - an iterator to the element we want
//                     to insert before
//                 : the number of copies of our new element that
//                     we want
//                 : newElem - an element of the vector's type
//    - inserts numCopies copies of newElem before the position
//        indicated by the iterator
template <class Etype>
void vector<Etype>::insert(iterator insIter, int numCopies, Etype insElem)
{
   Etype* travPtr;

   // we are making more than one insertion here, so
   //   one call to IncreaseCapacity might not be enough.
   //   So, call it enough times so that our current vectorSize +
   //   numCopies will be less than or equal to our total vectorCapacity.
   while (vectorSize+numCopies > vectorCapacity)
      IncreaseCapacity();

   // for all cells from finish (which is the cell just past the
   //   last cell that holds a value) back to our parameter iterator,
   //   shift cell one location to the right.
   for (travPtr = finish-1; travPtr != (insIter.ptr)-1; travPtr--)
   {
      // if we assume travPtr points to cell x of the array,
      //  the line below is the equivalent of
      //       start[x+numCopies] = start[x];
      *(travPtr + numCopies) = *(travPtr);
   }

   // travPtr should now be pointing to the location where the
   //   original iterator refers to. Thus, again if travPtr points
   //   to cell x, the below line becomes start[x] = insElem;
   for (int i = 1; i <= numCopies; i++)
   {
      travPtr++;
      *travPtr = insElem;
      vectorSize++;
      finish++;
   }
}





// erase
//    - parameters : eraseIter - iterator to element to be removed
//    - removes the element at the current postition of the vector
template <class Etype>
void vector<Etype>::erase(iterator eraseIter)
{
   iterator temp = eraseIter;
   iterator temp2 = eraseIter;
   ++temp2;
   while (temp2 != end())
   {
      *temp = *temp2;
      ++temp;
      ++temp2;
   }
   finish--;
   vectorSize--;
}



// erase
//    - parameters : first - iterator to first element in sequence
//                     to be removed
//                 : last - iterator to element after last one to
//                     be removed (see 3rd Insert comments for more
//                     explanation)
//    - removes the sequence [first, last) from this vector
template <class Etype>
void vector<Etype>::erase(iterator first, iterator last)
{
   // count how many cells are being erased
   iterator temp = first;
   int n = 0;
   while (temp != last)
   {
      n++; 
      temp++;
   }

   temp = first;
   iterator temp2 = last;
   while (temp2 != end())
   {
      *temp = *temp2;
      temp++;
      temp2++;
   }
   finish = temp.ptr;
   vectorSize = vectorSize - n;
}


// clear
//    - deletes all values from vector, resulting in an empty vector
template <class Etype>
void vector<Etype>::clear()
{
   finish = start;
   vectorSize = 0;
}



// ***** Other



// size
//    - parameters : none
//    - return value : integer
//    - returns vectorSize of vector
template <class Etype>
int vector<Etype>::size() const
{
   return vectorSize;
}



// empty
//    - parameters : none
//    - return value : boolean integer
//    - returns 1 if vector is empty, 0 else
template <class Etype>
int vector<Etype>::empty() const
{
   return (start == finish);
}



// capacity 
//    - parameters : none
//    - return value : integer
//    - returns vectorCapacity of vector
template <class Etype>
int vector<Etype>::capacity() const
{
   return vectorCapacity; 
}


// reserve()
//    - parameters : numCells - number of cells to reserve
//    - return value : none
//    - reserves future space
template <class Etype>
void vector<Etype>::reserve(int numCells)
{
   if (vectorCapacity < numCells)
   {
      int newCapacity;
      newCapacity = numCells;

      Etype* temp = new Etype[newCapacity];
      for (int i = 0; i < vectorSize; i++)
         temp[i] = start[i];
    
      if (start != 0)
         delete[] start;
      start = temp;
      onePastEnd = start + newCapacity;
      finish = start + vectorSize;
      vectorCapacity = newCapacity; 
   }
}



// operator==
//    - parameters : secondVal - another vector object to compare to
//    - return type : boolean integer
//    - returns 1 if this vector is equal to secondVal, 0 else
template <class Etype>
int vector<Etype>::operator==(const vector<Etype>& secondVal)
{
   int result = 1;
   if (vectorSize == secondVal.vectorSize)
   {
      iterator temp = iterator(start);
      iterator temp2 = iterator(secondVal.start);
      while (temp != end())
      {
         if (*temp != *temp2)
         {
           result = 0;
           break;
         }
         else
         {
            temp++;
            temp2++;
         }
      }
   } 
   return result;
}


// operator!=
//    - parameters : secondVal - another vector object to compare to
//    - return type : boolean integer
//    - returns 1 if this vector is not equal to secondVal, 0 else
template <class Etype>
int  vector<Etype>::operator!=(const vector<Etype>& secondVal)
{
   int result = 0;
   if (vectorSize == secondVal.vectorSize)
   {
      iterator temp = iterator(start);      
      iterator temp2 = iterator(secondVal.start);
      while (temp != end())
      {
         if (*temp != *temp2)
         {
           result = 1;
           break;
         }
         else
         {
            temp++;
            temp2++;
         }
      }
   } 
   return result;
}



// operator<
//    - parameters : secondVal - another vector object to compare to
//    - return type : boolean integer
//    - returns 1 if this vector is less than secondVal, 0 else
template <class Etype>
int vector<Etype>::operator<(const vector<Etype>& secondVal)
{
   int result = 0;
   const_iterator temp = iterator(start);      
   const_iterator temp2 = iterator(secondVal.start);
   while ((temp != end()) && (temp2 != secondVal.end()))
   {
      if (*temp < *temp2)
      {
        result = 1;
        break;
      }
      else if (*temp > *temp2)
         break;
      else  // *temp == *temp2
      {
         temp++;
         temp2++;
      }
   } 
   return result;
}




// operator<<
//    - friend function of vector class
//    - parameters : Out - the output stream to which we will write
//                 : printvector - the vector that we will write to
//                                   the output stream
//    - return value : a reference to the same output stream we passed in
//    - writes vectir values to parameter stream and returns stream
template <class Etype>
std::ostream& operator<<(std::ostream& Out, const vector<Etype>& printvector)
{
   int temp = 0;

   if (printvector.vectorSize==0)
      Out << "< empty vector >";
   else
   {
      Out << "< ";
      while (temp < printvector.vectorSize)
      {
         Out << printvector[temp] << " ";
         temp++;
      }
      Out << ">";
   }
   return Out;
}




// IncreaseCapacity
//    - doubles capacity of vector (increases it
//               by 10 if it is currently 0.
template <class Etype>
void vector<Etype>::IncreaseCapacity()
{
   int newCapacity;
   if (vectorCapacity == 0)
      newCapacity = 10; 
   else
      newCapacity = 2*vectorCapacity;

   Etype* temp = new Etype[newCapacity];
   for (int i = 0; i < vectorSize; i++)
      temp[i] = start[i];
    
   if (start != NULL)
      delete[] start;
   start = temp;
   onePastEnd = start + newCapacity;
   finish = start + vectorSize;
   vectorCapacity = newCapacity; 
}
 

