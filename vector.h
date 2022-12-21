#ifndef _vector_
#define _vector_


typedef struct {
    void * elems; // pointer to the elements of vector   
    int elem_size; // element size
    int size; // the logical length of vector
    int alloc_len; // allocated length
    void (*free_fn)(void*); // free function which clears the memory allocated on heap
    int (*comp_fn)(const void *,const void *); // comparator function which compares two elements 



} Vector;


// Constructor for vector
void VectorNew(Vector * obj,int elem_size,void(*free_fn)(void*),int (*comp_fn)(const void *,const void *));


// Destructor for vector
void VectorDestruct(Vector * obj);


// Pushing the element in the end of the vector

void VectorPush(Vector * obj,void * elem);


//Popping the element from the end of vector
void VectorPop(Vector * obj);

// Inserting element in particular index

void VectorInsert(Vector * obj,void * elem, int index);


//Deleting element from particular index

void VectorDelete(Vector * obj,int index);

// Replacing the particular element

void VectorReplace(Vector * obj,int index, void * key);

// returns the length size of vector 

int VectorSize(Vector * obj);


// N-th element of vector

void * VectorGet(Vector * obj,int index);

//search for the element in vector

int VectorSearch(Vector * obj,void * key,int isSorted);


// displaying the information of vector

void VectorDisplay(Vector * obj,void (*disp_fn)(void*));








#endif