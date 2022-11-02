/*

Authors: Ben Richmond and Christian Black
Assignment No.: 2
Date: 11/4/22
Name of File: Data.h
Short Description: includes the necessary headers and data structures for the RR scheduler

*/

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct Burst;

typedef struct Burst{

	int burstLength, idx, flag;
	pid_t pid;

} Burst;

typedef struct BurstList{

	Burst* list;
	int length;

}