
#include "Data.h"

unsigned long currPrime;
int procNum, runNum = 0;

int isPrime(unsigned long number)
{
	// for loop to check if the number is divisible by 2 (not an efficient method of checking)
	for (int i=2; i <= number/2; i++) {
		if (number % i == 0) {
			return 0;
		}
	}
	return 1;
}

void nextPrime()
{

	unsigned long prime = currPrime;
	while (1) {
		prime++;

		if (isPrime(prime))
			currPrime = prime;
	}

}

int main(int argc, char ** argv)
{

	procNum = atoi(argv[1]);

	char currPrimeStr[10];
	currPrimeStr[0] = 48 + (rand() % 8) + 1;
	for (int idx = 1; idx < 10; idx++) {

		currPrimeStr[idx] = 48 + (rand() % 10);

	}
	
	currPrime = strtoul(currPrimeStr, NULL, 10)
	printf("Process %d: my PID is %d: I just got started. I am starting with the number %lu to find the next prime number");
	nextPrime();
	
}


