#include<iostream>
#include<pthread.h>
#include<queue>
using namespace std;
int arr[2];
queue<pair<int,int> > q;
void input(){
        int a,b;
        cout<<"Enter the value of X and Y\n";
        cin>>a>>b;
        q.push(make_pair(a, b));
}
void* A(void*){
        int x=q.front().first;
        int y=q.front().second;
        cout<<"\nThread A accessing queue... (X*Y) = "<<(x*y)<<endl;
        arr[0]=(x*y);
        sleep(7);
        cout<<"\nThread A accessing queue... (X+Y)*(X+Y) = "<<arr[1]*arr[1]<<endl;
}

void* B(void*){
        sleep(1);
        int x=q.front().first;
        int y=q.front().second;
        cout<<"\nThread B accessing queue... (X*Y)/2 = "<<arr[0]/2<<endl;
        sleep(5);
        cout<<"\nThread B accessing queue... (X*Y) /(X+Y) = "<<arr[0]/arr[1]<<endl;
}
void* C(void*){
        sleep(2);
        int x=q.front().first;
        int y=q.front().second;
        cout<<"\nThread C accessing queue... (X+Y) = "<<(x+y)<<endl;
        arr[1]=(x+y);
}
int main(){
        int t=1;
        do{
        input();
        pthread_t A1,B1,C1;
        int retA = pthread_create(&A1,NULL, *A, NULL);
        int retB = pthread_create(&B1,NULL, *B, NULL);
        int retC = pthread_create(&C1,NULL, *C, NULL);
        if (!retA)
                pthread_join(A1, NULL);
        if (!retB)
                pthread_join(B1, NULL);
        if (!retC)
                pthread_join(C1, NULL);

        q.pop();
        cout << "input 0 to quit or 1 to run again" << endl;
        cin>>t;
        }while(t==1);

}


