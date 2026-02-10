#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    int lineno = 1;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s archivo1 archivo2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    if (!fp1 || !fp2) {
        fprintf(stderr, "Error abriendo archivos\n");
        return 1;
    }

    while (fgets(line1, MAXLINE, fp1) && fgets(line2, MAXLINE, fp2)) {
        if (strcmp(line1, line2) != 0) {
            printf("Diferencia en línea %d:\n", lineno);
            printf("< %s", line1);
            printf("> %s", line2);
            fclose(fp1); fclose(fp2);
            return 0;
        }
        lineno++;
    }

    if (fgets(line1, MAXLINE, fp1))
        printf("Archivo 1 es más largo desde línea %d\n", lineno);
    else if (fgets(line2, MAXLINE, fp2))
        printf("Archivo 2 es más largo desde línea %d\n", lineno);
    else
        printf("Los archivos son idénticos.\n");

    fclose(fp1); fclose(fp2);
    return 0;
}