//
// Created by osc on 10/26/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

static int count = 0;
int status = 1;

void timer_handler(int signum)
{

	printf("%d\n", count);
	count++;
	if(count > 10){

		status = 0;

	}

}

int main(int argc, char** argv) {

	struct itimerval timer;
	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &timer, NULL);

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &timer_handler;
	sigaction(SIGALRM, &sa, NULL);

	while(status){
		sleep(1);
	}

}
