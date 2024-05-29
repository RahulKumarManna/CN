/* Sample UDP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    int sockfd, n;
    struct sockaddr_in servaddr, cliaddr;
    char sendline[1000];
    char recvline[1000];

    if (argc != 2)
    {
        printf("usage: udpcli <IP address>\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr)); // Clear the servaddr structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); // Convert IP address from string to network format
    servaddr.sin_port = htons(32000); // Set port number

    while (fgets(sendline, sizeof(sendline), stdin) != NULL)
    {
        sendto(sockfd, sendline, strlen(sendline), 0,
               (struct sockaddr *)&servaddr, sizeof(servaddr));

        n = recvfrom(sockfd, recvline, sizeof(recvline), 0, NULL, NULL);
        recvline[n] = '\0'; // Ensure null-terminated string
        fputs(recvline, stdout);
    }

    close(sockfd); // Close the socket when done

    return 0;
}
