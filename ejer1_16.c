#include <stdio.h>
#define MAXLINE 100 /* entrada maxima */

int gettline(char line[], int maxline);
void copy(char to[], char from[]);

/* imprime la longuitud de las entradas lo mas largo que se puede */
int main(int argc, char *argv[]){
                      int len; /* largo de una linea normal */
                      int max; /* largo maximo */
                      char line[MAXLINE]; /* linea de entrada normal */
                      char longest[MAXLINE]; /* linea mas larga guardada aqui */
                      max = 0;
                      while((len = gettline(line, MAXLINE)) > 0){
                          printf("%d, %s\n", len, line);
                          if (len > max){
                                  max = len;
                                  copy(longest, line);
                          }
                      }
                       if (max > 0) /* hay una linea */
                            printf("%s\n", longest);
                      }

 /* función gettline: lee las lineas, y retorna el largo */
                      int gettline(char s[], int lim){
                        int i, c;

                        for (i = 0; (c=getchar()) != EOF && c != '\n' && i < lim - 1; +
                             +i){
                             s[i] = c;
                        }
                        if (c == '\n'){
                           s[i] = '\n';
                           i++;
                        }
                        s[i] = '\0';

                        return i;
                      }

                      /* función copy: copia 'from' a 'to' */
                      void copy(char to[], char from[]){
                           int i;
                           i = 0;
                           while ((to[i] = from[i]) != '\0')
                                  ++i;
                      } 