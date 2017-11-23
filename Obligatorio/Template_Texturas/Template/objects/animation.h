
#ifndef ANIMATION_H
#define ANIMATION_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC#include "../utils/list.h"
#include "../utils/list.h"
#include "time.h"
typedef struct{
	ArrayList objects;
	float duration_in_seconds;
	float started_seconds;
	
} Animation;
void initAnimation(Animation * animation, char ** paths, long npaths, float duration);
void freeAnimation(Animation * animation);
void animationRender(Animation * animation, float seconds);

#endif