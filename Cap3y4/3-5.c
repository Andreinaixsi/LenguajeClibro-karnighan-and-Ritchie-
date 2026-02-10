/*
 * Ejercicio 3-5. Escriba la función itob(n, s, b) que convierte al entero n 
 * en una representación de caracteres con base b dentro de la cadena s. 
 * En particular, itob(n, s, 16) da formato a n como un entero hexadecimal 
 * en s.
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);

/* itob: convierte el entero n a la base b (2 <= b <= 36) en la cadena s */
void itob(int n, char s[], int b)
{
    int i, sign;
    int rem; // Remainder (residuo)
    
    // Caracteres para bases > 10
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (b < 2 || b > 36) {
        // Manejo de error de base inválida
        s[0] = '\0'; 
        return;
    }

    sign = n; // Almacenar el signo

    i = 0;
    // La lógica de do-while y mantener negativo se usa para manejar INT_MIN correctamente
    do { 
        // Tomar el residuo
        rem = n % b;
        
        // El dígito se calcula a partir del valor absoluto del residuo
        s[i++] = digits[ (rem < 0) ? -rem : rem ];
        
    } while ((n /= b) != 0);

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
    int n = 255;
    
    // Base 10
    itob(n, s, 10);
    printf("%d en base 10: %s\n", n, s); // Esperado: 255

    // Base 16 (Hexadecimal)
    itob(n, s, 16);
    printf("%d en base 16: %s\n", n, s); // Esperado: FF

    // Base 2 (Binario)
    itob(n, s, 2);
    printf("%d en base 2: %s\n", n, s); // Esperado: 11111111

    // Base 8 (Octal)
    itob(n, s, 8);
    printf("%d en base 8: %s\n", n, s); // Esperado: 377
    
    // Número negativo en Base 16
    n = -255;
    itob(n, s, 16);
    printf("%d en base 16: %s\n", n, s); // Esperado: -FF

    return 0;
}