// *************************************************
// *                                               *
// *  graphalgs.cpp                                *
// *                                               *
// *  Headers for functions that operate publicly  *
// *   on the graph class.                         * 
// *                                               *
// *  Written 10 Nov 1998 by Jason Zych            *
// *    MP9 functions added by Lilian Fernandes    *
// *                                               *
// *************************************************


#include "graphalgs.h"



// Print
//    - parameters : dirGraph - graph to print
//    - prints out graph information
template <class Vtype, class Etype>
void Print(InfoGraph<Vtype, Etype>& dirGraph)
{

   Vertex v1; 
   Edge e1; 
  
   v1 = dirGraph.FirstVertex();
   while (!dirGraph.IsNil(v1)) 
   {
      cout << "Now processing Vertex " << dirGraph.VertexInfo(v1);
      cout << endl << endl;

      // printing departed edges
      e1 = dirGraph.FirstDepartEdge(v1); 
      while (!dirGraph.IsNil(e1))
      {
         cout << "   Departing Edge:" << endl; 
         cout << "      Source: " << dirGraph.VertexInfo(dirGraph.Source(e1));
         cout << endl;
         cout << "      Target: " << dirGraph.VertexInfo(dirGraph.Target(e1));
         cout << endl;
         cout << "      EdgeInfo: " << dirGraph.EdgeInfo(e1) << endl; 
         e1 = dirGraph.NextDepartEdge(e1); 
      }       
      cout << endl; 
    
 
      // printing entering edges
      e1 = dirGraph.FirstEnterEdge(v1); 
      while (!dirGraph.IsNil(e1))
      {
         cout << "   Entering Edge:" << endl;          
         cout << "      Source: " << dirGraph.VertexInfo(dirGraph.Source(e1));
         cout << endl;
         cout << "      Target: " << dirGraph.VertexInfo(dirGraph.Target(e1));
         cout << endl;
         cout << "      EdgeInfo: " << dirGraph.EdgeInfo(e1) << endl; 
         e1 = dirGraph.NextEnterEdge(e1); 
      }
      cout << endl; 
      
      v1 = dirGraph.NextVertex(v1); 
   }

} 


