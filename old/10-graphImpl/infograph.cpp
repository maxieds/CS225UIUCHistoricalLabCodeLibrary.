// ****************************************************
// *                                                  *
// *  infograph.cpp                                   *
// *                                                  *
// *  Implementation for a parameterized graph class  *
// *                                                  *
// *  Written 10 Nov 1998 by Jason Zych               *
// *                                                  *
// *  Inspiration for this graph class drawn from     *
// *   the publicly posted interface of the LEDA      *
// *   library: http://www.mpi-sb.mpg.de/LEDA/        *
// *                                                  *
// *  Directed flag added to constructor              *
// *    3 August 1999 by Jason Zych                   *
// ****************************************************


#include "infograph.h"



// InfoGraph
//    - default constructor
//    - initializes object to default values
template <class Vtype, class Etype>
InfoGraph<Vtype, Etype>::InfoGraph(int isDirectedFlag) : Graph(isDirectedFlag)
{
   vertexInfo.SetBounds(1, 100); 
   edgeInfo.SetBounds(1, 100); 
}


// InsertVertex
//    - parameters : vertValue - value to be attached to new vertex
//    - return value : the new vertex
//    - adds a new vertex to graph, assigns the vertex the value
//         vertValue, and returns the vertex
template <class Vtype, class Etype>
Vertex InfoGraph<Vtype, Etype>::InsertVertex(Vtype vertValue)
{
   Vertex v1 = Graph::InsertVertex(); 
   vertexInfo[VertexKey(v1)] = vertValue;
   return v1;
}


// InsertEdge
//    - parameters : sourceVert - source vertex of new edge
//                 : targetVert - target vertex of new edge
//                 : edgeValue - value to be attached to new edge
//    - return value : the new edge
//    - adds a new edge to the graph between the parameter vertices,
//         assigns the edge the value edgeValue, and returns that edge
template <class Vtype, class Etype>
Edge InfoGraph<Vtype, Etype>::InsertEdge(Vertex sourceVert, 
					Vertex targetVert, Etype edgeValue)
{
   Edge e1 = Graph::InsertEdge(sourceVert, targetVert); 
   edgeInfo[EdgeKey(e1)] = edgeValue;
   return e1; 
}



// VertexInfo
//    - parameters : infoVert - vertex whose value we want
//    - return type : a vertex information value
//    - returns the information variable stored in this vertex
template <class Vtype, class Etype>
Vtype InfoGraph<Vtype, Etype>::VertexInfo(Vertex infoVert)
{
   return vertexInfo[VertexKey(infoVert)]; 

}


// EdgeInfo
//    - parameters : infoEdge - edge whose value we want
//    - return type : an edge information value
//    - returns the information variable stored in this edge
template <class Vtype, class Etype>
Etype InfoGraph<Vtype, Etype>::EdgeInfo(Edge infoEdge)
{
   return edgeInfo[EdgeKey(infoEdge)];
}


// VertexAssign
//    - parameters : infoVert - vertex at which we will store info
//                 : vertValue - information value for the vertex
//    - stores the value vertValue at the vertex infoVert, writing
//       over whatever information used to be at infoVert, if any
template <class Vtype, class Etype>
void InfoGraph<Vtype, Etype>::VertexAssign(Vertex infoVert, Vtype vertValue)
{
   vertexInfo[VertexKey(infoVert)] = vertValue;
}


// EdgeAssign
//    - parameters : infoEdge - edge at which we will store info
//                 : edgeValue - information value for the edge
//    - stores the value edgeValue at the edge infoEdge, writing
//       over whatever information used to be at infoEdge, if any
template <class Vtype, class Etype>
void InfoGraph<Vtype, Etype>::EdgeAssign(Edge infoEdge, Etype edgeValue)
{
   edgeInfo[EdgeKey(infoEdge)] = edgeValue; 
}

