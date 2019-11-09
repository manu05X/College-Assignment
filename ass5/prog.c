#include<stdio.h>
#include<limits.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>


#define MAX 10000000

#define TMAX 1025


int arr[MAX] = {0};

int min_num[TMAX] = { INT_MAX };
int thread_no = 0;

void fill(){
	int i;
	for(i = 0; i < MAX; i++)
		arr[i] = rand();
}

void *minimum(void* arg){
	int i, num = thread_no++;
	int mins = INT_MAX;

	for(i = num * (MAX/TMAX); i < (num+1) * (MAX/TMAX); i++){
		if(arr[i] < mins)
			mins = arr[i];
	}
	min_num[num] = mins;
}

void timetocalmin(int currT){
	int i;
	int mins = INT_MAX;
	pthread_t threads[currT];

	for(i = 0; i < currT; i++)
                pthread_create(&threads[i], NULL,
                                 minimum, (void*)NULL);

        for(i = 0; i < currT; i++)
                pthread_join(threads[i],NULL);

        for(i = 0; i < currT; i++){
                if(min_num[i] < mins)
                        mins = min_num[i];
        }
}

int main(){
	int i;
	struct timeval start, end;

	fill();	
	gettimeofday(&start, NULL);
	timetocalmin(TMAX);
	gettimeofday(&end, NULL);
	
	printf("Thread No: %d & Time Required: %d\n", TMAX, 
		( (end.tv_sec*1000000 + end.tv_usec)
	 	  - (start.tv_sec*1000000 + start.tv_usec) ) );

	return 0;
}
