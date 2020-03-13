/*
ii) Implement a program for producer consumer problem using message passing :The problem
describes two processes, the producer and the consumer, who share a common, fixed-size
buffer. The producer&#39;s job is to generate a piece of data (A to Z) put it into the buffer and
start again. At the same time the consumer is consuming the data (i.e. removing it from the
buffer) one piece at a time. A producer process produces information that is consumed by a
consumer process.
1. Create a semaphore.
2. Create a shared buffer- Message queue.
3. Initialize value of the semaphore to 1.
4. Create a child process.
5. Child process (Producer) writes to the Message queue.
6. Producer performs an up operation on the semaphore for the consumer to consume.
7. Parent process (Consumer) performs a down operation on the semaphore and reads or
consumes the data from the Message queue.
8. Consumer then performs an up operation.
*/
#include <cstdio>
#include <pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
int s;
char buffer;

void up() {
        s++;
}

void down() {
        s--;
}

void* producer(void* arg) {
        char ch;
        for (ch='A'; ch <= 'Z'; ch++){
                while(s!=0);
                printf("Producer produced %c ", ch);
                buffer = ch;
                up();
                sleep(1);
        }
        buffer = '\0';
        return NULL;
}

void* consumer(void* arg) {
        while (s==0);
        while(buffer!='\0') {
                while (s==0);
                if (buffer == '\0')
                        printf("Consumer consumed Z");
                else
                        printf("Consumed consumed %c\n",buffer);
                down();
                sleep(1);
        }
        return NULL;
}

int main() {
        s = 0;
        pthread_t id1, id2;
        pthread_create(&id1, NULL, producer, NULL);
        pthread_create(&id2, NULL, consumer, NULL);
        pthread_join(id1, NULL);
        pthread_join(id2, NULL);
}