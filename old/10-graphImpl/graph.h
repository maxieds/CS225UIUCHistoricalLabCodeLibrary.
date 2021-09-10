// ******************************************************************
// *                                                                *
// *  graph.h                                                       *
// *                                                                *
// *  Interfaces for graph-related classes                          *
// *                                                                *
// *  Written Nov 1998 by Jason Zych                                *
// *   Updated by April 1999 by Jason Zych                          *
// *      - Mass Update and Remove functions repaired               *
// *      - general code cleanup and commenting                     *
// *                                                                *
// *  Planned future updates:                                       *
// *      - add code to insure that edges and vertices being        *
// *         passed into this graph are actually edges and          *
// *         vertices in this graph rather than some other graph    *         
// *      - perhaps reference counting code to internal nodes so    *
// *         that external iterators can be accurately converted to *
// *         point to the nil vertex when necessary                 *
// *      - perhaps along with the above, add code to allow user    *
// *         to compile error detection only when debugging         *
// *                                                                *
// *  Inspiration for this graph class drawn from                   *
// *   the publicly posted interface of the LEDA                    *
// *   library: http://www.mpi-sb.mpg.de/LEDA/                      *
// *                                                                *
// *  This file consists of five separate classes which             *
// *   are all related:                                             *
// *                                                                *
// *       - VertexNode : internal vertex implementation            *
// *       - Vertex : external "iterator" on VertexNode objects     *
// *                    client uses these Vertex objects            * 
// *       - EdgeNode : internal edge implementation                *
// *       - Edge : external "iterator" on EdgeNode objects         *
// *                    client uses these Edge objects              *
// *       - Graph : internally, holds collection of vertices and   *
// *                   collection of edges; functions take Vertex   *
// *                   and Edge objects as parameters and           *
// *                   manipulate the internal VertexNode and       *
// *                   EdgeNode objects they refer to.              *
// *                                                                *
// ******************************************************************


#ifndef _GRAPH_H
#define _GRAPH_H

#include "array.h"

// forward declarations
//    - with these lines we simply let the compiler know that
//      these classes exist and will be defined later, so that
//      we can, for example, refer to EdgeNode pointers inside a 
//      class before we formally declare the EdgeNode class. 
class VertexNode; 
class EdgeNode; 


// **************************************************************
// *                                                            *
// *  Class : VertexNode                                        *
// *                                                            *
// *  A vertex implementation, to be manipulated by a           *
// *     Graph class but hidden from the user of the Graph      *
// *     class. This is the interface for the class.            * 
// *                                                            *
// **************************************************************

class VertexNode
{
private:

   // *** member functions of VertexNode

   // VertexNode
   //    - default constructor
   //    - initializes object to default values
   VertexNode(); 


   // When we copy a VertexNode, we do not expect to copy all
   // nodes that this VertexNode might point to. Therefore,
   // we are not concerned about making hard copies of the pointed-to
   // dynamic memory, only soft-copies, and therefore the default copy
   // constructor and assignment operator (i.e. memberwise copies) and 
   // the default destructor (i.e. nothing) are what we want.  
 
 
   // *** member fields of VertexNode
    
   int vertexKey;            // table key held in Vertex (helpful for
			     //    parameterized graphs)

   int vertexMark;           // a numerical field used to record a 
                             //    processing flag or mark of some kind. 
                             //    Initially set to 0. 
 
   int isDirected;           // flag indicating whether this vertex
                             //    is in a directed graph (== 1) or
                             //    an undirected graph (== 0)

   int numDepartEdges;       // number of departing edges 

   int numEnterEdges;        // number of entering edges

	// NOTE: undirected edges will all be recorded as "departing" 
	//   and so for undirected graphs, the second field will
	//   always be 0.  

 
   EdgeNode* departingEdges; // list of edges for which this vertex 
	                     //    is the source)

   EdgeNode* enteringEdges;  // list of edges for which this vertex 
			     //    is the target)

        // NOTE: undirected edges will all be recorded as "departing" 
        //   and so for undirected graphs, the second field will
        //   always be NULL. 


