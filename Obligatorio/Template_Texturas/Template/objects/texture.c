#include "texture.h"
int initTexture(char * string,Texture * text){
	// printf("%s\n", string);
	sscanf(string, "vt %f %f", &(text->x), &(text-> y));
	// printf("%d\n", res);
	// printf("pvt %f %f \n", text->x, text->y);
	return 1;
}
int copyToDrawTexture(Texture * src, ArrayList * destination){
	addElement(&(src->x), destination);
	addElement(&(src->y), destination);
}