#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int prevtoken = 0;

int main() {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("error de sintaxis\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '*'; )
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " apuntador a");
}

void dirdcl(void) {
    int type;
    
    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: falta )\n");
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        printf("error: nombre o (dcl) esperado\n");
        prevtoken = 1;
    }
    
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " funcion que regresa");
        else {
            strcat(out, " arreglo");
            strcat(out, token);
            strcat(out, " de");
        }
    }
}

int gettoken(void) {
    int c;
    char *p = token;
    
    if (prevtoken) {
        prevtoken = 0;
        return tokentype;
    }
    
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    
    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getchar()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}