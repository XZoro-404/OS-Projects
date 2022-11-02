#include <stdlib.h>
#include <stdio.h>

/*

	Authors: Ben Richmond and Christian Black
	Assignment Number: 1
	Date of Submission; TBD
	Name of this File: A1.h
	Short Description of Contents:
		Contains structs for the data we will be using including one for a queue,
		a Node that will be included in the queue, and the Data from a file that has been
		written. 

*/
#define MAX_SIZE 500
#define DEFAULT_LEVEL 0
#define MAX_CHILD_ARR_SIZE 100

typedef struct Node{

	int num, level;

} Node;

typedef struct Queue{

	Node* arr;
	int first, last, length;

} Queue;

typedef struct Data{

	int* result, length;

} Data;
