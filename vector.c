#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <search.h>


void VectorNew(Vector * obj,int elem_size,void (*free_fn)(void*),int (*comp_fn)(const void*,const void*)) {
    assert(obj!=NULL);
    assert(elem_size!=0);
    assert(comp_fn!=NULL);

    obj->elem_size = elem_size;
    obj->free_fn = free_fn;
    obj->comp_fn = comp_fn;

    // initially allocating 4 times the element size of memory  on heap
    obj->alloc_len = 4;
    obj->size= 0;
    obj->elems = malloc(obj->elem_size*obj->alloc_len);
    assert(obj->elems!=NULL);


}


int VectorSize(Vector * obj) {
    assert(obj!=NULL);
    return obj->size;
}

void * VectorGet(Vector * obj,int index) {
    assert(obj!=NULL);
    // index should be valid 
    assert(index>=0 && index< obj->size);
    
    void * elem = (char*)obj->elems + index*obj->elem_size;
    
    return elem;

}

void VectorDestruct(Vector * obj) {
    assert(obj!=NULL);

    /*each type needs specific implementation of free function , if the type is not primitive and it's complex,
      then we need to travse all elements and free them with user defined free function.
    */
    if(obj->free_fn!=NULL) {
        for(int i = 0;i<obj->size;i++) {
            void * elem = (char*)obj->elems + i*obj->elem_size;
            obj->free_fn(elem);
        }
    }

    free(obj->elems);
    
}

void VectorPush(Vector * obj,void * elem) {
    assert(obj!=NULL);
    assert(elem!=NULL);
    if(obj->size==obj->alloc_len) {
        // if memory is not sufficent for adding element  , we increase the size by twice of it's size
        obj->alloc_len*=2;
        obj->elems = realloc(obj->elems,obj->alloc_len);
        assert(obj->elems!=NULL);
    }
    void * elem_ptr = (char*)obj->elems + obj->size*obj->elem_size;
    memmove(elem_ptr,elem,obj->elem_size);
    obj->size++;


}

void VectorPop(Vector * obj) {
    assert(obj!=NULL);
    assert(obj->size!=0);
    void * elem_ptr = (char*)obj->elems + obj->size*obj->elem_size;
    if(obj->free_fn!=NULL) {
        obj->free_fn(elem_ptr);
    }

    obj->size--;
    
}

void VectorInsert(Vector * obj,void * elem,int index) {
    assert(obj!=NULL);
    assert(elem!=NULL);
    assert(index>=0&&index<obj->size);
    if(obj->size==obj->alloc_len) {
        obj->alloc_len*=2;
        obj->elems = realloc(obj->elems,obj->alloc_len);
        assert(obj->elems!=NULL);

    }
    void * elem_ptr1 = (char*)obj->elems + index*obj->elem_size;
    void * elem_ptr2 = (char*)elem_ptr1 + obj->elem_size;
    memmove(elem_ptr2,elem_ptr1,(obj->size-index)*obj->elem_size);
    memmove(elem_ptr1,elem,obj->elem_size);
    obj->size++;

}

void VectorDelete(Vector * obj,int index) {
    assert(obj!=NULL);
    assert(obj->size!=0);
    assert(index>=0 && index<obj->size);
    void * elem_ptr1 = (char*)obj->elems + index*obj->elem_size;
    void * elem_ptr2 = (char*)elem_ptr1 + obj->elem_size;
    if(obj->free_fn!=NULL) {
        obj->free_fn(elem_ptr1);

    }
    memmove(elem_ptr1,elem_ptr2,(obj->size-index-1)*obj->elem_size);
    obj->size--;


}

void VectorReplace(Vector * obj,int index,void * key) {
    assert(obj!=NULL);
    assert(key!=NULL);
    assert(index>=0 && index<obj->size);
    void * elem = (char*)obj->elems + index*obj->elem_size;
    if(obj->free_fn!=NULL) {
        obj->free_fn(elem);

    }
    memmove(elem,key,obj->elem_size);



}

int VectorSearch(Vector * obj,void * key,int isSorted) {
    assert(obj!=NULL);
    assert(key!=NULL);
    assert(isSorted== 0 || isSorted ==1);


    void *elem_ptr = NULL;
    
    elem_ptr = isSorted==1? bsearch(key,obj->elems,obj->size,obj->elem_size,obj->comp_fn) : lfind(key,obj->elems,&obj->size,obj->elem_size,obj->comp_fn);

    return elem_ptr == NULL ? -1 : ((char*)elem_ptr-(char*)obj->elems)/obj->elem_size;




}

void VectorDisplay(Vector * obj,void (*disp_fn)(void*)) {
    assert(obj!=NULL);
    assert(disp_fn!=NULL);
    for(int i = 0;i<obj->size;i++) {
        void * elem_ptr = (char*)obj->elems + i*obj->elem_size;
        disp_fn(elem_ptr);
    }

}









