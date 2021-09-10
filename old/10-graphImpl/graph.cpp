// ************************************************************
// *                                                          *
// *  graph.cpp                                               *
// *                                                          *
// *  Implementations for graph-related classes               *
// *                                                          *
// *  Written Nov 1998 by Jason Zych                          *
// *   Updated by April 1999 by Jason Zych                    *
// *      - Mass Update and Remove functions repaired         *
// *      - general code cleanup and commenting               *
// *                                                          *
// *  Inspiration for this graph class drawn from             *
// *   the publicly posted interface of the LEDA              *
// *   library: http://www.mpi-sb.mpg.de/LEDA/                *
// *                                                          *
// *  This file consists of five separate classes which       *
// *   are all related:                                       *
// *                                                          *
// *       - VertexNode : internal vertex implementation      *
// *       - Vertex : external "iterator" on VertexNode       *
// *                    objects, client uses Vertex objects   *
// *       - EdgeNode : internal edge implementation          *
// *       - Edge : external "iterator" on EdgeNode           *
// *                    objects, client uses Edge objects     *
// *       - Graph : internally, holds collection of vertices *
// *                   and collection of edges; functions     *
// *                   take Vertex and Edge objects as        *
// *                   parameters and manipulate the internal *
// *                   VertexNode and EdgeNode objects they   *
// *                   refer to.                              *
// *                                                          * 
// ************************************************************

#include <stddef.h>
#include <iostream.h>
#include "graph.h"


// ***** PUT YOUR CODE HERE

















// *** END OF YOUR CODE

// **************************************************************
// *                                                            *
// *  Class : VertexNode                                        *
// *                                                            *
// *  A vertex implementation, to be manipulated by a           *
// *     Graph class but hidden from the user of the Graph      *
// *     class. This is the implementation for the class.       *
// *                                                            *
// **************************************************************


// VertexNode
//    - default constructor
//    - initializes object to default values
VertexNode::VertexNode()
{
   vertexKey = vertexMark = 0;          
   isDirected = 1;                      // defaults to directed


   numDepartEdges = numEnterEdges = 0;  // no edges of any kind yet
   departingEdges = NULL;  
   enteringEdges =  NULL;  

   prevVertex = this;    // If this is the only vertex
   nextVertex = this;    //   in the list, then it is also 
			 //   its own successor and predecessor,
			 //   since the list is circular. If it
			 //   is not the only vertex in the list,
			 //   these fields can be altered in the
			 //   vertex insertion algorithms. 
}




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


// Vertex
//    - default constructor
//    - initializes object to default values
Vertex::Vertex()
{
   vertexNodePtr = NULL; 
}



// operator==
//    - parameters : compareVert - a vertex to which we can compare
//                      this object
//    - return value : boolean integer
//    - returns 1 if the two vertices point to the same node,
//         otherwise returns 0
int Vertex::operator==(const Vertex& compareVert)
{
   return (vertexNodePtr == compareVert.vertexNodePtr);
}



// operator!=
//    - parameters : compareVert - a vertex to which we can compare
//                      this object
//    - return value : boolean integer
//    - returns 0 if the two vertices point to the same node,
//         otherwise returns 1
int Vertex::operator!=(const Vertex& compareVert)
{
   return (vertexNodePtr != compareVert.vertexNodePtr);
}



// Vertex
//    - constructor
//    - parameters : initPtr - a VertexNode pointer used to
//                     initialize this object
//    - a private constructor which initializes the Vertex object
//         given a VertexNode pointer. Essentially, this function
//         "casts" the VertexNode pointer to a Vertex object.
Vertex::Vertex(VertexNode* initVPtr)
{
   vertexNodePtr = initVPtr; 
}



// VPtr
//    - return value : pointer to the internal VertexNode pointer
//    - returns the value held in the internal VertexNode pointer.
//         Used to shorten the syntax needed to access the
//         "vertexNodePtr" field of this object
VertexNode* Vertex::VPtr()
{
   return vertexNodePtr; 
}




// **************************************************************
// *                                                            *
// *  Class : EdgeNode                                          *
// *                                                            *
// *  An edge implementation, to be manipulated by a            *
// *     Graph class but hidden from the user of the Graph      *
// *     class. This is the implementation for the class.       *
// *                                                            *
// *  Written 13 Nov 1998 by Jason Zych                         *
// *                                                            *
// **************************************************************


// EdgeNode
//    - default constructor
//    - initializes object to default values
EdgeNode::EdgeNode()
{
   edgeKey = edgeMark = 0;        
   isDirected = 1;               // defaults to directed  

   
   source = NULL;                // endpoints are unknown at 
   target = NULL;                //    creation time



   // EdgeNode objects are part of three lists:
   //    1) the list of all edges
   //    2) the list of all edges departing from its source vertex
   //    3) the list of all edges entering its target vertex
   // For each list, if this is the only edge in the list, then
   // it is also its own successor and predecessor, since we want
   // the lists to be circular. If it is not the only vertex in 
   // a certain list, then these fields can be altered in the edge
   // insertion algorithms. 

   prevEdge = nextEdge = this;               // list of all edges
   prevSourceEdge = nextSourceEdge = this;   // list of edges from source
   prevTargetEdge = nextTargetEdge = this;   // list of edges to target
} 



// ********************************************************************
// *                                                                  *
// *  Class : Edge                                                    *
// *                                                                  *
// *  An edge wrapper class. This class will provide access           *
// *     to an EdgeNode object, but only from within the              *
// *     actual Graph class itself. The only parts of this            *
// *     interface that are available to the user are the             *
// *     creation and assignment operators. This way, the user        *
// *     can maintain "pointers" to edges without actually            *
// *     being able to access their fields or needing to know         *
// *     their implementation.                                        *
// *                                                                  *
// *  Written 13 Nov 1998 by Jason Zych                               *
// *                                                                  *
// ********************************************************************



// Edge
//    - default constructor
//    - initializes object to default values
Edge::Edge()
{
   edgeNodePtr = NULL; 
}


// operator==
//    - parameters : compareEdge - an edge to which we can compare
//                      this object
//    - return value : boolean integer
//    - returns 1 if the two Edge objects wrap around the same edge, 
//         otherwise returns 0
int Edge::operator==(const Edge& compareEdge)
{
   return (edgeNodePtr == compareEdge.edgeNodePtr);
}



// operator!=
//    - parameters : compareEdge - an edge to which we can compare
//                      this object
//    - return value : boolean integer
//    - returns 0 if the two Edge objects wrap around the same edge 
//         otherwise returns 1
int Edge::operator!=(const Edge& compareEdge)
{
   return (edgeNodePtr != compareEdge.edgeNodePtr);
}



// Edge 
//    - constructor
//    - parameters : initEPtr - an EdgeNode pointer used to 
//                     initialize this object
//    - a private constructor which initializes the Edge object
//         given an EdgeNode pointer. Essentially, this function
//         "casts" the EdgeNode pointer to a Edge object.
Edge::Edge(EdgeNode* initEPtr)
{ 
   edgeNodePtr = initEPtr; 
}



// EPtr
//    - return value : pointer to the internal EdgeNode pointer
//    - returns the value held in the internal EdgeNode pointer.
//         Used to shorten the syntax needed to access the
//         "edgeNodePtr" field of this object
EdgeNode* Edge::EPtr()
{
   return edgeNodePtr; 
}





