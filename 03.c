#include <stdio.h>
#include <stdbool.h>


/* Variable overflow exploiting an adjacent variable */

void var_overflow(void) 
{
    char buffer[10];
    bool is_authenticated = false;

    /* Unsafe read: overflowing buffer can overwrite is_authenticated */
    scanf("%s", buffer);

    if (is_authenticated) {
        printf("You are authenticated\n");
    } else {
        printf("You are not authenticated\n");
    }
}

/*
Run with the no stck protector and executable stack options to demonstrate the vulnerability

run this use :
gcc -O0 -fno-stack-protector -z execstack -no-pie 03.c -o out
./out
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
You are authenticated
Segmentation fault         (core dumped) ./out

*/


int main(void) 
{
    var_overflow();
    return 0;
}
