#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000

/* Versión de getline para que funcione en Windows */
int mi_getline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') s[i++] = c;
    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = mi_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int main() {
    char *lineptr[10];
    printf("Escribe lineas (Ctrl+Z para terminar):\n");
    int n = readlines(lineptr, 10);
    printf("\nLineas leidas: %d\n", n);
    return 0;
}