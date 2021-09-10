// *************************************************
// *                                               *
// *  ugraph.C                                     *
// *                                               *
// *  Implementations for undirected graph classes *
// *                                               *
// *  Written 10 Nov 1998 by Jason Zych            *
// *                                               *
// *  Inspiration for these classes drawn from     *
// *   the publicly posted interface of the LEDA   *
// *   library: http://www.mpi-sb.mpg.de/LEDA/     *
// *                                               *
// *************************************************

#include "ugraph.h"


// **************************************************************
// *                                                            *
// *  Class : UndirGraph                                        *
// *                                                            *
// *  A class providing an undirected graph representation.     *
// *                                                            *
// *  Written 13 Nov 1998 by Jason Zych                         *
// *                                                            *
// **************************************************************

UndirGraph::UndirGraph() : Graph()
{
   SetDirectedFlag(0);  
}


UndirGraph::UndirGraph(const UndirGraph& origVal) : Graph(origVal) {} 

UndirGraph::~UndirGraph() {}

UndirGraph& UndirGraph::operator=(const UndirGraph& origVal)
{
   if (this!=&origVal)
   {
      Graph::operator=(origVal); 
   } 
   return *this;
} 



// **************************************************************
// *                                                            *
// *  Class : UndirInfoGraph                                    *
// *                                                            *
// *  A class providing an undirected graph representation      *
// *   that is parameterized so that information can be stored  *
// *   at the vertices and edges of the graph                   *
// *                                                            *
// *  Written 13 Nov 1998 by Jason Zych                         *
// *                                                            *
// **************************************************************


template <class Vtype, class Etype>
UndirInfoGraph<Vtype, Etype>::UndirInfoGraph() : 
		InfoGraph<Vtype, Etype>() 
{
   SetDirectedFlag(0); 
}


template <class Vtype, class Etype>
UndirInfoGraph<Vtype, Etype>::
   UndirInfoGraph(const UndirInfoGraph<Vtype, Etype>& origVal) : 
		InfoGraph<Vtype, Etype>(origVal) {}



template <class Vtype, class Etype>
UndirInfoGraph<Vtype, Etype>::~UndirInfoGraph() {} 



template <class Vtype, class Etype>
UndirInfoGraph<Vtype, Etype>& 
   UndirInfoGraph<Vtype, Etype>::
      operator=(const UndirInfoGraph<Vtype, Etype>& origVal)
{
   if (this!=&origVal)
   {
      InfoGraph<Vtype, Etype>::operator=(origVal); 
   }
   return *this; 
}


