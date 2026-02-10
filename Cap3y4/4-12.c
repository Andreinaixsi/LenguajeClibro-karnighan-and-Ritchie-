/*
 * Ejercicio 4-12: Adapte la impresión de enteros en una función recursiva 
 * itoa(n, s). (Convierte entero n a cadena s).
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

/* reverse: invierte la cadena s in-place (necesaria para itoa) */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa_recursive: convierte el entero n a cadena s recursivamente */
void itoa_recursive(int n, char s[])
{
    static int i = 0; // i debe ser estático para mantener el índice en las llamadas recursivas
    int sign;
    
    if (i == 0) // Primera llamada: determina el signo
        sign = n; 

    // Imprime el dígito actual (el residuo)
    s[i++] = ABS(n % 10) + '0';

    // Llamada recursiva con la siguiente parte
    if (n / 10 != 0)
        itoa_recursive(n / 10, s);
    else { // La última llamada: añade el signo y el terminador
        if (sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        i = 0; // Resetear el índice estático para futuras llamadas
        reverse(s); // La cadena está al revés, hay que invertirla
    }
}

// Función principal para probar
int main()
{
    char s[100];
    int n1 = 12345;
    int n2 = -987;
    int n3 = 0;
    
    itoa_recursive(n1, s);
    printf("Entero %d -> Cadena \"%s\"\n", n1, s);
    
    itoa_recursive(n2, s);
    printf("Entero %d -> Cadena \"%s\"\n", n2, s);

    itoa_recursive(n3, s);
    printf("Entero %d -> Cadena \"%s\"\n", n3, s);

    return 0;
}