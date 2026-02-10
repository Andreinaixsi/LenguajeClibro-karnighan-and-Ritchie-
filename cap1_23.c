#include <stdio.h>

int main(void) {
    int c, d;
    int state = 0; // 0 normal, 1 comentario, 2 cadena, 3 caracter

    while ((c = getchar()) != EOF) {
        if (state == 0) {
            if (c == '/') {
                d = getchar();
                if (d == '*') state = 1;
                else if (d == '/') { while ((c = getchar()) != '\n' && c != EOF); putchar('\n'); }
                else { putchar(c); putchar(d); }
            } else if (c == '"') { state = 2; putchar(c); }
            else if (c == '\'') { state = 3; putchar(c); }
            else putchar(c);
        } else if (state == 1) { // comentario
            if (c == '*') { d = getchar(); if (d == '/') state = 0; else ungetc(d, stdin); }
        } else if (state == 2) { // cadena
            putchar(c);
            if (c == '\\') { c = getchar(); putchar(c); }
            else if (c == '"') state = 0;
        } else if (state == 3) { // caracter
            putchar(c);
            if (c == '\\') { c = getchar(); putchar(c); }
            else if (c == '\'') state = 0;
        }
    }
    return 0;
}
