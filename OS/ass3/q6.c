#include <sys/time.h>
#include <stdio.h>

float main()
{
 
  	struct timeval tv1, tv2;
	gettimeofday(&tv1,NULL);
	float a = tv1.tv_usec;	
	getpid();
	gettimeofday(&tv2, NULL);	 	
	float b = tv2.tv_usec;
	return b-a;
}
