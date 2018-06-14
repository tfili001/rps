#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "readstr.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define SOCKET_NAME "/tmp/again.socket"
#define BUFFER_SIZE 12

void sigchld_handler(int s)
{

    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

int main(int argc, char *argv[]){
	unlink(SOCKET_NAME);
	struct sockaddr_un name;
    struct sigaction sa;
	int ret;
	int sockfd;
	int new_fd;
	int N, a;
	int reuseaddr=1;
	char buffer[BUFFER_SIZE];




	if(argv[1]!=NULL){
		
	     N = atoi(argv[1]);	
	}
	else
		N=1;
	
	printf("Referee______________________________________\n");

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);


		       if (sockfd == -1) {
		           perror("socket");
		           exit(EXIT_FAILURE);
		       }


    memset(&name, 0, sizeof(struct sockaddr_un));
	name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);



   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }



    ret = bind(sockfd, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));

     if (ret == -1) 
		{
          perror("bind error");
          exit(EXIT_FAILURE);
        }


	ret = listen(sockfd, 20);

	 if (ret < 0)
		{
		  perror ("listen error");
		  exit (EXIT_FAILURE);
		}

	sa.sa_handler = sigchld_handler;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }


	for(a=0;a<3;a++){

		new_fd = accept(sockfd, NULL, NULL);

				if (new_fd < 0){
				  perror("ERROR on accept");
						  exit (EXIT_FAILURE);
				}

				if(!fork()) 
				{ 
				
						
					close(sockfd);
					for (int i = 0; i < N; i++) {
				///	printf("\nGame %d \n",i+1);
			 		ret = write(new_fd, "GO \n", BUFFER_SIZE);
                    ret = read(new_fd, buffer, BUFFER_SIZE);
						printf("From Player %d:%s Game %d\n",a+1,buffer,i+1);
					}

					ret = write(new_fd, "Exit", BUFFER_SIZE);			
					close(new_fd);
					exit(0);
				}
  
	close(new_fd);
	   
}
return 0;
}
