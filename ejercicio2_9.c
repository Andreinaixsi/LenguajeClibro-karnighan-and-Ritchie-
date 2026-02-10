#include <stdio.h>

int bitcount(unsigned x);

int main() {
    printf("%d\n", 18);
    printf("%d\n", bitcount(18));
    return 0;
}


int bitcount(unsigned x) {
    int b;
    for (b = 0; x != 0; b++)
        x &= (x - 1);
    return b;
}