   VertexNode* prevVertex;   // previous vertex in vertex list

   VertexNode* nextVertex;   // next vertex in vertex list



   // *** friend classes of VertexNode

   friend class EdgeNode;
   friend class Graph;

};  



// **************************************************************
// *                                                            *
// *  Class : Vertex                                            *
// *                                                            *
// *  A vertex wrapper class. This class will provide access    *
// *     to a VertexNode object, but only from within the       *
// *     actual Graph class itself. The only parts of this      *
// *     interface that are available to the user are the       *
// *     creation and assignment operators. This way, the user  *
// *     can maintain "pointers" to vertices without actually   *
// *     being able to access their fields or needing to know   *
// *     their implementation.                                  *
// *                                                            *
// **************************************************************

class Vertex
{
public:

   // Vertex
   //    - default constructor
   //    - initializes object to default values 
   Vertex();


   // When we copy a Vertex, we do not expect to copy the node that 
   // this Vertex's pointer might point to -- we merely want to point 
   // a second pointer to the same VertexNode. Therefore, we are not 
   // concerned about making hard copies of the pointed-to dynamic 
   // memory, only soft-copies, and therefore the default copy 
   // constructor and assignment operator (i.e. memberwise copies) and 
   // the default destructor (i.e. nothing) are what we want.


   // operator==
   //    - parameters : compareVert - a vertex to which we can compare 
   //                      this object
   //    - return value : boolean integer
   //    - returns 1 if the two Vertex objects wrap around the same vertex 
   //         otherwise returns 0 
   int operator==(const Vertex& compareVert);


   // operator!=
   //    - parameters : compareVert - a vertex to which we can compare
   //                      this object
   //    - return value : boolean integer
   //    - returns 0 if the two Vertex objects wrap around the same vertex 
   //         otherwise returns 1
   int operator!=(const Vertex& compareVert);


private:

   // Vertex
   //    - constructor
   //    - parameters : initVPtr - a VertexNode pointer used to 
   //                     initialize this object
   //    - a private constructor which initializes the Vertex object
   //         given a VertexNode pointer. Essentially, this function
   //         "casts" the VertexNode pointer to a Vertex object.  
   Vertex(VertexNode* initVPtr); 


   // VPtr
   //    - return value : pointer to the internal VertexNode pointer
   //    - returns the value held in the internal VertexNode pointer.
   //         Used to shorten the syntax needed to access the 
   //         "vertexNodePtr" field of this object 
   VertexNode* VPtr(); 


   VertexNode* vertexNodePtr;   // pointer to a VertexNode in the graph 


   friend class Graph;  // the Graph class needs access to the internal
                        //   information of Vertex objects 

}; 




// **************************************************************
// *                                                            *
// *  Class : EdgeNode                                          *
// *                                                            *
// *  An edge implementation, to be manipulated by a            *
// *     Graph class but hidden from the user of the Graph      *
// *     class. This is the interface for the class.            *
// *                                                            *
// **************************************************************

class EdgeNode
{
private:

   // *** member functions of EdgeNode

   // EdgeNode
   //    - default constructor
   //    - initializes object to default values
   EdgeNode();


   // When we copy an EdgeNode, we do not expect to copy all
   // nodes that this EdgeNode might point to. Therefore,
   // we are not concerned about making hard copies of the pointed-to
   // dynamic memory, only soft-copies, and therefore the default copy 
   // constructor and assignment operator (i.e. memberwise copies) and 
   // the default destructor (i.e. nothing) are what we want.

  
   // *** member fields of EdgeNode

   int edgeKey;                  // table key held in Edge (helpful for
				 //    parameterized graphs)

   int edgeMark;            // a numerical field used to record a 
                            // processing flag or mark of some kind.
                            // Initially set to 0.

   int isDirected;          // flag indicating whether this edge 
                            //    is directed (== 1) or undirected (== 0)


   VertexNode* source;          // pointer to source vertex of edge 

   EdgeNode* prevSourceEdge;    // pointer to previous edge in the
				//    departingEdges list of the 
			        //    source vertex

   EdgeNode* nextSourceEdge;    // pointer to the next edge in the 
				//    departingEdges list of the
				//    source vertex

