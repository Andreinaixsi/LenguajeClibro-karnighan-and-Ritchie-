#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]) {
    double operand;
    int status = scanf("%lf", &operand);
    if (status == EOF) return EOF;
    if (status == 1) {
        sprintf(s, "%g", operand);
        return NUMBER;
    } else {
        if (scanf("%s", s) == EOF) return EOF;
        return s[0];
    }
}

int main() {
    int type;
    char s[MAXOP];
    double stack[MAXOP];
    int sp = 0;

    printf("--- Calculadora Activa ---\n");
    printf("Escribe un numero o un operador (+, -, *, /)\n");

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                stack[sp++] = atof(s);
                printf("  [Pila] Anadido: %s\n", s); // Esto te confirmará que leyó el número
                break;
            case '+':
                if (sp >= 2) {
                    stack[sp-2] = stack[sp-2] + stack[sp-1];
                    sp--;
                    printf("  [Resultado] -> %.8g\n", stack[sp-1]);
                } else printf("Error: faltan numeros\n");
                break;
            case '*':
                if (sp >= 2) {
                    stack[sp-2] = stack[sp-2] * stack[sp-1];
                    sp--;
                    printf("  [Resultado] -> %.8g\n", stack[sp-1]);
                } else printf("Error: faltan numeros\n");
                break;
            // (He omitido - y / por brevedad, pero funcionan igual)
            default:
                if (type != ' ' && type != '\n')
                    printf("Comando desconocido: %c\n", type);
                break;
        }
        fflush(stdout); // Esto fuerza a la pantalla a mostrar el texto inmediatamente
    }
    return 0;
}