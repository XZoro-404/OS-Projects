/*

Authors: Ben Richmond and Christian Black
Assignment No.: 2
Date: 11/4/22
Name of File: main.c
Short Description:

*/

#include "Data.h"

int complete = 0, counter = 0;

/*

	Function Name: forkProc
	Input: the Data structure containing the list of bursts read from the input to assign pids too
	Output: None
	Brief Description: Assign pids to the bursts within the burstList and stop them immediately

*/

void forkProc(BurstList *burstsData)
{
	
	//Assign pids
	burstsData->list[counter].pid = fork();

	//Stop processes that aren't the parent
	if (getpid() == 0)
		kill(burstsData->list[counter].pid, SIGTSTP);

}

/*

	Function Name: process
	Input: Data structure containing an array of bursts
	Output: None
	Brief Description: Continues a signal and decrements while running. Then sleeps until the Alarm goes off.
		Finally stops the process and decrements the length if necessary

*/

void process(BurstList *burstsData)
{
	//Continues and Decrements the timer
	kill(burstsData->list[counter].pid, SIGCONT);
	burstsData->list[counter].burstLength -=10;
	
	//Sleep until alarm
	while(!complete)
		sleep(1);

	//Send Stop signal
	kill(burstsData->list[counter].pid, SIGTSTP);
	
	//decrement the length if it needs to be decremented
	if (burstsData->list[counter].burstLength == 0)
		burstsData->length--;

	counter++;

}

/*

	Function Name: timerAction
	Input: None
	Output: None
	Brief Description: Changes a flag so that the process function will stop sleeping.

*/

void timerAction() {

	complete++;
	printf("ITS TIME\n");

}

/*

	Function Name: timerGen
	Input: None
	Output: Timer to our specifications
	Brief Description: Sets the timer's values to our specifications set in the TIME_SLICE constant

*/

struct itimerval timerGen(){
	
	struct itimerval timer;
	timer.it_value.tv_sec = TIME_SLICE;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = TIME_SLICE;
	timer.it_interval.tv_usec = 0;
	return timer;

}

/*

	Function Name: childRunner
	Input: None
	Output: None
	Brief Description: Execvps the children so that they can run Prime.c

*/

void childRunner(int idx) {

	char innerArg[2];
	sprintf(innerArg, "%d", idx);
	char *arg1[] = {"gcc", "-o", "PRIME", "prime.c"};
	char *arg2[] = {"./PRIME", innerArg};
	execvp("gcc", arg1);
	execvp("./PRIME", arg2);
	
}

/*

	Function Name: main
	Input: Argument Num and Arguments
	Output: None
	Brief Description: Creates and manages Bursts to preform a round robin scheduling by processing the length
		of the bursts and creating the children, Running the Children, processing the bursts and timers
		and sending signals

*/
/*
int main(int argc, char** argv) {

	//Be sure to read
	BurstList burstsData = readShit();
	int originalLength = burstsData.length;
	
	
	//Setup Timer and sigaction
	struct itimerval timer = timerGen();
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &timerAction;
	sigaction(SIGALRM, &sa, NULL);
	setitimer(ITIMER_REAL, &timer, NULL);
	
	//fork the correct number of children
	while(counter < originalLength && getpid() == 0) {

		forkProc(&burstsData);
		counter++;

	}

	if(getpid() > 0) {

		childRunner(burstsData.list[counter].idx);

	}

	counter = 0;
	while(burstsData.length) {

		if(burstsData.list[counter].burstLength == 0) {

			process(&burstsData);
			if (counter >= originalLength) {

				counter = 0;
		
			}

			complete = 0;

		}

	}

}
*/

int main(int argc, char** argv) {

	struct itimerval timer = timerGen();
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &timerAction;
	sigaction(SIGALRM, &sa, NULL);
	setitimer(ITIMER_REAL, &timer, NULL);
	while(complete !=2);


}
