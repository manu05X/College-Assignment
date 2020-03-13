#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#define MAX_THREAD_NUM 100
#define ARR_SIZE 1000000

int thread_no = 0;
int thread_result[MAX_THREAD_NUM];
int array[1000000];
int inputThreads;

void* minimum(void* args) {
	int i, num = thread_no++;
	int min = 0;

	for (i = num * (ARR_SIZE / inputThreads); i < (num + 1) * (ARR_SIZE / inputThreads); i++) {
		if (array[i] < min)
			min = array[i];
	}

	thread_result[thread_no - 1] = min;
}

int main() {
	int i, min = INT_MAX;
	pthread_t threads[MAX_THREAD_NUM];
	struct timeval tv0, tv1;
	printf("Enter the no. of threads: ");	
	scanf("%d",&inputThreads);

	for (i = 0; i < ARR_SIZE; i++)
		array[i] = (rand() * 2) % ARR_SIZE;

	gettimeofday(&tv0, NULL);

	for (i = 0; i < inputThreads; i++)
		pthread_create(&threads[i], NULL, minimum,(void*) NULL);

	for (i = 0; i < inputThreads; i++)
        	pthread_join(threads[i], NULL);

	for (i = 0; i < inputThreads; i++) {
		if (thread_result[i] < min)
			min = thread_result[i];
	}

	gettimeofday(&tv1, NULL);

	long long elapsed = ((tv1.tv_sec - tv0.tv_sec) * 1000000) + (tv1.tv_usec - tv0.tv_usec);
	printf("\nMinimum element in array = %d\nTime elapsed = %llu ms\n", min, elapsed);
	return 0;
}
