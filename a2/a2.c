/* a2.c
 *
 * CS 270.Rinker.........Seth Lunders
 * 2/17/2021..............lund4272@vandals.uidaho.edu
 *
 *  This program takes an input string and seperates it into tokens. It stores these tokens in an array of strings.
 *  It also counts the number of tokens.
 *  ---------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------
// Function declarations
// ----------------------

int makearg(char *, char ***);
int isSpace(char);
void clearInput(char[], int);

// ---------------
// Main Program
// ---------------

int main()
{
    // Create the string array and input string
    char **argv, str[] = "  This  is \t a test string. It has spaces  to demonstrate       that it \n\n works well. Here's the sample from the assignment:  \rls -l file\t";

    // Create the token counter
    int argc;

    // Count the tokens and store them to the array
    argc = makearg(str, &argv);

    // Check if there was an error during execution
    if (argc != -1)
    {
        // Print out the results value of argc and the results of makearg
        printf("There are %i tokens. They are:\n", argc);
        int printCount;
        for (printCount = 0; *(argv + printCount) != NULL; printCount++)
        {
            // Print out the tokens
            printf("%i: %s\n", printCount + 1, *(argv + printCount));
        }
    }
}

// ----------------------
// Function definitions
// ----------------------

int makearg(char *s, char ***strArr)
{
    int tokenLimit = 50;                           // Set the max number of tokens allowed to be input at once
    int tokenLengthLimit = 256;                    // Set the max length of any individual token
    *strArr = malloc(tokenLimit * sizeof(char *)); // token count limit
    char tokenIn[tokenLengthLimit];                // token character count limit

    char *tmp; // temporary string
    int i = 0; // index counter for string s
    int j = 0; // index counter for args
    int k = 0; // index counter for tokenIn

    while (isSpace(s[i]))
    {
        i++;
    } // Eliminate leading zeros

    while ((i <= strlen(s)) && (j <= tokenLimit) && (k <= tokenLengthLimit)) // Loop the length of the string
    {
        if (isSpace(s[i])) // Check for leading spaces
        {
            while (isSpace(s[i]))
            {
                i++;
            } // Eliminate spaces (won't run the first time)
            tokenIn[k] = '\0';
            tmp = strdup(tokenIn);
            *(*strArr + j) = (char *)tmp;
            // printf("setting strArr+%i to %s\n", j, (char*)tmp); // Debugging
            j++;
            k = 0;
        }
        else if (s[i])
        {
            tokenIn[k] = s[i];
            i++;
            k++;
        }
        else
        {
            return -1;
        }
    }
    if (j > tokenLimit) // If there are 
    {
        printf("Error: Input limited to %i tokens.\n", tokenLimit);
        return -1;
    }
    else if (k > tokenLengthLimit)
    {
        printf("Error: Tokens limited to %i characters.\n", tokenLengthLimit);
        return -1;
    }
    else
    {
        return j;
    }
}

void clearInput(char s[], int len) // Used to clear an array
{
    int i = 0;
    while (i < len) // Set array to null values
    {
        s[i] = '\0';
        i++;
    }
}

int isSpace(char charIn) // Checks if charIn is white space or \0
{
    if ((charIn == ' ') || (charIn == '\t') || (charIn == '\n') || (charIn == '\v') || (charIn == '\f') || (charIn == '\r') || (charIn == '\0'))
        return 1;
    else
        return 0;
}