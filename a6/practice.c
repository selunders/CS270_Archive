#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    int lineCount = 1; // Start at 1 for the last line
    char c;
    while (read(fd, &c, 1))
    {
        if (c == '\n')
            lineCount++;
    }
    printf("File %s has %i lines\n", argv[1], lineCount);
}