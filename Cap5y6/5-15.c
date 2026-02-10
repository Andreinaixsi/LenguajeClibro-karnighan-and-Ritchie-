#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

/* Prototipos */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int strcmp_ignore_case(const char *, const char *);
int getline2(char *s, int lim);
void swap(void *v[], int i, int j);

int reverse = 0;
int fold = 0;

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;

    /* Manejo de argumentos por consola */
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-n") == 0)
                numeric = 1;
            else if (strcmp(argv[i], "-r") == 0)
                reverse = 1;
            else if (strcmp(argv[i], "-f") == 0)
                fold = 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        /* Selección del puntero de función para comparar */
        int (*comp)(void *, void *);

        if (numeric)
            comp = (int (*)(void *, void *))numcmp;
        else if (fold)
            comp = (int (*)(void *, void *))strcmp_ignore_case;
        else
            comp = (int (*)(void *, void *))strcmp;
        
        qsort2((void **) lineptr, 0, nlines-1, comp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

/* --- Implementación de funciones --- */

int getline2(char *s, int lim) {
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

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

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
}

void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        int cmp = (*comp)(v[i], v[left]);
        if (reverse)
            cmp = -cmp;
        if (cmp < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort2(v, left, last-1, comp);
    qsort2(v, last+1, right, comp);
}

int numcmp(const char *s1, const char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    return 0;
}

int strcmp_ignore_case(const char *s1, const char *s2) {
    for (; tolower((unsigned char)*s1) == tolower((unsigned char)*s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}