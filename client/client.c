#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <time.h>


#define SOCKET_NAME "/tmp/again.socket"
#define BUFFER_SIZE 12


int getrand(int min,int max){
     return(rand()%(max-min)+min);
}

char *item(){
	char *rps[] = {"rock","paper","scissors"};
	int i = getrand(1,3);
	return rps[i];
}

int   main(int argc, char *argv[])
       {
           struct sockaddr_un addr;
           int ret;
           int data_socket;
           char buffer[BUFFER_SIZE];
		   char *in;

    		srand(time(NULL));


           data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
           if (data_socket == -1) {
               perror("socket");
               exit(EXIT_FAILURE);
           }


           memset(&addr, 0, sizeof(struct sockaddr_un));



           addr.sun_family = AF_UNIX;
           strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

           ret = connect (data_socket, (const struct sockaddr *) &addr,
                          sizeof(struct sockaddr_un));
           if (ret == -1) {
               fprintf(stderr, "The server is down.\n");
               exit(EXIT_FAILURE);
				}


	do{

		   ret = read(data_socket, buffer, BUFFER_SIZE);

           if (ret == -1) {
               perror("read");
               exit(EXIT_FAILURE);
           }

           ret = write(data_socket,in=item(), BUFFER_SIZE);

		
		}while(strcmp(buffer,"Exit")!=0);	
    	close(data_socket);

    exit(EXIT_SUCCESS);

return 0;
}
