#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORTNUM 50500
#define BUFLEN 80

int main(int argc, char **argv)
{
    struct sockaddr_in addr;
    int sockfd;
    char buf[BUFLEN];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORTNUM);

    
    connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));

    sprintf(buf, "%d", getpid());
    send(sockfd, buf, strlen(buf) + 1, 0);
    recv(sockfd, &buf, BUFLEN, 0);

    printf("received: %s \n", buf);
    close(sockfd);
}