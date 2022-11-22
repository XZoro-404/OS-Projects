#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct Queue{
	
	int first, length, last, data[50];
	
} Queue;
