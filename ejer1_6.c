#include <stdio.h>
 // determina el valor de (c = getchar( )) != EOF
int main( ){
 int c;
 while ((c = getchar( )) != EOF)
        printf("%d expresión verdadera\n", c);
 printf("%d es el valor EDF, y la expresión es falsa\n", c);
}