   VertexNode* target;          // pointer to target edge

   EdgeNode* prevTargetEdge;    // pointer to previous edge in the
				//    enteringEdges list of the
				//    target vertex

   EdgeNode* nextTargetEdge;    // pointer to next edge in the 
				//    enteringEdge list of the 
				//    target vertex


        // NOTE: undirected edges will all be recorded as "departing" 
        //   from the vertex point of view, and so from the edge point
        //   point of view, it is in the "deaparting" edges list for
	//   _both_ the source _and_ target vertex. Hence, the idea of
        //   one vertex specifically being the source and the other
        //   specifically being the target is a concept that is relatively
	//   meaningless for undirected graphs.  


   EdgeNode* prevEdge;    // previous edge in the graph's edge list

   EdgeNode* nextEdge;    // next edge in the graph's edge list



   // *** friend classes of EdgeNode

   friend class VertexNode;
   friend class Graph;

}; 



// **************************************************************
// *                                                            *
// *  Class : Edge                                              *
// *                                                            *
// *  An edge wrapper class. This class will provide access     *
// *     to an EdgeNode object, but only from within the        *
// *     actual Graph class itself. The only parts of this      *
// *     interface that are available to the user are the       *
// *     creation and assignment operators. This way, the user  *
// *     can maintain "pointers" to edges without actually      *
// *     being able to access their fields or needing to know   *
// *     their implementation.                                  *
// *                                                            *
// **************************************************************

class Edge 
{
public:

   // Edge
   //    - default constructor
   //    - initializes object to default values
   Edge();


   // When we copy an Edge, we do not expect to copy the node that
   // this Edge's pointer might point to -- we merely want to point
   // a second pointer to the same EdgeNode. Therefore, we are not
   // concerned about making hard copies of the pointed-to dynamic
   // memory, only soft-copies, and therefore the default copy
   // constructor and assignment operator (i.e. memberwise copies) and
   // the default destructor (i.e. nothing) are what we want.


   // operator==
   //    - parameters : compareEdge - an edge to which we can compare
   //                      this object
   //    - return value : boolean integer
   //    - returns 1 if the two Edge objects wrap around the same edge, 
   //         otherwise returns 0
   int operator==(const Edge& compareEdge);


   // operator!=
   //    - parameters : compareEdge - an edge to which we can compare
   //                      this object
   //    - return value : boolean integer
   //    - returns 0 if the two Edge objects wrap around the same edge 
   //         otherwise returns 1
   int operator!=(const Edge& compareEdge);


private:


   // Edge 
   //    - constructor
   //    - parameters : initEPtr - an EdgeNode pointer used to 
   //                     initialize this object
   //    - a private constructor which initializes the Edge object
   //         given an EdgeNode pointer. Essentially, this function
   //         "casts" the EdgeNode pointer to a Edge object.
   Edge(EdgeNode* initEPtr);


   // EPtr
   //    - return value : pointer to the internal EdgeNode pointer
   //    - returns the value held in the internal EdgeNode pointer.
   //         Used to shorten the syntax needed to access the
   //         "edgeNodePtr" field of this object
   EdgeNode* EPtr(); 


   EdgeNode* edgeNodePtr;   // pointer to an EdgeNode in the graph

   friend class Graph; // the Graph class needs access to the internal
                        //   information of Edge objects

};


// **************************************************************
// *                                                            *
// *  Class : Graph                                             *
// *                                                            *
// *  A class providing a graph representation. The interface   *
// *   functions allow the user to manipulate the graph with    *
// *   full knowledge of and access to the structure of the     *
// *   graph -- that is, knowledge of the existence of          *
// *   vertices and edges, and which vertices are adjacent to   *
// *   which other vertices via which edges -- but the user     * 
// *   does not have access to the actual vertex and edge       *
// *   implementations, but rather only knowledge of the        *
// *   _existence_ of the vertices and edges. Therefore, any    *
// *   manipulation of the graph _must_ be done via the graph   *
// *   functions themselves, and therefore the user is able     *
// *   to view the graph details in a very abstract manner      *
// *   while being prevented from accessing the implementation  *
// *   itself.                                                  *
// *                                                            *
// **************************************************************

