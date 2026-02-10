#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // Necesario para malloc y free

#define MAXWORD 100
#define MAXHIST 15

struct word {
    char *palabra;
    int count;
};

int getword(char *, int);
void addword(struct word *, char *, int *);

int main() {
    char word[MAXWORD];
    struct word palabras[100];
    int n = 0;

    // Se requiere la implementación de getword para que el bucle funcione
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            addword(palabras, word, &n);
    }

    for (int i = 0; i < n; i++) {
        printf("%15s | ", palabras[i].palabra);
        for (int j = 0; j < palabras[i].count && j < MAXHIST; j++)
            printf("*");
        printf("\n");
        // Opcional: liberar memoria si se usó malloc en addword
        free(palabras[i].palabra);
    }
    return 0;
}

// IMPLEMENTACIONES DE LAS FUNCIONES

void addword(struct word *palabras, char *w, int *n) {
    for (int i = 0; i < *n; i++) {
        if (strcmp(palabras[i].palabra, w) == 0) {
            palabras[i].count++;
            return;
        }
    }
    // Si la palabra es nueva, se agrega al arreglo
    palabras[*n].palabra = strdup(w); 
    palabras[*n].count = 1;
    (*n)++;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar())); // Salta espacios en blanco

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    }
    *w = '\0';
    return word[0];
}