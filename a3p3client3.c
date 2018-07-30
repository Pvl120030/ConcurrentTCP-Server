/*Part 3 Client 3

The Client#3 goes in a loop of sending a few commands and receiving its results. The loop is: 
	send the command: "date; ls -l junk.txt; uname -a "
sleep 1


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>  
#include <time.h>

#define BUFFSIZE 4096

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
  int socket_desc, val;
  struct sockaddr_in client_addr;
  struct hostent *server;
  FILE *out;
  char buffer[256];
  char serverMsg[4096];
  
   time_t T= time(NULL);
  struct tm tm = *localtime(&T);   
    
  if (argc != 3) {
       fprintf(stderr,"USAGE: %s <server ip> <port> \n", argv[0]);
       exit(0);
    }

    server = gethostbyname(argv[1]);
  if (server == NULL) 
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
  memset(&client_addr, 0, sizeof(client_addr));
  int port = atoi(argv[2]);
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr =  INADDR_ANY; 
    client_addr.sin_port = htons(port);

  if(connect(socket_desc, (struct sockaddr*)&client_addr, sizeof(client_addr)) == 0)
	  printf("CONNECT STATE: Connected to Server on port %d\n", port);
  else
	  printf("Connection to server failed !\n");


	
	printf("Message to server: ");
	bzero(buffer,256);
 
while(fgets(buffer,255,stdin)) 
{
  if(strcmp(buffer, "exit\n") == 0) 
    {
            exit(0);
    }
	if(strcmp(buffer,"\n") != 0)
	{
		while(1)
   {
    	 write(socket_desc,buffer,256);
		//bzero(buffer,256);
		
		   bzero(serverMsg,4096);
		   read(socket_desc,serverMsg,4096);
    	 //printf("Current local time and date: %s", asctime (timeinfo));
	     printf("Message from server:\n %s",serverMsg);
    	 //writing to log
       out = fopen("/home/012/p/pv/pvl120030/A3/a3p3client3.log", "a");
    	 if(out==NULL){ printf("FILE OPEN ERROR");}
    	 fprintf(out,"Message from server:\n %s", serverMsg);
    	 fputs("\n", out);
    	 fclose(out);
    	
       printf("Client sleep for one second\n");
       sleep(1);
       printf("Client waking up... \n");
       printf("Current local time and date: %02d:%02d:%02d %02d/%02d/%04d \n", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900);
    }
 		
    printf("Message to server: ");
	}
}
    
    //fclose(f);
	close(socket_desc);
	return 0;	
}