/*
 * Ejercicio 4-7: Escriba una rutina ungets(s) que regresa a la entrada una cadena
 * completa. ¿Debe ungets conocer acerca de buf y bufp, o sólo debe usar ungetch?
 *
 * Respuesta: ungets debe usar ungetch. De esta forma, el código de manejo del
 * buffer (buf y bufp) se mantiene centralizado y oculto en las rutinas getch
 * y ungetch, manteniendo un buen diseño modular.
 */

#include <stdio.h>
#include <string.h>

#define BUFSIZE 100 

char buf[BUFSIZE]; 
int bufp = 0; 

int getch(void);
void ungetch(int);

/* ungets: regresa una cadena completa a la entrada */
void ungets(char s[])
{
    int i = strlen(s);

    // Se inserta la cadena al revés en el buffer (como una pila)
    while (i > 0)
        ungetch(s[--i]);
}

// Implementación de getch y ungetch
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c;
}

// Función principal para probar
int main()
{
    char s[] = "hola mundo";
    int c;

    // Regresa la cadena "hola mundo" al buffer de entrada
    ungets(s);
    printf("Cadena regresada al buffer: \"%s\"\n", s);
    printf("Leyendo desde el buffer:\n");
    
    // Lee desde el buffer de entrada
    while ((c = getch()) != EOF && c != '\n') {
        putchar(c);
    }
    putchar('\n');

    return 0;
}