#include <semaphores.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Queue{
	
	int first, last, data[50]
	
} Queue