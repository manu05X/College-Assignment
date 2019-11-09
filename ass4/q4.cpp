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

int optimal(int vAdd[]){
	int pageFaults = 0;
	pair<int,int> frame[FSIZE];

	for(int i = 0; i < FSIZE; i++){
		frame[i].first = -1;
		frame[i].second = 0;
	}

	for(int i = 0; i < ASIZE; i++){
		int flag = 0;
		int pos = 0;
		for(int j = 0; j < FSIZE; j++){
			if(frame[j].first == vAdd[i]){
				flag = 1;
				pos = j;
			}
			int count = 0;
			for(int k = i+1; k < ASIZE; k++){
				if(frame[j].first == vAdd[k])
					 break;
				count++;
			}
			frame[j].second = count;
		}
		if(!flag){
			for(int j = 0; j < FSIZE; j++){
				if(frame[j].first == -1) { pos = j; break;}
				if(frame[j].second > frame[pos].second)
					pos = j;
			}
		}
		frame[pos].first = vAdd[i];
		frame[pos].second = 0;
		for(int k = i+1; k < ASIZE; k++){
			if(frame[pos].first == vAdd[k] ) break;
			frame[pos].second++;
		}
		cout << "For Pno: " << vAdd[i] <<" Page seq : ";
                for(int j = 0; j < FSIZE; j++){
                        if(frame[j].first == -1){ break;}
                        cout << frame[j].first << "|" << frame[j].second << " ";
                }
		if(flag){
			cout << endl;
			 continue;
		}
		pageFaults++;
		cout << "Page fault occured!!"<< endl;
	}
		
	return pageFaults;
}

int main(){
	int vAdd[] = {0, 1, 20, 2, 20, 21, 32, 31, 0, 60, 0, 0, 16, 1, 17, 18, 32, 31, 0, 61};
	int pRef[ASIZE];
        built(pRef,vAdd);
	cout << "No. of page faults: " << optimal(pRef) << endl;
	return 0;
}
