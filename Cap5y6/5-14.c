#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

/* Prototipos de funciones */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int getline2(char *s, int lim);
void swap(void *v[], int i, int j);

int reverse = 0; // Variable global para el orden inverso

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;

    /* Análisis de argumentos de línea de comandos */
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-n") == 0)
                numeric = 1;
            if (strcmp(argv[i], "-r") == 0)
                reverse = 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        /* Llamada corregida a qsort2 */
        qsort2((void **) lineptr, 0, nlines-1,
               (int (*)(void *, void *))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* Lee líneas de la entrada estándar */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = getline2(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
            return -1;
        else {
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* Escribe las líneas en la salida estándar */
void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
}

/* Implementación de getline para leer caracteres */
int getline2(char *s, int lim) {
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* Intercambia dos elementos de un arreglo de punteros */
void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* Algoritmo Quicksort personalizado */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    
    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        int cmp = (*comp)(v[i], v[left]);
        
        /* Aplicar lógica de reversa si se pasó el flag -r */
        if (reverse)
            cmp = -cmp;

        if (cmp < 0)
            swap(v, ++last, i);
    }
    
    swap(v, left, last);
    /* Llamadas recursivas corregidas a qsort2 */
    qsort2(v, left, last - 1, comp);
    qsort2(v, last + 1, right, comp);
}

/* Compara dos strings como números */
int numcmp(const char *s1, const char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    return 0;
}