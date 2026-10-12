#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


void vulnarable_func(char *input)
{
    char buffer[10];
    /* Unsafe copy: no bounds checking, can overflow buffer */
    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);

}


void safe_func(char *input)
{
    /*
    Ensure the buffer over flow
    */
    char buffer[10];
    uint64_t canary = 0xDEADBEEFCAFEBABE;
    strcpy(buffer, input);

    if (canary != 0xDEADBEEFCAFEBABE) {
        printf("Stack smashing detected!\n");
        exit(1);
    }

    printf("Buffer content: %s\n", buffer);


}

void bound_check_func(char *input)
{
    /*
    Ensure the allocated memory is not exceeded
    */
    char buffer[10];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null termination
}


void tag(char *input)
{
    int tag = 0xABCDEF;
    char buffer[10];

    // ensure the input within the buffer size

    /*
    So the buffer is allocated with a size of 10 bytes, and the tag variable is
    allocated with a size of 4 bytes(int).


    +-----------------------------------------------------------------+
    |              Buffer  (6)                               | Tag(4) |
    |                                                        |        |
    +-----------------------------------------------------------------+
    
    So the string should be in 6 bytes = Buffer(10)-Tag(4) = 6 bytes
    */

    if (strlen(input) < sizeof(buffer)-sizeof(tag))
    {
        strncpy(buffer, input, sizeof(buffer) - sizeof(tag));
        buffer[sizeof(buffer) - sizeof(tag) - 1 ] = '\0'; // Ensure null termination
        memcpy(buffer + sizeof(buffer) - sizeof(tag), &tag, sizeof(tag));
    }else
    {
        printf("Input is too long for the buffer\n");
    }
}



// int main()
// {
//     vulnarable_func("This is a very long string that will overflow the buffer");

//     return 0;
// }

/* Canry checked function*/

int main(int argc, char *argv[])
{

    // Canary checked function
    if (argc < 2 )
    {
        return 1;
    }
    safe_func(argv[1]);

    // bound check function
    bound_check_func(argv[1]);

    // tag function
    tag(argv[1]);
}

/*
Compile options for this :
    1. gcc -o test test.c : this is the normal compilation without any security flags
    2. gcc -fstack-protector-all -o test test.c : this is the compilation with stack protector enabled essentianly for every function

*/