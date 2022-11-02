/*

	Authors: Ben Richmond and Christian Black
	Assignment Number: 1
	Date of Submision: 10/19/22
	Name of this File: main.c
	Short Descritption of contents:
	Contains the main function for the program

 */

#include "Processing.c"

/*

	Function Name: main
	Input to Method: command line arguments and number of command line arguments
	Output: exit code
	Brief Description: initializes variable and runs a loop with the logic necessary for
		processing data

 */

int main(int argc, char * argv[])
{

	//Queue Initialization
	Queue mainQueue;
	mainQueue.first = 0;
	mainQueue.last = 0;
	mainQueue.length = 0;
	//Makes a very large queue so that all the processes can fit
	mainQueue.arr = (Node *) malloc(sizeof(Node) * MAX_SIZE);

	//Node initialization
	Node initial;
	initial.num = atoi(argv[1]);
	initial.level = DEFAULT_LEVEL;

	//Preparing the queue
	enqueue(&initial, &mainQueue);

	//Main Processing loop
	while(mainQueue.length > 0) {

		dataProcess(&mainQueue);
		printf("\n");

	}

}



