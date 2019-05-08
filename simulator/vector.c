#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

void vectorInit(Vector * v)
{
	v->data = NULL;
	v->size = 0;
	v->count = 0;
}

int vectorCount(Vector * v)
{
	return v->count;
}

void vectorAdd(Vector * v, void * e)
{
	if (v->size == 0) {
		v->size = 10;
		v->data = malloc(sizeof(void*) * v->size);
		memset(v->data, '\0', sizeof(void) * v->size);
	}

	// condition to increase v->data:
	// last slot exhausted
	if (v->size == v->count) {
		v->size *= 2;
		v->data = realloc(v->data, sizeof(void*) * v->size);
	}

	v->data[v->count] = e;
	v->count++;
}

void vectorSet(Vector *v, int index, void *e)
{
	if (index >= v->count) {
		return;
	}

	v->data[index] = e;
}

void * vectorGet(Vector *v, int index)
{
	if (index >= v->count) {
		return NULL;
	}

	return v->data[index];
}

void vectorDelete(Vector *v, int index)
{
	if (index >= v->count) {
		return;
	}

	v->data[index] = NULL;

	int i, j;
	void **newarr = (void**)malloc(sizeof(void*) * v->count * 2);
	for (i = 0, j = 0; i < v->count; i++) {
		if (v->data[i] != NULL) {
			newarr[j] = v->data[i];
			j++;
		}		
	}

	free(v->data);

	v->data = newarr;
	v->count--;
}

void vectorFree(Vector *v)
{
	free(v->data);
}

/*#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void vectorInit(Vector *vector) {
	printf("\n\nNEW VECTOR\n\n");
	// initialize size and capacity
	vector->size = 0;
	vector->capacity = VECTOR_INITIAL_CAPACITY;
	
	// allocate memory for vector->data
  	vector->captures = malloc(sizeof(Capture) * vector->capacity);
}

void vectorAppend(Vector *vector, Capture value) {
	printf("add to vector\n size: %d cap: %d\n", vector->size, vector->capacity);
	// make sure there's room to expand into
	vectorDoubleCapacityIfFull(vector);

	// append the value and increment vector->size
	vector->captures[vector->size++] = value;
}

Capture vectorGet(Vector *vector, unsigned char index) {
	if (index >= vector->size || index < 0) {
		printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
		exit(1);
	}
	return vector->captures[index];
}
*/
/*
void vectorSet(Vector *vector, unsigned char index, Capture value) {
	// zero fill the vector up to the desired index
	while (index >= vector->size) {
		vectorAppend(vector, NULL);
	}

	// set the value at the desired index
	vector->captures[index] = value;
}*/
/*
void vectorDoubleCapacityIfFull(Vector *vector) {
	if (vector->size >= vector->capacity) {
		printf("OOPSIE WOOPSIE VECTOR TO SMOLL\n");
		// double vector->capacity and resize the allocated memory accordingly
		vector->capacity *= 2;
		vector->captures = realloc(vector, sizeof(Capture[vector->capacity]));
	}
}

void vectorFree(Vector *vector) {
	free(vector->captures);
}*/

void printLocation(Location *location){
	printf("Row: %d Field: %d\n", location->row, location->field);
}

void printCapture(Capture *capture){	
	printf("Old ");	
	printLocation(&capture->oldLocation);
	printf("Capture ");
	printLocation(&capture->captureLocation);
	printf("New ");
	printLocation(&capture->newLocation);
	printf("Piece: ");
	switch(capture->piece){
		case ENEMY :
			printf("E");
			break;
		case ENEMYKING :
			printf("EK");
			break;
		case FRIENDLY :
			printf("F");
			break;
		case FRIENDLYKING :
			printf("FK");
			break;
	}
	printf("\n\n");
}

void printVector(Vector *vector){
	printf("bladiebladiebladie bla\n");
	printf("Count: %d\n Capacity: %d\n", vector->count, vector->size);
	for(unsigned char i = 0; i < vector->count; i++){
		printf("Current Count: %d\n", i);
		Capture * capture = vector->data[i];
		printCapture(capture);
	//	if(capture->nextCaptures == NULL){
			printVector(&capture->nextCaptures);
	/*	}else{
			printf("\nNULL\n");
		}*/
	}	
	printf("\n\n");
}
