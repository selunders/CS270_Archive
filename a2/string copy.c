#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **strs;
int makearg(char***);

int main(){
    strs = malloc(10*sizeof(char*));
    *(strs+1) = (char*)"Test";
    *(strs+3) = (char*)"Test2";
    printf("%s\n", *(strs+1));
    printf("%s\n", *(strs+3));

    fun(&strs);
    printf("%s\n", *(strs+1));
    printf("%s\n", *(strs+3));
}

int makearg(char *** strArr){
    // printf("Test\n");
    *(*strArr+1) = (char*)"Test4";
    *(*strArr+3) = (char*)"Test3";
}