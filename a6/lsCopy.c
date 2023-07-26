// Seth Lunders
// Professor Rinker
// CS 270
// Assignment 6 | ls copy
// 16 April 2021

// Notes:
// 

#include <stdio.h>
#include <string.h>
// #include <fcntl.h>
// #include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include "classifier.h"

void resetRead(int *, char[], int, char *);

int main(int argc, char *argv[])
{
    DIR *dp = opendir("./");
    struct dirent *entp = readdir(dp);
    entp = readdir(dp);
    entp = readdir(dp);
    if (argc == 1)
    {
        while (entp != NULL)
        {
            printf("%s ", entp->d_name);
            entp = readdir(dp);
        }
        printf("\n");
        closedir(dp);
        return 0;
    }
    else if (!strcmp(argv[1], "-t"))
    {
        while (entp != NULL)
        {
            struct stat entStat;
            stat(entp->d_name, &entStat);
            printf("%s | accessed: %s | modified: %s | status change: %s\n", entp->d_name, ctime(&entStat.st_atim.tv_sec), ctime(&entStat.st_mtim.tv_sec), ctime(&entStat.st_ctim.tv_sec));
            entp = readdir(dp);
        }
    }
    else if (!strcmp(argv[1], "-f"))
    {
        while (entp != NULL)
        {
            printf("%s | %s\n", entp->d_name, classify(entp->d_name));
            entp = readdir(dp);
        }
        closedir(dp);
        return 0;
    } else {
        printf("usage: ./lsCopy -t | -f\n");
    }
    closedir(dp);
}