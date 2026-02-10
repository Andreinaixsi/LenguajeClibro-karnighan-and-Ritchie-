/*
 * Ejercicio 4-9: Los buffers de getch y ungetch no se desbordan con EOF al usar
 * ungetch con él. Escriba el código.
 *
 * NOTA: Esto es importante porque EOF es un valor entero negativo (-1) que indica
 * el fin de archivo, y no un carácter válido.
 */

#include <stdio.h>

#define BUFSIZE 100 

int buf[BUFSIZE]; // El buffer debe ser de tipo int para almacenar EOF
int bufp = 0; 

int getch(void);
void ungetch(int);

/* getch: obtiene un (posiblemente) carácter regresado */
int getch(void)
{
    // El buffer almacena enteros, por lo que puede manejar EOF
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: regresa el carácter a la entrada (permite EOF) */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c; // Si c es EOF, se almacena.
}

// Función principal para probar
int main()
{
    int c;

    printf("Probando ungetch con EOF:\n");
    
    // Regresar EOF y luego un carácter normal
    ungetch(EOF);
    ungetch('X');
    
    printf("Leyendo desde el buffer:\n");
    
    // La primera llamada a getch debe devolver 'X'
    if ((c = getch()) != EOF)
        printf("Leido 1: %c\n", c);
    
    // La segunda llamada a getch debe devolver EOF.
    if ((c = getch()) == EOF)
        printf("Leido 2: EOF detectado\n");
    else
        printf("ERROR: Se esperaba EOF pero se obtuvo %c\n", c);
    
    return 0;
}