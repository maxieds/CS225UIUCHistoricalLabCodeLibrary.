// *************************************************
// *                                               *
// *  ugraph.h                                     *
// *                                               *
// *  Interfaces for undirected graph classes      *
// *                                               *
// *  Written 10 Nov 1998 by Jason Zych            *
// *                                               *
// *  Inspiration for these classes drawn from     *
// *   the publicly posted interface of the LEDA   *
// *   library: http://www.mpi-sb.mpg.de/LEDA/     *
// *                                               *
// *************************************************

#ifndef _UGRAPH_H
#define _UGRAPH_H

#include "graph.h"
#include "infograph.h"



// **************************************************************
// *                                                            *
// *  Class : UndirGraph                                        *
// *                                                            *
// *  A class providing an undirected graph representation.     * 
// *                                                            *
// *  Written 13 Nov 1998 by Jason Zych                         *
// *                                                            *
// **************************************************************

class UndirGraph : public Graph
{
public:

   UndirGraph(); 
   UndirGraph(const UndirGraph& origVal); 
   ~UndirGraph(); 
   UndirGraph& operator=(const UndirGraph& origVal); 

}; 



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
class UndirInfoGraph : public InfoGraph<Vtype, Etype>
{
public:

   UndirInfoGraph(); 
   UndirInfoGraph(const UndirInfoGraph& origVal); 
   ~UndirInfoGraph(); 
   UndirInfoGraph& operator=(const UndirInfoGraph& origVal); 
}; 

 
#endif

 
