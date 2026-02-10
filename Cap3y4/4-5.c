#include <stdio.h>
#include <stdlib.h> 
#include <math.h>   
#include <ctype.h>  

#define MAXOP 100   
#define NUMBER '0'  
#define MAXVAL 100  
#define BUFSIZE 100 

/* Variables y Buffer de Pila */
int sp = 0;        
double val[MAXVAL]; 
char buf[BUFSIZE]; 
int bufp = 0;      

/* Prototypes */
int getop(char []);
void push(double);
double pop(void);
void print_top(void);   
void duplicate_top(void); 
void swap_top(void);      
void clear_stack(void);   
int getch(void);
void ungetch(int);

/* ------------------------------------ */
/* FUNCIÓN PRINCIPAL          */
/* ------------------------------------ */
int main(void)
{
    int type;
    double op1, op2;
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
                    push(fmod(pop(), op2));
                else
                    printf("error: módulo por cero\n");
                break;
            
            /* --- COMANDOS MATEMÁTICOS (E4-5) --- */
            case 's': /* sin(x) */
                push(sin(pop()));
                break;
            case 'e': /* exp(x) */
                push(exp(pop()));
                break;
            case 'p': /* pow(x, y) */
                op2 = pop(); /* Exponente (y) */
                op1 = pop(); /* Base (x) */
                push(pow(op1, op2));
                break;
            
            /* --- COMANDOS DE PILA (E4-4) --- */
            case '?': /* Imprimir el tope sin sacarlo */
                print_top();
                break;
            case '#': /* Duplicar el tope */
                duplicate_top();
                break;
            case '~': /* Intercambiar los dos elementos */
                swap_top();
                break;
            case '!': /* Limpiar la pila */
                clear_stack();
                break;
            
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

/* ------------------------------------ */
/* FUNCIONES DE PILA          */
/* ------------------------------------ */

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: pila llena, no se puede meter %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: pila vacía\n");
        return 0.0;
    }
}

void print_top(void)
{
    if (sp > 0)
        printf("\tTope de la pila: %.8g\n", val[sp-1]);
    else
        printf("error: pila vacía\n");
}

void duplicate_top(void)
{
    if (sp > 0) {
        push(val[sp-1]);
    } else {
        printf("error: pila vacía, no se puede duplicar\n");
    }
}

void swap_top(void)
{
    double temp1, temp2;

    if (sp >= 2) {
        temp1 = pop(); 
        temp2 = pop(); 
        push(temp1);   
        push(temp2);   
    } else {
        printf("error: se necesitan al menos dos elementos para intercambiar\n");
    }
}

void clear_stack(void)
{
    sp = 0; 
    printf("Pila limpiada.\n");
}


/* ------------------------------------ */
/* FUNCIONES DE ENTRADA (CORREGIDAS)    */
/* ------------------------------------ */

/* getop: obtiene el siguiente operador u operando numérico */
int getop(char s[])
{
    int i, c;

    /* CORRECCIÓN FINAL: IGNORA espacios, tabuladores y el CARRIAGE RETURN (\r) de Windows */
    while ((c = getch()) == ' ' || c == '\t' || c == '\r')
        ;
        
    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c; 

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

    /* Es el inicio de un número */
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.') 
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c); 

    return NUMBER;
}


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