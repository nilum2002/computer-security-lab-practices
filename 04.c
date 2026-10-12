#include <stdio.h>
#include <string.h>


/*Explointing the pointer variable*/



void pointer_exploit(char *s)
{
    char buffer[10];
    int(*fptr)();
    fgets(buffer, sizeof(buffer), stdin);

}





int main()
{
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    pointer_exploit(str);

}