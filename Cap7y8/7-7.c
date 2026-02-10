#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* ffind: busca un patrón en un archivo o entrada estándar */
void ffind(FILE *fp, char *fname, char *patron) {
    char linea[MAXLINE];
    int lineno = 0;

    while (fgets(linea, MAXLINE, fp) != NULL) {
        lineno++;
        if (strstr(linea, patron) != NULL) {
            if (fname) 
                printf("%s:", fname);
            printf("%d:%s", lineno, linea);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc < 2) {
        printf("Uso: 7-7 patron [archivo1 archivo2 ...]\n");
        return 1;
    }

    char *patron = argv[1];

    if (argc == 2) {
        /* Si no hay archivos, busca en la entrada estándar (teclado) */
        ffind(stdin, NULL, patron);
    } else {
        /* Busca en cada archivo proporcionado */
        for (int i = 2; i < argc; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "7-7: no se puede abrir %s\n", argv[i]);
                continue;
            }
            ffind(fp, argv[i], patron);
            fclose(fp);
        }
    }
    return 0;
}