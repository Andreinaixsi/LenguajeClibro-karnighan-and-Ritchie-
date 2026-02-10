#include <stdio.h>
#include <stdlib.h> /* para atof() */
#include <math.h>   /* si se necesitan funciones matemáticas como sin, exp, pow */

#define MAXOP 100   /* tamaño máx. de operando u operador */
#define NUMBER '0'  /* señal de que se encontró un número */

/* Funciones de la calculadora */
int getop(char []);
void push(double);
double pop(void);

/* Nuevas funciones para el Ejercicio 4-4 */
void print_top(void);    /* ? : Imprime el tope */
void duplicate_top(void); /* # : Duplica el tope */
void swap_top(void);      /* ~ : Intercambia los dos topes */
void clear_stack(void);   /* ! : Limpia la pila */

/* --- Función Principal --- */
int main(void)
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
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    /* Para números de punto flotante, usamos fmod */
                    push(fmod(pop(), op2));
                else
                    printf("error: módulo por cero\n");
                break;
            /* --- NUEVOS COMANDOS (Ejercicio 4-4) --- */
            case '?': /* Imprimir el tope sin sacarlo */
                print_top();
                break;
            case '#': /* Duplicar el tope */
                duplicate_top();
                break;
            case '~': /* Intercambiar los dos elementos del tope */
                swap_top();
                break;
            case '!': /* Limpiar la pila */
                clear_stack();
                break;
            /* ------------------------------------- */
            case '\n':
                printf("\tResultado: %.8g\n", pop());
                break;
            default:
                printf("error: comando desconocido %s\n", s);
                break;
        }
    }
    return 0;
}

/* --- Implementación de la Pila --- */
#define MAXVAL 100 /* Profundidad máxima de la pila val */
int sp = 0;        /* Siguiente posición libre en val */
double val[MAXVAL]; /* Pila de valores */

/* push: ingresa f a la pila de valores */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: pila llena, no se puede meter %g\n", f);
}

/* pop: saca y retorna el valor superior de la pila */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: pila vacía\n");
        return 0.0;
    }
}

/* --- Implementación de las Nuevas Funciones de Pila --- */

/* print_top: imprime el elemento al tope sin sacarlo (?) */
void print_top(void)
{
    if (sp > 0)
        printf("\tTope de la pila: %.8g\n", val[sp-1]);
    else
        printf("error: pila vacía\n");
}

/* duplicate_top: duplica el elemento al tope (#) */
void duplicate_top(void)
{
    if (sp > 0) {
        /* Simplemente empuja el valor que ya está en el tope */
        push(val[sp-1]);
    } else {
        printf("error: pila vacía, no se puede duplicar\n");
    }
}

/* swap_top: intercambia los dos elementos del tope (~) */
void swap_top(void)
{
    double temp1, temp2;

    if (sp >= 2) {
        temp1 = pop(); /* Saca el tope (a) */
        temp2 = pop(); /* Saca el siguiente (b) */
        push(temp1);   /* Ingresa (a) de nuevo */
        push(temp2);   /* Ingresa (b) de nuevo (ahora es el tope) */
    } else {
        printf("error: se necesitan al menos dos elementos para intercambiar\n");
    }
}

/* clear_stack: limpia la pila (!) */
void clear_stack(void)
{
    sp = 0; /* Simplemente reinicia el puntero de pila */
    printf("Pila limpiada.\n");
}


/* --- Funciones de Entrada (getop, getch, ungetch) --- */
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: obtiene el siguiente operador u operando numérico */
int getop(char s[])
{
    int i, c;

    /* Ignora espacios, tabuladores, etc. */
    while ((c = getch()) == ' ' || c == '\t')
        ;
    s[0] = c;
    s[1] = '\0';

    /* No es un número, ni punto decimal, ni signo de inicio de número */
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* Retorna el operador (ej. '+', '*', '?', '#', etc.) */

    i = 0;
    /* Manejo de signo negativo o resta unaria */
    if (c == '-') {
        int next = getch();
        if (isdigit(next) || next == '.') {
            /* Es el inicio de un número negativo */
            s[++i] = c = next;
        } else {
            /* Es el operador de resta. Regresa el siguiente caracter. */
            ungetch(next);
            return s[0];
        }
    }

    /* Es el inicio de un número (o parte de un número negativo) */
    if (isdigit(c)) /* acumula parte entera */
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.') /* acumula parte fraccionaria */
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c); /* Empuja hacia atrás el carácter no numérico */

    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* Buffer para ungetch */
int bufp = 0;      /* Siguiente posición libre en buf */

/* getch: obtiene un (posiblemente regresado) carácter */
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