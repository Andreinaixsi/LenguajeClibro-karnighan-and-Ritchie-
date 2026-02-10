#include <ctype.h>
#include <stdio.h>

/* Prototipos de funciones */
int getch(void);
void ungetch(int);
int getfloat(float *pn);

/* --- FUNCIÓN PRINCIPAL (Punto de entrada) --- */
int main() {
    float f;
    int resultado;

    printf("Escribe un numero decimal (ejemplo: 3.14 o -10.5): ");
    
    /* Llamamos a getfloat pasando la direccion de la variable f */
    resultado = getfloat(&f);

    if (resultado > 0) {
        printf("Numero capturado con exito: %f\n", f);
    } else if (resultado == 0) {
        printf("Error: Lo ingresado no es un numero valido.\n");
    } else if (resultado == EOF) {
        printf("Se alcanzo el fin de archivo (EOF).\n");
    }

    return 0;
}

/* --- FUNCIÓN GETFLOAT --- */
int getfloat(float *pn) {
    int c, sign;
    float power;

    /* Salta espacios en blanco */
    while (isspace(c = getch()))
        ;

    /* Valida si es un numero o un signo */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    /* Parte entera */
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    /* Parte decimal */
    if (c == '.')
        c = getch();

    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }

    /* Ajuste final con el signo y la potencia */
    *pn = sign * *pn / power;

    if (c != EOF)
        ungetch(c);

    return c;
}

/* --- FUNCIONES DE SOPORTE (Búfer para getch/ungetch) --- */
#define BUFSIZE 100
char buf[BUFSIZE]; /* Búfer para ungetch */
int bufp = 0;      /* Siguiente posición libre en buf */

/* Obtiene un carácter (del búfer o de la entrada estándar) */
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