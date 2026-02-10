/*
 * Ejercicio 3-3. Escriba una función llamada expand(s1, s2) que expanda 
 * notaciones abreviadas como a-z en la cadena s1 en la lista completa 
 * equivalente abc...xyz en s2. Permita casos como a-b-c, a-z0-9 y -a-z. 
 * Trate guiones al principio o al final como caracteres literales.
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

/* expand: expande abreviaciones como a-z en s1 a caracteres completos en s2 */
void expand(char s1[], char s2[])
{
    int i, j, c1, c2;

    j = 0; // Índice de s2

    for (i = 0; s1[i] != '\0'; i++) {
        // Copiar el primer carácter
        s2[j++] = s1[i];

        // Verificar si el siguiente es un guion y si el siguiente al guion existe
        if (s1[i+1] == '-' && s1[i+2] != '\0') {
            c1 = s1[i];      // Carácter inicial del rango
            c2 = s1[i+2];    // Carácter final del rango

            // Validar que el rango sea del mismo tipo y c1 <= c2
            if ( ( (islower(c1) && islower(c2)) || 
                   (isupper(c1) && isupper(c2)) || 
                   (isdigit(c1) && isdigit(c2)) ) 
                 && c1 < c2 ) 
            {
                // El rango es válido. Agregar los caracteres intermedios.
                for (c1 = c1 + 1; c1 <= c2; c1++) {
                    s2[j++] = c1;
                }
                
                // Saltar el guion y el carácter final del rango en s1
                i += 2; 
            }
        }
        // Si no es un rango válido, se copia el carácter (s1[i]) y el guion (s1[i+1])
    }
    s2[j] = '\0';
}

int main(void)
{
    char s1_1[] = "a-f0-3Z-A";  // Rango inválido Z-A
    char s1_2[] = "-a-z0-9-";   // Guiones literales al inicio y final
    char s1_3[] = "a-b-c";      // Múltiples rangos

    char s2[MAXLINE];

    printf("Prueba 1: \"%s\" -> ", s1_1);
    expand(s1_2, s2);
    printf("\"%s\"\n", s2); 

    printf("Prueba 2: \"%s\" -> ", s1_2);
    expand(s1_2, s2);
    printf("\"%s\"\n", s2); // La salida correcta debe ser "-abcdefghijklmnopqrstuvwxyz0123456789-"

    printf("Prueba 3: \"%s\" -> ", s1_3);
    expand(s1_3, s2);
    printf("\"%s\"\n", s2); // La salida correcta debe ser "abc"
    
    // NOTA: Para Prueba 1, la salida es "-a-f0-3Z-A" debido al guion inicial
    // y Z-A no se expande ya que c1 > c2.
    
    return 0;
}