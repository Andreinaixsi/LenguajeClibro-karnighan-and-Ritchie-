/*
 * Ejercicio 4-8: Suponga que nunca existirá más de un carácter regresado a la entrada.
 * Modifique getch y ungetch según se requiera.
 */

#include <stdio.h>

// Variable estática para almacenar solo un carácter regresado
static int buf = EOF; // EOF es un buen valor inicial (ningún carácter regresado)

int getch(void);
void ungetch(int);

/* getch: obtiene un (posiblemente) carácter regresado (versión de un solo carácter) */
int getch(void)
{
    if (buf != EOF) {
        int c = buf;
        buf = EOF; // Limpia el buffer después de leer el carácter
        return c;
    } else {
        return getchar();
    }
}

/* ungetch: regresa el carácter a la entrada (versión de un solo carácter) */
void ungetch(int c)
{
    if (buf != EOF)
        printf("ungetch: solo se permite un caracter regresado\n");
    else
        buf = c;
}

// Función principal para probar
int main()
{
    int c;

    printf("Probando ungetch de un solo carácter:\n");
    ungetch('A');
    ungetch('B'); // Esto generará un error de "demasiados caracteres"
    
    // Debería imprimir solo 'A' y luego leer de la entrada estándar
    printf("Caracteres leidos: ");
    while ((c = getch()) != EOF && c != '\n') {
        putchar(c);
        // Si no hay más entrada, el programa esperará por ella.
    }
    putchar('\n');

    return 0;
}