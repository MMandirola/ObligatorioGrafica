#include "string.h"
#include "stdio.h"
#include "obj.h"
#include "face.h"
#include "normal.h"
#include "vect.h"
#include "texture.h"
#include "../utils/list.h"
#include <GL/gl.h>
int initObj(Obj* result){
    initArrayList(sizeof(Vect), &(result->vertexes));
    initArrayList(sizeof(Face), &(result->faces));
    initArrayList(sizeof(Norm), &(result->norms));
    initArrayList(sizeof(Texture), &(result->textures));
    initArrayList(sizeof(float), &(result->drawVertexes));
    initArrayList(sizeof(float), &(result->drawNorms));
    initArrayList(sizeof(float), &(result->drawTextures));
    return 1;
}
int parseObj(char * fileName, Obj* result){
    FILE *fp;
    long MAX_LINE = 256;
    char buffer[MAX_LINE];
    fp = fopen(fileName,"r");
    if( fp == NULL ){
        printf("%s\n","Boom");
        return 0;
    }
    while(fgets(buffer, MAX_LINE, fp) != NULL){
      if(strncmp("vn",buffer,2) == 0){
        Norm n;
        initNorm(&n, buffer);
        addElement(&n, &(result->norms));
      }
      else if(strncmp("vt",buffer,2) == 0){
        Texture t;
        initTexture(buffer, &t);
        addElement(&t, &(result->textures));
      }
      else if (strncmp(buffer,"v",1) == 0){
        Vect v;
        initVect(&v, buffer);
        addElement(&v, &(result->vertexes));
      }
      else if (strncmp(buffer,"f",1) == 0){
        Face f;
        initFace(&f,buffer);
        correctIndex(&f);
        addElement(&f, &(result->faces));
      }
      else if (strncmp(buffer,"o",1) == 0){
        strcpy(result->name, buffer);
      }

    }
 
    fclose(fp);
    return 1;
}
void showObj(Obj * object){
  ArrayList vertexList = object->vertexes;
  ArrayList facesList = object->faces;
  ArrayList normalList = object->norms;
  ArrayList textureList = object->textures;
  Vect * vertexes = (Vect *)(vertexList.vector);
  Face * faces = (Face *) (facesList.vector);
  Norm * norm = (Norm *) (normalList.vector);
  Texture * t = (Texture *) (textureList.vector);
  for(int i=0; i<vertexList.list_size;i++){
     printf("v %f %f %f %f \n", vertexes[i].x, vertexes[i].y, vertexes[i].z, vertexes[i].w);
  }
  for(int i=0; i<facesList.list_size;i++){
    printf("f %d/%d/%d %d/%d/%d %d/%d/%d \n", faces[i].x1, faces[i].t1, faces[i].n1, faces[i].x2, faces[i].t2, faces[i].n2, faces[i].x3, faces[i].t3, faces[i].n3);
  }
  for(int i=0; i<normalList.list_size;i++){
    printf("vn %f %f %f \n", norm[i].x, norm[i].y, norm[i].z);
  }
  for(int i=0; i<textureList.list_size;i++){
    printf("vt %f %f \n", t[i].x, t[i].y);
  }
}
int prepareToDraw(Obj * object){
  ArrayList faces = object-> faces;
  ArrayList vertexes = object -> vertexes;
  ArrayList norms = object -> norms;
  ArrayList textures = object -> textures;
  ArrayList drawVertexes = object->drawVertexes;
  ArrayList drawNorms = object->drawNorms;
  ArrayList drawTextures = object -> drawTextures; 
  Face * facesList = (Face *) faces.vector;
  Vect * vertexList = (Vect *) vertexes.vector;
  Norm * normList = (Norm *) norms.vector;
  Texture * textureList = (Texture *) textures.vector;
  for(int i = 0;i<faces.list_size;i++){
    // printf("%d\n", i);

    // printf("%d\n", vertexes.list_size);
    // printf("%d\n", norms.list_size);
    // printf("%d\n", textures.list_size);
    
    Face triangle = facesList[i];
    Vect vect1 = vertexList[triangle.x1];
    copyToDrawVector(&vect1, &drawVertexes);
    Vect vect2 = vertexList[triangle.x2];
    copyToDrawVector(&vect2, &drawVertexes);
    Vect vect3 = vertexList[triangle.x3];
    copyToDrawVector(&vect3, &drawVertexes);


    Norm  norm1 = normList[triangle.n1];
    copyToDrawNorm(&norm1, &drawNorms);
    Norm norm2 = normList[triangle.n2];
    copyToDrawNorm(&norm2, &drawNorms);
    Norm norm3 = normList[triangle.n3];
    copyToDrawNorm(&norm3, &drawNorms);

    Texture text1 = textureList[triangle.t1];
    copyToDrawTexture(&text1, &drawTextures);
    Texture text2 = textureList[triangle.t2];
    copyToDrawTexture(&text2, &drawTextures);
    Texture text3 = textureList[triangle.t3];
    copyToDrawTexture(&text3, &drawTextures);
    object -> drawVertexes = drawVertexes;
    object -> drawNorms = drawNorms;
    object -> drawTextures = drawTextures;
  }
  return 1;
}

void freeObj(Obj * obj){
  freeList(&(obj -> vertexes));
  freeList(&(obj -> faces));
  freeList(&(obj -> norms));
  freeList(&(obj -> textures));
  freeList(&(obj -> drawVertexes));
  freeList(&(obj -> drawNorms));
  freeList(&(obj -> drawTextures));
}

void obj_render(Obj * obj){
  glVertexPointer(3, GL_FLOAT, 0, (obj->drawVertexes).vector);
  glNormalPointer(GL_FLOAT, 0, (obj->drawNorms).vector);
  glTexCoordPointer(2,GL_FLOAT,0, (obj->drawTextures).vector);
  glDrawArrays(GL_TRIANGLES, 0, (obj -> faces).list_size * 3);

  return;
}


