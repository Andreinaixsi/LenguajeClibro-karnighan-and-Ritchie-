#include <stdio.h>

/* Función que comprueba si t ocurre al final de s */
int strend(char *s, char *t) {
    char *start_s = s;
    char *start_t = t;

    while (*s) s++; // Mover s al final
    while (*t) t++; // Mover t al final

    // Comparar de atrás hacia adelante
    while (t > start_t && s > start_s && *s == *t) {
        s--;
        t--;
    }

    return (t == start_t && *s == *t) ? 1 : 0;
}

int main() {
    char *s1 = "universidad";
    char *t1 = "dad";
    
    if (strend(s1, t1)) 
        printf("EXITO: '%s' termina en '%s'\n", s1, t1);
    else 
        printf("No coinciden.\n");

    return 0;
}