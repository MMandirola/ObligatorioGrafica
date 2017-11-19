#include "face.h"
void initFace(Face * face, char * line){
	int res = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &(face->x1), &(face->n1), &(face->t1),
	                 &(face->x2), &(face->n2), &(face->t2), &(face->x3), &(face->n3), &(face->t3));
	if(res != 9){
			res = sscanf(line, "f %d/%d %d/%d %d/%d", &(face->x1), &(face->t1),
	                 &(face->x2), &(face->t2), &(face->x3), &(face->t3));
			if (res != 6){
				res = sscanf(line, "f %d//%d %d//%d %d//%d", &(face->x1), &(face->n1),
	                 &(face->x2), &(face->n2), &(face->x3), &(face->n3));
				if(res != 6){
					res = sscanf(line, "f %d %d %d", &(face->x1), &(face->x2), &(face->x3));
				}
			}
	}
	// printf("%d\n", res);
}
void freeFace(Face * face);
void correctIndex(Face * face){
	face -> x1 = face -> x1 -1;
	face -> x2 = face -> x2 -1;
	face -> x3 = face -> x3 -1;
	face -> t1 = face -> t1 -1;
	face -> t2 = face -> t2 -1;
	face -> t3 = face -> t3 -1;
	face -> n1 = face -> n1 -1;
	face -> n2 = face -> n2 -1;
	face -> n3 = face -> n3 -1;

}