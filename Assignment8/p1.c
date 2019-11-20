/*
i) Implement two-process communication to generate Echo server application using pipes: An
echo server is usually an application which is used to test if the connection between a client
and a server is successful. The server sends back whatever text the client sends.

1. Create two pipes pipe1 and pipe2
2. Create a child process
3. Child closes read end of pipe1
4. Child closes write end of pipe2
5. Child writes to pipe1 and waits for response from parent
6. Parent closes write end of pipe1
7. Parent closes read end of pipe2
8. Parent reads data from pipe1 and writes to pipe2 for child to read
9. Child reads data written by parent to pipe2 through read end of pipe2 and
displays
on.


*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main() {

    int p1[2];
    int p2[2];

    char input_str[100];
    pid_t p;

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        printf("pipe failed");
    }

    printf("Enter the message: ");
    scanf("%s", input_str);
    p = fork();

    if (p < 0) {
        fprintf(stderr, "fork Failed" );
        return 1;
    } else if (p == 0) {
        close(p1[0]);
        printf("\nChild process closed read end of pipe 1");
        close(p2[1]);
        printf("\nChild process closed write end of pipe 2");
        printf("\nChild wrote to pipe 1 and is waiting for a response...");
        printf("\n");
        write(p1[1], input_str, strlen(input_str)+1);
        wait(NULL);

               char str[100];
        read(p2[0], str, 100);
        printf("Child received data from pipe 2. Input string: %s\n", str);

    } else {
        sleep(1);
        close(p1[1]);
        printf("\nParent process closes write end of pipe 1");
        close(p2[0]);
        printf("\nParent process closes read end of pipe 2");

        char str[100];
        read(p1[0], str, 100);
        printf("\nParent process read data from pipe 1");

        write(p2[1], str, strlen(str)+1);
        printf("\nParent process wrote data to pipe 2\n");

    }
        return 0;
}
