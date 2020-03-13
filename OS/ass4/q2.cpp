#include <iostream>
#include <queue>

#define FSIZE 3
#define ASIZE 20

using namespace std;

void built(int pRef[],int vAdd[]){
        for(int i = 0; i < ASIZE; i++){
                int bit = 4;
                while(bit--)
                        vAdd[i] = vAdd[i] >> 1;
                pRef[i] = vAdd[i];
        }
}

int FIFO(int vAdd[]){
	int pageFaults = 0;
	int frame[FSIZE];
	for(int i = 0; i < FSIZE; i++)
		frame[i] = -1;
	int pos = 0;
	for(int i = 0; i < ASIZE; i++){
		int flag = 0;
		for(int j = 0; j < FSIZE; j++){
			if(frame[j]== vAdd[i])
				flag = 1;
		}
		cout << "For Pno: " << vAdd[i] <<" Page seq : "; 
		if(flag){
			for(int i = 0; i < FSIZE; i++){
				if(frame[i] == -1) break;
				cout << frame[i] << " ";
			}
			cout << endl;
			continue;
		}

		frame[pos] = vAdd[i];
		pos = (pos+1)%3;
		pageFaults++;
		for(int i = 0; i < FSIZE; i++){
			if(frame[i] == -1) break;
			cout << frame[i] << " ";
		}
		cout << "Page Fault occured!!"<<endl; 
	}
		
	return pageFaults;
}

int main(){
	int vAdd[] = {0, 1, 20, 2, 20, 21, 32, 31, 0, 60, 0, 0, 16, 1, 17, 18, 32, 31, 0, 61};
	int pRef[ASIZE];
        built(pRef,vAdd);
	cout << "No. of page faults: " << FIFO(pRef) << endl;
	return 0;
}
