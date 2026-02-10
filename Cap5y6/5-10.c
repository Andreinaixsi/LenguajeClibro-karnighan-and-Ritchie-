#include <stdio.h>
#include <stdlib.h>  /* para atof() */
#include <ctype.h>   /* para isdigit() */

#define MAXVAL 100   /* máxima profundidad de la pila */

int sp = 0;          /* siguiente posición libre en la pila */
double val[MAXVAL];  /* pila de valores */

/* push: mete un valor en la pila */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: pila llena, no se puede meter %g\n", f);
}

/* pop: saca y regresa el valor superior de la pila */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: pila vacia\n");
        return 0.0;
    }
}

/* expr: calculadora de notación polaca inversa desde la línea de comandos */
int main(int argc, char *argv[]) {
    double op2;
    char *s;

    while (--argc > 0) {
        s = *++argv; /* apunta al siguiente argumento */

        /* Verificamos si el argumento es un número. 
           Un número puede empezar con:
           1. Un dígito (ej: 5)
           2. Un signo menos seguido de un dígito (ej: -5)
           3. Un punto decimal (ej: .5)
        */
        if (!isdigit(s[0]) && s[0] != '.' && !(s[0] == '-' && isdigit(s[1]))) {
            /* Si no es un número, debe ser un operador */
            switch (s[0]) {
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
                default:
                    printf("error: comando desconocido %s\n", s);
                    argc = 1; /* Para salir del bucle */
                    break;
            }
        } else {
            /* Es un operando (número), lo convertimos y lo metemos a la pila */
            push(atof(s));
        }
    }

    /* Al final, el resultado debe ser el único elemento en la pila */
    if (sp == 1) {
        printf("\t%.8g\n", pop());
    } else if (sp > 1) {
        printf("error: la expresion no termino correctamente (quedan elementos en la pila)\n");
    }

    return 0;
}