#include  <stdio.h>
#include  <sys/types.h>

void  ChildProcess(void);                
void  ParentProcess(void);               

void  main(void)
{
     pid_t  pid;

     pid = fork();
     if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void  ChildProcess(void)
{
     printf("In Child process\n");
}

void  ParentProcess(void)
{
     printf("In Parent process\n");
}