class Graph
{
public:

   // ********************** Mass Update **********************

   // Graph
   //    - default constructor
   //    - parameters : isDirectedFlag - flag to indicated whether graph
   //                      will be directed or undirected
   //    - initializes object to default values
   Graph(int isDirectedFlag = 1);


   // Graph
   //    - copy constructor
   //    - parameters : origVal - previously allocated Graph object
   //    - initializes object to be a copy of origVal
   Graph(const Graph& origVal); 


   // ~Graph
   //    - destructor
   //    - deletes dynamically allocated memory
   virtual ~Graph();


   // operator=
   //    - parameters : origVal - previously allocated Graph object
   //    - return value : reference to this object
   //    - sets object to be a copy of origVal
   Graph& operator=(const Graph& origVal); 


   // Clear
   //    - sets object to be a copy of default (empty) graph 
   //      Graph will remain directed or remain undirected; this
   //      function call will not change that.
   void Clear(); 


   // ******************* Graph structure alteration ******************* 


   // MakeUndirected
   //    - if graph is undirected, function returns without
   //       doing anything. If graph is directed, it is converted
   //       to an undirected graph. The new graph will be the old
   //       graph with direction removed from the edges -- that
   //       is, if you previously had an edge from a->b, you now
   //       have an a-b edge (i.e. the edge becomes undirected). 
   void MakeUndirected();


   // InsertVertex
   //    - return value : the new vertex 
   //    - adds a new vertex to graph and returns it 
   Vertex InsertVertex();

  
   // RemoveVertex
   //    - parameters : delVert - vertex to be deleted
   //    - deletes parameter vertex from graph 
   void RemoveVertex(Vertex delVert); 


   // InsertEdge
   //    - parameters : sourceVert - source vertex of new edge
   //                 : targetVert - target vertex of new edge
   //    - return value : the new edge 
   //    - adds a new edge to the graph between the parameter vertices,
   //         returns that edge 
   Edge InsertEdge(Vertex sourceVert, Vertex targetVert); 

   
   // RemoveEdge
   //    - parameters : delEdge - edge to be deleted
   //    - deletes parameter edge
   void RemoveEdge(Edge delEdge); 


   // ReverseEdge
   //    - parameters : revEdge - edge to reverse
   //    - reverse revEdge (i.e. makes its former source endpoint
   //       its target endpoint and vice-versa)
   void ReverseEdge(Edge revEdge);



   // ******************* Graph structure information ******************


   //      ---------- Graph information 

   // NumGraphVertices
   //    - return value : integer quantity
   //    - returns the number of vertices in the graph
   int NumGraphVertices();


   // NumGraphEdges
   //    - return value : integer quantity
   //    - returns the number of edges in the graph
   int NumGraphEdges();


   //      ---------- Vertex information

   // NumDepartEdges
   //    - parameters : queryVert - vertex which we want information about
   //    - return value : integer quantity
   //    - returns the number of edges departing from Vertex queryVert 
   int NumDepartEdges(Vertex queryVert); 


   // NumEnterEdges
   //    - parameters : queryVert - vertex which we want information about
   //    - return value : integer quantity
   //    - returns the number of edges entering Vertex queryVert 
   int NumEnterEdges(Vertex queryVert); 


   // NumTotalEdges
   //    - parameters : queryVert - vertex which we want information about
   //    - return value : integer quantity
   //    - returns the number of edges departing or entering Vertex queryVert 
   int NumTotalEdges(Vertex queryVert);



   //      ---------- Edge information

   // Source
   //    - parameters : queryEdge - edge which we want information about
   //    - return value : a vertex of the graph 
   //    - returns source vertex of this edge (i.e. the vertex it departs)
   Vertex Source(Edge queryEdge); 


   // Target
   //    - parameters : queryEdge - edge which we want information about
   //    - return value : a vertex of the graph
   //    - returns target vertex of this edge (i.e. the vertex it enters)
   Vertex Target(Edge queryEdge);


