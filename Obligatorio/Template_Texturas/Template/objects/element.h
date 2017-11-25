
#ifndef ELEMENT_H
#define ELEMENT_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC#include "../utils/list.h"
#include "../utils/list.h"
typedef struct{
	ArrayList animations;
	unsigned int texture;
	float rotatex;
	float rotatey;
	float rotatez;
	float translatex;
	float translatey;
	float translatez;
	float scalex;
	float scaley;
	float scalez;
} Element;
void initElement(Element face, char * line);
void freeElement(Element * element);
void renderElement(Element * element);
#endif