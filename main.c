#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vector.h"


int stringCompare(const void * x,const void * y) {

}

void stringFree(void * str) {
    char ** x = (char**)str;
    free(*x);
    free(x);


}

void stringDisplay(void * str) {
    char * x = *(char**)str;
    printf("%s ",x);

}



int main() {
    Vector x;
    VectorNew(&x,sizeof(char*),stringFree,stringCompare);
    char * a = strdup("Paulie");
    char * b = strdup("Tony");
    char * c = strdup("Silvio");
    VectorPush(&x,&a);
    VectorPush(&x,&b);
    VectorPush(&x,&c);
    VectorDisplay(&x,stringDisplay);



    return 0;
}