/*
 * Ejercicio 4-3: Dada la estructura básica, es fácil extender la calculadora. 
 * Agregue el operador módulo (%) y consideraciones para números negativos.
 */

#include <stdio.h>
#include <stdlib.h> /* para atof() */
#include <math.h> /* para fmod() */
#include <ctype.h> /* <<-- CORRECCIÓN: NECESARIO para isdigit() y isalpha() */

#define MAXOP 100 /* max. de tamaño de operando u operador */
#define NUMBER '0' /* señal de que se encontró un número */
#define MAXVAL 100 /* profundidad máxima de la pila de valores */
#define BUFSIZE 100 /* tamaño de buffer para getch/ungetch */

int sp = 0; /* siguiente posición libre en la pila */
double val[MAXVAL]; /* pila de valores */
char buf[BUFSIZE]; /* buffer para ungetch */
int bufp = 0; /* siguiente posición libre en buf */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

/* calculadora de notación polaca inversa */
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: divisor cero\n");
            break;
        case '%': // Añadido para el Ejercicio 4-3: Operador Módulo
            op2 = pop();
            if (op2 != 0.0) {
                // Se usa fmod() para el módulo de punto flotante.
                push(fmod(pop(), op2)); 
            } else {
                printf("error: divisor cero en modulo\n");
            }
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: comando desconocido %s\n", s);
            break;
        }
    }
    return 0;
}

/* push: introduce un valor a la pila */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: pila llena, no puede hacer push %g\n", f);
}

/* pop: saca y regresa el valor superior de la pila */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: pila vacia\n");
        return 0.0;
    }
}

/* getop: obtiene el siguiente operador u operando numérico */
int getop(char s[])
{
    int i, c;

    // 1. Omitir blancos y tabuladores.
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    // 2. Comprobar si es un operador o el inicio de un número.
    // Si no es un dígito, un punto o un signo de resta, es un operador simple.
    if (!isdigit(c) && c != '.' && c != '-')
        return c; 

    i = 0;
    
    // 3. Manejar el signo '-'
    if (c == '-') {
        // Almacenar el signo. Si el siguiente no es dígito/punto, es el operador.
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next); // Devolver el carácter.
            return s[0]; // Devolver '-' como operador.
        }
        // Si el siguiente es un dígito o punto, es parte de un número negativo.
        c = next;
        s[++i] = c;
    }

    // 4. Recorrer la parte entera.
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    // 5. Recorrer la parte fraccionaria (si existe).
    if (c == '.') { 
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    s[i] = '\0'; // Finalizar la cadena del número.
    
    // 6. Devolver el carácter que terminó la lectura.
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

/* getch: obtiene un (posiblemente) carácter regresado */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: regresa el carácter a la entrada */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c;
}