/* a2.c
 *
 * CS 270.Rinker.........Seth Lunders
 * 2/17/2021..............lund4272@vandals.uidaho.edu
 *
 *
 * 
 * 
 *-------------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int makearg(char *, char ***);

int isSpace(char);
void clearInput(char[]);

int main()
{
    // Create the 
    char **argv, str[]="  This  is \t a test string. It has spaces  to demonstrate  it \n\n works well.   \rls -l file";
 
    int argc;
 
    argc = makearg(str, &argv);
 
    // Print out the tokens

    for (int i = 0; *(argv + i) != NULL; i++)
    {
        printf("%i: %s\n", i, *(argv + i));
    }
}

int makearg(char *s, char ***strArr)
{
    *strArr = malloc(50 * sizeof(char *)); // Token limit
    char tokenIn[256]; // Token length limit

    char *tmp;
    int i = 0; // index counter for string s
    int j = 0; // index counter for args
    int k = 0; // index counter for tokenIn
    
    while(isSpace(s[i])){i++;} // Eliminate leading zeros

    while (i <= strlen(s)) // Loop the length of the string
    {
        if (isSpace(s[i])) // Check for leading spaces
        {
            while(isSpace(s[i])){i++;} // Eliminate spaces (won't run the first time)
                tokenIn[k] = '\0';
                tmp = strdup(tokenIn);
                clearInput(tokenIn);
                *(*strArr + j) = (char *)tmp;
                // printf("setting strArr+%i to %s\n", j, (char*)tmp); // Debugging
                j++;
                k = 0;
        }
        else
        {
            tokenIn[k] = s[i];
            i++;
            k++;
        }
    }
    clearInput(tokenIn);
    return j;
}

void clearInput(char s[]) // Used to clear the input array
{
    int i = 0;
    while (i < 256) // Set array to null values
    {
        s[i] = '\0';
        i++;
    }
}

int isSpace(char charIn) // Checks if charIn is white space
{
    if ((charIn == ' ') || (charIn == '\t') || (charIn == '\n') || (charIn == '\v') || (charIn == '\f') || (charIn == '\r') || (charIn == '\0'))
        return 1;
    else
        return 0;
}