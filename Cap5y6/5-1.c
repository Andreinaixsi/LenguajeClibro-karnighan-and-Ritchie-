#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
char buf[BUFSIZE];    /* Buffer para ungetch */
int bufp = 0;         /* Siguiente posición libre en el buffer */

/* Obtiene un carácter (del buffer o del teclado) */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Devuelve un carácter a la entrada */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c;
}

/* getint: lee el siguiente entero de la entrada a *pn */
int getint(int *pn) {
    int c, d, sign;

    while (isspace(c = getch())) /* Salta espacios en blanco */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* No es un número, lo devuelve */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    /* Lógica del Ejercicio 5-1: Manejo de signos sueltos */
    if (c == '+' || c == '-') {
        d = getch();
        if (!isdigit(d)) {
            if (d != EOF)
                ungetch(d);
            ungetch(c); /* Devuelve el signo porque no le sigue un número */
            return 0;
        }
        c = d; /* Si era un dígito, continuamos */
    }

    /* Acumula el número */
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * (*pn) + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c); /* Devuelve el carácter que detuvo la lectura */

    return c;
}

int main() {
    int n, res;
    printf("Escribe algo (ejemplo: +5, -10, o solo un +): ");
    
    res = getint(&n);
    
    if (res > 0)
        printf("Resultado: Encontré el número %d\n", n);
    else if (res == 0)
        printf("Resultado: No se encontró un número válido (carácter devuelto a la entrada).\n");
    else
        printf("Resultado: Fin de archivo (EOF).\n");

    return 0;
}