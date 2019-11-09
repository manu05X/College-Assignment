#include <iostream>
#define SIZE 20

using namespace std;

void built(int pRef[],int vAdd[]){
	for(int i = 0; i < SIZE; i++){
		int bit = 4;
		while(bit--)
			vAdd[i] = vAdd[i] >> 1;
		pRef[i] = vAdd[i];
	}
}

int main(){
	int vAdd[] = {0, 1, 20, 2, 20, 21, 32, 31, 0, 60, 0, 0, 16, 1, 17, 18, 32, 31, 0, 61};
	int pRef[SIZE];
	built(pRef,vAdd);
	for(int i = 0; i < SIZE; i++)
		cout << pRef[i] << " ";
	cout << endl;
	return 0;
}
