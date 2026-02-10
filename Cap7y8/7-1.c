#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int c;
    int (*convert)(int) = NULL;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s [-upper | -lower]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-upper") == 0)
        convert = toupper;
    else if (strcmp(argv[1], "-lower") == 0)
        convert = tolower;
    else {
        fprintf(stderr, "Opción no válida: %s\n", argv[1]);
        return 1;
    }

    while ((c = getchar()) != EOF)
        putchar(convert(c));

    return 0;
}