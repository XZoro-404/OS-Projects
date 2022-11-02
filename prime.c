// Global variable that will be the prime number and will change every time I find the next prime number
// Global variable that will be the prime number and will change every time I find the next prime number
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function that returns true if n
// is prime else returns false
bool isPrime(long unsigned int number)
{
    
    for (int i=2; i <= number/2; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

// Function to return the smallest
// prime number greater than N
unsigned long nextPrime(long unsigned int prevPrime)
{

    long unsigned int prime = prevPrime;
    bool found = false;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;

        if (isPrime(prime))
            found = true;
    }

    return prime;
}


int main()
{
    int startingNumber = 2147483647;
    long unsigned int currPrime;
    currPrime = nextPrime(startingNumber);
    printf("The next prime is %ld", currPrime);
    return 0;
}