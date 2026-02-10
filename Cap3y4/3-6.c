/*
 * Ejercicio 3-6. Modifique itoa de modo que acepte un tercer argumento que 
 * sea el ancho mínimo de campo. El número convertido deberá rellenarse con 
 * espacios a la izquierda si es necesario para que sea lo suficientemente ancho.
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);

/* itoa_padding: convierte n a caracteres en s con ancho de campo 'width' */
void itoa_padding(int n, char s[], int width)
{
    int i, sign;

    sign = n; 

    i = 0;
    do { /* generar dígitos en orden inverso */
        // Usamos la misma lógica del Ejercicio 3-4 para manejar INT_MIN
        s[i++] = -(n % 10) + '0'; 
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';
    
    // Relleno con espacios hasta el ancho mínimo
    while (i < width)
        s[i++] = ' ';

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
    int n1 = 1234;
    int n2 = -5;
    int n3 = 123456;
    
    // Número más corto que el ancho
    itoa_padding(n1, s, 8);
    printf("N: %d, Ancho: 8 -> \"%s\"\n", n1, s); // Esperado: "    1234" (4 espacios + 1234)

    // Número negativo más corto que el ancho
    itoa_padding(n2, s, 5);
    printf("N: %d, Ancho: 5 -> \"%s\"\n", n2, s); // Esperado: " -5" (2 espacios + -5)

    // Número más largo que el ancho (el ancho es ignorado)
    itoa_padding(n3, s, 4);
    printf("N: %d, Ancho: 4 -> \"%s\"\n", n3, s); // Esperado: "123456"

    // Prueba con INT_MIN
    itoa_padding(INT_MIN, s, 15);
    printf("N: INT_MIN, Ancho: 15 -> \"%s\"\n", INT_MIN, s); 

    return 0;
}