
#include "Data.h"

unsigned long currPrime; // This sets the current prime number
int procNum, runNum = 100; // sets procNum and runNum to 100

struct sigaction resumeAction;
memset(&resumeAction, 0, sizeof(resumeAction));
resumeAction.resumeAction_handler = &timerAction;
sigaction(sigCONT, &resumeAction, NULL);

struct sigaction stopAction;
memset(&stopAction, 0, sizeof(stopAction));
stopAction.stopAction_handler = &timerAction;
sigaction(sigSTP, &stopAction, NULL);

void resumeActioninue(){
    printf("Process 0: my PID is 1314: I just got resumed. ");
}

void sigSuspend(){
    printf("Process 0: my PID is 1314: I am about to be suspended... Highest prime number I found is 5754853343.");
}
// Checks an int to check if it is prime or not
int isPrime(unsigned long number)
{
	// for loop to check if the number is divisible by 2 (not an efficient method of checking which is what we want)
	for (int i=2; i <= number/2; i++) {
		if (number % i == 0) {
			return 0;
		}
	}
	return 1;
}

void nextPrime()
{

	unsigned long prime = currPrime; // This has to hold a number that is 10 digits minimum
	while (runNum) {
		prime++; // increments the number to check for primality
        // passes the new number to check if it is prime
		if (isPrime(prime)) {

			currPrime = prime; // if the number is prime then set the number to the current prime number

		}
	}

}

int main(int argc, char ** argv)
{

	procNum = atoi(argv[1]); // makes the procNum into an integer
	srand(procNum * getpid());
	char currPrimeStr[10]; // string to hold the currentPrime
	currPrimeStr[0] = 48 + (rand() % 8) + 1;
    // creates a random starting number that is 10 digits long
	for (int idx = 1; idx < 10; idx++) {

		currPrimeStr[idx] = 48 + (rand() % 10);

	}
	
	currPrime = strtoul(currPrimeStr, NULL, 10);
	//printf("Process %d: my PID is %d: I just got started. I am starting with the number %lu to find the next prime number");
	nextPrime();
	
}


