#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESPAGE 60
#define MAXLINE 1000

void printfile(FILE *fp, const char *title, int *pageno) {
    char line[MAXLINE];
    int lineno = 0;

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (lineno % LINESPAGE == 0) {
            printf("\f"); // Salto de pagina (form feed)
            printf("%s - Pagina %d\n\n", title, ++(*pageno));
            lineno += 2;
        }
        printf("%s", line);
        lineno++;
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int pageno = 0;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s archivo1 archivo2 ...\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "No se puede abrir %s\n", argv[i]);
            continue;
        }
        printfile(fp, argv[i], &pageno);
        fclose(fp);
    }

    return 0;
}