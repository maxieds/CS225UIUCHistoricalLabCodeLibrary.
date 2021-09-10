// ***********************************************************
// *                                                         *
// *   iterVectorFns.h                                       *    
// *                                                         *
// *   Interface for functions that perform iteration        *
// *      on vector objects                                  *
// *                                                         *
// *   Written January 2005 by Jason Zych                    *
// *                                                         * 
// ***********************************************************

#ifndef ITER_VECTOR_FNS_225_H
#define ITER_VECTOR_FNS_225_H

#include "string.h"
#include "vector225.h"


// BriefForwardIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward order once
void BriefForwardIteration(vector<String> & theVector);



// ForwardIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward and reverse
//        order, twice, using an iterator. 
void ForwardIteration(vector<String> & theVector);



// ForwardConstIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward and reverse
//        order, twice, using a const_iterator. 
void ForwardConstIteration(vector<String> const & theVector);



// ReverseIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in "reverse order" forwards
//        and backwards, twice, using a reverse_iterator. 
void ReverseIteration(vector<String> & theVector);



// ReverseConstIteration
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in "reverse order" forwards
//        and backwards, twice, using a const_reverse_iterator. 
void ReverseConstIteration(vector<String> const & theVector);



// ForwardIterationWithChanges
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in forward and reverse
//        order, twice, using an iterator. A letter 'M' is 
//        added to the end of each String the first time forward, 
//        and that 'M' is changed to a 'L' the second time forward. 
void ForwardIterationWithChanges(vector<String> & theVector);



// ReverseIterationWithChanges
//    - parameters : theVector - the vector to iterate over
//    - prints the items in the vector in "reverse order" forwards
//        and backwards, twice, using a reverse_iterator. A letter 'M' 
//        is added to the end of each String the first time in forwards
//        "reverse order", and that 'M' is changed to a 'L' the second 
//        time forwards in "reverse order". 
void ReverseIterationWithChanges(vector<String> & theVector);


#endif