   // OtherEndpoint
   //    - parameters : queryEdge - edge which we want information about
   //                 : endpointOne - one of the two endpoints of the edge
   //    - return value : a vertex of the graph
   //    - if endpointOne is the source vertex of this edge, the target
   //        vertex of this edge will be returned. If endpointOne is 
   //        instead the target vertex of this edge, the source vertex 
   //        will be returned. If endpointOne is not an endpoint of this
   //        edge, the nil vertex will be returned
   Vertex OtherEndpoint(Edge queryEdge, Vertex endpointOne); 


   

   // ****************** Graph traversal ********************

   //      ---------- Vertex traversal 

   // FirstVertex
   //    - return type : a vertex of the graph
   //    - returns the "first" vertex in the abstract set of
   //        vertices of the graph. If graph is empty, returns
   //        the nil vertex.
   Vertex FirstVertex();


   // LastVertex
   //    - return type : a vertex of the graph
   //    - returns the "last" vertex in the abstract set of
   //        vertices of the graph. If graph is empty, returns
   //        the nil vertex.
   Vertex LastVertex();


   // NextVertex
   //    - parameters : currentVert - a vertex of the graph
   //    - return type : a vertex of the graph
   //    - returns the vertex "after" currentVert in the abstract set 
   //        of vertices of the graph. If currentVert is the last vertex 
   //        in the vertex set, returns the nil vertex.
   Vertex NextVertex(Vertex currentVert);


   // PrevVertex
   //    - parameters : currentVert - a vertex of the graph
   //    - return type : a vertex of the graph
   //    - returns the vertex "before" currentVert in the abstract set 
   //        of vertices of the graph. If currentVert is the first 
   //        vertex in the vertex set, returns the  nil vertex.
   Vertex PrevVertex(Vertex currentVert);


   //      ---------- Edge traversal 

   // FirstEdge
   //    - return type : an edge of the graph
   //    - returns the "first" edge in the abstract set of
   //        edges of the graph. If graph has no edges, returns
   //        the nil edge.
   Edge FirstEdge();


   // LastEdge
   //    - return type : an edge of the graph
   //    - returns the "last" edge in the abstract set of
   //        edges of the graph. If graph has no edges, returns
   //        the nil edge.
   Edge LastEdge();


   // NextEdge
   //    - parameters : currentEdge - an edge of the graph
   //    - return type : an edge of the graph
   //    - returns the edge "after" currentEdge in the abstract
   //        set of edges of the graph. If currentEdge is the last 
   //        edge in the edge set, returns the nil edge
   Edge NextEdge(Edge currentEdge); 


   // PrevEdge
   //    - parameters : currentEdge - an edge of the graph
   //    - return type : an edge of the graph
   //    - returns the edge "before" currentEdge in the abstract 
   //        set of edges of the graph. If currentEdge is the first 
   //        edge in the edge set, returns the nil edge
   Edge PrevEdge(Edge currentEdge); 



   //      ---------- Vertex departing edge traversal
   //                     --- meant for directed graphs

   // FirstDepartEdge
   //    - parameters : departFromVert - vertex we are inspecting 
   //    - return value : an edge of the graph 
   //    - returns the "first" edge in the abstract set 
   //        of all edges departing from the vertex departFromVert.
   //        If departFromVert has no departing edges, returns
   //        the nil edge.   
   Edge FirstDepartEdge(Vertex departFromVert);


   // LastDepartEdge
   //    - parameters : departFromVert - vertex we are inspecting
   //    - return value : an edge of the graph
   //    - returns the "last" edge in the abstract set
   //        of all edges departing from the vertex departFromVert. 
   //        If departFromVert has no departing edges, returns
   //        the nil edge.
   Edge LastDepartEdge(Vertex departFromVert); 


   // NextDepartEdge
   //    - parameters : currentEdge - an edge of the graph
   //    - return value : an edge of the graph 
   //    - returns the edge "after" currentEdge in the abstract
   //        set of all edges which depart from the same source 
   //        vertex as currentEdge. (The source vertex can be found
   //        from the edge, which is why we don't need to pass in
   //        the source vertex as a parameter.) If this is the last
   //        edge in the set described above, returns the nil edge. 
   Edge NextDepartEdge(Edge currentEdge);            


