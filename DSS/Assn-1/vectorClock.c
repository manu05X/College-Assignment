/*Q->1 In the given scenario there are four nodes, namely P1, P2, P3 and P4 
Using the events shown in the diagram generate an optimized Vector clock.*/



#include <stdio.h>
int max(int a,int b){
    return (a>b)?a:b;
}

struct process{
    int count[4];
    int LS[4];
    int LU[4];
};

int main()
{
    struct process p[4];
    int t,i,j,t1,t2;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
                p[i].count[j]=0;
                p[i].LU[j]=0;
                p[i].LS[j]=0;
        }
    }

    printf("Enter 5 for send operation\n Enter 6 for recieve operation\nEnter 7 for local operation\n");
    for(i=0;i<10;i++){
        printf("Enter the type of operation\n");
        scanf("%d",&t);
        printf("Enter the process involved Numberwise\n");
        scanf("%d%d",&t1,&t2);
        switch(t){
            case 5:
               p[t1-1].count[t1-1]+=1;
               printf("Process%d sends to Process%d\n",t1,t2);
               p[t1-1].LS[t2-1]+=1;
               for(j=0;j<4;j++)
               p[t1-1].LU[j]=p[t1-1].count[j];
               for(j=0;j<4;j++)
               {
                    if(p[t1-1].LS[j]<p[t1-1].LU[j])
                    printf("Time stamp =( %d,%d )\n",j+1,p[t1-1].LU[j]);
               }

               break;

            case 6:
                 printf("Process%d recieves from Process%d\n",t1,t2);
                 for(j=0;j<4;j++)
               {
                    if(p[t2-1].LS[j]<p[t2-1].LU[j])
                    p[t1-1].count[j]=p[t2-1].LU[j];
               }
                  p[t1-1].count[t1-1]+=1;
                 break;

            case 7:
                 p[t1].count[t1]+=1;
                 printf("Local operation of Process%d\n",t1);
                 break;
        }

    printf("******************\n");
    printf("L[e%d]\n",i+1);
    printf("Process%d=[",t1);
    for(j=0;j<4;j++)
    printf("%d ",p[t1-1].count[j]);
    printf("]\n");
    printf("Process%d=[",t2);
    for(j=0;j<4;j++)
    printf("%d ",p[t2-1].count[j]);
    printf("]\n");
    }
    return 0;
}