// *********************************************************************
// *                                                                   *
// *  Class : Graph                                                    *
// *                                                                   *
// *  A class providing a graph representation. The interface          *
// *   functions allow the user to manipulate the graph with           *
// *   full knowledge of and access to the structure of the            *
// *   graph -- that is, knowledge of the existence of                 *
// *   vertices and edges, and which vertices are adjacent to          *
// *   which other vertices via which edges -- but the user            *
// *   does not have access to the actual vertex and edge              *
// *   implementations, but rather only knowledge of the               *
// *   _existence_ of the vertices and edges. Therefore, any           *
// *   manipulation of the graph _must_ be done via the graph          *
// *   functions themselves, and therefore the user is able            *
// *   to view the graph in a very abstract manner.                    *
// *                                                                   *
// *  Written 13 Nov 1998 by Jason Zych                                *
// *                                                                   *
// *********************************************************************


// ********************** Mass Update **********************


// Graph
//    - default constructor
//    - initializes object to default values
Graph::Graph(int isDirectedFlag)
{   
   vHead = NULL;         // circularly-linked list of vertices
   vSize = 0;            //   starts out empty

   eHead = NULL;         // circularly-linked list of edges
   eSize = 0;            //   start out empty

   isDirected = isDirectedFlag;   // defaults to directed

   vertexKeyCounter = 0;
   edgeKeyCounter = 0;
}



// Graph
//    - copy constructor
//    - parameters : origVal - previously allocated Graph object
//    - initializes object to be a copy of origVal
Graph::Graph(const Graph& origVal)
{
   Copy(origVal);   
}
 


// ~Graph
//    - destructor
//    - deletes dynamically allocated memory
Graph::~Graph()
{
   Clear(); 
}



// operator=
//    - parameters : origVal - previously allocated Graph object
//    - return value : reference to this object
//    - sets object to be a copy of origVal
Graph& Graph::operator=(const Graph& origVal)
{
   if (this!=&origVal)
   {
      Clear();
      Copy(origVal);
   }
   return *this; 
}




// Clear 
//    - sets object to be a copy of default (empty) graph. 
//      Graph will remain directed or remain undirected; this
//      function call will not change that.
void Graph::Clear()
{
   // Step 1 : Delete vertex list
   //    - traverse circularly-linked list of VertexNode
   //       objects, deleting them one-by-one 

   VertexNode *frontVPtr, *prevVPtr; 
   frontVPtr = vHead;

   // if there are vertices in the vertex list, set the last
   //   node to point to NULL rather than the first node, 
   //   for ease of loop stopping
   if (frontVPtr!=NULL)
      frontVPtr->prevVertex->nextVertex = NULL; 

   while (frontVPtr != NULL)
   {
      prevVPtr = frontVPtr;
      frontVPtr = frontVPtr->nextVertex; 
      delete prevVPtr; 
   }

 
   // Step 2 : Delete edge list
   //    - traverse circularly-linked list of EdgeNode
   //       objects, deleting them one-by-one

   EdgeNode *frontEPtr, *prevEPtr; 
   frontEPtr = eHead; 

   // if there are edges in the edge list, set the last 
   //   node point to NULL rather than the first node, 
   //   for ease of loop stopping
   if (frontEPtr!=NULL)
      frontEPtr->prevEdge->nextEdge = NULL; 
  
   while (frontEPtr != NULL)
   {
      prevEPtr = frontEPtr; 
      frontEPtr = frontEPtr->nextEdge; 
      delete prevEPtr; 
   }


   // Step 3 : re-initialize the Graph member data, EXCEPT
   //   for the "isDirected" flag. Whatever the user last set
   //   this graph to be -- directed or undirected -- is what
   //   it should still be. 

   vHead = NULL;         // circularly-linked list of vertices
   vSize = 0;            //   is once again empty

   eHead = NULL;         // circularly-linked list of edges
   eSize = 0;            //   is once again empty

   vertexKeyCounter = 0;
   edgeKeyCounter = 0;

}





// ******************* Graph structure alteration *******************

// MakeUndirected
//    - if graph is undirected, function returns without
//       doing anything. If graph is directed, it is converted
//       to an undirected graph. The new graph will be the old
//       graph with direction removed from the edges -- that
//       is, if you previously had an edge from a->b, you now
//       have an a-b edge (i.e. the edge becomes undirected).
void Graph::MakeUndirected()
{
   if (isDirected)
   {
      isDirected = 0;
      int moreVertices;
      VertexNode* vertPtr;
      EdgeNode* tempEdge;
      vertPtr = vHead;    // first vertex of graph
      if (vertPtr == NULL)
         moreVertices = 0;
      else
         moreVertices = 1;
      while (moreVertices)
      {
         if (vertPtr->departingEdges == NULL)
         {
            vertPtr->departingEdges = vertPtr->enteringEdges;
            vertPtr->enteringEdges = NULL;
         }
         else if (vertPtr->enteringEdges != NULL)
         {
            tempEdge = vertPtr->enteringEdges->prevTargetEdge;
            vertPtr->departingEdges->prevSourceEdge->nextSourceEdge =
                vertPtr->enteringEdges;
            vertPtr->enteringEdges->prevTargetEdge->nextTargetEdge =
                vertPtr->departingEdges;
            vertPtr->enteringEdges->prevTargetEdge =
                vertPtr->departingEdges->prevSourceEdge;
            vertPtr->departingEdges->prevSourceEdge = tempEdge;
            vertPtr->numDepartEdges += vertPtr->numEnterEdges;
            vertPtr->enteringEdges = NULL;
            vertPtr->numEnterEdges = 0;
         }

         vertPtr = vertPtr->nextVertex;
         if (vertPtr == vHead)
            moreVertices = 0;
      }

   }
}




// InsertVertex
//    - return value : the new vertex
//    - adds a new vertex to graph and returns it
Vertex Graph::InsertVertex()
{
   // Step 1 : create new VertexNode for the list of vertices
   //    - assign this node an array key, for use in parameterized
   //        class
   //    - verify edge direction or lack of it in this graph 

   VertexNode* insVert = new VertexNode(); 
   vertexKeyCounter++; 
   insVert->vertexKey = vertexKeyCounter; 
   insVert->isDirected = isDirected; 


   // Step 2 : insert this VertexNode at end of vertex list
 
   if (vHead == NULL)
      vHead = insVert; 
   else
   {
      insVert->prevVertex = vHead->prevVertex; 
      insVert->nextVertex = vHead; 
      vHead->prevVertex->nextVertex = insVert;
      vHead->prevVertex = insVert; 
   }
   vSize++; 


   // Step 3 : return a Vertex that stores a pointer to the 
   //            new VertexNode

   return Vertex(insVert);  
}



 
// RemoveVertex
//    - parameters : delVert - vertex to be deleted
//    - deletes parameter vertex from graph
void Graph::RemoveVertex(Vertex delVert)
{
   // extract VertexNode pointer from Vertex
   VertexNode* deleteVertNode = delVert.VPtr();

   EdgeNode *travPtr,   // for traversing down lists of edges 
            *delPtr;    // for deleting edges


   // Step 1 : delete departing edges of delVert 

   travPtr = deleteVertNode->departingEdges; 
   if (travPtr != NULL)   // if the vertex has departing edges 
   {
      // exit loop when our current edge is the last one in
      //   the list, i.e. when the next edge in the circularly
      //   linked list is also the first one
      while (travPtr->nextSourceEdge != deleteVertNode->departingEdges)
      {
         delPtr = travPtr; 
         travPtr = travPtr->nextSourceEdge;
         RemoveEdge(Edge(delPtr));
      }
      RemoveEdge(Edge(travPtr));  // now, take care of that last edge 
   }


   // Step 2 : delete entering edges of delVert

   travPtr = deleteVertNode->enteringEdges;
   if (travPtr != NULL)
   {
      // exit loop when our current edge is the last one in 
      //   the list, i.e. when the next edge in the circularly
      //   linked list is also the first one 
      while (travPtr->nextTargetEdge != deleteVertNode->enteringEdges)
      {
         delPtr = travPtr; 
         travPtr = travPtr->nextTargetEdge;
         RemoveEdge(Edge(delPtr));
      }
      RemoveEdge(Edge(travPtr));  // now, take care of that last edge
   }


   // Step 3 : remove the vertex itself from the graph
    
   // if the vertex points to itself, it is the only vertex in 
   //    the vertex list
   if (deleteVertNode == deleteVertNode->nextVertex)   
      vHead = NULL;    // no more vertices left in list 
   else   // else there is more than vertex in the vertex list
   {
      deleteVertNode->nextVertex->prevVertex = deleteVertNode->prevVertex; 
      deleteVertNode->prevVertex->nextVertex = deleteVertNode->nextVertex; 

      // if the first vertex in the list is being deleted, point the
      //   list pointer (vHead) to the next vertex instead
      if (vHead == deleteVertNode)            
         vHead = deleteVertNode->nextVertex; 
   }                               

   delete deleteVertNode; 
   vSize--;  
}




