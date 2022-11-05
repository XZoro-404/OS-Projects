/* 
Authors: Ben Richmond and Christian Black
Assignment No.: 2
Date: 11/4/22
Name of File: main.c
Short Description: 
*/



#include "Data.h"

 int complete = 0, counter = 0, prevCounter, time = 0, originalLength, timeSlice;
 BurstList burstsData;

/* 

	Function Name: childRunner
	Input: None
	Output: None
	Brief Description: Execvps the children so that they can run Prime.c

 */

void childRunner(int idx) {

	char innerArg[2];
	sprintf(innerArg, "%d", idx);
	char *arg[] = {"./PRIME", innerArg, NULL};
	execv("./PRIME", arg);
	printf("Shit dog\n");
	exit(1);
	
}


/* 

	Function Name: forkProc
	Input: the Data structure containing the buffer of bursts read from the input to assign pids too
	Output: None
	Brief Description: Assign pids to the bursts within the burstList and stop them immediately

 */

void forkProc()
{
	
	//Assign pids
	pid_t isChild = fork();

	//Stop processes that aren't the parent
	if (isChild == 0){

		kill(getpid(), SIGTSTP);
		childRunner(burstsData.buffer[counter].idx);

	}
	else{

		burstsData.buffer[counter].pid = isChild;
		

	}

}

/* 

	Function Name: process
	Input: Data structure containing an array of bursts
	Output: None
	Brief Description: Continues a signal and decrements while running. Then sleeps until the Alarm goes off.
		Finally, stops the process and decrements the length if necessary

 */

int process()
{
	
	//Continues and Decrements the timer
		
	kill(burstsData.buffer[counter].pid, SIGCONT);
	
	
	//Sleep until alarm
	while(!complete)
		sleep(1);
	
	burstsData.buffer[counter].burstLength -= timeSlice;
	//Send Stop signal
	kill(burstsData.buffer[counter].pid, SIGTSTP);
	
	//decrement the length if it needs to be decremented
	if (burstsData.buffer[counter].burstLength <= 0) {

		burstsData.length--;
		kill(burstsData.buffer[counter].pid, SIGKILL);
	

	}

	complete = 0;

}


/*
	Function Name: timerAction
	Input: None
	Output: None
	Brief Description: Changes a flag so that the process function will stop sleeping.
*/


void timerAction() {

	complete++;
	time += timeSlice;

}

/* 

	Function Name: timerGen
	Input: None
	Output: Timer to our specifications
	Brief Description: Sets the timer's values to our specifications set in the timeSlice argument

 */

struct itimerval timerGen(){
	
	struct itimerval timer;
	timer.it_value.tv_sec = timeSlice;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = timeSlice;
	timer.it_interval.tv_usec = 0;
	return timer;

}



void readFile (char *inputTxt)
{
FILE* file = fopen (inputTxt, "r");
    int i = 0, j = 0;
    int lineNum = 0;
	burstsData.length = 0;
	char s[100];
	if (file == NULL){

	printf("OH FUCK\n");
	exit(1);
}
	printf("WEOUTHRE\n");
	Burst burstArr[10];
    fgets(s, 100, file);
    while (fscanf (file, "%d%d", &i, &j) == 2)
    {
	Burst burstBuff;
        burstBuff.idx = i;
        burstBuff.burstLength = j;
        
	burstsData.length++;
	printf("%d %d\n", i, j);
	printf("%d %d\n", burstBuff.idx, burstBuff.burstLength);
	burstsData.buffer[lineNum] = burstBuff;
	lineNum++;
	

    }
    fclose (file);
}

int increment() {
	
	int incremented = 0, runs = 0;
	prevCounter = counter;
	while(!incremented) {
		
		counter++;
		if (counter >= originalLength) {
			
			counter = 0;
			
		}
		if (burstsData.buffer[counter].burstLength != 0) 
				incremented++;
		runs++;
		if (runs == originalLength)
			return 0;
	}
	return 1;
}

/* 

	Function Name: main
	Input: Argument Num and Arguments
	Output: None
	Brief Description: Creates and manages Bursts to preform a round robin scheduling by processing the length
		of the bursts and creating the children, Running the Children, processing the bursts and timers
		and sending signals

 */

int main(int argc, char** argv) {

	//Be sure to read
	readFile(argv[1]);
	timeSlice = atoi(argv[2]);
	originalLength = burstsData.length;	
	
	//Setup Timer and sigaction
	struct itimerval timer;
	timer = timerGen();
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &timerAction;
	sigaction(SIGALRM, &sa, NULL);
	
	//fork the correct number of children
	while(counter < originalLength) {

		forkProc();
		counter++;

	}
	
	counter = 0;
	setitimer(ITIMER_REAL, &timer, NULL);
	process();
	while(burstsData.length) {

		increment();
		printf("Scheduler: Time Now: %d seconds\n", time);
		printf("Suspending Process %d and scheduling Process %d (Pid %d) for the time\n", burstsData.buffer[prevCounter].idx, burstsData.buffer[counter].idx, burstsData.buffer[counter].pid);
		printf("slice of %d seconds.\n", timeSlice);
		process();

	}

}


