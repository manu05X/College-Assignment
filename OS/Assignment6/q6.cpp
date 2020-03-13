#include <iostream>
#include <cstdlib>
#include <queue>
#include <utility>
#include <pthread.h>

using namespace std;

float firstOut, secondOut, thirdOut, fourthOut, fifthOut;

queue<pair<int, int> > sharedQueue;

int step;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t completed_A = PTHREAD_COND_INITIALIZER;
pthread_cond_t completed_B = PTHREAD_COND_INITIALIZER;
pthread_cond_t completed_C = PTHREAD_COND_INITIALIZER;

pthread_cond_t completed = PTHREAD_COND_INITIALIZER;

void getInput() {
	step = 1;
	int x, y;
	cout << "\nEnter the value of X and Y: ";
	cin >> x >> y;
	
	sharedQueue.push(make_pair(x,y));
}

void* multiplyA(void*) {
	while(1) {
		pthread_mutex_lock(&mutex);

		if (step == 1) {	
			int x = sharedQueue.front().first;
			int y = sharedQueue.front().second;
			firstOut = (x * y);
			cout << "\nThread A accessing queue... (X * Y) = " << firstOut << endl;
			step++;
			
			sleep(1);
			pthread_cond_signal(&completed_A);
		} else if (step == 5) {
			fifthOut = (thirdOut * thirdOut);	
			cout << "\nThread A accessing queue... ((X + Y) * (X + Y)) = " << fifthOut << endl;

			sleep(1);

			pthread_cond_signal(&completed_A);

			getInput();
			sharedQueue.pop();
		} else {
			cout << "\nThread A is waiting..." << endl;
			//if (step == 4)
				pthread_cond_wait(&completed_B, &mutex);
			//else
			//	pthread_cond_wait(&completed_C, &mutex);
		}

		pthread_mutex_unlock(&mutex);
	}
}

void* divideB(void*) {
	while(1) {
		pthread_mutex_lock(&mutex);

		if (step == 2) {
			// secondOut = firstOut / 2;
			//int x = sharedQueue.front().first;
			//int y = sharedQueue.front().second;
			secondOut = firstOut / 2;
			cout << "\nThread B accessing queue... (X * Y)/2 = " << secondOut << endl;
			step++;

			sleep(1);

			pthread_cond_signal(&completed_B);
		} else if (step == 4) {
			// int x = sharedQueue.front().first;
			// int y = sharedQueue.front().second;
			// fourthOut = ((x * y) / (x + y));
			
			fourthOut = (firstOut / thirdOut);
			cout << "\nThread B accessing queue... ((X * Y) / (X + Y)) = " << fourthOut << endl;
			step++;

			sleep(1);

			pthread_cond_signal(&completed_B);
		} else {
			cout << "\nThread B is waiting..." << endl;
			// if (step == 3)
				pthread_cond_wait(&completed_C, &mutex);
			// else
			//	pthread_cond_wait(&completed_A, &mutex);
		}

		pthread_mutex_unlock(&mutex);
	}
}

void* addC(void*) {
	while(1) {
		pthread_mutex_lock(&mutex);

		if (step == 3) {
			int x = sharedQueue.front().first;
			int y = sharedQueue.front().second;
			thirdOut = x + y;
			cout << "\nThread C accessing queue... (X + Y) = " << thirdOut << endl;
			step++;

			sleep(1);

			pthread_cond_signal(&completed_C);
		} else {
			cout << "\nThread C is waiting..." << endl;
			// if (step == 2)
				pthread_cond_wait(&completed_B, &mutex);
			// else
			//	pthread_cond_wait(&completed_A, &mutex);
		}

		pthread_mutex_unlock(&mutex);
	}	
}

int main() {
	getInput();

	pthread_t A, B, C;
	
	int returnA = pthread_create(&A, NULL, multiplyA, NULL);
	int returnB = pthread_create(&B, NULL, divideB, NULL);
	int returnC = pthread_create(&C, NULL, addC, NULL);

	if (!returnA)
		pthread_join(A, NULL);
	if (!returnB)
		pthread_join(B, NULL);
	if (!returnC)
		pthread_join(C, NULL);

	return 0;
}
