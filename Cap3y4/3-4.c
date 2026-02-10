/*
 * Ejercicio 3-4. En una representación de números en complemento a dos, 
 * nuestra versión de itoa no maneja el número negativo más grande, esto es, 
 * el valor de n igual a -(2^(tamaño de palabra - 1)). Explique por qué. 
 * Modifíquelo para imprimir el valor correctamente, sin importar la máquina 
 * en que ejecute.
 *
 * Explicación: El valor de INT_MIN (p. ej., -2147483648) no puede ser 
 * representado como un entero positivo. Si se intenta calcular n = -n,
 * se produce un desbordamiento (overflow) y el número sigue siendo negativo
 * o cambia de forma inesperada.
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);

/* itoa_minint: convierte n a caracteres en s, manejando INT_MIN */
void itoa_minint(int n, char s[])
{
    int i, sign;

    sign = n; // Se almacena el número para la comprobación del signo

    i = 0;
    do { /* generar dígitos en orden inverso */
        // Usamos -(n % 10) para el dígito, manteniendo n negativo si es posible.
        // Si n es INT_MIN, -(n % 10) es 8 (positivo), y n / 10 sigue siendo negativo.
        s[i++] = -(n % 10) + '0'; 
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

/* reverse: invierte la cadena s en el mismo lugar */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int main(void)
{
    char s[100];
    int n_max_neg = INT_MIN; // El entero negativo más grande (-2147483648 en 32-bit)
    int n_pos = 12345;
    int n_neg = -6789;

    printf("INT_MIN: %d\n", n_max_neg);
    itoa_minint(n_max_neg, s);
    printf("itoa(INT_MIN): %s\n", s); // Debe imprimir correctamente -2147483648

    itoa_minint(n_pos, s);
    printf("itoa(12345): %s\n", s); 

    itoa_minint(n_neg, s);
    printf("itoa(-6789): %s\n", s); 

    return 0;
}