#include <stdio.h>
#include <time.h>

void getSecond(unsigned long *p);

int main(int argc, char const *argv[])
{
    unsigned long t;
    getSecond(&t);
    printf("The current time is %ld\n", t);

    /* code */
    return 0;
}
void getSecond(unsigned long *p){
    *p = time ( NULL );
    return;
}