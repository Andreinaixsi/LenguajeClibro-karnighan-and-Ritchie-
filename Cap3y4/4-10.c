#include <stdio.h>
#include <stdlib.h> 
#include <math.h>   
#include <ctype.h>  
#include <string.h> 

#define MAXOP 100   
#define NUMBER '0'  
#define MAXVAL 100  
#define NUM_VARS 26 
#define MAXLINE 1000 // Tamaño máximo para la línea de entrada

/* --- VARIABLES GLOBALES DE PILA DE VALORES --- */
int sp = 0;        
double val[MAXVAL]; 
double variables[NUM_VARS]; 
double last_printed = 0.0;  
int recent_var_index = -1; 

/* --- VARIABLES GLOBALES DE ENTRADA (E4-10) --- */
char line[MAXLINE];    // Buffer para la línea de entrada
int line_index = 0;    // Índice de la posición actual en 'line'

/* Prototypes */
int getop(char []);
void push(double);
double pop(void);
void print_top(void);    
void duplicate_top(void); 
void swap_top(void);      
void clear_stack(void);   
int getLine(void);      


/* ------------------------------------ */
/* FUNCIÓN PRINCIPAL (CORREGIDA EN case '=') */
/* ------------------------------------ */
int main(void)
{
    int type;
    double op1, op2;
    char s[MAXOP];

    memset(variables, 0, sizeof(variables));

    // Bucle principal: obtiene una nueva línea si la actual se agota
    while ((getLine() != 0)) { // Lee una línea completa
        line_index = 0; // Reinicia el índice para procesar la nueva línea
        
        while ((type = getop(s)) != EOF && type != '\n') {
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
                case 's': 
                    push(sin(pop()));
                    break;
                case 'e': 
                    push(exp(pop()));
                    break;
                case 'p': 
                    op2 = pop(); 
                    op1 = pop(); 
                    push(pow(op1, op2));
                    break;
                case '?': 
                    print_top();
                    break;
                case '#': 
                    duplicate_top();
                    break;
                case '~': 
                    swap_top();
                    break;
                case '!': 
                    clear_stack();
                    break;

                /* --- LÓGICA DE ASIGNACIÓN CORREGIDA (E4-6/E4-10) --- */
                case '=':
                    if (recent_var_index != -1) {
                        double assigned_value = pop(); // 1. Extrae el valor antiguo de la variable (basura)
                        double real_value = pop();     // 2. Extrae el valor REAL a asignar (Ej: 100)
                        
                        variables[recent_var_index] = real_value;
                        printf("\tAsignado a %c: %.8g\n", (char)('A' + recent_var_index), variables[recent_var_index]);
                        recent_var_index = -1;
                        
                        // 3. Vuelve a poner el valor asignado en la pila para que '\n' lo imprima.
                        push(real_value); 
                    } else {
                        printf("error: variable de asignacion no especificada\n");
                    }
                    break;
                /* --- FIN LÓGICA DE ASIGNACIÓN CORREGIDA --- */
                    
                default:
                    if (type >= 'A' && type <= 'Z') {
                        recent_var_index = type - 'A';      
                        push(variables[recent_var_index]); 
                    } else if (type == 'L') {
                        push(last_printed); 
                    }
                    else {
                        printf("error: comando desconocido %s\n", s);
                    }
                    break;
            }
        }
        // Cuando el bucle interno termina (por '\n' o EOF)
        if (type == '\n') {
            op1 = pop(); 
            printf("\tResultado: %.8g\n", op1);
            last_printed = op1; 
        }
    }
    return 0;
}


/* ------------------------------------ */
/* NUEVAS FUNCIONES DE ENTRADA (E4-10)  */
/* ------------------------------------ */

/* getLine: lee una línea en el buffer global 'line' */
int getLine(void)
{
    int c, i;

    // Lee caracteres uno por uno hasta EOF o '\n'
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    
    // Manejo del salto de línea (lo almacena en el buffer)
    if (c == '\n') {
        line[i++] = c;
    }
    
    // Termina la cadena con el nulo
    line[i] = '\0';
    
    return i; 
}


/* getop: obtiene el siguiente operador u operando de la línea */
int getop(char s[])
{
    int i, c;

    // Lee de la posición actual, ignorando el Carriage Return de Windows
    while ((c = line[line_index++]) == ' ' || c == '\t' || c == '\r')
        ;
        
    s[0] = c;
    s[1] = '\0';

    // Manejo de fin de línea
    if (c == '\0' || c == EOF) {
        return c;
    }
    
    // Si no es un dígito o un signo, devuélvelo como operador (incluye A-Z, L, =)
    if (!isdigit(c) && c != '.' && c != '-')
        return c; 

    i = 0;
    
    // Manejo de signo negativo o resta unaria
    if (c == '-') {
        int next = line[line_index];
        if (isdigit(next) || next == '.') {
            // Es el inicio de un número negativo, consume el signo y el siguiente dígito
            s[++i] = c = line[line_index++]; 
        } else {
            // Es el operador de resta. Retrocede el índice para "devolver" el '-'
            line_index--; 
            return s[0];
        }
    }

    // Es el inicio de un número (parte entera)
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[line_index++]))
            ;

    // Parte fraccionaria
    if (c == '.') 
        while (isdigit(s[++i] = c = line[line_index++]))
            ;

    s[i] = '\0';

    // El último carácter leído (c) NO era parte del número, "Ungetch" ese carácter (decrementa el índice)
    line_index--; 

    return NUMBER;
}


/* ------------------------------------ */
/* FUNCIONES DE PILA Y AUXILIARES       */
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