#include <stdio.h>

/* Code that is not performing range checking */

void noRangeCheck(void) 
{
    int buffer[5] = {1, 2, 3, 4, 5};

    /* Out of bounds access: loop runs to 9 but array only holds 5 */
    for (int i = 0; i < 10; i++) {
        buffer[i] = i * 2;
    }
}

int main(void) 
{
    noRangeCheck();
    return 0;
}