   // PrevDepartEdge 
   //    - parameters : currentEdge - an edge of the graph
   //    - return value : an edge of the graph
   //    - returns the edge "before" currentEdge in the abstract
   //        set of all edges which depart from the same source 
   //        vertex as currentEdge. (The source vertex can be found
   //        from the edge, which is why we don't need to pass in
   //        the source vertex as a parameter.) If this is the first 
   //        edge in the set described above, returns the nil edge. 
   Edge PrevDepartEdge(Edge currentEdge);          


   //      ---------- Vertex entering edge traversal
   //                     --- meant for directed graphs

   // FirstEnterEdge
   //    - parameters : enterIntoVert - vertex we are inspecting
   //    - return value : an edge of the graph
   //    - returns the "first" edge in the abstract set
   //        of all edges entering the vertex enterIntoVert. 
   //        If enterIntoVert has no entering edges, returns
   //        the nil edge.
   Edge FirstEnterEdge(Vertex enterIntoVert); 


   // LastEnterEdge
   //    - parameters : enterIntoVert - vertex we are inspecting
   //    - return value : an edge of the graph
   //    - returns the "last" edge in the abstract set
   //        of all edges entering the vertex enterIntoVert. 
   //        If enterIntoVert has no entering edges, returns
   //        the nil edge.
   Edge LastEnterEdge(Vertex v1); 


   // NextEnterEdge
   //    - parameters : currentEdge - an edge of the graph
   //    - return value : an edge of the graph
   //    - returns the edge "after" currentEdge in the abstract
   //        set of all edges which enter same target 
   //        vertex as currentEdge. (The target vertex can be found
   //        from the edge, which is why we don't need to pass in
   //        the target vertex as a parameter.) If this is the last
   //        edge in the set described above, returns the nil edge. 
   Edge NextEnterEdge(Edge currentEdge); 


   // PrevEnterEdge
   //    - parameters : currentEdge - an edge of the graph
   //    - return value : an edge of the graph
   //    - returns the edge "before" currentEdge in the abstract
   //        set of all edges which enter the same target 
   //        vertex as currentEdge. (The target vertex can be found
   //        from the edge, which is why we don't need to pass in
   //        the target vertex as a parameter.) If this is the first 
   //        edge in the set described above, returns the nil edge. 
   Edge PrevEnterEdge(Edge currentEdge); 



   //      ---------- Vertex adjacent edge traversal 
   //                      --- meant for undirected graphs

   // FirstAdjacentEdge
   //    - parameters : endpointVert - vertex we are inspecting
   //    - return value : an edge of the graph
   //    - returns the "first" edge in the abstract set
   //        of all edges which have endpointVert as an endpoint 
   //        If endpointVert is not an endpoint of any edge, returns
   //        the nil edge.
   Edge FirstAdjacentEdge(Vertex endpointVert);       


   // LastAdjacentEdge
   //    - parameters : endpointVert - vertex we are inspecting
   //    - return value : an edge of the graph
   //    - returns the "last" edge in the abstract set
   //        of all edges which have endpointVert as an endpoint 
   //        If endpointVert is not an endpoint of any edge, returns
   //        the nil edge.
   Edge LastAdjacentEdge(Vertex endpointVert); 


   // NextAdjacentEdge
   //    - parameters : currentEdge - an edge in the graph
   //                 : endpointVert - an endpoint of currentEdge 
   //    - return value : an edge of the graph
   //    - returns the edge "after" currentEdge in the abstract 
   //        set of all edges that have the vertex endpointVert 
   //        as an endpoint. If this is the last edge in the set
   //        described above, returns the nil edge. 
   Edge NextAdjacentEdge(Edge currentEdge, Vertex endpointVert); 


