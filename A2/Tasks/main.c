/*
 * Authors: Ben Richmond and Christian Black
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    pid_t pid = fork();
    if (pid == 0){
        printf("I'm alive\n");
    }
    else{
        wait(NULL);
        printf("not anymore lol");
    }
}