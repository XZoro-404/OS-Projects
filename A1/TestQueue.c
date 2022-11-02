#include "Queue.c"

int main(int argc, char* argv[]) {
	
	printf("start");
	Queue mainQueue;
	mainQueue.first = 0;
	mainQueue.last = 0;
	mainQueue.length = 0;
	printf("Queue init");
	//Makes a very large queue so that all the processes can fit
	Node* array = (Node *) malloc(sizeof(Node) * 500);
	mainQueue.arr = array;
	printf("QueueCreated");
	Node initial;
	initial.num = atoi(argv[1]);
	initial.level = DEFAULT_LEVEL;
	printf("Node Created");
	enqueue(&initial, &mainQueue);
	printf("Enqueue Success");
	enqueue(&initial, &mainQueue);
	enqueue(&initial, &mainQueue);
	printf("%d %d\n", mainQueue.length, mainQueue.length);
	dequeue(&mainQueue);
	dequeue(&mainQueue);
	printf("%d %d", mainQueue.length, mainQueue.length);

}
