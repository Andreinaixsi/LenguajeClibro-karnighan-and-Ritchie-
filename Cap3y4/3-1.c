/*
 * Ejercicio 3-1. Nuestra versión de binsearch requiere dos pruebas
 * dentro del ciclo (if (v[mid] < x) y else if (v[mid] > x)). 
 * Al escribir sólo una prueba, haga sólo una, a expensas de más pruebas 
 * fuera del ciclo. Mida la diferencia en tiempos de ejecución.
 */
#include <stdio.h>

/* binsearch: encuentra x en v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    // Ciclo con una sola prueba: v[mid] != x
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else { // x >= v[mid]
            low = mid + 1;
        }
    }
    
    // Una prueba adicional fuera del ciclo para confirmar si se encontró x
    if (v[--low] == x)
        return low;
    else
        return -1;
}

int main(void)
{
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = 10;
    int x = 23;
    int y = 50;

    printf("Array: 2, 5, 8, 12, 16, 23, 38, 56, 72, 91\n");
    printf("Buscando %d: Indice %d\n", x, binsearch(x, arr, n)); // Esperado: 5
    printf("Buscando %d: Indice %d\n", y, binsearch(y, arr, n)); // Esperado: -1

    return 0;
}