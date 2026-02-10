#include <ctype.h>
#include <stdio.h>

// Función para validar caracteres de directorio
int isdirchar(int c) {
    return isalnum(c) || c == ' ' || c == '\t';
}

// Función de comparación
int strcmp_directory(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        while (*s1 && !isdirchar(*s1)) s1++;
        while (*s2 && !isdirchar(*s2)) s2++;

        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        if (*s1) {
            s1++;
            s2++;
        }
    }
    return *s1 - *s2;
}

// Punto de entrada para evitar error de WinMain/ld
int main() {
    char s1[] = "Hola, mundo!";
    char s2[] = "Hola mundo";
    
    printf("Resultado: %d\n", strcmp_directory(s1, s2));
    return 0;
}