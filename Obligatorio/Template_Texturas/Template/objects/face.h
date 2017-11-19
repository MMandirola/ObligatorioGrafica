
#ifndef FACE_H
#define FACE_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC#include "../utils/list.h"
#include "../utils/list.h"
typedef struct{
	unsigned int x1;
	unsigned int x2;
	unsigned int x3;
	unsigned int t1;
	unsigned int t2;
	unsigned int t3;
	unsigned int n1;
	unsigned int n2;
	unsigned int n3;
} Face;
void initFace(Face * face, char * line);
void freeFace(Face * face);
void correctIndex(Face * face);
#endif