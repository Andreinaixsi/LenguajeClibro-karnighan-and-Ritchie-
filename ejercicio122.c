#include <stdio.h>

#define MAXCOL 40    // Máximo de columnas antes de doblar
#define MAXLINE 1000 // Máximo tamaño de línea

void fold(char line[], int maxcol);

int main(void) {
    int c, i = 0;
    char line[MAXLINE];

    while ((c = getchar()) != EOF) {
        line[i++] = c;

        // Si llegamos al límite o encontramos un salto de línea
        if (c == '\n' || i >= MAXLINE - 1) {
            line[i] = '\0';
            fold(line, MAXCOL);
            i = 0;
        }
    }

    // Si queda texto sin salto final, también procesarlo
    if (i > 0) {
        line[i] = '\0';
        fold(line, MAXCOL);
    }

    return 0;
}

/*
 * fold: divide líneas largas en varias más cortas
 * justo después del último espacio o tab antes de la columna maxcol
 */
void fold(char line[], int maxcol) {
    int i = 0, col = 0, last_blank = -1;

    while (line[i] != '\0') {
        if (line[i] == ' ' || line[i] == '\t')
            last_blank = i;

        putchar(line[i]);
        col++;

        if (col >= maxcol) {
            if (last_blank != -1) {
                putchar('\n');
                // Saltar a la posición después del último espacio
                i = last_blank + 1;
                // Saltar espacios o tabs adicionales
                while (line[i] == ' ' || line[i] == '\t')
                    i++;
                col = 0;
                last_blank = -1;
                continue;
            } else {
                // No había espacios antes, cortamos a la fuerza
                putchar('\n');
                col = 0;
            }
        }
        i++;
    }
}
