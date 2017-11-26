#include "element.h"
#include "../utils/list.h"
#include <GL/gl.h>
#include "animation.h"
void initElement(Element * element, Animation * animations, int * indexs, long nanims, unsigned int texture, float rotatex, float rotatey, float rotatez, float translatex, float translatey, float translatez, float scalex, float scaley, float scalez){
	initArrayList(sizeof(Animation *), &(element -> animations));
	initArrayList(sizeof(Element *), &(element -> children));
	element -> texture = texture;
	element -> rotatex = rotatex;
	element -> rotatey = rotatey;
	element -> rotatez = rotatez;
	element -> translatex = translatex;
	element -> translatey = translatey;
	element -> translatez = translatez;
	element -> scalex = scalex;
	element -> scaley = scaley;
	element -> scalez = scalez;
	for(int i=0;i<nanims;i++){
		int index = indexs[i];
		Animation * anim = animations + index;
		addElement(&anim, &(element -> animations));  
	}

}
void addChild(Element * parent, Element * son){
	addElement(&son, &(parent -> children));
}
void freeElement(Element * element){
	freeList(&(element -> animations));
	freeList(&(element -> children));
	free(element);
}
void renderElement(Element * element, float seconds){
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, element -> texture);
	glTranslatef(element -> translatex, element -> translatey, element -> translatez);
	glRotatef(element -> rotatex, 1, 0, 0);
	glRotatef(element -> rotatey, 0, 1, 0);
	glRotatef(element -> rotatez, 0, 0, 1);
	glScalef(element -> scalex, element -> scaley, element -> scalez);
	if ((element -> animations).list_size != 0){
		Animation ** current = (element ->animations).vector;
		Animation * element = current[0];
		animationRender(element, seconds);
	}
	Element ** children = (element -> children).vector;
	for(int i=0; i<(element -> children).list_size; i++){
		renderElement(children[i],seconds);
	}
	glPopMatrix();
}