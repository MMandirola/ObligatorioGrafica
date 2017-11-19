#ifndef NORM_H
#define NORM_H

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
} Norm;
void initNorm(Norm * face, char * line);
void copyToDrawNorm(Norm * src, ArrayList * dest);
void freeNorm(Norm * face);
#endif