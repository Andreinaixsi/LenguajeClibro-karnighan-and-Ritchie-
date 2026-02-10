/*
 * Ejercicio 4-13: Escriba una versión recursiva de reverse(s) para invertir la
 * cadena s.
 */

#include <stdio.h>
#include <string.h>

/* reverse_recursive: invierte la cadena s recursivamente */
void reverse_recursive(char s[], int start, int end)
{
    char temp;

    if (start >= end)
        return; // Caso base: si los índices se cruzan o son el mismo
    
    // Intercambiar los caracteres en los límites
    temp = s[start];
    s[start] = s[end];
    s[end] = temp;
    
    // Llamada recursiva para el segmento interior
    reverse_recursive(s, start + 1, end - 1);
}

// Wrapper para la función recursiva
void reverse(char s[])
{
    reverse_recursive(s, 0, strlen(s) - 1);
}

// Función principal para probar
int main()
{
    char s[] = "hola mundo";
    char t[] = "reverso";

    printf("Original S: %s\n", s);
    reverse(s);
    printf("Invertida S: %s\n", s); // Debe ser "odnum aloh"

    printf("Original T: %s\n", t);
    reverse(t);
    printf("Invertida T: %s\n", t); // Debe ser "osrever"

    return 0;
}