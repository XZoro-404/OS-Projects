#include <pthread.h>
#include <stdio.h>

void thread_task(int i) {

 	//Code for the thread task goes here
	printf("Yahooooooooo %d\n", i);
	fflush(stdout);
 	pthread_exit(0); // this code returns to the corresponding pthread_join issued in main()
	
} 

int main()
{
 	pthread_t thread_id[5];
 	// The following code creates 5 threads.
 	for (int i =0; i <5; i++)
 		pthread_create(&thread_id [i], NULL, thread_task, (void *) i);
 	// The following code makes sure the main program waits until all threads have finished execution
 	for (int i =0; i <5; i++)
		pthread_join(thread_id[i], NULL);
}