// InsertEdge
//    - parameters : sourceVert - source vertex of new edge
//                 : targetVert - target vertex of new edge
//    - return value : the new edge 
//    - adds a new edge to the graph between the parameter vertices, 
//         returns that edge
Edge Graph::InsertEdge(Vertex sourceVert, Vertex targetVert)
{
   // extract VertexNode pointers from Vertex parameters 
   VertexNode* srcEndpoint = sourceVert.VPtr(); 
   VertexNode* tarEndpoint = targetVert.VPtr(); 

   // Step 1 : create new EdgeNode for the list of edges 
   //    - assign this node an array key, for use in parameterized
   //        class
   //    - verify edge direction or lack of it in this graph

   EdgeNode* insEdge = new EdgeNode(); 
   edgeKeyCounter++; 
   insEdge->edgeKey = edgeKeyCounter; 
   insEdge->isDirected = isDirected; 


   // Step 2 : insert node into edge list

   if (eHead == NULL)
      eHead = insEdge; 
   else
   {
      insEdge->prevEdge = eHead->prevEdge; 
      insEdge->nextEdge = eHead; 
      eHead->prevEdge->nextEdge = insEdge; 
      eHead->prevEdge = insEdge; 
   }
   eSize++; 


   // Step 3 : insert node into source and target edge lists
   // insertion into edge lists is different depending on 
   //   whether graph is directed or undirected

   insEdge->source = srcEndpoint;
   insEdge->target = tarEndpoint;
   if (isDirected)
      InsertEdgeIntoDirected(insEdge); 
   else
      InsertEdgeIntoUndirected(insEdge);


   // Step 4 : return an Edge that stores a pointer to the
   //            new EdgeNode

   return Edge(insEdge);
}



// RemoveEdge
//    - parameters : delEdge - edge to be deleted
//    - deletes parameter edge
void Graph::RemoveEdge(Edge delEdge)
{
   // Extract EdgeNode pointer from edge
   EdgeNode* deleteEdgeNode = delEdge.edgeNodePtr;


   // Step 1 : Disconnect deleteEdgeNode from the two lists
   //              of vertex's edges that it is a part of 

   if (isDirected)
      RemoveEdgeFromDirected(deleteEdgeNode);
   else
      RemoveEdgeFromUndirected(deleteEdgeNode);



   // Step 2: Remove deleteEdgeNode from list of all edges 
    
   if (eSize == 1)
      eHead = NULL;
   else  // else there is more than one edge in the edge list
   {
      deleteEdgeNode->nextEdge->prevEdge = deleteEdgeNode->prevEdge;
      deleteEdgeNode->prevEdge->nextEdge = deleteEdgeNode->nextEdge;
    
      // if the first edge in the list is being deleted, point the
      //   list pointer (eHead) to the next edge instead
      if (eHead == deleteEdgeNode)
         eHead = deleteEdgeNode->nextEdge;
   }

   delete deleteEdgeNode;
   eSize--;
}



// ReverseEdge
//    - parameters : revEdge - edge to reverse
//    - reverse revEdge (i.e. makes its former source endpoint
//       its target endpoint and vice-versa)
void Graph::ReverseEdge(Edge revEdge)
{
   // Extract EdgeNode pointer from edge
   EdgeNode* edgeToReverse = revEdge.edgeNodePtr;

   VertexNode* tempVert;
   EdgeNode* tempEdge;

   if (isDirected)
   {
      // if this is the last departing edge, then there are now none
      if (edgeToReverse->source->numDepartEdges == 1)
         edgeToReverse->source->departingEdges = NULL;
      // otherwise, if this is the first of many departing edges,
      //   the next one is now first
      else if (edgeToReverse->source->departingEdges == edgeToReverse)
         edgeToReverse->source->departingEdges =
                                edgeToReverse->nextSourceEdge;
      // otherwise, nothing special about this edge as far as its
      //   source vertex is concerned

      // extract from doubly, circularly linked departing edge list
      //    of source
      edgeToReverse->prevSourceEdge->nextSourceEdge =
                                edgeToReverse->nextSourceEdge;
      edgeToReverse->nextSourceEdge->prevSourceEdge =
                                edgeToReverse->prevSourceEdge;
      (edgeToReverse->source->numDepartEdges)--;



      // if this is the last entering edge, then there are now none
      if (edgeToReverse->target->numEnterEdges == 1)
         edgeToReverse->target->enteringEdges = NULL;
      // otherwise, if this is the first of many entering edges,
      //   the next one is now first
      if (edgeToReverse->target->enteringEdges == edgeToReverse)
         edgeToReverse->target->enteringEdges =
                                edgeToReverse->nextTargetEdge;
      // otherwise, nothing special about this edge as far as its
      //   target vertex is concerned

      // extract from doubly, circularly linked entering edge list
      //    of target
      edgeToReverse->prevTargetEdge->nextTargetEdge =
                                edgeToReverse->nextTargetEdge;
      edgeToReverse->nextTargetEdge->prevTargetEdge =
                                edgeToReverse->prevTargetEdge;
      (edgeToReverse->target->numEnterEdges)--;

   

      // reverse source and target
      tempVert = edgeToReverse->source;
      edgeToReverse->source = edgeToReverse->target;
      edgeToReverse->target = tempVert;


      // insert into departing edge list of new source
      if (edgeToReverse->source->departingEdges == NULL)
      {
         edgeToReverse->source->departingEdges = edgeToReverse;
         edgeToReverse->nextSourceEdge = edgeToReverse;
         edgeToReverse->prevSourceEdge = edgeToReverse;
      }
      else
      {
         edgeToReverse->prevSourceEdge =
                edgeToReverse->source->departingEdges->prevSourceEdge;
         edgeToReverse->nextSourceEdge =
                edgeToReverse->source->departingEdges;
         edgeToReverse->source->departingEdges->prevSourceEdge->nextSourceEdge =
                edgeToReverse;
         edgeToReverse->source->departingEdges->prevSourceEdge = edgeToReverse;
      }
      (edgeToReverse->source->numDepartEdges)++;


      // insert into entering edge list of new target
      if (edgeToReverse->target->enteringEdges == NULL)
      {
         edgeToReverse->target->enteringEdges = edgeToReverse;
         edgeToReverse->nextTargetEdge = edgeToReverse;
         edgeToReverse->prevTargetEdge = edgeToReverse;
      }
      else
      {
         edgeToReverse->prevTargetEdge =
                edgeToReverse->target->enteringEdges->prevTargetEdge;
         edgeToReverse->nextTargetEdge =
                edgeToReverse->target->enteringEdges;
         edgeToReverse->target->enteringEdges->prevTargetEdge->nextTargetEdge =
                edgeToReverse;
         edgeToReverse->target->enteringEdges->prevTargetEdge = edgeToReverse;
      }
      (edgeToReverse->target->numEnterEdges)++;
   }
}






