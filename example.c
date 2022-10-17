#include <stdio.h>
int main(){
	char s1[80];

char s2[80];
printf("Enter first word:\n");
printf("This is a test");
fgets(s1, 80, stdin);
printf("Enter second word:\n");
fgets(s2, 80, stdin);
if (s1 == s2)
    printf("Words are the same\n");
else
    printf("Words are different\n");


}

