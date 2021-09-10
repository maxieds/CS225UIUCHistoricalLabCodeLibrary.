// *****************************************************
// *                                                   *
// *   simpleArray.h                                   *   
// *                                                   *
// *   Interface for a generalized array class         * 
// *                                                   *
// *   Written June 1998 by Jason Zych                 * 
// *                                                   *
// *     - changes by Jason Zych October 1999          *
// *        - added constructor to create an array     *
// *           of size 0                               *
// *       - altered other functions so that an array  *
// *           of size 0 is supported                  *
// *                                                   * 
// *     - changes by Jason Zych October 2004          *
// *        - #ifndef macro name changed               *
// *        - const standardized on right of item      *
// *        - comments enhanced                        *
// *        - some code clean-up done                  *
// *        - class changed to typename for generic    *
// *             variable                              *
// *                                                   *
// *     - changes by Jason Zych January 2005          *
// *        - name of type changed to SimpleArray,     * 
// *              along with related changes to        *
// *              comments, #ifndef macro, etc.        *
// *        - put <Etype> qualifier for the name of    *
// *             type into header file                 * 
// *                                                   *
// *****************************************************

#ifndef SIMPLEARRAY_225_H
#define SIMPLEARRAY_225_H

template <typename Etype>
class SimpleArray
{
public:

   // SimpleArray
   //    - constructor
   //    - initializes object to be a zero-element array; low and high
   //        indices will be 0 and -1, respectively
   SimpleArray();


   // SimpleArray
   //    - constructor
   //    - parameters : low - desired lower bound of array 
   //                 : high - desired higher bound of array
   //    - high is required to be greater than or equal to low - 1; if it
   //       is not, an assertion is triggered. Assuming high >= low - 1,
   //        initializes object to be a (high - low + 1)-element array; cells 
   //        themselves are uninitialized (for primitive types) or 
   //        initialized using the no-argument constructor (for non-primitive 
   //        types). Note that if high == low - 1, then the value of the 
   //        expression high - low + 1 is 0 and we create an SimpleArray 
   //        object without any legal indices
   SimpleArray(int low, int high); 


   // SimpleArray
   //    - constructor
   //    - parameters : origVal - reference to previously-created SimpleArray
   //                    object; that SimpleArray object cannot be changed 
   //                    through the parameter reference
   //    - initializes array to be a copy of origVal	
   SimpleArray(SimpleArray<Etype> const & origVal);

 
   // ~SimpleArray
   //    - destructor
   //    - deletes dynamically allocated memory	
   ~SimpleArray(); 


   // operator=
   //    - parameters : origVal - reference to previously-created SimpleArray
   //                    object; that SimpleArray object cannot be changed 
   //                    through the parameter reference
   //    - return value : reference to this SimpleArray object, after the
   //        assignment operation has been performed; we cannot change this 
   //        object through the returned reference
   //    - assigns this object to be a copy of origVal
   SimpleArray<Etype> const & operator=(SimpleArray<Etype> const & origVal);
 

   // operator[]
   //    - parameters : index - integer index into array
   //    - return type : reference to the array cell at the parameter index;
   //         value stored in array cell cannot be changed through the 
   //         returned reference
   //    - This version of the operator[] will be called on const objects.
   //       The parameter index is required to be a legal index into the
   //       array, i.e. lowerBound <= index and index <= upperBound. (Note 
   //       that for arrays of size 0, there *is* no legal index.) If the 
   //       index is NOT legal, an assertion is triggered. Otherwise, the 
   //       function returns a reference to the array cell at the given 
   //       index, but the array cell is const (i.e. its value cannot be 
   //       changed if accessed through the returned index.  
   Etype const & operator[](int index) const;					


   // operator[]
   //    - parameters : index - integer index into array
   //    - return type : reference to the array cell at the parameter index
   //    - This version of the operator[] will be called on non-const objects.
   //       The parameter index is required to be a legal index into the
   //       array, i.e. lowerBound <= index and index <= upperBound. (Note
   //       that for arrays of size 0, there *is* no legal index.) If the
   //       index is NOT legal, an assertion is triggered. Otherwise, the
   //       function returns a reference to the array cell at the given index.
   Etype & operator[](int index);


   // initialize
   //    - parameters : initElement - reference to object with which to 
   //                     initialize the array; that object cannot be
   //                     changed through the parameter reference
   //    - assigns each cell in the array to hold a copy of parameter value
   void initialize(Etype const & initElement);


   // setBounds
   //    - parameters : theLow - desired new lower bound of array
   //                 : theHigh - desired new upper bound of array
   //    - theHigh is required to be greater than or equal to theLow - 1;  
   //        if it is not, an assertion is triggered. Assuming 
   //        theHigh >= theLow - 1,assigns object to be a 
   //        (theHigh - theLow + 1)-element array. For any indices in 
   //        the array's new index range (theLow <= index <= theHigh) that 
   //        were also in the array's old index range 
   //        (lower() <= index <= upper()), the cells at those contain the 
   //        same values that they contained before this function was called. 
   //        For any indices in the array's new index range that were NOT 
   //        in the array's old index range, the cells at those indices are 
   //        uninitialized (for primitive types) or initialized using the
   //        no-argument constructor (for non-primitive types). For any 
   //        indices in the array's old index range that are NOT indices in
   //        the array's new index range, the values in the cells at those
   //        indices are lost, since we no longer have cells with those 
   //        indices in our array.
   void setBounds(int theLow, int theHigh);


   // size
   //    - return value : non-negative integer
   //    - returns size of array  
   int size() const; 


   // lower
   //    - return value : integer index
   //    - returns "lower bound" index of array. If array has size >= 1,
   //        this will be lowest legal index of array. If array is of 
   //        size 0, then this will be an integer one greater than the
   //        value returned by upper(), but will not be a legal index.
   int lower() const; 


   // upper
   //    - return value : integer index
   //    - returns "upper bound" of array. If array has size >= 1,
   //        this will be highest legal index of array. If array is of
   //        size 0, then this will be an integer one less than the
   //        value returned by lower(), but will not be a legal index.
   int upper() const; 


private:

   int lowerBound;  // lower bound 
   int upperBound;  // upper bound
   Etype * data; // Pointer to the array elements. 

};


#endif
