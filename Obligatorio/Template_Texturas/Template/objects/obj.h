#ifndef OBJ_H
#define OBJ_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC

#include "string.h"
#include "stdio.h"
#include <assert.h>
#include "../utils/list.h"
typedef struct{
    ArrayList  faces;
    ArrayList  vertexes;
    ArrayList  norms;
    ArrayList  textures;
    ArrayList  drawVertexes;
    ArrayList  drawNorms;
    ArrayList  drawTextures;
    char name [256];
}Obj;
int parseObj(char * fileName, Obj * result);
int prepareToDraw(Obj * obj);
void showObj(Obj * object);
int initObj(Obj* result);
void freeObj(Obj * obj);
void obj_render(Obj * obj);
#endif //CANVAS_H