// ******************* Graph structure information ******************


//      ---------- Graph information

// NumGraphVertices
//    - return value : integer quantity
//    - returns the number of vertices in the graph
int Graph::NumGraphVertices()
{
   return vSize; 
}


// NumGraphEdges
//    - return value : integer quantity
//    - returns the number of edges in the graph
int Graph::NumGraphEdges()
{ 
   return eSize; 
}



//      ---------- Vertex information

// NumDepartEdges
//    - parameters : queryVert - vertex which we want information about
//    - return value : integer quantity
//    - returns the number of edges departing from Vertex queryVert
int Graph::NumDepartEdges(Vertex queryVert)
{
   return queryVert.VPtr()->numDepartEdges; 
}



// NumEnterEdges
//    - parameters : queryVert - vertex which we want information about
//    - return value : integer quantity
//    - returns the number of edges entering Vertex queryVert
int Graph::NumEnterEdges(Vertex queryVert)
{
   return queryVert.VPtr()->numEnterEdges;
}



// NumTotalEdges
//    - parameters : queryVert - vertex which we want information about
//    - return value : integer quantity
//    - returns the number of edges departing or entering Vertex queryVert
int Graph::NumTotalEdges(Vertex queryVert)
{
   return (queryVert.VPtr()->numEnterEdges + 
	  queryVert.VPtr()->numDepartEdges); 
}




//      ---------- Edge information

// Source
//    - parameters : queryEdge - edge which we want information about
//    - return value : a vertex of the graph
//    - returns source vertex of this edge (i.e. the vertex it departs)
Vertex Graph::Source(Edge queryEdge)
{
   return Vertex(queryEdge.EPtr()->source); 
}


// Target
//    - parameters : queryEdge - edge which we want information about
//    - return value : a vertex of the graph
//    - returns target vertex of this edge (i.e. the vertex it enters)
Vertex Graph::Target(Edge queryEdge)
{
   return Vertex(queryEdge.EPtr()->target); 
}


// OtherEndpoint
//    - parameters : queryEdge - edge which we want information about
//                 : endpointOne - one of the two endpoints of the edge
//    - return value : a vertex of the graph
//    - if endpointOne is the source vertex of this edge, the target 
//        vertex of this edge will be returned. If endpointOne is 
//        instead the target vertex of this edge, the source vertex 
//        will be returned. If endpointOne is not an endpoint of this
//        edge, the nil vertex will be returned
Vertex Graph::OtherEndpoint(Edge queryEdge, Vertex endpointOne)
{
   if (queryEdge.EPtr()->source == endpointOne.VPtr())
      return Vertex(queryEdge.EPtr()->target); 
   else if (queryEdge.EPtr()->target == endpointOne.VPtr())
      return Vertex(queryEdge.EPtr()->source); 
   else 
      return Vertex(); 
}





// ********************** Graph traversal *******************


//      ---------- Vertex traversal 

// FirstVertex
//    - return type : a vertex of the graph
//    - returns the "first" vertex in the abstract set of
//        vertices of the graph. If graph is empty, returns
//        the nil vertex.
Vertex Graph::FirstVertex()
{
   if (vHead == NULL)
      return Vertex(); 
   else
      return Vertex(vHead); 
}



// LastVertex
//    - return type : a vertex of the graph
//    - returns the "last" vertex in the abstract set of
//        vertices of the graph. If graph is empty, returns
//        the nil vertex.
Vertex Graph::LastVertex()
{
   if (vHead == NULL)
      return Vertex(); 
   else
      return Vertex(vHead->prevVertex); 
}



// NextVertex
//    - parameters : currentVert - a vertex of the graph
//    - return type : a vertex of the graph
//    - returns the vertex "after" currentVert in the abstract set 
//        of vertices of the graph. If currentVert is the last vertex 
//        in the vertex set, returns the nil vertex.
Vertex Graph::NextVertex(Vertex currentVert)
{
   if (currentVert.VPtr()->nextVertex == vHead)
      return Vertex(); 
   else
      return Vertex(currentVert.VPtr()->nextVertex); 
}



// PrevVertex
//    - parameters : currentVert - a vertex of the graph
//    - return type : a vertex of the graph
//    - returns the vertex "before" currentVert in the abstract set 
//        of vertices of the graph. If currentVert is the first 
//        vertex in the vertex set, returns the  nil vertex.
Vertex Graph::PrevVertex(Vertex currentVert)
{
   if (currentVert.VPtr() == vHead)
      return Vertex(); 
   else
      return Vertex(currentVert.VPtr()->prevVertex); 
}




//      ---------- Edge traversal 

// FirstEdge
//    - return type : an edge of the graph
//    - returns the "first" edge in the abstract set of
//        edges of the graph. If graph has no edges, returns
//        the nil edge.
Edge Graph::FirstEdge()
{
   if (eHead == NULL)
      return Edge(); 
   else
      return Edge(eHead); 
}


// LastEdge
//    - return type : an edge of the graph
//    - returns the "last" edge in the abstract set of
//        edges of the graph. If graph has no edges, returns
//        the nil edge.
Edge Graph::LastEdge()
{
   if (eHead == NULL)
      return Edge(); 
   else
      return Edge(eHead->prevEdge); 
}


// NextEdge
//    - parameters : currentEdge - an edge of the graph
//    - return type : an edge of the graph
//    - returns the edge "after" currentEdge in the abstract
//        set of edges of the graph. If currentEdge is the last
//        edge in the edge set, returns the nil edge
Edge Graph::NextEdge(Edge currentEdge)
{
   if (currentEdge.EPtr()->nextEdge == eHead) 
      return Edge(); 
   else
      return Edge(currentEdge.EPtr()->nextEdge);  
}


// PrevEdge
//    - parameters : currentEdge - an edge of the graph
//    - return type : an edge of the graph
//    - returns the edge "before" currentEdge in the abstract 
//        set of edges of the graph. If currentEdge is the first 
//        edge in the edge set, returns the nil edge
Edge Graph::PrevEdge(Edge currentEdge)
{
   if (currentEdge.EPtr() == eHead)
      return Edge(); 
   else
      return Edge(currentEdge.EPtr()->prevEdge);  
}



//      ---------- Vertex departing edge traversal
//                     --- meant for directed graphs

// FirstDepartEdge
//    - parameters : departFromVert - vertex we are inspecting
//    - return value : an edge of the graph
//    - returns the "first" edge in the abstract set
//        of all edges departing from the vertex departFromVert. 
//        If departFromVert has no departing edges, returns
//        the nil edge.
Edge Graph::FirstDepartEdge(Vertex departFromVert)
{
   if (departFromVert.VPtr()->departingEdges == NULL)
      return Edge(); 
   else
      return Edge(departFromVert.VPtr()->departingEdges); 
}


// LastDepartEdge
//    - parameters : departFromVert - vertex we are inspecting
//    - return value : an edge of the graph
//    - returns the "last" edge in the abstract set
//        of all edges departing from the vertex departFromVert. 
//        If departFromVert has no departing edges, returns
//        the nil edge.
Edge Graph::LastDepartEdge(Vertex departFromVert)
{
   if (departFromVert.VPtr()->departingEdges == NULL)
      return Edge(); 
   else 
      return Edge(departFromVert.VPtr()->departingEdges->prevSourceEdge); 
}