   // PrevAdjacentEdge
   //    - parameters : currentEdge - an edge in the graph
   //                 : endpointVert - an endpoint of currentEdge 
   //    - return value : an edge of the graph
   //    - returns the edge "before" currentEdge in the abstract 
   //        set of all edges that have the vertex endpointVert 
   //        as an endpoint. If this is the first edge in the set 
   //        described above, returns the nil edge.
   Edge PrevAdjacentEdge(Edge currentEdge, Vertex endpointVert); 



   // *************** Mark processing *********************


   //      ---------- Vertex marks

   // GetVertexMark
   //    - parameters : markVert - vertex with mark to read
   //    - return value : integer flag
   //    - returns the mark value of the vertex markVert 
   int GetVertexMark(Vertex markVert);


   // SetVertexMark
   //    - parameters : markVert - vertex to be marked 
   //                 : markToAssign - mark to assign to vertex
   //    - sets the mark of vertex markVert to be equal to markToAssign  
   void SetVertexMark(Vertex markVert, int markToAssign);


   // ClearVertexMarks
   //    - sets all vertex mark fields to 0
   void ClearVertexMarks();


   //      ---------- Edge Marks

   // GetEdgeMark
   //    - parameters : markEdge - edge with mark to read 
   //    - return value : integer flag
   //    - returns the mark value of the edge markEdge
   int GetEdgeMark(Edge markEdge);


   // SetEdgeMark
   //    - parameters : markEdge - edge to be marked
   //                 : markToAssign - mark to assign to edge
   //    - sets the mark of edge markEdge to be equal to markToAssign
   void SetEdgeMark(Edge markEdge, int markToAssign);


   // ClearEdgeMarks
   //    - sets all edge mark fields to 0
   void ClearEdgeMarks();



   // ****************** Queries ***********************


   // IsEmpty
   //    - return value : boolean integer
   //    - returns 1 if the graph has no vertices or edges, and
   //         0 otherwise
   int IsEmpty(); 


   // IsDirected
   //    - return value : boolean integer
   //    - returns 1 if the graph is directed, and 0 otherwise
   int IsDirected(); 


   // IsUndirected
   //    - return value : boolean integer
   //    - returns 1 if the graph is undirected, and 0 otherwise
   int IsUndirected(); 


   // IsNil
   //    - parameters : queryVert
   //    - return value : boolean integer
   //    - returns 1 if queryVert is the nil vertex, and 0 otherwise
   int IsNil(Vertex queryVert);

   
   // IsNil
   //    - parameters : queryEdge
   //    - return value : boolean integer
   //    - returns 1 if queryEdge is the nil Edge, and 0 otherwise
   int IsNil(Edge queryEdge); 






protected:

   // ***************** Protected helper functions

   // VertexKey
   //    - parameters : infoVertex - the vertex whose key we want
   //    - return value : integer which is a vertex key
   //    - returns the vertex-to-information map key stored inside
   //        the vertex 
   int VertexKey(Vertex infoVertex); 


   // EdgeKey
   //    - parameters : infoEdge - the edge whose key we want 
   //    - return value : integer which is an edge key
   //    - returns the edge-to-information map key stored inside
   //        the edge
   int EdgeKey(Edge infoEdge); 


private:


   // ****************** Copying helper functions ******************

   // Copy
   //    - parameters : origVal - previously allocated Graph object
   //    - sets this object to be a copy of origVal; helper function
   //         for the copy constructor and assignment operator
   void Copy(const Graph& origVal);



   // CopyVertexNodes
   //    - parameters : origVal - previously allocated Graph object
   //                 : vArray - array mapping vertex keys to
   //                       VertexNode pointers
   //    - correctly creates a copy of the VertexNode list of origVal
   //         and stores it as the VertexNode list of this object.
   //         The pointers to EdgeNodes are not set here, but the rest
   //         of the VertexNode fields and all other Graph fields that
   //         are VertexNode-related will be correctly set (i.e. size
   //         and "maximum key value so far").
   void CopyVertexNodes(const Graph& origVal, 
			   Array<VertexNode*>& vArray);



