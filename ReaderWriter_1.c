# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/types.h>
# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <unistd.h>

//semaphores
sem_t resource, mutex;	// mutex for reader	RWMutex for writer
static int readCount = 0;
int value;
static int t = 0;
int timeChange = 0;
int threadFinish = 0;

struct data {
	int id;
	int opTime;
	int lastTime;
	char role;
};

//reader
void * Reader(void *param) {
	struct data *dt = (struct data*) param;
	while (1) {
		if (dt->opTime == t) break;
	}
	printf("R (ID=%d) comes at t = %d\n",dt->id, t);
	
	sem_wait(&mutex);
	readCount++;
	if (readCount == 1)
		sem_wait(&resource);
	sem_post(&mutex);
	int tempTime = t + dt->lastTime;
	printf("Reader (ID=%d) (from %d to %d) has read: %d\n", dt->id, t, tempTime, value);
	while (t < tempTime) {
		
	}
	
	sem_wait(&mutex);
	readCount--;
	threadFinish++;
	if (readCount == 0)
		sem_post(&resource);
	sem_post(&mutex);
	pthread_exit(0);
}

//Writer
void * Writer(void *param) {
	struct data *dt = (struct data*) param;
	while (1) {
		if (dt->opTime == t) break;
	}
	printf("W (ID=%d) comes at t = %d\n", dt->id, t);
	
	sem_wait(&resource);
	int tempTime = t + dt->lastTime;
	if (timeChange == 0) {
		value = 0;
	} else if (timeChange == 1) {
		value = 1;
	} else {
		value = 2;
	}
	timeChange++;
	printf("Writer (ID=%d) (from %d to %d) has write value: %d\n", dt->id, t, tempTime, value);
	while (t < tempTime) {
		
	}
	
	threadFinish++;
	sem_post(&resource);
	pthread_exit(0);
}

int main() {
	//pthread
	pthread_t tid[8]; // the thread identifier

	//initial the semaphores
	sem_init(&mutex, 0, 1);
	sem_init(&resource, 0, 1);
	int status, *pstatus= &status;
	int i;
	struct data arrData[8];
	
	arrData[0].id = 1;
	arrData[0].opTime = 0;
	arrData[0].lastTime = 3;
	arrData[0].role = 'W';
	
	arrData[1].id = 2;
	arrData[1].opTime = 1;
	arrData[1].lastTime = 5;
	arrData[1].role = 'R';
	
	arrData[2].id = 3;
	arrData[2].opTime = 3;
	arrData[2].lastTime = 4;
	arrData[2].role = 'R';
	
	arrData[3].id = 4;
	arrData[3].opTime = 2;
	arrData[3].lastTime = 4;
	arrData[3].role = 'W';
	
	arrData[4].id = 5;
	arrData[4].opTime = 8;
	arrData[4].lastTime = 1;
	arrData[4].role = 'R';
	
	arrData[5].id = 6;
	arrData[5].opTime = 10;
	arrData[5].lastTime = 3;
	arrData[5].role = 'R';
	
	arrData[6].id = 7;
	arrData[6].opTime = 11;
	arrData[6].lastTime = 3;
	arrData[6].role = 'R';
	
	arrData[7].id = 8;
	arrData[7].opTime = 14;
	arrData[7].lastTime = 6;
	arrData[7].role = 'W';

	for (i = 0; i < 8; i++) {
		if (arrData[i].role == 'R') {
			pthread_create(&tid[i], NULL, &Reader, (void*) &arrData[i]);
		} else {
			pthread_create(&tid[i], NULL, &Writer, (void*) &arrData[i]);
		}
	}
	
	while (threadFinish < 8) {
		t++;
		sleep(1);
	}
	printf("Done");
	// End Program
	for (i = 0; i < 8; i++)
		pthread_join(tid[i],(void**) pstatus);
	sem_destroy(&mutex);
	sem_destroy(&resource);
	return 0;
}