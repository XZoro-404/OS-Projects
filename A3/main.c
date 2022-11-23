#include "queue.c"

sem_t vocal, composer, room, mutex, composerRoom, vocalRoom;

int maxWanderTime = 0, maxSoundRoomTime = 0, vocNum, compNum, totalRoomNum, claimedVoc = 0, claimedComp = 0;

Queue vocalNums, compNums;

void random_sleep(int max) {
	
	if (!max == 0)
		sleep(rand() % max);

}

void room_task(int num) {
	
	while(1) {
		
		sem_wait(&mutex);
		if(claimedVoc == vocNum || claimedComp == compNum) {

			sem_post(&mutex);
			pthread_exit(0);

		}
		else {

			claimedVoc++;
			claimedComp++;
			sem_post(&mutex);

		}
		sem_wait(&vocal);
		sem_wait(&composer);
		sem_wait(&mutex);
		int myVocNum = dequeue(&vocalNums), myCompNum = dequeue(&compNums);
		sem_post(&mutex);
		printf("Vocalist %d and Composer %d have found a soundproof room\n", myVocNum, myCompNum);
		random_sleep(maxSoundRoomTime);
		sem_post(&composerRoom);
		sem_post(&vocalRoom);
		
	}

}

void voc_task(int num) {
	

	printf("Vocalist %d: I am wandering...\n", num);
	random_sleep(maxWanderTime);
	printf("Vocalist %d: I am ready to make music...\n", num);
	sem_wait(&mutex);
	enqueue(&vocalNums, num);
	sem_post(&mutex);
	sem_post(&vocal);
	sem_wait(&vocalRoom);
	printf("Vocalist %d: I am done now. Goodbye...\n", num);
	pthread_exit(0);
	
}

void comp_task(int num) {
	

	printf("Composer %d: I am wandering...\n", num);
	random_sleep(maxWanderTime);
	printf("Composer %d: I am ready to make music...\n", num);
	sem_wait(&mutex);
	enqueue(&compNums, num);
	sem_post(&mutex);
	sem_post(&composer);
	sem_wait(&composerRoom);
	printf("Composer %d: I am done now. Goodbye...\n", num);
	pthread_exit(0);
	
}

void initialize_global(char ** argv) {
	
	sem_init(&vocal, 0, 0);
	sem_init(&composer, 0, 0);
	sem_init(&composerRoom, 0, 0);
	sem_init(&vocalRoom, 0, 0);
	sem_init(&mutex, 0, 1);
	
	char * option = argv[1];
	vocNum = atoi(argv[2]);
	compNum = atoi(argv[3]);
	totalRoomNum = atoi(argv[4]);
	
	if (strcmp("-randomdelay", option) == 0) {
		
		maxWanderTime = atoi(argv[5]);
		maxSoundRoomTime = atoi(argv[6]);
		
	}
	
	queue_init(vocalNums);
	queue_init(compNums);
	
}

int main(int argc, char** argv) {
	
	initialize_global(argv);
	
	pthread_t vocalists[vocNum], composers[compNum], rooms[totalRoomNum];
	
	for (int vocIdx = 0; vocIdx < vocNum; vocIdx++){
		
		pthread_create(&vocalists[vocIdx], NULL, voc_task, (void *) vocIdx);

	}
	
	for (int compIdx = 0; compIdx < compNum; compIdx++) {
		
		pthread_create(&composers[compIdx], NULL, comp_task, (void*) compIdx);

	}
	
	for (int roomIdx = 0; roomIdx < totalRoomNum; roomIdx++) {
		
		pthread_create(&rooms[roomIdx], NULL, room_task, NULL);
		
	}

	for (int joinIdx = 0; joinIdx < totalRoomNum; joinIdx++) {
		pthread_join(rooms[joinIdx], NULL);
	}
	
	exit(0);	

}
