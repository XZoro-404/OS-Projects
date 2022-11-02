/*

	Author: Ben Richmond and Christian Black
	Assaignment Number: 1
	Date of Submission: TBD
	Short Description of Contents:
	These are the functinos to queue and dequeue various Node objects from the Queue

 */

#include "Queue.h"

/*

	Function Name: enqueue
	Input to the Method: The node to be added as well as the mainQueue that we are adding
		it to
	Output: There is no output
	Brief Description of the Task:
		Sets the pointer of the array's last filled element's next position to a
		Node object.

 */

void enqueue(Node* addend, Queue* mainQueue)
{

	//Initialize the new node to be placed
	int pointAddend = mainQueue->last;
	Node tempNode;
	tempNode.num = addend->num;
	tempNode.level = addend->level;

	//Places the new node
	mainQueue->arr[pointAddend] = tempNode;

	//Updates the mainQueue's variables
	(mainQueue->length)++;
	(mainQueue->last)++;
}

/*

	Function Name: dequeue
	Input to the Method: the queue that we are pulling from
	Output: Returns a pointer to the node that was the first into the queue.
	Brief Description:
	First checks to make sure that the queue isn't empty then remove the item at
	the first position and increments and returns appropriately

 */

Node dequeue(Queue* mainQueue)
{

	//Error checking if Statement and error code
	if (mainQueue->length <= 0){

		printf("Error invalid Queue");
		Node node;
		return node;
	}

	//If it passes creates a reference to the first item in the queue then increment
	else{

		Node fin = mainQueue->arr[mainQueue->first];
		(mainQueue->first)++;
		(mainQueue->length)--;
		return fin;

	}

}
