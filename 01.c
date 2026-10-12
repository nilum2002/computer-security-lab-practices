#include <stdio.h>
#include <string.h>

/* Stack Smashing */

void stackSmash(char *str)
{
    char buffer[64];
    /* Unsafe copy: no bounds checking, can overflow buffer */
    strcpy(buffer, str);

}

int main(void) 
{
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    stackSmash(str);
    return 0;
}
