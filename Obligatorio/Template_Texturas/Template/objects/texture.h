#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC
#include "../utils/list.h"
typedef struct{
	float x;
	float y;
}Texture;
int initTexture(char * string,Texture * text);
int copyToDrawTexture(Texture * src, ArrayList * destination);
#endif