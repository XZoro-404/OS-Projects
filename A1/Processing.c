/*

	Authors: Ben Richmond and Christian Black
	Assignment Number: 1
	Date of Submission: 10/19/22
	Name of this File: Processing.c
	Short Description of Contents:
	Contains the functions needed to get the children from the proc file system
	and to process this data.

 */
#include "Queue.c"

/*

	Authors: Ben Richmond and Christian Black
	Input to method: the parent that we're searching for in the proc file system and
			    the pointer to the array that we want to fill with our numbers
	Output: Data structure that contains the length of an array of children and a pointer to the array itself
	Short Description of the Function:
	Creating a string to the appropriate part of the proc function then navigating to it,
	extracting the children and placing them in an appropriate struct to be returned
*/

Data getChildren(int parent, int * number) {
    int child = 0; // the Pid(s) for the children in the file
    char filePath[35] = ""; // the string for the file path
    int arraySize = 0; // an array to hold the children Pid(s)

    // Below we are changing the parent int to a string and creating the file path string
    sprintf(filePath, "/proc/%d/task/%d/children", parent, parent);

    FILE *in_file = fopen(filePath, "r"); // read only

    // test for files not existing.
    if (in_file == NULL) {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }

    // goes through the file and gets the numbers while counting the amount of ints in the file
    while (fscanf(in_file, "%d", &child ) == 1)
    {
        number[arraySize] = child; // sets the child pid to an array
        arraySize++; // increments the array size
    }
    fclose(in_file); // closes the file

	//Return the children and length of array in data struct
    Data children;
    children.result = number;
    children.length = arraySize;
    return children;
}

/*

	Function name: dataProcess
	Input to the Method: the main queue we created in main
	Output: none
	Brief Description of the task:
	Creates a new Node that holds the dequeued Node then gets the data and prints
	appropriately based on the input and level as well as queueing the children.

 */

void dataProcess(Queue* queue)
{

	//Initializing the temporary node
	Node temp;
	temp = dequeue(queue);

	//Initializing the Data struct to process
	int childrenNums[MAX_CHILD_ARR_SIZE];
	Data tempData = getChildren(temp.num, childrenNums);

	//Prints tabs based on the level of the child
	for(int idx = 0; idx < temp.level; idx++) {

		printf("\t");

	}

	//Prints the inital string to be built upon
	printf("Children of %d:", temp.num);

	//Queues chidren as well as printing them
	for(int childIdx = 0; childIdx < tempData.length; childIdx++) {

		printf("%d ", tempData.result[childIdx]);
		Node child;
		child.num = tempData.result[childIdx];

		//Sets it to the appropriate level
		child.level = temp.level + 1;
		enqueue(&child, queue);
	}

}
