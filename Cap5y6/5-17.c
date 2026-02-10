#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
int field = 0;

// Prototipos
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *));
int getline2(char *s, int lim);

char *field_of_line(char *line) {
    char *p = line;
    int col = 1;
    while (*p && col < field) {
        if (*p == ' ' || *p == '\t') {
            while (*p == ' ' || *p == '\t') p++;
            col++;
        } else {
            p++;
        }
    }
    return p;
}

int strcmp_field(const char *s1, const char *s2) {
    return strcmp(field_of_line((char *)s1), field_of_line((char *)s2));
}

int main(int argc, char *argv[]) {
    int nlines;
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'k') {
        field = atoi(&argv[1][2]);
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort2((void **) lineptr, 0, nlines-1,
               (int (*)(void *, void *))(field ? strcmp_field : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
}

// IMPLEMENTACIONES (Lo que te faltaba)

int getline2(char *s, int lim) {
    int c, i;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) s[i] = c;
    if (c == '\n') s[i++] = c;
    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = getline2(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL) return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) printf("%s\n", *lineptr++);
}

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right) return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0) swap(v, ++last, i);
    swap(v, left, last);
    qsort2(v, left, last-1, comp);
    qsort2(v, last+1, right, comp);
}

void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}