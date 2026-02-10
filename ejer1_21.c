#include <stdio.h>

#define MAXLINE 1000    /* máxima cantidad de caracteres */
#define TABWIDTH 4      /* ancho del tab */

int getline(char line[], int maxline);
void entab(char to[], char from[]);

int main(void)
{
    int len;
    char line[MAXLINE];
    char nline[MAXLINE];
    
    while ((len = getline(line, MAXLINE)) > 0) {
        entab(nline, line);
        printf("%s", nline);
    }
    return 0;
}

int getline(char s[], int lim)
{
    int i, c;
    
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    
    return i;
}

/* entab: reemplaza cadenas de espacios por tabs y espacios */
void entab(char to[], char from[])
{
    int i, j, k;
    int space_count;
    int tab_stop;
    
    i = j = 0;
    
    while (from[i] != '\0') {
        if (from[i] == ' ') {
            // Contar espacios consecutivos
            space_count = 0;
            k = i;
            while (from[k] == ' ') {
                space_count++;
                k++;
            }
            
            // Calcular cuántos tabs y espacios necesitamos
            int current_pos = j;
            int target_pos = current_pos + space_count;
            
            // Insertar tabs hasta donde sea posible
            while (current_pos + TABWIDTH - (current_pos % TABWIDTH) <= target_pos) {
                int next_tab = current_pos + TABWIDTH - (current_pos % TABWIDTH);
                if (next_tab <= target_pos) {
                    to[j++] = '\t';
                    current_pos = next_tab;
                }
            }
            
            // Insertar espacios restantes
            while (current_pos < target_pos) {
                to[j++] = ' ';
                current_pos++;
            }
            
            i = k; // Saltar los espacios procesados
        } else {
            to[j++] = from[i++];
        }
    }
    to[j] = '\0';
}