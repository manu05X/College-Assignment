#include <iostream>
#include <utility>
#include <queue>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

using namespace std;

queue<pair<int, int> > sharedMem;
sem_t semA, semB, semC;

void input()
{
        /===========Taking value of X and Y/
        int x, y;
        cout << "Enter Value Of X: " ;
        cin >> x ;
        cout << "Enter Value Of Y: " ;
        cin >> y ;

        /==========Pushing X and Y in queue/
        sharedMem.push(make_pair(x,y));
}


void* computeA(void*)
{
	while(1) {
		pair<int, int> temp = sharedMem.front();
		
		//performing A1
		sem_wait(&semA);
		cout << "A1:\t(x * y) = " << temp.first * temp.second << endl;
		sem_post(&semB);
		
		//performing A2
		sem_wait(&semA);
		cout << "A2:\t(x + y) * (x + y) = ";
		cout << (temp.first +temp.second) * (temp.first + temp.second) << endl;
		
		//Taking Input Again
		sharedMem.pop();
		int opt;
		cout << "InPut Again?? (0/1) : ";
		cin >> opt;
		if(!opt) exit(0);
		input();
		sem_post(&semA);
		
	}
}

void* computeB(void*)
{    	
	while(1) {
		pair<int, int> temp = sharedMem.front();
		
		//performing B1
		sem_wait(&semB);
		cout << "B1:\t(x * y) / 2 = " << ((temp.first * temp.second ) / 2) <<endl;
		sem_post(&semC);
		

		//performing B2
		sem_wait(&semB);
		cout << "B2:\t(x * y) / (x + y) = ";
		cout << (temp.first * temp.second) / (temp.first + temp.second ) << endl;
		sem_post(&semA);
	}
}

void* computeC(void*)
{
	while(1){
    	pair<int, int> temp = sharedMem.front();
       	sem_wait(&semC);
		cout << "C:\t( x + y ) = " << temp.first + temp.second << endl;
		sem_post(&semB);	
	}
}

int main() 
{
	//Taking Input
    input();

	sem_init(&semA, 0, 1);
	sem_init(&semB, 0, 0);
	sem_init(&semC, 0, 0);

	/==========Creating Threads/
	pthread_t  A, B, C;
	int retA = pthread_create(&A, NULL, computeA, NULL);
	int retB = pthread_create(&B, NULL, computeB, NULL);
	int retC = pthread_create(&C, NULL, computeC, NULL);

	/==========joining the Threads/
	if(!retA)
		pthread_join(A,NULL);
	if(!retB)
   		pthread_join(B,NULL);
	if(!retC)
        pthread_join(C,NULL);

	return 0;
}