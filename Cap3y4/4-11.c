#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // Para atoi (Aunque no se usa en esta prueba)

#define MAXOP 100   
#define NUMBER '0'  
#define EOF_INDICATOR -1 // Usamos -1 para EOF

/* Prototypes */
int getop(char s[]);

/* ------------------------------------ */
/* FUNCIÓN getop MODIFICADA (E4-11)     */
/* ------------------------------------ */

/* getop: obtiene el siguiente operador u operando. 
   Usa una variable static interna para devolver un carácter. */
int getop(char s[])
{
    // Variable static interna: actúa como un buffer de 1 carácter.
    // Mantiene su valor entre llamadas a getop.
    static int last_char = 0; 
    int i, c;

    // 1. Usa el carácter guardado o lee uno nuevo
    if (last_char != 0) {
        c = last_char; // Usa el carácter guardado
        last_char = 0; // Reinicia el buffer
    } else {
        c = getchar(); // Lee desde la entrada estándar
    }
    
    // 2. Saltar espacios, tabs y retornos de carro
    while (c == ' ' || c == '\t' || c == '\r')
        c = getchar();
        
    s[0] = c;
    s[1] = '\0';

    // 3. Devolver si es fin de archivo o un operador simple
    if (c == EOF_INDICATOR)
        return EOF;
    
    // Si no es un dígito, un punto o un signo, es un operador simple o una variable.
    if (!isdigit(c) && c != '.' && c != '-')
        return c; 

    i = 0;
    
    // 4. Manejo de signo negativo o resta unaria
    if (c == '-') {
        int next_c;
        
        // Usamos la variable static interna si hay un carácter devuelto anteriormente
        if (last_char != 0) {
            next_c = last_char;
            last_char = 0;
        } else {
            next_c = getchar();
        }
        
        // Si el siguiente carácter es un dígito o un punto, es un número negativo.
        if (isdigit(next_c) || next_c == '.') {
            s[++i] = c = next_c; // Consume el siguiente dígito o punto
        } else {
            // Es el operador de resta. El carácter siguiente se debe "devolver".
            if (next_c != EOF_INDICATOR) {
                last_char = next_c; // Almacena el carácter 'sobrante'
            }
            return s[0]; // Devuelve el operador de resta '-'
        }
    }

    // 5. Acumular parte entera del número
    if (isdigit(c))
        while (isdigit(s[++i] = c = getchar()))
            ;

    // 6. Acumular parte fraccionaria
    if (c == '.') 
        while (isdigit(s[++i] = c = getchar()))
            ;

    s[i] = '\0';

    // 7. Almacenar el carácter que NO es parte del número (sustituye a ungetch)
    if (c != EOF_INDICATOR) {
        last_char = c; 
    }

    return NUMBER;
}


/* ------------------------------------ */
/* PROGRAMA DE PRUEBA                   */
/* ------------------------------------ */
int main()
{
    int type;
    char s[MAXOP];
    
    printf("--- Prueba de getop con variable static (E4-11) ---\n");
    printf("Ingrese una expresión (Ej: 123 456 + ):\n");
    
    // Simulación de la lectura de la entrada
    while ((type = getop(s)) != EOF) {
        if (type == NUMBER) {
            printf("TOKEN: NUMERO (%s)\n", s);
        } else if (type == '\n') {
            printf("TOKEN: SALTO DE LINEA\n");
        } else {
            printf("TOKEN: OPERADOR (%c)\n", type);
        }
        
        // Detener la prueba después de procesar el salto de línea
        if (type == '\n') 
            break;
    }

    return 0;
}