// NextDepartEdge
//    - parameters : currentEdge - an edge of the graph
//    - return value : an edge of the graph
//    - returns the edge "after" currentEdge in the abstract
//        set of all edges which depart from the same source 
//        vertex as currentEdge. (The source vertex can be found
//        from the edge, which is why we don't need to pass in
//        the source vertex as a parameter.) If this is the last
//        edge in the set described above, returns the nil edge. 
Edge Graph::NextDepartEdge(Edge currentEdge)
{
   if (currentEdge.EPtr()->nextSourceEdge == 
		currentEdge.EPtr()->source->departingEdges)
      return Edge(); 
   else
      return Edge(currentEdge.EPtr()->nextSourceEdge);  
}



// PrevDepartEdge
//    - parameters : currentEdge - an edge of the graph
//    - return value : an edge of the graph
//    - returns the edge "before" currentEdge in the abstract
//        set of all edges which depart from the same source 
//        vertex as currentEdge. (The source vertex can be found
//        from the edge, which is why we don't need to pass in
//        the source vertex as a parameter.) If this is the first 
//        edge in the set described above, returns the nil edge. 
Edge Graph::PrevDepartEdge(Edge currentEdge)
{
   if (currentEdge.EPtr() == currentEdge.EPtr()->source->departingEdges)
      return Edge(); 
   else
      return Edge(currentEdge.EPtr()->prevSourceEdge);  
}



//      ---------- Vertex entering edge traversal
//                     --- meant for directed graphs

// FirstEnterEdge
//    - parameters : enterIntoVert - vertex we are inspecting
//    - return value : an edge of the graph
//    - returns the "first" edge in the abstract set
//        of all edges entering the vertex enterIntoVert. 
//        If enterIntoVert has no entering edges, returns
//        the nil edge.
Edge Graph::FirstEnterEdge(Vertex enterIntoVert)
{
   if ((enterIntoVert.VPtr()->enteringEdges == NULL) || (!isDirected))
      return Edge(); 
   else
      return Edge(enterIntoVert.VPtr()->enteringEdges); 
}


// LastEnterEdge
//    - parameters : enterIntoVert - vertex we are inspecting
//    - return value : an edge of the graph
//    - returns the "last" edge in the abstract set
//        of all edges entering the vertex enterIntoVert. 
//        If enterIntoVert has no entering edges, returns
//        the nil edge.
Edge Graph::LastEnterEdge(Vertex enterIntoVert)
{
   if ((enterIntoVert.VPtr()->enteringEdges == NULL) || (!isDirected))
      return Edge(); 
   else 
      return Edge(enterIntoVert.VPtr()->enteringEdges->prevTargetEdge); 
}


// NextEnterEdge
//    - parameters : currentEdge - an edge of the graph
//    - return value : an edge of the graph
//    - returns the edge "after" currentEdge in the abstract
//        set of all edges which enter same target 
//        vertex as currentEdge. (The target vertex can be found
//        from the edge, which is why we don't need to pass in
//        the target vertex as a parameter.) If this is the last
//        edge in the set described above, returns the nil edge.
Edge Graph::NextEnterEdge(Edge currentEdge)
{
   if ((currentEdge.EPtr()->nextTargetEdge == 
		currentEdge.EPtr()->target->enteringEdges) || (!isDirected))
      return Edge(); 
   else
      return Edge(currentEdge.EPtr()->nextTargetEdge); 
}



// PrevEnterEdge
//    - parameters : currentEdge - an edge of the graph
//    - return value : an edge of the graph
//    - returns the edge "before" currentEdge in the abstract
//        set of all edges which enter the same target 
//        vertex as currentEdge. (The target vertex can be found
//        from the edge, which is why we don't need to pass in
//        the target vertex as a parameter.) If this is the first 
//        edge in the set described above, returns the nil edge. 
Edge Graph::PrevEnterEdge(Edge currentEdge)
{
   if ((currentEdge.EPtr() == 
              currentEdge.EPtr()->target->enteringEdges) || (!isDirected))
      return Edge(); 
   else 
      return Edge(currentEdge.EPtr()->prevTargetEdge); 
}



//      ---------- Vertex adjacent edge traversal 
//                      --- meant for undirected graphs

// FirstAdjacentEdge
//    - parameters : endpointVert - vertex we are inspecting
//    - return value : an edge of the graph
//    - returns the "first" edge in the abstract set
//        of all edges which have endpointVert as an endpoint 
//        If endpointVert is not an endpoint of any edge, returns
//        the nil edge.
Edge Graph::FirstAdjacentEdge(Vertex endpointVert)
{
   if (endpointVert.VPtr()->departingEdges == NULL)
      return Edge(); 
   else
      return Edge(endpointVert.VPtr()->departingEdges); 
}




// LastAdjacentEdge
//    - parameters : endpointVert - vertex we are inspecting
//    - return value : an edge of the graph
//    - returns the "last" edge in the abstract set
//        of all edges which have endpointVert as an endpoint 
//        If endpointVert is not an endpoint of any edge, returns
//        the nil edge.
Edge Graph::LastAdjacentEdge(Vertex endpointVert)
{
   VertexNode* vert1 = endpointVert.VPtr(); 
   if (vert1->departingEdges == NULL)
      return Edge(); 
   else if (vert1->departingEdges->source == vert1)
      return Edge(vert1->departingEdges->prevSourceEdge); 
   else   // vert1->departingEdges->target == vert1
      return Edge(vert1->departingEdges->prevTargetEdge); 
}
      


// NextAdjacentEdge
//    - parameters : currentEdge - an edge in the graph
//                 : endpointVert - an endpoint of currentEdge 
//    - return value : an edge of the graph
//    - returns the edge "after" currentEdge in the abstract 
//        set of all edges that have the vertex endpointVert 
//        as an endpoint. If this is the last edge in the set 
//        described above, returns the nil edge.
Edge Graph::NextAdjacentEdge(Edge currentEdge, Vertex endpointVert)
{
   VertexNode* vert1 = endpointVert.VPtr(); 
   EdgeNode* edge1 = currentEdge.EPtr(); 
   EdgeNode* possibleNextEdge; 
   
   if (edge1->source == vert1)
      possibleNextEdge = edge1->nextSourceEdge; 
   else if (edge1->target == vert1)
      possibleNextEdge = edge1->nextTargetEdge; 
   else // vertex not endpoint of edge
   {
      cout << "ERROR!!!! " << endl; 
      return Edge(); 
   }

   if (possibleNextEdge == vert1->departingEdges)
      return Edge(); 
   else
      return Edge(possibleNextEdge); 
}


// PrevAdjacentEdge
//    - parameters : currentEdge - an edge in the graph
//                 : endpointVert - an endpoint of currentEdge 
//    - return value : an edge of the graph
//    - returns the edge "before" currentEdge in the abstract 
//        set of all edges that have the vertex endpointVert 
//        as an endpoint. If this is the first edge in the set 
//        described above, returns the nil edge.
Edge Graph::PrevAdjacentEdge(Edge currentEdge, Vertex endpointVert)
{
   VertexNode* vert1 = endpointVert.VPtr(); 
   EdgeNode* edge1 = currentEdge.EPtr(); 
   EdgeNode* possiblePrevEdge; 
   
   if (edge1->source == vert1)
      possiblePrevEdge = edge1->prevSourceEdge; 
   else if (edge1->target == vert1)
      possiblePrevEdge = edge1->prevTargetEdge; 
   else // vertex not endpoint of edge
   {
      cout << "ERROR!!!! " << endl; 
      return Edge(); 
   }

   if (edge1 == vert1->departingEdges)
      return Edge(); 
   else
      return Edge(possiblePrevEdge); 
}


// *************** Mark processing *********************


//      ---------- Vertex marks

