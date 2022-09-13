#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    /* code */
    char st1[12] = "Hello";
    char st2[12] = "World!";
    char st3[12];
    int len;
    strcpy(st3, st1);
    printf("This is the result that is stored in st3: %s \n", st3);
    printf("This is the result that is stored in st1: %s \n", st1);
    len = strlen(st1);
    printf("The length of st1 is: %d", len);
    short int r;
    printf("the size of int: %d", sizeof(r));

    return 0;
}
