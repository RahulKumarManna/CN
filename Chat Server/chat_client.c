#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include<string.h>
#include<stdlib.h>

#define SERVER_ADDR "192.168.1.166"
#define CLIENT_ADDR "192.168.1.163"

 main (int argc,char *argv[]) {
  int sd,rc,i,cliLen,n,newsd,MAX_MSG =100,j;
  struct sockaddr_in clientAddr, servAddr;
  char msg[100];

  if (argc !=3)
    {
	fprintf(stderr,"Usage:  %s  <SERVER_PORT>  <CLIENT_PORT>\n",argv[0]);
	exit(1);
    }


  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  servAddr.sin_port = htons(atoi(argv[1]));
	

  bzero((char *)&clientAddr, sizeof(clientAddr));
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_addr.s_addr = inet_addr(CLIENT_ADDR);
  clientAddr.sin_port = htons(atoi(argv[2]));  		


  sd= socket(AF_INET, SOCK_STREAM, 0);
  bind(sd, (struct sockaddr *) &clientAddr, sizeof(clientAddr));
  connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));

  do{
    memset(msg,0x0,100);
    printf("Send message to server : ");
   
    j=0;
    while((msg[j++]=getchar())!='\n');
    msg[--j]='\0';
    send(sd, msg, strlen(msg) + 1, 0);
    printf("data sent (%s)\n", msg);   
    memset(msg,0x0,100);
    n=recv(sd, msg,MAX_MSG, 0);
    printf("Received message from server : %s\n",msg);
    
    }while(strcmp(msg,"quit"));

  printf("closing connection with the server\n");
  close(sd);
 }

