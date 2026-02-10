#include <stdio.h>
#include <ctype.h>

// Versión 1: ahorro de espacio (tabla)
int isupper_space(int c) {
    static const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; upper[i]; i++)
        if (c == upper[i])
            return 1;
    return 0;
}

// Versión 2: ahorro de tiempo (macro)
#define isupper_time(c) ((c) >= 'A' && (c) <= 'Z')

int main() {
    char c = 'A';
    printf("isupper_space('%c') = %d\n", c, isupper_space(c));
    printf("isupper_time('%c') = %d\n", c, isupper_time(c));
    printf("isupper('%c') = %d\n", c, isupper(c));
    return 0;
}