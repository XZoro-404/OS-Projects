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

void forkLoop(BurstList *burstsData)
{

	burstsData->list[counter].pid = fork();
	if (getpid() == 0)
		kill(burstsData->list[counter].pid, SIGTSTP);

}

void process(BurstList *burstsData)
{

	kill(burstsData->list[counter].pid, SIGCONT);
	burstsData->list[counter].burstLength -=10;
	while(!complete)
		sleep(1);
	kill(burstsData->list[counter].pid, SIGTSTP);

	if (burstsData->list[counter].burstLength == 0)
		burstsData->length--;

	

}

void timerAction() {

	complete = 1;

}

struct itimerval timerGen(){
	
	struct itimerval timer;
	timer.it_value.tv_sec = 10;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 10;
	timer.it_interval.tv_usec = 0;
	return timer;

}

int main(int argc, char** argv)
{

	//Be sure to read
	BurstList burstsData;
	Burst burstArr[10];
	burstsData.list = burstArr;
	char *arg1[] = {"gcc", "-o", "Prime", "prime.c"};
	char *arg2[] = {"./PRIME"};

	//Setup Timer and other fun stuff
	struct itmerval timer = timerGen();
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &timerAction;
	sigaction(SIGALRM, &sa, NULL);

	while(counter < 10 && getpid() == 0)
	{

		forkLoop(&burstsData);
		counter++;

	}

	if(getpid() > 0)
	{
		execvp("gcc", arg1);
		execvp("./PRIME", arg2);
		return 0;

	}

	counter = 0;
	while(burstsData.length)
	{

		if(burstsData.list[counter].burstLength == 0)
		{

			process(&burstsData);

		}

		complete = 0;

	}

}

