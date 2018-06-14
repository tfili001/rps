///This is the main process
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int   main(int argc, char *argv[]){
	

	int a;
	char buf[32];

	if(argv[1]==NULL)
	{
	a=1;
	}
	else
	{
	a = atoi(argv[1]);
	}


	sprintf(buf, "/home/tim/Documents/rps/ref/ref %d", a);
	strcat(buf," &");

	system(buf);
	sleep(3);

	 
	pid_t player = fork();

	 execl("/home/tim/Documents/rps/client/client",NULL);




	return 0;
}
