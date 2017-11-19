#include "normal.h"
void initNorm(Norm * norm, char * line){
	sscanf(line, "vn %f %f %f", &(norm->x), &(norm->y), &(norm->z));
}
void freeNorm(Norm * face);
void copyToDrawNorm(Norm * src, ArrayList * dest){
	addElement(&(src->x), dest);
	addElement(&(src->y), dest);
	addElement(&(src->z), dest);
}