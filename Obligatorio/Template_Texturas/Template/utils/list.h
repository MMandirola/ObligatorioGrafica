#ifndef LIST_H
#define LIST_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC
typedef struct{
    int list_size;
    int capacity;
    int element_size;
    char* vector;
}ArrayList;
void initArrayList(long element_size,ArrayList * list);
void addElement(void * data, ArrayList * list);
void freeList(ArrayList * list);
void* getIElement(ArrayList * list, int n);
int searchElement(ArrayList * list, void * element);

#endif