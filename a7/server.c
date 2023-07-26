ka
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int playerWins = 0;
int computerWins = 0;
int draws = 0;
void closeAll(int, int, int);
void whoWon(char, char);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd, playerfd, computerfd, portno;
    socklen_t clilen;
    char pChoice;
    char cChoice;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = 4500;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    if (fork() != 0)
    {
        computerfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    }
    else
    {
        execl("./computer", "./computer", NULL);
    }
    int pid = getpid();
    if (fork() != 0 && pid)
    {
        playerfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    }
    else
    {
        execl("./player", "./player", NULL);
    }
    read(computerfd, &cChoice, 1);

    if (playerfd < 0)
        error("ERROR on accept");
    n = read(playerfd, &pChoice, 1);
    if (n < 0)
        error("ERROR reading from socket");

    whoWon(pChoice, cChoice);

    closeAll(playerfd, computerfd, sockfd);
    return 0;
}

void closeAll(int pfd, int cfd, int sfd)
{
    close(pfd);
    close(cfd);
    close(sfd);
}

void whoWon(char p, char c)
{
    switch (c)
    {
    case 'r': // Rock
        switch (p)
        {
        case 'r':
            printf("You chose rock, computer chose rock, a draw!\n\n");
            ++draws;
            break;
        case 'p':
            printf("You chose paper, computer chose rock, you win!\n\n");
            ++playerWins;
            break;
        case 's':
            printf("You chose scissors, computer chose rock, computer wins!\n\n");
            ++computerWins;
            break;
        case 'q':
            printf("R: Final results: you = %i, computer = %i, draws = %i\n\n", playerWins, computerWins, draws);
            printf("R: thanks for playing!\n");
            break;
        default:
            printf("Whoops, that's an error...\n");
            break;
        }
        break;
    case 'p': // Paper
        switch (p)
        {
        case 'r':
            printf("You chose rock, computer chose paper, computer wins!\n\n");
            ++computerWins;
            break;
        case 'p':
            printf("You chose paper, computer chose paper, a draw!\n\n");
            ++draws;
            break;
        case 's':
            printf("You chose scissors, computer chose paper, you win!\n\n");
            ++playerWins;
            break;
        case 'q':
            printf("R: Final results: you = %i, computer = %i, draws = %i\n\n", playerWins, computerWins, draws);
            printf("R: thanks for playing!\n");
            break;
        default:
            printf("Whoops, that's an error...\n");
            break;
        }
        break;
    case 's': // Scissors
        switch (p)
        {
        case 'r':
            printf("You chose rock, computer chose scissors, you win!\n\n");
            ++playerWins;
            break;
        case 'p':
            printf("You chose paper, computer chose scissors, computer wins!\n\n");
            ++computerWins;
            break;
        case 's':
            printf("You chose scissors, computer chose scissors, a draw!\n\n");
            ++draws;
            break;
        case 'q':
            printf("R: Final results: you = %i, computer = %i, draws = %i\n\n", playerWins, computerWins, draws);
            printf("R: thanks for playing!\n");
            break;
        default:
            printf("Whoops, that's an error...\n");
            break;
        }
        break;
    default:
        break;
    }
}