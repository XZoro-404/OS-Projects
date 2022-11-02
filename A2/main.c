/*

Authors: Ben Richmond and Christian Black
Assignment No.: 2
Date: 11/4/22
Name of File: main.c
Short Description:

*/

#include "Data.h"
int complete = 0;
int counter = 0;

int main(int argc, char** argv)
{

	//Be sure to read
	BurstList burstsData;
	Burst burstArr[10];
	burstsData.list = burstArr;

	//Setup Timer and other fun stuff

	while(counter < 10 && getpid() == 0)
	{

		forkLoop(&burstsData);
		counter++;

	}

	if(getpid() > 0)
	{

		exec(prime.c);
		return 0;

	}

	counter = 0;
	while(burstsData.length)
	{

		if(burstData.list[counter].burstLength == 0)
		{

			process(burstList)

		}

		complete = 0;

	}

}

void forkLoop(BurstList *burstsData)
{

	burstsData->list[counter].pid = fork();
	if (pid == 0)
		kill(burstsData.list[counter]->pid, SIGTSTP);
	
}

void process(BurstList *burstsData)
{

	kill(burstsData->list[counter].pid SIGCONT);
	burstsData->list[counter].burstLength -=10;
	while(!complete)
		sleep(1);
	kill(burstsData->list[counter].pid, SIGTSTP);
	
	if (burstsData->list[counter].pid, SIGTSTP)
		burstData.length--;
	
}

void timerAction() {

	complete = 1;

}
