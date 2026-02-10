#include <stdio.h>
 // cambia a un solo espacio en blanco cuando cuando hay mas de un espacio en blanco
int main(){
         int ultimoChar;
         int c;
         ultimoChar = 'n';
         while ((c = getchar()) != EOF){
                if (c != ' ')
                         putchar(c);
                         else if (ultimoChar != ' ')
                                 putchar(c);
                         ultimoChar = c;
                }

         }
