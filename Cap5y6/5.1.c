#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

// Variables globales para getch y ungetch
char buf[BUFSIZE]; 
int bufp = 0;      

// Prototipos de funciones
int getch(void);
void ungetch(int);
int getint(int *pn);

// --- FUNCIÓN PRINCIPAL (Lo que le faltaba a tu código) ---
int main() {
    int n, result;
    int array[5]; // Ejemplo para capturar 5 números

    printf("Introduce números enteros (usa espacios o letras para terminar):\n");

    for (n = 0; n < 5; n++) {
        result = getint(&array[n]);
        
        if (result > 0) {
            printf("Número guardado: %d\n", array[n]);
        } else if (result == 0) {
            printf("Eso no era un número. Saltando...\n");
            getch(); // Limpiar el carácter no numérico
        } else {
            break; // Fin de archivo (EOF)
        }
    }

    printf("\nProceso terminado.\n");
    return 0;
}

// --- TU FUNCIÓN GETINT ---
int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch()))
        ; // Saltar espacios en blanco

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); // No es un número
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

// --- FUNCIONES DE SOPORTE (Necesarias para que compile) ---
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c;
}