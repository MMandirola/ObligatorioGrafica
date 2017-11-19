#include "list.h"
#include "string.h"
#include "stdlib.h"


void initArrayList(long element_size,ArrayList * list){
    char* vector = malloc(element_size);
    list -> list_size = 0;
    list -> capacity = 1;
    list -> element_size = element_size;
    list -> vector = vector;
}

void addElement(void * data, ArrayList * list){
    if (list -> list_size == list -> capacity){
        list -> capacity = 2 * (list -> capacity);
        list->vector = realloc(list -> vector, list->capacity * list->element_size);
    }
    char * dest = list->vector;
    dest = dest + (list -> list_size) * (list -> element_size);
    memcpy(dest,data,list->element_size);
    (list -> list_size) ++ ;
}

void freeList(ArrayList * list){
    free(list->vector);
    free(list);
}

void* getIElement(ArrayList * list, int n){
    if (n >= (list -> list_size)){
        return NULL;
    }
    else{
        char * puntero = list->vector;
        long tamano = (list -> element_size) * n;
        return (puntero + tamano);
    }
}

int searchElement(ArrayList * list, void * element){
    for (int i=0; i < (list->list_size); i++){
        void * elemento = getIElement(list,i);
        if(memcmp(elemento, element, list->element_size) == 0){
            return i;
        }
    }
    return -1;
}