// GetVertexMark
//    - parameters : markVert - vertex with mark to read 
//    - return value : integer flag
//    - returns the mark value of the vertex markVert
int Graph::GetVertexMark(Vertex markVert)
{
   return (markVert.VPtr()->vertexMark);
}



// SetVertexMark
//    - parameters : markVert - vertex to be marked 
//                 : markToAssign - mark to assign to vertex
//    - sets the mark of vertex markVert to be equal to markToAssign
void Graph::SetVertexMark(Vertex markVert, int markToAssign)
{
   markVert.VPtr()->vertexMark = markToAssign; 
}


// ClearVertexMarks
//    - sets all vertex mark fields to 0
void Graph::ClearVertexMarks()
{
   VertexNode* nodePtr = vHead;
   if (nodePtr != NULL)   // if we have some vertices
   {
      while (nodePtr->nextVertex != vHead)
      {
         nodePtr->vertexMark = 0;
         nodePtr = nodePtr->nextVertex;
      }
      nodePtr->vertexMark = 0;
   }
}



//      ---------- Edge Marks

// GetEdgeMark
//    - parameters : markEdge - edge with mark to read
//    - return value : integer flag
//    - returns the mark value of the edge markEdge
int Graph::GetEdgeMark(Edge markEdge)
{
   return (markEdge.EPtr()->edgeMark);
}



// SetEdgeMark
//    - parameters : markEdge - edge to be marked
//                 : markToAssign - mark to assign to edge
//    - sets the mark of edge markEdge to be equal to markToAssign
void Graph::SetEdgeMark(Edge markEdge, int markToAssign)
{
   markEdge.EPtr()->edgeMark = markToAssign; 
}



// ClearEdgeMarks
//    - sets all edge mark fields to 0
void Graph::ClearEdgeMarks()
{
   EdgeNode* nodePtr = eHead;
   if (nodePtr != NULL)   // if we have some edges 
   {
      while (nodePtr->nextEdge != eHead)
      {
         nodePtr->edgeMark = 0;
         nodePtr = nodePtr->nextEdge;
      }
      nodePtr->edgeMark = 0;
   }
}



// ****************** Queries ***********************

// IsEmpty
//    - return value : boolean integer
//    - returns 1 if the graph has no vertices or edges, and
int Graph::IsEmpty()
{
   return ((vHead == NULL) && (eHead == NULL));
}



// IsDirected
//    - return value : boolean integer
//    - returns 1 if the graph is directed, and 0 otherwis
int Graph::IsDirected()
{
   return isDirected;
}



// IsUndirected
//    - return value : boolean integer
//    - returns 1 if the graph is undirected, and 0 otherwise
int Graph::IsUndirected()
{
   return !isDirected; 
}



// IsNil
//    - parameters : queryVert
//    - return value : boolean integer
//    - returns 1 if queryVert is the nil vertex, and 0 otherwise
int Graph::IsNil(Vertex queryVert)
{
   return (queryVert.VPtr() == NULL);
}



// IsNil
//    - parameters : queryEdge
//    - return value : boolean integer
//    - returns 1 if queryEdge is the nil Edge, and 0 otherwise
int Graph::IsNil(Edge queryEdge)
{
   return (queryEdge.EPtr() == NULL); 
}




// **************** Protected Functions ***********************



// VertexKey
//    - parameters : infoVertex - the vertex whose key we want
//    - return value : integer which is a vertex key
//    - returns the vertex-to-information map key stored inside
int Graph::VertexKey(Vertex infoVertex)
{
   return infoVertex.VPtr()->vertexKey;
}


// EdgeKey
//    - parameters : infoEdge - the edge whose key we want
//    - return value : integer which is an edge key
//    - returns the edge-to-information map key stored inside
//        the edge
int Graph::EdgeKey(Edge infoEdge)
{
   return infoEdge.EPtr()->edgeKey;
}



// ****************** Copying helper functions ******************


// Copy
//    - parameters : origVal - previously allocated Graph object
//    - sets this object to be a copy of origVal; helper function
//         for the copy constructor and assignment operator
void Graph::Copy(const Graph& origVal)
{
   // arrays to map index keys to pointers to the VertexNode
   //   and EdgeNode objects in the new graph. This will make  
   //   setting the pointer fields of those new graph nodes much
   //   easier.  
   Array<VertexNode*> vArray(1, origVal.vertexKeyCounter);
 
   int i;
   for (i = 1; i<=origVal.vertexKeyCounter; i++)
      vArray[i] = NULL; 
   Array<EdgeNode*> eArray(1, origVal.edgeKeyCounter);
   for (i = 1; i<=origVal.edgeKeyCounter; i++)
      eArray[i] = NULL; 

   // copy the vertex list 
   CopyVertexNodes(origVal, vArray); 
   // copy the edge list
   CopyEdgeNodes(origVal, eArray);

   // correctly set the departing/entering edge list pointers in 
   //    the new graph's vertices 
   CopyVertexConnections(origVal, eArray); 
   // correctly set the source/target vertex pointers and the 
   //   source/target edge list pointers in the new graph's edges 
   CopyEdgeConnections(origVal, vArray, eArray); 
   
   isDirected = origVal.isDirected;
}


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
void Graph::CopyVertexNodes(const Graph& origVal, 
				Array<VertexNode*>& vArray)
{
   int stillVerticesToCopy = 1; 

   vSize = origVal.vSize; 
   if (vSize == 0)
      vHead = NULL; 
   else
   {
      vHead = new VertexNode(*(origVal.vHead)); 
      vArray[vHead->vertexKey] = vHead; 
      
      VertexNode *oldTrav = origVal.vHead; 
      VertexNode *newTrav = vHead; 
      if (oldTrav->nextVertex == origVal.vHead)
         stillVerticesToCopy = 0; 
      while (stillVerticesToCopy)
      {
         oldTrav = oldTrav->nextVertex; 
         newTrav->nextVertex = new VertexNode(*oldTrav); 
         newTrav->nextVertex->prevVertex = newTrav; 
         newTrav = newTrav->nextVertex; 
         newTrav->nextVertex = vHead; 
         vHead->prevVertex = newTrav;
         
         vArray[newTrav->vertexKey] = newTrav; 
         if (oldTrav->nextVertex == origVal.vHead)
            stillVerticesToCopy = 0; 
      }
      vertexKeyCounter = origVal.vertexKeyCounter;
   }
}


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
void Graph::CopyEdgeNodes(const Graph& origVal, 
                                Array<EdgeNode*>& eArray)
{
   int stillEdgesToCopy = 1; 

   eSize = origVal.eSize; 
   if (eSize == 0)
      eHead = NULL; 
   else
   {
      eHead = new EdgeNode(*(origVal.eHead)); 
      eArray[eHead->edgeKey] = eHead; 
      
      EdgeNode *oldTrav = origVal.eHead; 
      EdgeNode *newTrav = eHead; 
      if (oldTrav->nextEdge == origVal.eHead)
         stillEdgesToCopy = 0; 
      while (stillEdgesToCopy)
      {
         oldTrav = oldTrav->nextEdge; 
         newTrav->nextEdge = new EdgeNode(*oldTrav); 
         newTrav->nextEdge->prevEdge = newTrav; 
         newTrav = newTrav->nextEdge; 
         newTrav->nextEdge = eHead; 
         eHead->prevEdge = newTrav;
         
         eArray[newTrav->edgeKey] = newTrav; 
         if (oldTrav->nextEdge == origVal.eHead)
            stillEdgesToCopy = 0; 
      }
      edgeKeyCounter = origVal.edgeKeyCounter;
   }
}


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
void Graph::CopyVertexConnections(const Graph& origVal, 
			            const Array<EdgeNode*>& eArray)
{
   int stillVerticesToSet = 1; 
   VertexNode *oldTrav = origVal.vHead;
   VertexNode *newTrav = vHead; 
   if (newTrav == NULL)
      stillVerticesToSet = 0; 
   while (stillVerticesToSet)
   {
      if (oldTrav->departingEdges == NULL)
         newTrav->departingEdges = NULL; 
      else
         newTrav->departingEdges = eArray[oldTrav->departingEdges->edgeKey]; 
      if (oldTrav->enteringEdges == NULL)
         newTrav->enteringEdges = NULL; 
      else
         newTrav->enteringEdges = eArray[oldTrav->enteringEdges->edgeKey];
      newTrav = newTrav->nextVertex; 
      oldTrav = oldTrav->nextVertex; 
      if (newTrav==vHead)
         stillVerticesToSet = 0; 
   }
}



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
void Graph::CopyEdgeConnections(const Graph& origVal, 
			const Array<VertexNode*>& vArray, 
			const Array<EdgeNode*>& eArray)
{
   int stillEdgesToSet = 1; 
   EdgeNode *oldTrav = origVal.eHead; 
   EdgeNode *newTrav = eHead;
   if (newTrav == NULL)
      stillEdgesToSet = 0; 
   while (stillEdgesToSet)
   {
      newTrav->source = vArray[oldTrav->source->vertexKey];
      newTrav->target = vArray[oldTrav->target->vertexKey];
      newTrav->prevSourceEdge = eArray[oldTrav->prevSourceEdge->edgeKey];
      newTrav->nextSourceEdge = eArray[oldTrav->nextSourceEdge->edgeKey];
      newTrav->prevTargetEdge = eArray[oldTrav->prevTargetEdge->edgeKey];
      newTrav->nextTargetEdge = eArray[oldTrav->nextTargetEdge->edgeKey];
   
      newTrav = newTrav->nextEdge;
      oldTrav = oldTrav->nextEdge;

      if (newTrav == eHead)
         stillEdgesToSet = 0;  
   }
}



