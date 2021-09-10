// ***************************************************************
// *  graphalgs.h                                                *
// *                                                             *
// *  Headers for functions that operate publicly                *
// *   on the graph class.                                       *
// *                                                             *
// *  Written 10 Nov 1998 by Jason Zych                          *
// *                                                             *
// ***************************************************************

#ifndef _GRAPHALGS_H
#define _GRAPHALGS_H

#include "infograph.h"


//Print
//   - parameters : theGraph - a graph to print
//   - prints graph information
template <class Vtype, class Etype>
void Print(InfoGraph<Vtype, Etype>& theGraph);


#endif


