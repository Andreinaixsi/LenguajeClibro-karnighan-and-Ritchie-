#include <stdio.h>

#define IN  1   /* dentro de una palabra */
#define OUT 0   /* fuera de una palabra */

/* imprime cada palabra en una línea nueva */
int main(void) {
    int c, state;

    state = OUT;  // al principio, estamos fuera de una palabra

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                // fin de una palabra → salto de línea
                putchar('\n');
                state = OUT;
            }
        } else {
            // estamos dentro de una palabra
            state = IN;
            putchar(c);
        }
    }

    return 0;
}
