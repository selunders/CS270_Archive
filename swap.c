/* swap.c */
extern int buf[]; //declaration rather than definition

int *bufp0 = &buf[0]; //initialization
int *bufp1;

void swap()
    {
        int temp;

        bufp1 = &buf[1];
        temp = *bufp0;
        *bufp0 = *bufp1;
        *bufp1 = temp;
    }