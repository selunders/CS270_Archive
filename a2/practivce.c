#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **ints;
int fun(int***);

int main(){
    ints = malloc(10*sizeof(int*));
    *(ints+1) = 2;
    *(ints+3) = 4;
    printf("%i\n", *(ints+1));
    printf("%i\n", *(ints+3));

    fun(&ints);
    printf("%i\n", *(ints+1));
    printf("%i\n", *(ints+3));
}

int fun(int *** intArr){
    printf("Test\n");
    *(*intArr+1) = 1;
    *(*intArr+3) = 1;
}