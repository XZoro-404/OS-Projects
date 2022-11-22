#include "queue.c"

sem_t vocal, composer, room, mutex, composerRoom, vocalRoom;

int maxWanderTime = 0, maxSoundRoomTime = 0, vocNum, compNum, totalRoomNum;

Queue vocalNums, compNums;
void room_task(int num) {
	
	while(1) {
		if (vocalNums.length <= 0 || compNums.length <= 0)
			exit(0);
		
		sem_wait(&vocal);
		sem_wait(&composer);
		sem_wait(&mutex);
		int myVocNum = vocalNums.dequeue(), myCompNum = compNums.dequeue();
		sem_post(&mutex);
		printf("Vocalist %d and Composer %d have found a soundproof room", myVocNum, myCompNum);
		random_sleep(maxSoundRoomTime);
		sem_post(&composerRoom);
		sem_post(&vocalRoom);
		
		
	}
	
}

void voc_task(int num) {
	

	printf("Vocalist %d: I am wandering...", num);
	random_sleep(maxWanderTime);
	printf("Vocalist %d: I am ready to make music...", num);
	sem_wait(&mutex);
	enqueue(&vocalNums, num);
	sem_post(&mutex);
	sem_post(&vocal);
	sem_wait(&vocalRoom);
	printf("Vocalist %d: I am done now. Goodbye...", num);
	
}

void voc_task(int num) {
	

	printf("Composer %d: I am wandering...", num);
	random_sleep(maxWanderTime);
	printf("Composer %d: I am ready to make music...", num);
	sem_wait(&mutex);
	enqueue(&compNums, num);
	sem_post(&mutex);
	sem_post(&composer);
	sem_wait(&composerRoom);
	printf("Composer %d: I am done now. Goodbye...", num);
	
}

void initialize_global(char ** argv) {
	
	sem_init(&vocal, 0, 1);
	sem_init(&composer, 0 ,1);
	sem_init(&composerRoom, 0, 1);
	sem_init(&vocalRoom, 0, 1);
	sem_init(&mutex, 0, 1);
	sem_init(&vocalPost, 0, 1);
	sem_init(&composerPost, 0, 1);
	
	char * option = argv[1];
	vocNum = atoi(argv[2]);
	compNum = atoi(argv[3]);
	totalRoomNum = atoi(argv[4]);
	
	if (strcomp("-randomdelay", option == 0)) {
		
		maxWanderTime = atoi(argv[5]);
		maxSoundRoomTime = atoi(argv[6]);
		
	}
	
	queueInit(vocalNums);
	queueInit(compNums);
	
}

int main(int argc, char** argv) {
	
	initialize_global(argv);
	
	pthread_t vocalists[vocNum], composers[compNum], rooms[totalRoomNum];
	
	for (vocIdx = 0; vocIdx < vocNum; vocIdx++){
		
		pthread_create(&vocalists [vocIdx], NULL, voc_task, (void *) vocIdx);
		
	}
	
	for (compIdx = 0; compIdx < compNum; vocIdx++) {
		
		pthread_create(&composers[compIdx], NULL, comp_task, (void*) compIdx);
		
	}
	
	for (roomIdx = 0; roomIdx < totalRoomNum; roomIdx++) {
		
		pthread_create(&rooms[roomIdx], NULL, room_task);
		pthread_join(&rooms[roomIdx], NULL);
		
	}
	
	
	
}