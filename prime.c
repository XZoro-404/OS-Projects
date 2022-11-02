// Global variable that will be the prime number and will change every time I find the next prime number
// Global variable that will be the prime number and will change every time I find the next prime number
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Checks the current number that was received from the nextPrime function
 if the number is prime it will return true if not it will return false
 */
bool isPrime(long unsigned int number)
{
    // for loop to check if the number is divisible by 2 (not an efficient method of checking)
    for (int i=2; i <= number/2; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

/*Function to find the prime number that comes after the previous prime number (in the first run it will start from
the number provided in the main function)
 This will iterate through numbers until it finds the next prime
*/
unsigned long nextPrime(long unsigned int prevPrime)
{

    long unsigned int prime = prevPrime;
    bool found = false;

    // This will loop through until isPrime returns true for all numbers greater then prevPrime
    while (!found) {
        prime++;

        if (isPrime(prime)) // Calls the function isPrime passing it the current number to check if prime
            found = true;
    }

    return prime; // Returns the new prime number to main
}

int main()
{
    int startingNumber = 2147483647; // Starting number for the next prime check
    long unsigned int currPrime; // Var for the current prime number
    currPrime = nextPrime(startingNumber); // passes the current prime number to the nextPrime function
    printf("The next prime is %ld", currPrime);
    return 0;
}