#include <stdio.h>

/* Cambiamos el nombre a mi_strcat para que no choque con la de C */
void mi_strcat(char *s, char *t) {
    while (*s)      /* encuentra el fin de s */
        s++;
    while ((*s++ = *t++)) /* copia t al final de s */
        ;
}

int main() {
    /* Creamos un espacio grande para la cadena de destino */
    char saludo[50] = "Hola ";
    char nombre[] = "Mundo";

    printf("Antes: %s\n", saludo);
    
    mi_strcat(saludo, nombre);
    
    printf("Despues: %s\n", saludo);

    return 0;
}