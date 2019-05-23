#ifndef VECTOR_H
#define VECTOR_H

#include "constants.h"

#define VECTOR_INITIAL_CAPACITY 5

typedef struct {
	unsigned char field;
	unsigned char row;
} Location;

typedef struct vector_ {
    void** data;
    int size;
    int count;
} Vector;


typedef struct {
	Vector *nextCaptures;
	Location oldLocation;
	Location captureLocation;
	Location newLocation;
	unsigned char piece;
} VectorCapture;

typedef struct {
	Location captureLocation;
	unsigned char piece;
} Capture;

typedef struct Move{
	Location oldLocation;
	Location newLocation;
	Capture capture;
	struct Move * nextMove;
} _move;

typedef struct {
	struct Move * move;
	unsigned char board[10][10];
} VectorMove;

Vector *vectorInit();
int vectorCount(Vector * v);
void vectorAdd(Vector * v, void * e);
void vectorSet(Vector * v, int index, void * e);
void *vectorGet(Vector * v, int index);
void vectorDelete(Vector * v, int index);
void vectorFree(Vector * v);
void printVector(Vector *vector, unsigned char depth);


/*
typedef struct {
	unsigned char size;
	unsigned char capacity;
	Capture captures[];
} Vector;


	

void vectorInit(Vector *vector);

void vectorAppend(Vector *vector, Capture value);

Capture vectorGet(Vector *vector, unsigned char index);

void vectorSet(Vector *vector, unsigned char index, Capture value);

void vectorDoubleCapacityIfFull(Vector *vector);

void vectorFree(Vector *vector);

void printCapture(Capture *capture);

void printVector(Vector *vector);
*/

#endif
