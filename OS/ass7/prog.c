#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 26

char buffer[BUFFER_SIZE];
char item;

sem_t sem;
int fillCount = 0; // items produced
int emptyCount = BUFFER_SIZE; // remaining space
 
void producer();
void consumer();


int  main()
{
	
	sem_init(&sem, 1, 1);
	
    	pid_t  pid, parentId;

    	parentId = getpid();
    	pid = fork();
    	if(pid == 0)
        	producer(); /*Child Process*/
 //   	else
        	//consumer(); /*Parent Process*/
	
	return 0;
}


void producer()
{
    while (1)
    {
 
	/*ProduceItem*/
        item = (char)(fillCount + 'A');
	printf("Produce item = %c", item);

        if(fillCount++ == BUFFER_SIZE) sem_wait(&sem);
    //    buffer[fillCount++] = item;
   //     up(fillCount);
    }
}

/*
void* consumer(void*)
{
    while (true)
    {
        down(fillCount);
        item = removeItemFromBuffer();
        up(emptyCount);
        consumeItem(item);
    }
}*/


