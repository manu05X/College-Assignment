#include<stdio.h>
#include<stdlib.h>

int s = 1;
char ch = 64;

int down(int S) {
        return --S;
}

int up(int S) {
        return ++S;
}


void producer() {
        s = down(s);
        ch++;
        printf("\nProduced: %c",ch);
        s = up(s);
}

void consumer() {
        s = down(s);
        printf("\nConsumed: %c ",ch);
        s = up(s);
}

int main() {
        for(int i = 0; i < 26; i++) {
                if(s==1)
                        producer();

                if(s==1)
                        consumer();
        }
        return 0;
}


