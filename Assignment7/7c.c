#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 26

sem_t fsem, esem;
char buffer;

void producer(void args) 
{
    int count = 0;
    while(count < BUFFER_SIZE ) {
        sem_wait(&esem);
        buffer = 'a' + count++;
        printf("Producer Produce : %c\n", buffer);
        sem_post(&fsem);
    }
}

void consumer(void args)
{
    int count = BUFFER_SIZE;
    while(count--){
        sem_wait(&fsem);
        printf("Consumer consumes : %c\n" , buffer);
        sem_post(&esem);
    }
}

int main()
{
    sem_init(&fsem, 0, 0);
    sem_init(&esem, 0, 1);

    pthread_t pt, ct;


    pthread_create(&ct, NULL, consumer, (void*)NULL);
    pthread_create(&pt, NULL, producer, (void*)NULL);

    pthread_join(pt,NULL);
    pthread_join(ct,NULL);

    return 0;
}