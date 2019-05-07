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
	Vector nextCaptures;
	Location oldLocation;
	Location captureLocation;
	Location newLocation;
	unsigned char piece;
} Capture;

void vectorInit(Vector*);
int vectorCount(Vector*);
void vectorAdd(Vector*, void*);
void vectorSet(Vector*, int index, void*);
void *vectorGet(Vector*, int index);
void vectorDelete(Vector*, int index);
void vectorFree(Vector*);


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
