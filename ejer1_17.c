#include <stdio.h>
#define MAXLINE 80 /* entrada maxima */

int gettline(char line[], int maxline);

 /* imprime la longuitud de las entradas lo mas largo que se puede */
int main(int argc, char *argv[]){
                      int len; /* largo de una linea normal */
                      char line[MAXLINE]; /* linea de entrada normal */

                           while ((len = gettline(line, MAXLINE)) > 0){
                                  if(len > 80){
                                          printf("%d: %s", len, line);
                                  }
                           }
                           return 0;
                      }
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