#include <cstdio>
#include <pthread.h>

int s;
char buffer;

void* producer(void* arg)
{
        char ch;
        for (ch='A'; ch <= 'Z'; ch++){
                while(s!=1);
		printf("Produced %c ", ch);
                buffer = ch;
                s--;
        }
        buffer = '\0';
        return NULL;
}

void* consumer(void* arg)
{
        while (s==1);
        while(buffer!='\0') {
                while (s==1);
		if (buffer == '\0')
			printf("Consumed Z");
		else
                	printf("Consumed %c\n",buffer);
                s++;
        }
        return NULL;
}

int main() {
        s = 1;
        pthread_t id1, id2;
        pthread_create(&id1, NULL, producer, NULL);
        pthread_create(&id2, NULL, consumer, NULL);
        pthread_join(id1, NULL);
        pthread_join(id2, NULL);
}
