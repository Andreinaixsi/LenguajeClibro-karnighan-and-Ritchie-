#include <stdio.h>
#include <ctype.h>

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getchar()) && *w != '_') {
            ungetc(*w, stdin);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

int main() {
    char palabra[100];
    printf("Escribe algo: ");
    getword(palabra, 100);
    printf("Primera palabra: %s\n", palabra);
    return 0;
}