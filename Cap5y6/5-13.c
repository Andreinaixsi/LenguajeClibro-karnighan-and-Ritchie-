#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define DEFAULT_N 10

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int start);

int main(int argc, char *argv[]) {
    int n = DEFAULT_N;
    
    if (argc > 1 && argv[1][0] == '-') {
        n = atoi(&argv[1][1]);
        if (n <= 0) n = DEFAULT_N;
    }
    
    int total_lines = readlines(lineptr, MAXLINES);
    if (total_lines < 0) {
        printf("Error: demasiadas líneas\n");
        return 1;
    }
    
    int start = (total_lines > n) ? total_lines - n : 0;
    writelines(lineptr, total_lines, start);
    
    return 0;
}

int getline(char *s, int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];
    
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
            return -1;
        else {
            line[len] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines, int start) {
    for (int i = start; i < nlines; i++)
        printf("%s", lineptr[i]);
}