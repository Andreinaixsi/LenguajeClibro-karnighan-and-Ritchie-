#include <stdio.h>
#define NUM_CHAR 128

int main(){
    int arreglo[NUM_CHAR] = {0};
    int c;
    while((c = getchar()) != EOF)
        ++arreglo[c];
                  for(int i = 0; i < NUM_CHAR; ++i){
                      if (arreglo[i] == 0) continue;
                      putchar(i);
                      putchar(' ');
                      for(int j = 0; j < arreglo[i]; ++j)
                            putchar('*');
                      putchar('\n');
                      }
                  }
