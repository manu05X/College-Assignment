#include  <stdio.h>
#include  <sys/types.h>

void  ChildProcess(pid_t);                
void  ParentProcess(pid_t);               

void  main(void)
{
     	pid_t  pid, parentId;

	parentId = getpid();
     	pid = fork();
     	if (pid == 0) 
        	  ChildProcess(parentId);
    	else 
        	  ParentProcess(pid);
}

void  ChildProcess(pid_t id){
     	printf("In Child process\nProcess Id = %d\tParent Id = %d\n",getpid(),id);
}

void  ParentProcess(pid_t id){
	printf("In Parent process\nProcess Id = %d\tChild Id = %d\n",getpid(),id);
}
