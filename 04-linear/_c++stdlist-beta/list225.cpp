// *****************************************************************
// *                                                               *
// *  list225.cpp                                                  *
// *                                                               *
// *  This file provides the implementation for our abbreviated    *
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



#include <iostream>
#include <cstddef>
#include "asserts.h"
#include "list225.h"


// ***********************************************************
// *        member functions for the iterator class          *
// ***********************************************************


// iterator
//    - constructor
//    - initializes this iterator to point to NULL
template <class Etype>
list<Etype>::iterator::iterator() 
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
typename list<Etype>::reference list<Etype>::iterator::operator*() 
{ 
   return ptr->element;  
}


// operator->
//    - return type : a pointer to the element type
//    - returns a pointer to the cell storing the element
//         to which this iterator points.  There is no
//          error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename list<Etype>::pointer list<Etype>::iterator::operator->()  
{ 
   return &(ptr->element); 
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
typename list<Etype>::iterator& list<Etype>::iterator::operator++() 
{ 
   ptr = ptr->next;
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
typename list<Etype>::iterator& list<Etype>::iterator::operator--()  
{ 
   ptr = ptr->prev; 
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
typename list<Etype>::iterator list<Etype>::iterator::operator++(int ignore)
{
   typename list<Etype>::iterator temp = *this;
   ptr = ptr->next;
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
typename list<Etype>::iterator list<Etype>::iterator::operator--(int ignore)
{
   typename list<Etype>::iterator temp = *this;
   ptr = ptr->prev;
   return temp;
}



// operator==
//    - parameters : origVal - previously created iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point to the same location, 0 else
template <class Etype>
int list<Etype>::iterator::operator==(
               typename const list<Etype>::iterator& origVal) const
{ 
   return (ptr == origVal.ptr); 
}


// operator!=
//    - parameters : origVal - previously created iterator
//    - return value : boolean integer
//    - returns 1 if this iterator and the parameter
//         iterator point different locations, 0 else
template <class Etype>
int list<Etype>::iterator::operator!=(
               typename const list<Etype>::iterator& origVal) const
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
list<Etype>::iterator::iterator(
                     typename list<Etype>::listNode* assignPtr) 
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
list<Etype>::const_iterator::const_iterator() 
{ 
   ptr = NULL;
}



// const_iterator
//    - constructor
//    - parameters : theIter - an iterator
//    - initializes this const_iterator to point to the same
//           location as the parameter iterator
template <class Etype>
list<Etype>::const_iterator::const_iterator(
               typename const list<Etype>::iterator& theIter) 
{
   ptr = theIter.ptr;
}




// operator*
//    - return type : a const reference to the element type
//    - returns by const_reference the cell storing the element
//         to which this const_iterator points.  There is no
//          error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename list<Etype>::reference 
                    list<Etype>::const_iterator::operator*() const
{ 
   return ptr->element;  
}


// operator->
//    - return type : a const_pointer to the element type
//    - returns a const_pointer to the cell storing the element
//         to which this const_iterator points.  There is no
//          error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename list<Etype>::pointer 
                    list<Etype>::const_iterator::operator->() const 
{ 
   return &(ptr->element); 
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
typename list<Etype>::const_iterator& 
                    list<Etype>::const_iterator::operator++() 
{ 
   ptr= ptr->next;
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
typename list<Etype>::const_iterator& 
                    list<Etype>::const_iterator::operator--()  
{ 
   ptr = ptr->prev; 
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
typename list<Etype>::const_iterator 
                    list<Etype>::const_iterator::operator++(int ignore)
{
   typename list<Etype>::const_iterator temp = *this;
   ptr = ptr->next;
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
typename list<Etype>::const_iterator 
                    list<Etype>::const_iterator::operator--(int ignore)
{
   typename list<Etype>::const_iterator temp = *this;
   ptr = ptr->prev;
   return temp;
}



// operator==
//    - parameters : origVal - previously created const_iterator
//    - return value : boolean integer
//    - returns 1 if this const_iterator and the parameter
//         const_iterator point to the same location, 0 else
template <class Etype>
int list<Etype>::const_iterator::operator==(
               typename const list<Etype>::const_iterator& origVal) const
{ 
   return (ptr == origVal.ptr); 
}


// operator!=
//    - parameters : origVal - previously created const_iterator
//    - return value : boolean integer
//    - returns 1 if this const_iterator and the parameter
//         const_iterator point different locations, 0 else
template <class Etype>
int list<Etype>::const_iterator::operator!=(
               typename const list<Etype>::const_iterator& origVal) const
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
list<Etype>::const_iterator::const_iterator( 
                           typename list<Etype>::listNode* assignPtr)
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
list<Etype>::reverse_iterator::reverse_iterator() : current()
{ 
   // initializer list used above; no code needed here
}



// operator*
//    - return type : a reference to the element type
//    - returns by reference the cell storing the element
//         to which this reverse_iterator points.  There is no
//          error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename list<Etype>::reference list<Etype>::reverse_iterator::operator*() 
{ 
   iterator temp = current;
   --temp;
   return *temp;
}


// operator->
//    - return type : a pointer to the element type
//    - returns a pointer to the cell storing the element
//         to which this reverse_iterator points.  There is no
//          error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename list<Etype>::pointer list<Etype>::reverse_iterator::operator->()  
{ 
   return &(this->operator*());
}



// operator++ (prefix version)
//    - return type : reference to an reverse_iterator
//    - moves this reverse_iterator one position forward in the
//          collection it points to, and then returns
//          this reverse_iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <class Etype>
typename list<Etype>::reverse_iterator& 
                    list<Etype>::reverse_iterator::operator++() 
{ 
   --current;
   return *this; 
}




// operator-- (prefix version)
//    - return type: reference to an reverse_iterator
//    - moves this reverse_iterator one position backward in the
//          collection it points to, and then returns
//          this reverse_iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <class Etype>
typename list<Etype>::reverse_iterator& 
                    list<Etype>::reverse_iterator::operator--()  
{ 
   ++current;
   return *this; 
}



// operator++ (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : an reverse_iterator
//    - moves this reverse_iterator one position forward in the
//          collection it points to, and then returns an
//          reverse_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <class Etype>
typename list<Etype>::reverse_iterator 
                    list<Etype>::reverse_iterator::operator++(int ignore)
{
   typename list<Etype>::reverse_iterator temp = *this;
   --current;
   return temp;
}





// operator-- (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : an reverse_iterator
//    - moves this reverse_iterator one position backward in the
//          collection it points to, and then returns an
//          reverse_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <class Etype>
typename list<Etype>::reverse_iterator 
                    list<Etype>::reverse_iterator::operator--(int ignore)
{
   typename list<Etype>::reverse_iterator temp = *this;
   ++current;
   return temp;
}



// operator==
//    - parameters : origVal - previously created reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this reverse_iterator and the parameter
//         reverse_iterator point to the same location, 0 else
template <class Etype>
int list<Etype>::reverse_iterator::operator==(
               typename const list<Etype>::reverse_iterator& origVal) const
{ 
   return (current == origVal.current);
}


// operator!=
//    - parameters : origVal - previously created reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this reverse_iterator and the parameter
//         reverse_iterator point different locations, 0 else
template <class Etype>
int list<Etype>::reverse_iterator::operator!=(
               typename const list<Etype>::reverse_iterator& origVal) const
{ 
   return (current != origVal.current); 
}




// reverse_iterator
//    - constructor
//    - parameters : assignIter - iterator to the same type of
//         data to which this reverse_iterator points
//    - initializes this reverse_iterator to point to the same
//       place that the parameter iterator points to
template <class Etype>
list<Etype>::reverse_iterator::reverse_iterator(
                             typename list<Etype>::iterator assignIter)
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
list<Etype>::const_reverse_iterator::const_reverse_iterator() : current()
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
list<Etype>::const_reverse_iterator::const_reverse_iterator(
           typename const list<Etype>::reverse_iterator& theIter)
{
   current = theIter.current;
}




// operator*
//    - return type : a const_reference to the element type
//    - returns by const_reference the cell storing the element
//         to which this const_reverse_iterator points.  There is no
//          error checking done to ensure that this is a legal 
//          cell on which to perform this operation.
template <class Etype>
typename list<Etype>::const_reference 
                    list<Etype>::const_reverse_iterator::operator*() const
{ 
   iterator temp = current;
   --temp;
   return *temp;
}


// operator->
//    - return type : a const_pointer to the element type
//    - returns a const_pointer to the cell storing the element
//         to which this const_reverse_iterator points.  There is no
//          error checking done to ensure that this is
//          a legal cell on which to perform this operation.
template <class Etype>
typename list<Etype>::const_pointer 
                    list<Etype>::const_reverse_iterator::operator->() const 
{ 
   return &(this->operator*());
}



// operator++ (prefix version)
//    - return type : reference to an const_reverse_iterator
//    - moves this const_reverse_iterator one position forward in the
//          collection it points to, and then returns
//          this const_reverse_iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <class Etype>
typename list<Etype>::const_reverse_iterator& 
                    list<Etype>::const_reverse_iterator::operator++() 
{ 
   --current;
   return *this; 
}




// operator-- (prefix version)
//    - return type: reference to an const_reverse_iterator
//    - moves this const_reverse_iterator one position backward in the
//          collection it points to, and then returns
//          this const_reverse_iterator after moving it. There is no
//          error checking done to ensure that this is
//          a legal position at which to perform this
//          operation.
template <class Etype>
typename list<Etype>::const_reverse_iterator& 
                    list<Etype>::const_reverse_iterator::operator--()  
{ 
   ++current;
   return *this; 
}


// operator++ (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : an const_reverse_iterator
//    - moves this const_reverse_iterator one position forward in the
//          collection it points to, and then returns an
//          const_reverse_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <class Etype>
typename list<Etype>::const_reverse_iterator 
                    list<Etype>::const_reverse_iterator::operator++(int ignore)
{
   typename list<Etype>::const_reverse_iterator temp = *this;
   --current;
   return temp;
}





// operator-- (postfix version)
//    - parameters : ignore - argument always the integer 1, to
//                       distinguish this from prefix version
//    - return type : an const_reverse_iterator
//    - moves this const_reverse_iterator one position backward in the
//          collection it points to, and then returns an
//          const_reverse_iterator to the position this iterator pointed
//          to before this function was run. There is no
//          error checking done to ensure that this is a
//          legal position at which to perform this operation.
template <class Etype>
typename list<Etype>::const_reverse_iterator 
                    list<Etype>::const_reverse_iterator::operator--(int ignore)
{
   typename list<Etype>::const_reverse_iterator temp = *this;
   ++current;
   return temp;
}


// operator==
//    - parameters : origVal - previously created const_reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this const_reverse_iterator and the parameter
//         const_reverse_iterator point to the same location, 0 else
template <class Etype>
int list<Etype>::const_reverse_iterator::operator==(
           typename const list<Etype>::const_reverse_iterator& origVal) const
{ 
   return (current == origVal.current);
}


// operator!=
//    - parameters : origVal - previously created const_reverse_iterator
//    - return value : boolean integer
//    - returns 1 if this const_reverse_iterator and the parameter
//         const_reverse_iterator point different locations, 0 else
template <class Etype>
int list<Etype>::const_reverse_iterator::operator!=(
           typename const list<Etype>::const_reverse_iterator& origVal) const
{ 
   return (current != origVal.current); 
}




// ***********************************************************
// *         member functions for the list class             *
// ***********************************************************



// list
//    - default constructor
template <class Etype>
list<Etype>::list()
{
   headerNode = new listNode(); 
   headerNode->next = headerNode->prev = headerNode;
   listSize=0; 
}



// list
//    - constructor
//    - parameters : theListSize - number of elements in this list
//    - creates a list of listSize default elements
template <class Etype>
list<Etype>::list(int theListSize)
{
   headerNode = new listNode(); 
   listNode* temp = headerNode; 
   for (int i = 1; i <= theListSize; i++)
   { 
      temp->next = new listNode(); 
      temp->next->prev = temp; 
      temp = temp->next; 
   }
   temp->next = headerNode;
   headerNode->prev = temp;   
   listSize = theListSize; 
}



// list
//    - constructor
//    - parameters : theListSize - number of elements in this list
//    - creates a list of listSize elements each initialized to 
//           initElem
template <class Etype> 
list<Etype>::list(int theListSize, Etype initElem)
{
   headerNode = new listNode(); 
   listNode* temp = headerNode; 
   for (int i = 1; i <= theListSize; i++)
   { 
      temp->next = new listNode(); 
      temp->next->prev = temp; 
      temp = temp->next; 
      temp->element = initElem;
   }   
   temp->next = headerNode;
   headerNode->prev = temp;
   listSize = theListSize;
}





// list
//    - copy constructor
//    - parameters : origlist - a previously allocated list object
//    - initializes the list to be a copy of origlist
template <class Etype>
list<Etype>::list(const list<Etype>& origlist)
{
   listNode* origlistPtr = (origlist.headerNode)->next,
   listNode* newlistPtr; 

   headerNode = new listNode(); 
   newlistPtr = headerNode; 
   
   if (origlistPtr == (origlist.headerNode))  // then origlist is empty
   {
      headerNode->next = headerNode;
      headerNode->prev = headerNode;
      listSize = 0;
   }
   else    // origlist is not empty; copy it node for node
   {
      while (origlistPtr!=origlist.headerNode) 
      {
         // at least one node in origlist; create that node
         newlistPtr->next = new listNode(); 
         newlistPtr->next->prev = newlistPtr;
         newlistPtr = newlistPtr->next; 
         newlistPtr->element = origlistPtr->element; 
         origlistPtr = origlistPtr->next;
      }
      newlistPtr->next = headerNode; 
      headerNode->prev = newlistPtr; 
      listSize = origlist.listSize;       
   }
}




// ~list
//    - destructor
//    - deallocates all dynamically allocated memory inside the list
template <class Etype>
list<Etype>::~list()
{
   clear(); 
   delete headerNode; 
}



// operator=
//    - parameters: origlist - a previously allocated list object
//    - sets the the list to be a copy of origlist
template <class Etype>
list<Etype>& list<Etype>::operator=(const list<Etype>& origlist)
{

   if (this!=&origlist)
   {
      clear(); 

      listNode *origlistPtr = (origlist.headerNode)->next,
           *newlistPtr;

      newlistPtr = headerNode; 
   
      if (origlistPtr == (origlist.headerNode))  // then origlist is empty 
      {
         headerNode->next = headerNode->prev = headerNode;
         listSize = 0;
      }
      else    // origlist is not empty; copy it node for node
      {
         while (origlistPtr!=origlist.headerNode) 
         {
            // at least one node in origlist; create that node
            newlistPtr->next = new listNode;
            newlistPtr->next->prev = newlistPtr;
            newlistPtr = newlistPtr->next; 
            newlistPtr->element = origlistPtr->element;
            origlistPtr = origlistPtr->next;
         }
         newlistPtr->next = headerNode; 
         headerNode->prev = newlistPtr; 
         listSize = origlist.listSize;
      }
   }
   return *this;
}


// assign
//    - parameters : listSize - new listSize of list
//                 : assignElem - assigning element
//    - assigns list to be of given listSize with each cell
//        assigned to hold assignElem
template <class Etype>
void list<Etype>::assign(int requestedSize, Etype assignElem)
{
   list L(requestedSize, assignElem);
   operator=(L);
}




 // *************** list public functions for iterators

// begin
//    - return type : iterator
//    - returns an iterator that points to first
//        node of list
template <class Etype>
typename list<Etype>::iterator list<Etype>::begin()
{ 
   // the first real node of the abstract list is the 
   //   node after the implementation's header node
   return iterator(headerNode->next); 
}


// begin
//    - return type : iterator
//    - returns an iterator that points to first
//        node of list
template <class Etype>
typename list<Etype>::const_iterator list<Etype>::begin() const
{
   // the first real node of the abstract list is the
   //   node after the implementation's header node
   return iterator(headerNode->next);
}



// end
//    - return type : iterator
//    - returns an iterator that points to "after the last node"
//        so we know we are "off the list".
template <class Etype>
typename list<Etype>::iterator list<Etype>::end() 
{ 
   // The header node follows the last element and comes before
   //   the first element (i.e. the list is circular), so if we 
   //   want to refer to the abstract ``just past the end of list'' 
   //   location, we should return an iterator to this header node 
   //   which immediately follows the last element
   return iterator(headerNode);
}


// end
//    - return type : iterator
//    - returns an iterator that points to "after the last node"
//        so we know we are "off the list".
template <class Etype>
typename list<Etype>::const_iterator list<Etype>::end() const
{
   // The header node follows the last element and comes before
   //   the first element (i.e. the list is circular), so if we
   //   want to refer to the abstract ``just past the end of list''
   //   location, we should return an iterator to this header node
   //   which immediately follows the last element
   return iterator(headerNode);
}


// rbegin
//    - return type : reverse iterator
//    - returns a reverse iterator that points to
//        first node of abstract "reverse list", i.e.
//        last real node of list
template <class Etype>
typename list<Etype>::reverse_iterator list<Etype>::rbegin() 
{ 
   // To create an iterator that traverses back to front
   //   instead of front to back, we would need to have the
   //   idea of an abstract "before head of list" element
   //   so we can traverse from the last node of the list
   //   to the "before head of list" value in the same way
   //   our forward iterator traverses from the first 
   //   element in the list to the "just after the last
   //   element" position. Since we don't want to bother 
   //   with two "special nodes", the standard way to
   //   implement this is to have the reverse iterator
   //   traverse from our "after the list" spot to the 
   //   first element, but when we access the iterator's
   //   value, we really return the location to the left
   //   of this iterator, i.e. the position one earlier 
   //   in the list. Hence, if we abstractly want a
   //   reverse iterator to start at the last node, then
   //   the implementation should return an iterator to the
   //   "after the list" position.  
   // 
   //   That is, generally the rbegin() function is defined
   //   to be equivalent to end() except for the iterator 
   //   type returned. 
   return reverse_iterator(headerNode);
}



// rbegin
//    - return type : reverse iterator
//    - returns a reverse iterator that points to
//        first node of abstract "reverse list", i.e.
//        last real node of list
template <class Etype>
typename list<Etype>::const_reverse_iterator list<Etype>::rbegin() const
{
   // To create an iterator that traverses back to front
   //   instead of front to back, we would need to have the
   //   idea of an abstract "before head of list" element
   //   so we can traverse from the last node of the list
   //   to the "before head of list" value in the same way
   //   our forward iterator traverses from the first
   //   element in the list to the "just after the last
   //   element" position. Since we don't want to bother
   //   with two "special nodes", the standard way to
   //   implement this is to have the reverse iterator
   //   traverse from our "after the list" spot to the
   //   first element, but when we access the iterator's
   //   value, we really return the location to the left
   //   of this iterator, i.e. the position one earlier
   //   in the list. Hence, if we abstractly want a
   //   reverse iterator to start at the last node, then
   //   the implementation should return an iterator to the
   //   "after the list" position.
   //
   //   That is, generally the rbegin() function is defined
   //   to be equivalent to end() except for the iterator
   //   type returned.
   return reverse_iterator(headerNode);
}

// rend
//    - return type : reverse iterator
//    - returns a reverse iterator that points to
//        "end position" of abstract "reverse list", 
//         i.e. the abstract "before first element"
//         spot in list 
template <class Etype>
typename list<Etype>::reverse_iterator list<Etype>::rend() 
{ 
   // Likewise (see the rbegin description), rend() should
   // be equivalent to begin() except for the iterator
   // returned. Abstractly, this function is returning
   // an iterator to the "just before the list" position,
   // but since our implementation doesn't want to mess
   // with a "just before the list" position, we instead 
   // return the "first element" node and the reverse iterator
   // knows to move one to the left for the access. 
   return reverse_iterator(headerNode->next); 
}




// rend
//    - return type : reverse iterator
//    - returns a reverse iterator that points to
//        "end position" of abstract "reverse list",
//         i.e. the abstract "before first element"
//         spot in list
template <class Etype>
typename list<Etype>::const_reverse_iterator list<Etype>::rend() const
{
   // Likewise (see the rbegin description), rend() should
   // be equivalent to begin() except for the iterator
   // returned. Abstractly, this function is returning
   // an iterator to the "just before the list" position,
   // but since our implementation doesn't want to mess
   // with a "just before the list" position, we instead
   // return the "first element" node and the reverse iterator
   // knows to move one to the left for the access.
   return reverse_iterator(headerNode->next);
}


 // ************** Element Access  


// front
//    - return type : a constant reference to a list element 
//    - returns a constant reference to the first cell in the list 
template <class Etype>
const Etype& list<Etype>::front() const 
{   
   // node after header is first real node
   // NOTE: if list is empty, the default element in 
   //   the header node gets returned, since both
   //   pointers of the header node point to itself 
   //   when list is empty. This way, we *do* return
   //   *something*, and don't necessarily need to crash
   //   the program with an assert.
   return headerNode->next->element; 
}



// front 
//    - return type : a reference to a list element 
//    - returns a reference to the first cell in the list 
template <class Etype>
Etype& list<Etype>::front()  
{    
   // node after header is first real node
   // NOTE: if list is empty, the default element in 
   //   the header node gets returned, since both
   //   pointers of the header node point to itself 
   //   when list is empty. This way, we *do* return
   //   *something*, and don't necessarily need to crash
   //   the program with an assert.
   return headerNode->next->element; 
}



// back 
//    - return type : a constant reference to a list element 
//    - returns a constant reference to the first cell in the list 
template <class Etype>
const Etype& list<Etype>::back() const 
{  
   // node prior to header is actual ending node
   // NOTE: if list is empty, the default element in 
   //   the header node gets returned, since both
   //   pointers of the header node point to itself 
   //   when list is empty. This way, we *do* return
   //   *something*, and don't necessarily need to crash
   //   the program with an assert.
   return headerNode->prev->element; 
}



// back 
//    - return type : a reference to a list element 
//    - returns a reference to the first cell in the list 
template <class Etype>
Etype& list<Etype>::back()  
{    
   // node prior to header is actual ending node
   // NOTE: if list is empty, the default element in 
   //   the header node gets returned, since both
   //   pointers of the header node point to itself 
   //   when list is empty. This way, we *do* return
   //   *something*, and don't necessarily need to crash
   //   the program with an assert.
   return headerNode->prev->element; 
}
  




 // ********** (Stack/Queue)-type access



// push_back
//    - parameters : insElem - element to insert
//    - inserts element as last element in list
template <class Etype>
void list<Etype>::push_back(Etype insElem)
{
   listNode* temp = new listNode(insElem); 

   temp->prev = headerNode->prev;
   temp->next = headerNode;

   // if list is empty, headerNode->prev->next is
   //   the next pointer of the headerNode, so
   //   the empty case gets handled gracefully as well. 
   headerNode->prev->next = temp;
   headerNode->prev = temp;
   listSize++;
}




// pop_back
//    - removes last element of list (but does NOT
//        return it)
template <class Etype>
void list<Etype>::pop_back()
{
   // if list is not empty...
   if (headerNode->next != headerNode)
   {   
      listNode* temp = headerNode->prev; 

      // If we want the last node removed, then second-to-last
      //   node should point to header instead of last node.
      // If list had only one element, we will be settting
      //   headerNode to point to itself.
      headerNode->prev->prev->next = headerNode; 
      headerNode->prev = headerNode->prev->prev;
      delete temp;
   }
   // else...?
   // 
   // Do nothing if list is empty. Since we
   //   don't return a value, this will not cause
   //   a problem (though we could have used a 
   //   Warn() call in that case if we wanted to.
   listSize--;
}



 

// push_front
//    - parameters : insElem - element to insert
//    - inserts element as first element in list
template <class Etype>
void list<Etype>::push_front(Etype insElem)
{
   listNode* temp = new listNode(insElem);
   temp->next = headerNode->next;
   temp->prev = headerNode;

   // if list is empty, headerNode->next->prev is
   //   the prev pointer of the headerNode, so
   //   the empty case gets handled gracefully as well. 
   headerNode->next->prev = temp;
   headerNode->next = temp;
   listSize++;
}




// pop_front
//    - removes first element of list (but does NOT 
//        return it. 
template <class Etype>
void list<Etype>::pop_front()
{
   // if list is not empty...
   if (headerNode->next != headerNode)
   {   
      listNode* temp = headerNode->next; 

      // If we want the first node removed, then the second
      //   node should point to header instead of first node.
      // If list had only one element, we will be settting
      //   headerNode to point to itself.
      headerNode->next->next->prev = headerNode;
      headerNode->next = headerNode->next->next;
      delete temp;
   }
   // else...?
   // 
   // Do nothing if list is empty. Since we
   //   don't return a value, this will not cause
   //   a problem (though we could have used a
   //   Warn() call in that case if we wanted to.
   listSize--;
}





 // *************** General list operations




// insert
//    - parameters : insIter - an iterator to the element we want to
//                     insert before
//                 : newElem - an element of the list's type
//    - inserts newElem before the position indicated by the iterator
template <class Etype>
void list<Etype>::insert(iterator insIter, Etype newElem)
{
   listNode *tempPtr = new listNode(newElem); 
    
   tempPtr->next = (insIter.ptr);
   tempPtr->prev = (insIter.ptr)->prev; 
   tempPtr->prev->next = tempPtr;
   tempPtr->next->prev = tempPtr; 
   listSize++; 
}




// insert
//    - parameters : insIter - an iterator to the element we want 
//                     to insert before
//                 : the number of copies of our new element that 
//                     we want
//                 : newElem - an element of the list's type
//    - inserts numCopies copies of newElem before the position 
//        indicated by the iterator
template <class Etype>
void list<Etype>::insert(iterator insIter, int numCopies, Etype insElem)
{
   if (numCopies > 0)
   {
      listNode *headOfChain, *chainTrav; 
      headOfChain = new listNode(insElem); 
      chainTrav = headOfChain;
      for (int i = 1; i <= numCopies - 1; i++) 
      {
         chainTrav->next = new listNode(insElem); 
         chainTrav->next->prev = chainTrav; 
         chainTrav = chainTrav->next; 
      }
      // now headOfChain points to the first node in a 
      // list of numCopies nodes all of which hold insElem;
      // chainTrav points to the last node in that same list.

      headOfChain->prev = (insIter.ptr)->prev;
      chainTrav->next = (insIter.ptr);
      (insIter.ptr)->prev->next = headOfChain;
      //(insIter.ptr)->next->prev = chainTrav;
      (insIter.ptr)->prev = chainTrav;  //@@@@@@@@@@
   
      listSize += numCopies;  
   }
}




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
template <class Etype>
void list<Etype>::insert(iterator insIter, iterator first, iterator last)
{
   if (first != last)
   {
      listNode *headOfChain, *chainTrav;
      int numNewElements = 1; 
      headOfChain = new listNode(*first);
      chainTrav = headOfChain;
      ++first; 
      while (first != last)
      {
         chainTrav->next = new listNode(*first); 
         chainTrav->next->prev = chainTrav; 
         chainTrav = chainTrav->next; 
         ++first;
         numNewElements++; 
      }
      // now headOfChain points to the first node in a 
      // list of nodes which contains the sequential values
      // indicated by [first, last)  

      headOfChain->prev = (insIter.ptr)->prev;
      chainTrav->next = (insIter.ptr);
      (insIter.ptr)->prev->next = headOfChain; 
      //(insIter.ptr)->next->prev = chainTrav;
      (insIter.ptr)->prev = chainTrav; //@@@@@@@@@
      listSize += numNewElements;
   }
}





// erase
//    - parameters : eraseIter - iterator to element to be removed
//    - removes the element at the current postition of the list
template <class Etype> 
void list<Etype>::erase(iterator eraseIter)
{
   // The STL doesn't print out warnings when you do things
   //  such as removing from an empty list, and so we won't
   //  either, even though that is what we did in the list 
   //  class we inspected in section 
   if (eraseIter.ptr != headerNode)
   {
      listNode* temp = eraseIter.ptr;
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
      delete temp;
      listSize--;
   }
}


// erase
//    - parameters : first - iterator to first element in sequence 
//                     to be removed
//                 : last - iterator to element after last one to
//                     be removed (see 3rd insert comments for more
//                     explanation)
//    - removes the sequence [first, last) from this list
template <class Etype>
void list<Etype>::erase(iterator first, iterator last)  
{
   if (first.ptr != headerNode)
   {
      listNode* lastRealNode = (last.ptr)->prev;
      (first.ptr)->prev->next = last.ptr; //@@@@
      lastRealNode->next->prev = (first.ptr)->prev;
      // at this point, the relevant elements are 
      //  spliced out of the list
  
      int numElementsDeleted = 0; 
      iterator trav = first;
      while (first != last)
      {
         ++first;
         numElementsDeleted++;
         delete (trav.ptr);
         trav = first;
      }
      // at this point the given sequence, which was spliced out,
      //  is completely deleted

      listSize -= numElementsDeleted; 
   }
}


// clear
//    - deletes all values from list, resulting in an empty list
template <class Etype>
void list<Etype>::clear()
{
   listNode *deletionPtr = headerNode->next;
   listNode *listRestPtr = deletionPtr;

   while (listRestPtr != headerNode)
   {
      listRestPtr = listRestPtr->next;
      delete deletionPtr;
      deletionPtr = listRestPtr;
   }
   headerNode->next = headerNode->prev = headerNode;
   listSize=0;
}




// **************** Other general operations


// size
//    - parameters : none
//    - return value : integer
//    - returns size of list
template <class Etype>
int list<Etype>::size() const
{
   return listSize;
}


// empty
//    - parameters : none
//    - return value : boolean integer
//    - returns 1 if list is empty, 0 else
template <class Etype>
int list<Etype>::empty() const
{
   return (headerNode->next == headerNode);
}




// operator==
//    - parameters : secondVal - another list object to compare to
//    - return type : boolean integer
//    - returns 1 if this list is equal to secondVal, 0 else
template <class Etype>
int list<Etype>::operator==(const list<Etype>& secondVal)
{
   int result = 1;
   if (listSize == secondVal.listSize)
   {
      iterator temp = begin();
      iterator temp2 = iterator(secondVal.begin());
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
//    - parameters : secondVal - another list object to compare to
//    - return type : boolean integer
//    - returns 1 if this list is not equal to secondVal, 0 else
template <class Etype>
int  list<Etype>::operator!=(const list<Etype>& secondVal)
{
   int result = 0;
   if (listSize == secondVal.listSize)
   {
      iterator temp = iterator(begin());
      iterator temp2 = iterator(secondVal.begin());
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
//    - parameters : secondVal - another list object to compare to
//    - return type : boolean integer
//    - returns 1 if this list is less than secondVal, 0 else
template <class Etype>
int list<Etype>::operator<(const list<Etype>& secondVal)
{
   int result = 0;
   const_iterator temp = iterator(begin());
   const_iterator temp2 = iterator(begin());
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



	
// **************  list-class-specific operations

// operator<<
//    - friend function of list class
//    - parameters : Out - the output stream to which we will write
//                 : printlist - the list that we will write to the output stream
//    - return value : a reference to the same output stream we passed in
//    - writes list values to parameter stream and returns stream
template <class Etype>
std::ostream& operator<<(std::ostream& Out, const list<Etype>& printlist)
{
   list<Etype>::listNode* listHead = printlist.headerNode;
   list<Etype>::listNode* temp = listHead->next;

   if (printlist.listSize==0)
      Out << "< empty list >";
   else
   {
      Out << "< ";
      while (temp != listHead)
      {
         Out << temp->element << " ";
         temp=temp->next;
      }
      Out << ">";
   }
   return Out;
}




// split
//   - parameters: pos - the position where we want to split the list
//   - this list will be splitted into two list before pos, and the new
//           list will be from pos on.
template <class Etype>
list<Etype> list<Etype>::split(iterator pos)
{

   list<Etype> newL;
   iterator iC=pos;
   int nCounter = 0;
   while(iC!=end())
   {
        nCounter++;
        iC++;
   }
   if(nCounter==0)
        return newL;

   newL.headerNode->prev = headerNode->prev;
   headerNode->prev->next = newL.headerNode;

   pos.ptr->prev->next = headerNode;
   headerNode->prev=pos.ptr->prev;
   listSize-=nCounter;

   newL.listSize=nCounter;
   newL.headerNode->next = pos.ptr;
   pos.ptr->prev = newL.headerNode;

   return newL;
}


