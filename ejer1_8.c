#include <stdio.h>

/* Cuenta líneas nuevas, espacios en blanco y tabuladores */
int main() {
    int c, nl = 0, nt = 0, nE = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n')
            ++nl;
        else if (c == '\t')
            ++nt;
        else if (c == ' ')
            ++nE;
    }

    printf("\nHay %d lineas nuevas, %d tabuladores y %d espacios en blanco\n", nl, nt, nE);
    return 0;
}