   // CopyEdgeNodes
   //    - parameters : origVal - previously allocated Graph object
   //                 : eArray - array mapping edge keys to EdgeNode
   //                       pointers
   //    - correctly creates a copy of the EdgeNode list of origVal
   //         and stores it as the EdgeNode list of this object.
   //         The only pointers set here are the ones to the previous
   //         and next EdgeNode in the main edge list. In addition, all
   //         other Graph fields that are EdgeNode-related will also be
   //         correctly set (i.e. size and "maximum key value so far").
   void CopyEdgeNodes(const Graph& origVal, 
			   Array<EdgeNode*>& eArray);



   // CopyVertexConnections
   //    - parameters : origVal - previously allocated Graph object
   //                 : eArray - array mapping edge keys to EdgeNode
   //                       pointers
   //    - correctly reconstructs in this object (the new Graph) the
   //         connections between the VertexNode objects and the EdgeNode
   //         objects which are the heads of the entering and departing
   //         edge lists of those VertexNode objects. The object origVal
   //         (the old Graph) is used as a guide to do this, and the
   //         array eArray is used to quickly obtain a desired EdgeNode,
   //         given its key
   void CopyVertexConnections(const Graph& origVal, 
			   const Array<EdgeNode*>& eArray);




   // CopyEdgeConnections
   //    - parameters : origVal - previously allocated Graph object
   //                 : vArray - array mapping vertex keys to
   //                       VertexNode pointers
   //                 : eArray - array mapping edge keys to edge
   //                       pointers
   //    - correctly reconstructs in this object (the new Graph) the
   //         connections between the EdgeNode objects and
   //            1) the VertexNode objects which are its source and target
   //            2) the EdgeNode objects which are its neighbors in the
   //                 departing edge list of some VertexNode and the entering
   //                 edge list of some VertexNodes
   //         The object origVal (the old Graph) is used as a guide to do
   //         this, and the arrays vArray and eArray are used to quickly
   //         obtain a desired VertexNode or EdgeNode, given its key
   void CopyEdgeConnections(const Graph& origVal, 
			   const Array<VertexNode*>& vArray, 
		           const Array<EdgeNode*>& eArray);


   // ************** Vertex addition helper functions ***************

   // InsertEdgeIntoDirected
   //    - parameters : insEdge - pointer to EdgeNode being inserted 
   //                               into graph 
   //    - inserts insEdge into the departing edge list of its 
   //         source vertex, and into the entering edge list of 
   //         its target vertex
   void InsertEdgeIntoDirected(EdgeNode* insEdge);


   // InsertEdgeIntoUndirected
   //    - parameters : insEdge - pointer to EdgeNode being inserted
   //                                into graph 
   //    - inserts insEdge into the edge lists of both of its endpoints 
   void InsertEdgeIntoUndirected(EdgeNode* insEdge);


   // RemoveEdgeFromDirected
   //    - parameters : deleteEdgeNode - pointer to edge node that
   //                      is to be deleted
   //    - extracts deleteEdgeNode from the list of edges departing 
   //         from its source vertex, and also from the list of edges
   //         entering its target vertex
   void RemoveEdgeFromDirected(EdgeNode* deleteEdgeNode);


   // RemoveEdgeFromUndirected
   //    - parameters : deleteEdgeNode - pointer to edge node that
   //                      is to be deleted
   //    - extracts deleteEdgeNode from the edge list of deleteEdgeNode's
   //         first endpoint, and also extracts it from the edge list of 
   //         its second endpoint
   void RemoveEdgeFromUndirected(EdgeNode* deleteEdgeNode);



   // ************ Graph member data ***************

   VertexNode* vHead;    // pointer to front of list of vertices
   EdgeNode* eHead;      // pointer to front of list of edges
	
   int vSize;            // total number of vertices currently in graph
   int eSize;            // total number of edges currently in graph
 
   int isDirected;       // a flag indicating whether the graph has
			 // directed edges (flag == 1) or undirected
			 // edges (flag == 0). The results of certain
			 // functions depend on whether the graph is
			 // directed or undirected. 

   int vertexKeyCounter;  // counter to help assign index values to
                          //  vertices (helpful for parameterized graphs)

   int edgeKeyCounter;   // counter to help assign index values to
                         //   edges (helpful for parameterized graphs)

}; 


#endif 