// ************** Vertex addition helper functions ***************


// InsertEdgeIntoDirected
//    - parameters : insEdge - pointer to EdgeNode being inserted  
//                               into graph
//    - inserts insEdge into the departing edge list of its 
//         source vertex, and into the entering edge list of 
//         its target vertex 
void Graph::InsertEdgeIntoDirected(EdgeNode* insEdge)
{
   VertexNode* source = insEdge->source;
   VertexNode* target = insEdge->target;


   // Step 1 : Insert insEdge into source's departing edges list

   // if there are no entering edges, new edge is the only edge
   if (source->departingEdges == NULL)
      source->departingEdges = insEdge;
   else  // else insert new edge into doubly and circularly linked list
   {
      insEdge->prevSourceEdge = source->departingEdges->prevSourceEdge;
      insEdge->nextSourceEdge = source->departingEdges;
      source->departingEdges->prevSourceEdge->nextSourceEdge = insEdge;
      source->departingEdges->prevSourceEdge = insEdge;
   }
   (source->numDepartEdges)++;



   // Step 2 : Insert insEdge into target's entering edges list

   // if there are no entering edges, new edge is the only edge
   if (target->enteringEdges == NULL)
      target->enteringEdges = insEdge;
   else  // else insert new edge into doubly and circularly linked list 
   {
      insEdge->prevTargetEdge = target->enteringEdges->prevTargetEdge;
      insEdge->nextTargetEdge = target->enteringEdges;
      target->enteringEdges->prevTargetEdge->nextTargetEdge = insEdge;
      target->enteringEdges->prevTargetEdge = insEdge;
   }
   (target->numEnterEdges)++;
}




// InsertEdgeIntoUndirected
//    - parameters : insEdge - pointer to EdgeNode being inserted 
//                                into graph
//    - inserts insEdge into the edge lists of both of its endpoints 
void Graph::InsertEdgeIntoUndirected(EdgeNode* insEdge)
{
   // In an undirected graph, all the edges are listed in a vertex's
   //  "departing edges" list and no edges are listed in a vertex's
   //  "entering edges" list; however, the edge nodes themselves still
   //  point to two endpoints, so one is named "source" and one is named
   //  "target", though from the abstract point of view, the edge's two
   //  endpoints are just "endpoint1" and "endpoint2"
   VertexNode* endpoint1 = insEdge->source;
   VertexNode* endpoint2 = insEdge->target;


   // Step 1 : insert insEdge into endpoint1's departing edges list

   // if there are no adjacent edges, new edge is the only edge 
   if (endpoint1->departingEdges == NULL)
      endpoint1->departingEdges = insEdge;
   else  // else insert into doubly and circularly linked list
   {
      // endpoint1 is the "source" vertex for this edge, simply because
      // it happened to be listed first in the "InsertEdge" function
      // call. But, conceptually, there *is* no "source vertex", there is
      // just an "endpoint1" --  because this is an undirected edge.

      // **** Pointer Assignment #1
      insEdge->nextSourceEdge = endpoint1->departingEdges;

      // Since this graph is undirected, all of a vertex's edges are
      // on its "departing" edges list. Therefore, all the edges which 
      // had that given vertex as its "first" endpoint, AND all the edges 
      // which had that given vertex as its "second" endpoint, are ALL on 
      // that vertex's departing edge list. This means that some edges on a 
      // vertex's departing edge list (again, only for undirected graphs) 
      // point to that vertex with their "source" pointers, and other edges 
      // on that vertex's departing edge list point to that vertex with 
      // their "target" pointers.

      // If the first node in the current list sees endpoint1 as its
      // "first" or "source" endpoint, then it will be connected to the 
      // last vertex in the list with its source list pointers and so it 
      // is those source list pointers we must read and assign to.
      if (endpoint1->departingEdges->source == endpoint1)
      {
         // **** Pointer Assignments #2 and #3 -- possibility 1
         insEdge->prevSourceEdge = endpoint1->departingEdges->prevSourceEdge;
         endpoint1->departingEdges->prevSourceEdge = insEdge;
      }
      // Otherwise, the first node in the current list sees endpoint1
      //  as its "second" or "target" endpoint and it will be connected
      //  to its list neighbors via its target list pointers
      else    // then endpoint1->departingEdges->target == endpoint1 
      {
         // **** Pointer Assignments #2 and #3 - possibility 2
         insEdge->prevSourceEdge = endpoint1->departingEdges->prevTargetEdge;
         endpoint1->departingEdges->prevTargetEdge = insEdge;
      }

      // Likewise, we don't know whether the *last* edge in endpoint1's
      //  edge list thinks of endpoint1 as its "source" or "target" 
      //  endpoint 
      if (insEdge->prevSourceEdge->source == endpoint1 )
         // **** Pointer Assignment #4 - possibility 1
         insEdge->prevSourceEdge->nextSourceEdge = insEdge;
      else    // insEdge->prevSourceEdge->target == endpoint1
         // **** Pointer Assignment #4 - possibility 2
         insEdge->prevSourceEdge->nextTargetEdge = insEdge;
   }
   (endpoint1->numDepartEdges)++;


   // Step 2 : insert insEdge into endpoint2's departing edges list

   // if there are no adjacent edges, then new edge is the only one 
   if (endpoint2->departingEdges == NULL)
      endpoint2->departingEdges = insEdge;
   else // insert into doubly and circularly linked list
   {

      // **** Pointer Assignment #1
      insEdge->nextTargetEdge = endpoint2->departingEdges;


      // If the first node in the current list sees endpoint2 as its
      // "first" or "source" endpoint, then it will be connected to the
      // last vertex in the list with its source list pointers and so it
      // is those source list pointers we must read and assign to.
      if (endpoint2->departingEdges->source == endpoint2)
      {
         // **** Pointer Assignments #2 and #3 -- possibility 1
         insEdge->prevTargetEdge = endpoint2->departingEdges->prevSourceEdge;
         endpoint2->departingEdges->prevSourceEdge = insEdge;
      }
      // Otherwise, the first node in the current list sees endpoint2
      //  as its "second" or "target" endpoint and it will be connected
      //  to its list neighbors via its target list pointers
      else      // then endpoint2->departingEdges->target == endpoint2
      {
         // **** Pointer Assignments #2 and #3 - possibility 2
         insEdge->prevTargetEdge = endpoint2->departingEdges->prevTargetEdge;
         endpoint2->departingEdges->prevTargetEdge = insEdge;
      }

      // Likewise, we don't know whether the *last* edge in endpoint2's
      //  edge list thinks of endpoint2 as its "source" or "target"
      //  endpoint
      if (insEdge->prevTargetEdge->source == endpoint2)
         // **** Pointer Assignment #4 - possibility 1
         insEdge->prevTargetEdge->nextSourceEdge = insEdge;
      else    // insEdge->prevSourceEdge->target == endpoint2
         // **** Pointer Assignment #4 - possibility 2
         insEdge->prevTargetEdge->nextTargetEdge = insEdge;
   }
   (endpoint2->numDepartEdges)++;
}




