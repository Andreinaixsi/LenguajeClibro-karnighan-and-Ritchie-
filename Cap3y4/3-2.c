/*
 * Ejercicio 3-2. Escriba una función escape(s, t) que convierta caracteres 
 * como nueva línea y tabulación en secuencias de escape visibles como \n y \t 
 * a medida que copia la cadena t a s. Use un switch. Escriba también una 
 * función para la dirección opuesta, convirtiendo secuencias de escape a 
 * caracteres reales a medida que copia.
 */
#include <stdio.h>

#define MAXLINE 1000

/* escape: convierte caracteres en t a secuencias de escape visibles en s */
void escape(char s[], char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

/* unescape: convierte secuencias de escape visibles en t a caracteres en s */
void unescape(char s[], char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        if (t[i] == '\\') {
            i++; // Avanzar para verificar el carácter después de '\'
            switch (t[i]) {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                // Si no es un escape conocido, copiar '\' y el carácter siguiente
                default:
                    s[j++] = '\\';
                    s[j++] = t[i];
                    break;
            }
        } else {
            s[j++] = t[i];
        }
    }
    s[j] = '\0';
}

int main(void)
{
    char t[] = "Hola\tMundo\nC";
    char s_escaped[MAXLINE];
    char s_unescaped[MAXLINE];

    printf("Cadena original (t):\n---\n%s---\n", t);

    // 1. Convertir a escapes visibles
    escape(s_escaped, t);
    printf("Cadena con escapes visibles (s_escaped):\n---\n%s---\n", s_escaped);

    // 2. Convertir de nuevo a caracteres reales
    unescape(s_unescaped, s_escaped);
    printf("Cadena restaurada (s_unescaped):\n---\n%s---\n", s_unescaped);

    return 0;
}