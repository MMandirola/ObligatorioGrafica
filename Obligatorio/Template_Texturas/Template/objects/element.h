
#ifndef ELEMENT_H
#define ELEMENT_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC#include "../utils/list.h"
#include "../utils/list.h"
#include "animation.h"
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
void initElement(Element * element, Animation * animations, int * indexs, long nanims, unsigned int texture, float rotatex, float rotatey, float rotatez, float translatex, float translatey, float translatez, float scalex, float scaley, float scalez);
void renderElement(Element * element, float seconds);
#endif