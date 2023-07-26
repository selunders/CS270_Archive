// Seth Lunders
// Professor Rinker
// CS 270
// Assignment 5 | File classifier
// 12 April 2021

// Notes:
//      The CS server uses the C89 standard I believe, instead of C99. C89 doesn't support initializing a variable in a for loop,
//        so I changed this to a c++ file to compile with g++, which does have this support.
//      Also, on my own machine, gcc and g++ create an executable shared object file by default, unless I pass in the '-no-pie' flag.
//        This doesn't seem to be necessary on the CS server.

// *** I ran the program on my folder of test files, the output is listed at the bottom of this source code, and in the file output.txt.

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

char c;                                     // Store the current character from the file
char lagC;                                  // For storing the previous character
int arrSize = 512;                          // Only needed for reading the first line
char buff[512];                             // Only needed for reading the first line
int endReached = 1;                         // Checks for the end of the file
int DOSFlag = -1;                           // For checking if the file is DOS ASCII or just ASCII
void resetRead(int *, char[], int, char *); // Resets the read command to the start of the file. There may be a simpler way to do this.

// void beep(int); // For quick debugging

int main(int argc, char *argv[])
{
    // Check if file was given
    if (argv[1] == NULL)
    {
        printf("No file given.\n");
        return -1;
    }
    // Open file
    int fileIn = open(argv[1], O_RDONLY);
    // Check for error opening file
    if (fileIn == -1)
    {
        printf("Unable to open: \'%s\'\n", argv[1]);
        close(fileIn);
        return -1;
    }

    // ---------------------
    // Check for empty file
    // ---------------------

    endReached = read(fileIn, &c, 1);
    if (endReached == 0)
    {
        printf("%s is an empty file.\n", argv[1]);
        return 0;
    }
    // resetRead(&fileIn, buff, arrSize, argv[1]);
    // ---------------
    //  Check for ELF
    // ---------------
    // endReached = read(fileIn, &c, 1);
    if (c == 127)
    {
        // printf("%s could be an ELF file...\n", argv[1]);
        read(fileIn, &c, 1);
        if (c == 'E')
        {
            read(fileIn, &c, 1);
            if (c == 'L')
            {
                read(fileIn, &c, 1);
                if (c == 'F')
                {
                    resetRead(&fileIn, buff, arrSize, argv[1]);
                    // Get the 17th byte, which identifies the ELF type

                    for (int i = 0; i < 17; i++)
                    {
                        read(fileIn, &c, 1);
                    }

                    switch (c)
                    {
                    case 0:
                        printf("%s is an ELF file without a file type.\n", argv[1]);
                        close(fileIn);
                        return 0;
                        break;
                    case 1:
                        printf("%s is an ELF Relocatable file.\n", argv[1]);
                        close(fileIn);
                        return 0;
                        break;
                    case 2:
                        printf("%s is an ELF Executable file.\n", argv[1]);
                        close(fileIn);
                        return 0;
                        break;
                    case 3:
                        printf("%s is an ELF Shared Object file.\n", argv[1]);
                        close(fileIn);
                        return 0;
                        break;
                    case 4:
                        printf("%s is an ELF Core file.\n", argv[1]);
                        close(fileIn);
                        return 0;
                        break;
                    default:
                        printf("%s is an unknown ELF file.\n", argv[1]);
                        close(fileIn);
                        return 0;
                        break;
                    }
                }
            }
        }
    }
    resetRead(&fileIn, buff, arrSize, argv[1]);

    // -----------------------
    // Check for ps/pdf files
    // -----------------------

    // Check first line of file

    for (int i = 0; c != '\n' && i < arrSize; i++)
    {
        read(fileIn, &c, 1);
        buff[i] = c;
    }
    printf("%s\n", buff);
    // Check if PDF file
    if (strstr(buff, "%PDF-1."))
    {
        printf("%s is a PDF file\n", argv[1]);
        close(fileIn);
        return 0;
    }
    else // check if ps file
        if (strstr(buff, "%!PS-Adobe"))
    {
        printf("%s is a postscript file\n", argv[1]);
        close(fileIn);
        return 0;
    }
    // If not a PDF or ps, then check if it's a DOS ASCII file
    resetRead(&fileIn, buff, arrSize, argv[1]);
    // For some reason my program is getting a seg fault if it reads more than 4000 characters.
    buff[0] = '\0';
    for (int i = 0; endReached != 0; i++)
    {
        endReached = read(fileIn, &c, 1);
        // printf("%c", c);
        buff[1] = c;
        // Check for any non-ASCII characters
        if (!(c <= 127 && c >= 0))
        {
            printf("%s is a binary file.\n", argv[1]);
            return 0;
        }
        lagC = buff[0];
        // printf("%c", buff[i]);
        if (c == '\n') // Check for new line
        {
            if (lagC == '\r') // Check for \r\n
            {
                if (DOSFlag != 0) // Starts at -1, so if it's at zero the file is already disqualified.
                    DOSFlag = 1;
            }
            else if (DOSFlag == 1)
            {
                DOSFlag = 0;
            }
        }
        buff[0] = buff[1];
    }
    if (DOSFlag == 1)
    {
        printf("%s is a DOS ASCII file.\n", argv[1]);
        close(fileIn);
        return 0;
    }
    else
    {
        printf("%s is a 'regular' ASCII file.\n", argv[1]);
        close(fileIn);
        return 0;
    }
}

// Lets you start reading from the start of the file again, and reset the buffer
void resetRead(int *fd, char arr[], int arrlen, char *fName)
{
    close(*fd);
    *fd = open(fName, O_RDONLY);
    for (int i = 0; i < arrlen; i++)
    {
        arr[i] = '\0';
    }
}

// void beep(int n)
// {
//     printf("beep %i\n", n);
// }


// Output when running on my test files:
/*

for i in *;do ./a.out "$i";done > output.txt

output.txt:
    a.out is an ELF Executable file.
    assign5s21.pdf is a PDF file
    classifier.cpp is a 'regular' ASCII file.
    classifier.o is an ELF Relocatable file.
    cregion.ps is a postscript file
    DOSASCII.txt is a DOS ASCII file.
    empty.txt is an empty file.
    nonASCII.txt is a binary file.
    output.txt is a 'regular' ASCII file.
    regularASCII.txt is a 'regular' ASCII file.
    sample.bin is a binary file.

*/