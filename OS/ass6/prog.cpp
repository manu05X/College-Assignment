#include <iostream>
#include <utility>
#include <queue>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

queue<pair<int, int> > sharedMem;

int syn = 0;

void input()
{
        /*===========Taking value of X and Y*/
        int x, y;
        cout << "Enter Value Of X: " ;
        cin >> x ;
        cout << "Enter Value Of Y: " ;
        cin >> y ;

        /*==========Pushing X and Y in queue*/
        sharedMem.push(make_pair(x,y));
}


void* computeA(void*)
{
	while(1) {
		pair<int, int> temp = sharedMem.front();
		//performing A1
		if(syn == 1) {
			cout << "A1: ( " << temp.first << " * " << temp.second << " )" << endl;
			syn = 2;
        	}
		//performing A2
		if(syn == 5) {
       			cout << "A2: ( " << temp.first << " + " << temp.second << " ) * " ;
        		cout << "( " << temp.first << " + " << temp.second << " )" << endl;
			sharedMem.pop();
			syn = 0;
			int opt;
			cout << "InPut Again?? (0/1) : ";
			cin >> opt;
			if(!opt) exit(0);
			input();
			syn = 1;
		}
	}
}

void* computeB(void*)
{
        while(1) {
		pair<int, int> temp = sharedMem.front();
	
        	//performing B1
        	if(syn == 2){
        		cout << "B1: ( " << temp.first << " * " << temp.second << " ) / 2" <<endl;
        		syn = 3; 
		}
        	//performing B2
        	if(syn == 4){
       			cout << "B2: ( " << temp.first << " * " << temp.second << " ) / " ;
        		cout << "( " << temp.first << " + " << temp.second << " )" << endl;
			syn = 5;
		}
	}
}

void* computeC(void*)
{
	while(1){
        	pair<int, int> temp = sharedMem.front();
        	if(syn == 3){
        		cout << "C: ( " << temp.first << " + " << temp.second << " )" << endl;
			syn = 4;
		}
	}
}

int main() 
{
        input();

	/*==========Creating Threads*/
	pthread_t  A, B, C;
	int retA = pthread_create(&A, NULL, computeA, NULL);
	int retB = pthread_create(&B, NULL, computeB, NULL);
	int retC = pthread_create(&C, NULL, computeC, NULL);
 
	syn = 1;

	/*==========joining the Threads*/
	if(!retA)
		pthread_join(A,NULL);
	if(!retB)
   		pthread_join(B,NULL);
	if(!retC)
                pthread_join(C,NULL);

	return 0;
}
