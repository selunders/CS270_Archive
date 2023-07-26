#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char c;
    portno = 4500;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    do
    {
        printf("Y: Enter your guess (r, s, p) or q to quit: ");
        scanf(" %c", &c);
        // printf("\n");
    } while (c != 'r' && c != 's' && c != 'p' && c != 'q');
    // printf("\n");
    n = write(sockfd, &c, 1);
    if (n < 0)
        error("ERROR writing to socket");
    c = '\0';
    n = read(sockfd, &c, 1);
    if (n < 0)
        error("ERROR reading from socket");
    // printf("%c\n", &c);
    close(sockfd);
    return 0;
}