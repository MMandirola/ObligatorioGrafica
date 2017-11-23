#include "animation.h"
#include "obj.h"
#include "time.h"
#include "math.h"
void initAnimation(Animation * animation, char ** paths, long npaths, float duration){
	initArrayList(sizeof(Obj), &(animation -> objects));
	animation -> duration_in_seconds = duration;
	animation -> started_seconds = SDL_GetTicks() / (float) 1000;
	for(int i=0;i<npaths;i++){
		char * path = paths[i];
		Obj obj;
		initObj(&obj);
		parseObj(path, &obj);
		prepareToDraw(&obj);
		addElement(&obj, &(animation -> objects));
	}
}
void freeAnimation(Animation * animation){
	freeList(&(animation -> objects));
	free(animation);
}
void animationRender(Animation * animation, float seconds){
	Obj * obj = (animation -> objects).vector;
	float difference = seconds - (animation -> started_seconds);
	printf("%f\n", difference);
	float frameDuration = (float) animation -> duration_in_seconds / (animation -> objects).list_size;
	printf("%f\n", frameDuration);
	int frames_passed = (int) roundf(difference / frameDuration);
	printf("%d\n", frames_passed);
	int current_index = frames_passed % (animation->objects).list_size;
	obj_render(obj + current_index);

}