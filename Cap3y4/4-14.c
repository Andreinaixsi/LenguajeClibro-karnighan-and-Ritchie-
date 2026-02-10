/*
 * Ejercicio 4-14: Escriba la macro swap(t, x, y) que intercambie dos argumentos
 * de tipo t.
 */

#include <stdio.h>

/* * swap(t, x, y): Macro para intercambiar dos variables x e y de tipo t.
 * Usa una variable temporal de tipo t.
 */
#define swap(t, x, y) \
    {                 \
        t temp;       \
        temp = x;     \
        x = y;        \
        y = temp;     \
    }

// Función principal para probar
int main()
{
    int a = 10;
    int b = 20;
    double f = 3.14;
    double g = 2.71;

    printf("Antes del intercambio:\n");
    printf("a = %d, b = %d\n", a, b);
    printf("f = %f, g = %f\n", f, g);

    // Intercambiar enteros
    swap(int, a, b); 
    // Intercambiar doubles
    swap(double, f, g); 

    printf("Despues del intercambio:\n");
    printf("a = %d, b = %d\n", a, b); // a = 20, b = 10
    printf("f = %f, g = %f\n", f, g); // f = 2.71, g = 3.14

    return 0;
}