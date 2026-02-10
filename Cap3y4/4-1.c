/*
 * Ejercicio 4-1: Escriba la función strrindex(s, t) que regresa la posición
 * de la t más a la derecha en s, o -1 si no existe ninguna.
 */

#include <stdio.h>
#include <string.h>

/* strrindex: regresa el índice de la t más a la derecha en s, o -1 */
int strrindex(char s[], char t[])
{
    int i, j, k;
    int pos = -1; // Almacena la posición de la ocurrencia más a la derecha

    // Recorre la cadena s hasta el final
    for (i = 0; s[i] != '\0'; i++) {
        // Compara el substring t comenzando en s[i]
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;

        // Si t[k] es '\0', significa que se encontró t completamente
        if (k > 0 && t[k] == '\0')
            pos = i; // Almacena el índice de la ocurrencia
    }
    return pos;
}

// Función principal para probar
int main()
{
    char s[] = "esto es una prueba de prueba";
    char t[] = "prueba";
    
    printf("Cadena S: \"%s\"\n", s);
    printf("Cadena T: \"%s\"\n", t);
    printf("La ocurrencia más a la derecha comienza en el índice: %d\n", strrindex(s, t));

    char u[] = "inexistente";
    printf("Cadena U: \"%s\"\n", u);
    printf("La ocurrencia más a la derecha comienza en el índice: %d\n", strrindex(s, u));
    
    return 0;
}