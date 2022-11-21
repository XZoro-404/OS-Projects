#include "head.h"

sem_t vocal, composer, mutex;

int maxWanderTime = 0, maxSoundRoomTime = 0, currCompNum, currVocalNum, vocNum, compNum, totalRoomNum;

void room_task() {
	
	while(1) {
		sem_wait(&mutex);
		compNum--;
		vocNum--;
		sem_post(mutex);
		if (compNum <= 0 || vocNum <= 0)
			exit(0);
		
		sem_wait(&vocal);
		sem_wait(&composer);
		random_sleep(maxSoundRoomTime);
		sem_post(&composer);
		sem_post(&vocal);
		
	}
	
}

int main(int argc, char** argv) {
	
	sem_init(&vocal, 0, 1);
	sem_init(&composer, 0 ,1);
	sem_init(&mutex, 0, 1);
	
	char * option = argv[1];
	vocNum = atoi(argv[2]);
	compNum = atoi(argv[3]);
	totalRoomNum = atoi(argv[4]);
	
	if (strcomp("-randomdelay", option == 0)) {
		
		maxWanderTime = atoi(argv[5]);
		maxSoundRoomTime = atoi(argv[6]);
		
	}
	
	pthread_t vocalists[vocNum], composers[compNum], rooms[totalRoomNum];
	
	for (vocIdx = 0; vocIdx < vocNum; vocIdx++){
		
		pthread_create(&vocalists [vocIdx], NULL, voc_task, (void *) vocIdx);
		
	}
	
	for (compIdx = 0; compIdx < compNum; vocIdx++) {
		
		pthread_create(&composers[compIdx], NULL, comp_task, (void*) compIdx);
		
	}
	
	for (roomIdx = 0; roomIdx < totalRoomNum; roomIdx++) {
		
		pthread_create(&rooms[roomIdx], NULL, room_task);
		
	}
	
	
	
}