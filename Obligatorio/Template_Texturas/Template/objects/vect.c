#include "vect.h"
void initVect(Vect * vect, char * line){
	sscanf(line ,"v %f %f %f %f", &(vect->x), &(vect->y), &(vect->z), &(vect->w));
}
void copyToDrawVector(Vect * src, ArrayList * dest){
	addElement(&(src->x), dest);
	addElement(&(src->y), dest);
	addElement(&(src->z), dest);
}