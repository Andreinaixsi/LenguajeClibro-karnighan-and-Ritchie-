#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 60

void print_file(FILE *fp, const char *filename, int *page_num) {
    int line_count = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (line_count % LINES_PER_PAGE == 0) {
            printf("\f"); // Salto de pagina
            printf("Archivo: %s\tPagina: %d\n\n", filename, ++(*page_num));
            line_count = 2;
        }
        printf("%s", buffer);
        line_count++;
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int page_num = 0;
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
        print_file(fp, argv[i], &page_num);
        fclose(fp);
    }

    return 0;
}