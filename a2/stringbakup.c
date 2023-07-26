#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **strs;
int makearg(char*, char***);
char* temp = "test";
char* tmp;

int main(){
    strs = malloc(30*sizeof(char*));
    *(strs+1) = (char*)"Test";
    *(strs+3) = (char*)"Test2";
    printf("%s\n", *(strs+1));
    printf("%s\n", *(strs+3));

    makearg(temp, &strs);
    printf("%s\n", *(strs+1));
    printf("%s\n", *(strs+3));
}

int makearg(char *s, char ***strArr){
    // printf("Test\n");
    tmp = "test";
    *(*strArr+1) = (char*) tmp;

    // *(*strArr+1) = (char*)"Test3";
    tmp = "test2";
    *(*strArr+3) = (char*) tmp;
    // *(*strArr+3) = (char*)"Test4";
}