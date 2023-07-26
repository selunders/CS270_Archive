#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> /* for sockaddr_un struct */
#include <unistd.h>
#include <stdlib.h>

#define DEFAULT_PROTOCOL 0

/****************************************************************/
void writeRecipe(int);

int main()

{
  int serverFd, clientFd, serverLen, clientLen;
  struct sockaddr_un serverAddress;   /* Server address */
  struct sockaddr_un clientAddress;   /* Client address */
  struct sockaddr *serverSockAddrPtr; /* Ptr to server address */
  struct sockaddr *clientSockAddrPtr; /* Ptr to client address */

  /* Ignore death-of-child signals to prevent zombies */
  signal(SIGCHLD, SIG_IGN);

  serverSockAddrPtr = (struct sockaddr *)&serverAddress;
  serverLen = sizeof(serverAddress);

  clientSockAddrPtr = (struct sockaddr *)&clientAddress;
  clientLen = sizeof(clientAddress);

  /* Create a socket, bidirectional, default protocol */
  serverFd = socket(PF_LOCAL, SOCK_STREAM, DEFAULT_PROTOCOL);
  serverAddress.sun_family = PF_LOCAL;          /* Set domain type */
  strcpy(serverAddress.sun_path, "RPS");     /* Set name */
  unlink("RPS");                             /* Remove file if it already exists */
  bind(serverFd, serverSockAddrPtr, serverLen); /* Create file */
  listen(serverFd, 5);                          /* Maximum pending connection length */

  while (1) /* Loop forever */
  {
    /* Accept a client connection */
    clientFd = accept(serverFd, clientSockAddrPtr, &clientLen);

    if (fork() == 0) /* Create child to send recipe */
    {
      writeRecipe(clientFd);      /* Send the recipe */
      close(clientFd);            /* Close the socket */
      exit(/* EXIT_SUCCESS */ 0); /* Terminate */
    }
    else
      close(clientFd); /* Close the client descriptor */
  }
}

/****************************************************************/

void writeRecipe(int fd)
{
  static char *line1 = "spam, spam, spam, spam,";
  static char *line2 = "spam, and spam.";
  write(fd, line1, strlen(line1) + 1); /* Write first line */
  write(fd, line2, strlen(line2) + 1); /* Write second line */
}
