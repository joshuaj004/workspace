#include <stdio.h>

int main(void) {
	int jumpVal = 1000;
    while (jumpVal != 0) {
        printf("%d\n", jumpVal);
        jumpVal = jumpVal / 2;
    }
    printf("OUT: %d\n", jumpVal);
	return 0;
}

