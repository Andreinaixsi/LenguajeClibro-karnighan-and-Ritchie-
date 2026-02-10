#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int needsparens(char *s); // Prototipo necesario

int tokentype;
char token[MAXTOKEN];
char out[1000];

int main() {
    int type;
    char temp[MAXTOKEN];
    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n' && type != EOF) {
            if (type == PARENS || type == BRACKETS) {
                if (needsparens(out)) { // Uso de la función corregido
                    sprintf(temp, "(%s)%s", out, token);
                    strcpy(out, temp);
                } else {
                    strcat(out, token);
                }
            } else if (type == '*') {
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

// Verifica si la cadena actual requiere paréntesis antes de agregar [] o ()
int needsparens(char *s) {
    while (*s) {
        if (*s == '*') return 1;
        s++;
    }
    return 0;
}

int gettoken(void) {
    int c;
    char *p = token;
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
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    } else
        return tokentype = c;
}