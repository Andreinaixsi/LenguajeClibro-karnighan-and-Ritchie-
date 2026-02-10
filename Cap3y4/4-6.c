#include <stdio.h>
#include <stdlib.h> 
#include <math.h>   
#include <ctype.h>  
#include <string.h> 

#define MAXOP 100   
#define NUMBER '0'  
#define MAXVAL 100  
#define BUFSIZE 100 
#define NUM_VARS 26 

int sp = 0;        
double val[MAXVAL]; 
char buf[BUFSIZE]; 
int bufp = 0;      

double variables[NUM_VARS]; 
double last_printed = 0.0;  
int recent_var_index = -1; 

/* Prototipos */
int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int main(void)
{
    int type;
    double op1, op2;
    char s[MAXOP];

    memset(variables, 0, sizeof(variables));

    printf("Calculadora RPN con variables A-Z\n");
    printf("Comandos: + - * / %% = ? # ~ !\n");
    printf("Variables: A-Z (mayúsculas), L (último resultado)\n");
    printf("Ejemplo: 5 A = 3 B = A B +\n\n");

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
            
            /* Comandos matemáticos */
            case 's': /* sin */
                push(sin(pop()));
                break;
            case 'e': /* exp */
                push(exp(pop()));
                break;
            case 'p': /* pow */
                op2 = pop(); 
                op1 = pop(); 
                push(pow(op1, op2));
                break;
            
            /* Comandos de pila */
            case '?': /* ver tope */
                if (sp > 0)
                    printf("\tTope: %.8g\n", val[sp-1]);
                else
                    printf("pila vacía\n");
                break;
            case '#': /* duplicar */
                if (sp > 0)
                    push(val[sp-1]);
                else
                    printf("pila vacía\n");
                break;
            case '~': /* intercambiar */
                if (sp >= 2) {
                    op1 = pop();
                    op2 = pop();
                    push(op1);
                    push(op2);
                } else {
                    printf("necesita 2 elementos\n");
                }
                break;
            case '!': /* limpiar */
                sp = 0;
                printf("pila limpiada\n");
                break;
            
            /* Asignación */
            case '=':
                if (recent_var_index != -1 && sp > 0) {
                    variables[recent_var_index] = val[sp-1];
                    printf("\t%c = %.8g\n", 'A' + recent_var_index, variables[recent_var_index]);
                } else {
                    printf("error en asignación\n");
                }
                break;

            case '\n':
                if (sp > 0) {
                    last_printed = val[sp-1];
                    printf("\t= %.8g\n", last_printed);
                }
                break;
            
            default:
                /* Variables A-Z y L */
                if (type >= 'A' && type <= 'Z') {
                    recent_var_index = type - 'A';
                    push(variables[recent_var_index]);
                } else if (type == 'L') {
                    push(last_printed);
                } else {
                    printf("error: comando desconocido '%c'\n", type);
                    /* Limpiar buffer de entrada */
                    while (getchar() != '\n');
                }
                break;
        }
    }
    return 0;
}

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: pila llena\n");
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

int getop(char s[])
{
    int i, c;
    
    /* Saltar espacios */
    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    
    if (c == EOF) return EOF;
    
    /* Si no es número ni punto, devolver el carácter */
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    
    i = 0;
    
    /* Manejar signo negativo */
    if (c == '-') {
        int next = getch();
        if (isdigit(next) || next == '.') {
            s[++i] = c = next;
        } else {
            ungetch(next);
            return '-';
        }
    }
    
    /* Leer número */
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));
    
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    
    s[i] = '\0';
    
    if (c != EOF)
        ungetch(c);
    
    return NUMBER;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: buffer lleno\n");
    else
        buf[bufp++] = c;
}