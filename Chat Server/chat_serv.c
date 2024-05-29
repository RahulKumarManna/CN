#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include<string.h>
#include<stdlib.h>
#define MAX_MSG 100
#define SERVER_ADDR "127.0.0.1"
main (int argc,char *argv[] ) 
 {
  int listensocket, acceptsocket, cliLen, n,pid,j ;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];
  if(argc !=2)
    {
	fprintf(stderr,"Usage: %s <Server port>\n",argv[0]);
	exit(1);
    }

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  servAddr.sin_port = htons(atoi(argv[1]));

  listensocket = socket(AF_INET, SOCK_STREAM, 0);
  printf("Successfully created stream socket \n");

  bind(listensocket, (struct sockaddr *) &servAddr, sizeof(servAddr));
  printf("Bound local port successfully\n");

  listen(listensocket,5);
  while(1)
  {
    printf("waiting for client connection on port TCP %u\n",atoi(argv[1]));
    
    acceptsocket= accept(listensocket, (struct sockaddr *) &cliAddr, &cliLen);
    printf("received connection from host [IP %s ,TCP port %d]\n",inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
    pid=fork();
                   
     if(pid>0)      
     {
      close(acceptsocket);
      continue; 
     }
     else	
     {      
      memset(msg,0x0,MAX_MSG);
      while(1)	
      {
       memset(msg,0x0,MAX_MSG);
       n=recv(acceptsocket,msg, MAX_MSG, 0);
       printf("received from host [IP %s ,TCP port %d] : %s\n",  
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), msg);
       
       if(strcmp(msg,"quit")==0)
       {	
         memset(msg,0x0,MAX_MSG);
         strcpy(msg,"quit");
       }
       else
       {
       printf("\nEnter a string for client : ");
       
       j=0;
       while((msg[j++]=getchar())!='\n');
       msg[--j]='\0';
       }

       send(acceptsocket, msg, strlen(msg) + 1, 0);
       if(strcmp(msg,"quit")==0) 
       {
    	printf("closing connection with host [IP %s ,TCP port %d]\n",inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
    	break;
       }
      }
      close(acceptsocket);
     } 
  }
} 

    


