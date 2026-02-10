#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char qualifiers[MAXTOKEN];
char out[1000];

int main() {
    int type;
    char temp[MAXTOKEN];
    qualifiers[0] = '\0';
    
    // Mientras no llegue al final del archivo
    while (gettoken() != EOF) {
        strcpy(out, token);
        // Mientras no llegue al final de la línea
        while ((type = gettoken()) != '\n' && type != EOF) {
            if (type == PARENS || type == BRACKETS) {
                if (out[0] == '*') {
                    sprintf(temp, "(%s)%s", out, token);
                    strcpy(out, temp);
                } else {
                    strcat(out, token);
                }
            } else if (type == '*') {
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                // Inserta el tipo y los calificadores acumulados al inicio
                sprintf(temp, "%s %s%s", token, qualifiers, out);
                strcpy(out, temp);
            } else if (type == 'q') { // Calificador (const o volatile)
                strcat(qualifiers, token);
                strcat(qualifiers, " ");
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
        qualifiers[0] = '\0'; // Limpiar calificadores para la siguiente línea
    }
    return 0;
}

int gettoken(void) {
    int c;
    char *p = token;

    // Saltar espacios y tabuladores
    while ((c = getchar()) == ' ' || c == '\t');

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getchar()) != ']'; );
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        // Recolectar palabras alfanuméricas
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        
        // Verificar si la palabra es un calificador de tipo
        if (strcmp(token, "const") == 0 || strcmp(token, "volatile") == 0)
            return tokentype = 'q'; 
        else
            return tokentype = NAME;
    } 
    return tokentype = c;
}