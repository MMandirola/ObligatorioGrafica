
#ifndef ELEMENT_H
#define ELEMENT_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC#include "../utils/list.h"
#include "../utils/list.h"
typedef struct{
	
} Elment;
void initFace(Face * face, char * line);
void freeFace(Face * face);
void correctIndex(Face * face);
#endif