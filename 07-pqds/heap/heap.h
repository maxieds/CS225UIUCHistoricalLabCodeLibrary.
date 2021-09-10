#include <stddef.h>

template <class Etype>
class Binary_Heap
{
 private:
   unsigned int Max_Size;   // defines maximum size of the array
   unsigned int Size;    // defines current number of elements
			 //  (and thus always <= Max_Size) 
   Etype *Elements;   // array that holds data  

public:
   //Constructor
   Binary_Heap(unsigned int Initial_Size = 10);  
   
   //Destructor
   ~Binary_Heap() {delete [] Elements; }

   // Member functions
   void Make_Empty()  { Size=0;}
   int Is_Empty() const {return Size==0;}
   int Is_Full() const  {return Size==Max_Size; }
   void Insert(const Etype & X); 
   Etype Delete_Min(); 


   Etype Find_Min() const;

};


