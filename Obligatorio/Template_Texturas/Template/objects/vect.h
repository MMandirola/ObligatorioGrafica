#ifndef VECT_H
#define VECT_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC
#include "../utils/list.h"
typedef struct{
	float x;
	float y;
	float z;
	float w;
} Vect;
void initVect(Vect * vect, char * line);
void freeVect(Vect * face);
void copyToDrawVector(Vect * src, ArrayList * dest);
#endif