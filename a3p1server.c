/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include<fcntl.h>

static FILE * out;

//the thread function
void *connection_handler(void *);

void executeCommand(char *command, char *result)
{
    /*This function runs a command./*/
    /*The return value is the output of command*/

    int nSuccess = -1;
    FILE * fp = NULL;
   
    
    char buffer[4096];

    if (command!=NULL)
    {
        printf("Command input %s\n",command );
        //append to log
        out = fopen("/home/012/p/pv/pvl120030/A3/a3p1server.log", "a");
        if(out==NULL){ printf("FILE OPEN ERROR");}
        fprintf(out,"\n Command input from client :\n %s", command);
        fclose(out);
        
        fp=popen(strcat(command," 2>&1"),"r");
        
        if(fp!=NULL)
        {
            while(fgets(buffer, sizeof(buffer)-1,fp)!=NULL)
            {
                strcat(result,buffer);
                //printf("%s",buffer );
                            }
        }
        if(strcmp(result,"\n")){
             strcat(result,"Done to execute\n");
        }
        printf("%s",result);
        out = fopen("/home/012/p/pv/pvl120030/A3/a3p1server.log", "a");
        if(out==NULL){ printf("FILE OPEN ERROR");}
        fprintf(out,"\n Message to client:\n%s", result);
        fclose(out);
        pclose(fp);
        //printf("END\n");
    }
}

int main(int argc , char *argv[])
{
    int socket_desc , client_sock, portno , c;
    struct sockaddr_in server , client;
    
    if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    portno = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( portno );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{   
    
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
    
    time_t T= time(NULL);
    struct tm tm = *localtime(&T);  
          
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //end of string marker
		client_message[read_size] = '\0';
         printf("Client said %s from Thread ID= %u at Time: %02d:%02d:%02d \n",client_message, (unsigned int)pthread_self(), tm.tm_hour, tm.tm_min, tm.tm_sec );
        out = fopen("/home/012/p/pv/pvl120030/A3/a3p1server.log", "a");
        if(out==NULL){ printf("FILE OPEN ERROR");}
        fprintf(out,"Client said %s from Thread ID= %u\n",client_message, (unsigned int)pthread_self() );
        fclose(out);
        //exec command
        char* result = malloc(4096);
        executeCommand(client_message,result);

		//Send the message back to client
        write(sock , result , strlen(result));


		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    return 0;
}