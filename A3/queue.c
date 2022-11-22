#include "head.h"

void enqueue(Queue* mainQueue, int addend) {
	
	mainQueue->data[mainQueue->last] = addend;
	mainQueue->last++;
	mainQueue->length++;
	
}

int dequeue(Queue* mainQueue) {
	
	temp = mainQueue->data[mainQueue->first];
	mainQueue->first++;
	mainQueue->length--;
	return temp;
	
}

Queue queue_init() {

	Queue temp;
	temp.length = 0;
	temp.last = 0;
	temp.first = 0;
	int tempArr[50];
	temp.data = tempArr;
	
	return temp;

}