// ***********************************************************
// *                                                         *
// *   iterarrayFns.h                                        *    
// *                                                         *
// *   Interface for functions that perform iteration        *
// *      on Array objects                                   *
// *                                                         *
// *   Written January 2005 by Jason Zych                    *
// *                                                         * 
// ***********************************************************

#ifndef ITER_ARRAY_FNS_225_H
#define ITER_ARRAY_FNS_225_H

#include "string.h"
#include "array.h"


// BriefForwardIteration
//    - parameters : theArray - the Array to iterate over
//    - prints the items in the Array in forward order once
void BriefForwardIteration(Array<String> & theArray);



// ForwardIteration
//    - parameters : theArray - the Array to iterate over
//    - prints the items in the Array in forward and reverse
//        order, twice, using an iterator. 
void ForwardIteration(Array<String> & theArray);



// ForwardConstIteration
//    - parameters : theArray - the Array to iterate over
//    - prints the items in the Array in forward and reverse
//        order, twice, using a const_iterator. 
void ForwardConstIteration(Array<String> const & theArray);



// ReverseIteration
//    - parameters : theArray - the Array to iterate over
//    - prints the items in the Array in "reverse order" forwards
//        and backwards, twice, using a reverse_iterator. 
void ReverseIteration(Array<String> & theArray);



// ReverseConstIteration
//    - parameters : theArray - the Array to iterate over
//    - prints the items in the Array in "reverse order" forwards
//        and backwards, twice, using a const_reverse_iterator. 
void ReverseConstIteration(Array<String> const & theArray);



// ForwardIterationWithChanges
//    - parameters : theArray - the Array to iterate over
//    - prints the items in the Array in forward and reverse
//        order, twice, using an iterator. A letter 'M' is 
//        added to the end of each String the first time forward, 
//        and that 'M' is changed to a 'L' the second time forward. 
void ForwardIterationWithChanges(Array<String> & theArray);



// ReverseIterationWithChanges
//    - parameters : theArray - the Array to iterate over
//    - prints the items in the Array in "reverse order" forwards
//        and backwards, twice, using a reverse_iterator. A letter 'M' 
//        is added to the end of each String the first time in forwards
//        "reverse order", and that 'M' is changed to a 'L' the second 
//        time forwards in "reverse order". 
void ReverseIterationWithChanges(Array<String> & theArray);


#endif



