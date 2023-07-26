#include <stdio.h>

int main(int argc, char* argv[]){
    printf("The number of arguments: %i\n", (argc-1));
    printf("The first argument is: %s\n", argv[1]);
}