// RemoveEdgeFromDirected
//    - parameters : deleteEdgeNode - pointer to edge node that
//                      is to be deleted
//    - extracts deleteEdgeNode from the list of edges departing 
//         from its source vertex, and also from the list of edges
//         entering its target vertex
void Graph::RemoveEdgeFromDirected(EdgeNode* deleteEdgeNode)
{
   // Step 1: Remove deleteEdgeNode from source's departing edges list

   // if this is the last edge left in the list of its source vertex 
   if (deleteEdgeNode == deleteEdgeNode->nextSourceEdge)
      deleteEdgeNode->source->departingEdges = NULL;
   else  // else there is more than one vertex in this edge list
   {
      deleteEdgeNode->nextSourceEdge->prevSourceEdge = 
			         deleteEdgeNode->prevSourceEdge;
      deleteEdgeNode->prevSourceEdge->nextSourceEdge = 
                                 deleteEdgeNode->nextSourceEdge;
  
      // if the source vertex's "departing edges" pointer points
      //   to this edge, point it to the next edge instead
      if (deleteEdgeNode->source->departingEdges == deleteEdgeNode)
         deleteEdgeNode->source->departingEdges = 
                                        deleteEdgeNode->nextSourceEdge;
   }
   (deleteEdgeNode->source->numDepartEdges)--; 


   // Step 2: Remove deleteEdgeNode from target's entering edges list

   // if this is the last edge left in the list of its target vertex
   if (deleteEdgeNode == deleteEdgeNode->nextTargetEdge)
      deleteEdgeNode->target->enteringEdges = NULL;
   else  // else there is more than one vertex in this edge list
   {
      deleteEdgeNode->nextTargetEdge->prevTargetEdge = 
				     deleteEdgeNode->prevTargetEdge;
      deleteEdgeNode->prevTargetEdge->nextTargetEdge = 
				     deleteEdgeNode->nextTargetEdge;
  
      // if the target vertex's "entering edges" pointer points
      //   to this edge, point it to the next edge instead 
      if (deleteEdgeNode->target->enteringEdges == deleteEdgeNode)
         deleteEdgeNode->target->enteringEdges = 
                                      deleteEdgeNode->nextTargetEdge;
   }
   (deleteEdgeNode->target->numEnterEdges)--;
}




// RemoveEdgeFromUndirected
//    - parameters : deleteEdgeNode - pointer to edge node that
//                      is to be deleted
//    - extracts deleteEdgeNode from the edge list of deleteEdgeNode's
//         first endpoint, and also extracts it from the edge list of 
//         its second endpoint
void Graph::RemoveEdgeFromUndirected(EdgeNode* deleteEdgeNode)
{
   // In an undirected graph, the "source" and "target" vertices
   //   are really just "endpoint1" and "endpoint2" since the edge
   //   has no direction
   VertexNode* endpoint1 = deleteEdgeNode->source;
   VertexNode* endpoint2 = deleteEdgeNode->target;


   // Step 1: Remove deleteEdgeNode from endpoint1's edge list

   // if this is the last edge left in the list of endpoint1 
   if (deleteEdgeNode == deleteEdgeNode->nextSourceEdge)
      endpoint1->departingEdges = NULL;
   else  // else there is more than one vertex in this edge list
   {
      // the edge after this one in endpoint1's edge list might see 
      //    endpoint1 as its "source" OR as its "target" 
      if (deleteEdgeNode->nextSourceEdge->source == endpoint1)
         deleteEdgeNode->nextSourceEdge->prevSourceEdge = 
                                 deleteEdgeNode->prevSourceEdge;
      else  // deleteEdgeNode->nextSourceEdge->target == endpoint1
         deleteEdgeNode->nextSourceEdge->prevTargetEdge = 
				 deleteEdgeNode->prevSourceEdge;

      // the edge before this one in endpoint1's edge list might see 
      //    endpoint1 as its "source" OR as its "target" 
      if (deleteEdgeNode->prevSourceEdge->source == endpoint1)
         deleteEdgeNode->prevSourceEdge->nextSourceEdge = 
                                 deleteEdgeNode->nextSourceEdge;
      else   // deleteEdgeNode->prevSourceEdge->target == endpoint1
         deleteEdgeNode->prevSourceEdge->nextTargetEdge = 
				 deleteEdgeNode->nextSourceEdge; 
 
 
      // if endpoint1's "departing edges" pointer points
      //   to this edge, point it to the next edge instead
      if (endpoint1->departingEdges == deleteEdgeNode)
         endpoint1->departingEdges = deleteEdgeNode->nextSourceEdge;
   }
   (endpoint1->numDepartEdges)--; 


   // Step 2: Remove deleteEdgeNode from endpoint2's edge list 

   // if this is the last edge left in the list of its target vertex
   if (deleteEdgeNode == deleteEdgeNode->nextTargetEdge)
      deleteEdgeNode->target->enteringEdges = NULL;
   else  // else there is more than one vertex in this edge list
   {
      // the edge after this one in endpoint2's edge list might see 
      //    endpoint2 as its "source" OR as its "target" 
      if (deleteEdgeNode->nextTargetEdge->source == endpoint2)
         deleteEdgeNode->nextTargetEdge->prevSourceEdge =
                                 deleteEdgeNode->prevTargetEdge;
      else  // deleteEdgeNode->nextTargetEdge->target == endpoint2
         deleteEdgeNode->nextTargetEdge->prevTargetEdge = 
                                 deleteEdgeNode->prevTargetEdge;

      // the edge before this one in endpoint2's edge list might see 
      //    endpoint2 as its "source" OR as its "target" 
      if (deleteEdgeNode->prevTargetEdge->source == endpoint2)
         deleteEdgeNode->prevTargetEdge->nextSourceEdge =
                                 deleteEdgeNode->nextTargetEdge;
      else   // deleteEdgeNode->prevTargetEdge->target == endpoint2
         deleteEdgeNode->prevTargetEdge->nextTargetEdge =   
                                 deleteEdgeNode->nextTargetEdge;


      // if endpoint2's "departing edges" pointer points
      //   to this edge, point it to the next edge instead 
      if (endpoint2->enteringEdges == deleteEdgeNode)
         endpoint2->enteringEdges = deleteEdgeNode->nextTargetEdge;
   }
   (endpoint2->numEnterEdges)--;
}



