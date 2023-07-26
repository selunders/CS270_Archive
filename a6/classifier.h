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
int i = 0;
void resetRead(int *, char[], int, char *); // Resets the read command to the start of the file. There may be a simpler way to do this.
char* classify(char*);

char* classify(char* fileName)
{
    // Check if file was given
    // if (fileName == NULL)
    // {
    //     printf("No file given.\n");
    //     return "";
    // }
    // Open file
    int fileIn = open(fileName, O_RDONLY);
    // Check for error opening file
    if (fileIn == -1)
    {
        // printf("Unable to open: \'%s\'\n", fileName);
        close(fileIn);
        return "unable to read";
    }

    // ---------------------
    // Check for empty file
    // ---------------------

    endReached = read(fileIn, &c, 1);
    if (endReached == 0)
    {
        // printf("%s is an empty file.\n", fileName);
        return "empty file";
    }
    if(endReached == -1){
        return "directory"; // for use with lsCopy.c
    }
    // ---------------
    //  Check for ELF
    // ---------------
    // endReached = read(fileIn, &c, 1);
    if (c == 127)
    {
        // printf("%s could be an ELF file...\n", fileName);
        read(fileIn, &c, 1);
        if (c == 'E')
        {
            read(fileIn, &c, 1);
            if (c == 'L')
            {
                read(fileIn, &c, 1);
                if (c == 'F')
                {
                    resetRead(&fileIn, buff, arrSize, fileName);
                    // Get the 17th byte, which identifies the ELF type

                    for (i = 0; i < 17; i++)
                    {
                        read(fileIn, &c, 1);
                    }

                    switch (c)
                    {
                    case 0:
                        // printf("%s is an ELF file without a file type.\n", fileName);
                        close(fileIn);
                        return "ELF file without type";
                        break;
                    case 1:
                        // printf("%s is an ELF Relocatable file.\n", fileName);
                        close(fileIn);
                        return "ELF Relocatable file";
                        break;
                    case 2:
                        // printf("%s is an ELF Executable file.\n", fileName);
                        close(fileIn);
                        return "ELF Executable file";
                        break;
                    case 3:
                        // printf("%s is an ELF Shared Object file.\n", fileName);
                        close(fileIn);
                        return "ELF Shared Object file";
                        break;
                    case 4:
                        // printf("%s is an ELF Core file.\n", fileName);
                        close(fileIn);
                        return "ELF Core file";
                        break;
                    default:
                        // printf("%s is an unknown ELF file.\n", fileName);
                        close(fileIn);
                        return "unknown ELF file";
                        break;
                    }
                }
            }
        }
    }
    resetRead(&fileIn, buff, arrSize, fileName);

    // -----------------------
    // Check for ps/pdf files
    // -----------------------

    // Check first line of file

    for (i = 0; c != '\n' && i < arrSize; i++)
    {
        read(fileIn, &c, 1);
        buff[i] = c;
    }
    // printf("%s\n", buff);
    // Check if PDF file
    if (strstr(buff, "%PDF-1."))
    {
        // printf("%s is a PDF file\n", fileName);
        // printf("Beep\n");
        close(fileIn);
        return "PDF file";
    }
    else // check if ps file
        if (strstr(buff, "%!PS-Adobe"))
    {
        // printf("%s is a postscript file\n", fileName);
        close(fileIn);
        return "PostScript file";
    }
    // If not a PDF or ps, then check if it's a DOS ASCII file
    resetRead(&fileIn, buff, arrSize, fileName);
    // For some reason my program is getting a seg fault if it reads more than 4000 characters.
    buff[0] = '\0';
    for (i = 0; endReached != 0; i++)
    {
        endReached = read(fileIn, &c, 1);
        // printf("%c", c);
        buff[1] = c;
        // Check for any non-ASCII characters
        if (!(c <= 127 && c >= 0))
        {
            // printf("%s is a binary file.\n", fileName);
            close(fileIn);
            return "unknown binary file";
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
        close(fileIn);
        return "DOS ASCII file";
    }
    else
    {
        close(fileIn);
        return "ASCII text file";
    }
}

// Lets you start reading from the start of the file again, and reset the buffer
void resetRead(int *fd, char arr[], int arrlen, char *fName)
{
    close(*fd);
    int i = 0;
    *fd = open(fName, O_RDONLY);
    for (i = 0; i < arrlen; i++)
    {
        arr[i] = '\0';
    }
}