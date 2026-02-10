#include <stdio.h>
#include <ctype.h> // Necesario para isspace e isdigit

int atoi2(char *s) {
    int n, sign;
    while (isspace(*s)) s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

int main() {
    char *texto = "  -1234";
    printf("Texto: %s -> Entero: %d\n", texto, atoi2(texto));
    return 0;
}