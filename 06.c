#include <stdio.h>
/* Code that is not performing range checking */

void noRangeCheck(int *src, int count) {
    int buffer[5];

    /* No check that count <= 5: writes past the end of buffer */
    for (int i = 0; i < count; i++) {
        buffer[i] = src[i];
    }

    for (int i = 0; i < count; i++) {
        printf("buffer[%d] = %d\n", i, buffer[i]);
    }
}

int main(void) {
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    setvbuf(stdout, NULL, _IONBF, 0); /* unbuffered so output shows before the crash */

    /* Copies 10 ints into a 5-int buffer */
    noRangeCheck(data, 10);
    return 0;
}
