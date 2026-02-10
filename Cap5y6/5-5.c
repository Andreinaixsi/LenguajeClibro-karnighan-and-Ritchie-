#include <stdio.h>

void mi_strncpy(char *s, char *t, int n) {
    while (n-- > 0 && (*s++ = *t++))
        ;
    while (n-- > 0)
        *s++ = '\0';
}

void mi_strncat(char *s, char *t, int n) {
    while (*s) s++;
    while (n-- > 0 && (*s++ = *t++))
        ;
    *s = '\0';
}

int mi_strncmp(char *s, char *t, int n) {
    for (; n > 0 && *s == *t; s++, t++, n--)
        if (*s == '\0' || n == 1) return 0;
    return *s - *t;
}

int main() {
    char destino[50] = "Hola ";
    mi_strncat(destino, "Mundo", 3);
    printf("Resultado strncat: %s\n", destino); // Imprime "Hola Mun"
    return 0;
}