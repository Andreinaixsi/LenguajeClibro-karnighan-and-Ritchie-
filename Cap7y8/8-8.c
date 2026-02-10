#include <stdio.h>
#include "malloc_kr.h"

/* bfree: coloca un bloque arbitrario p en la lista libre */
unsigned bfree(void *p, unsigned n) {
    Header *hp;

    if (n < sizeof(Header) * 2) return 0;

    hp = (Header *)p;
    hp->s.size = n / sizeof(Header);
    
    mi_free((void *)(hp + 1));
    return hp->s.size;
}

int main() {
    printf("Probando Ejercicio 8-8 (bfree)...\n");
    static char buffer_extra[1024]; /* Memoria estática */
    
    unsigned unidades = bfree(buffer_extra, 1024);
    if (unidades > 0)
        printf("Se han inyectado %u unidades a la lista libre.\n", unidades);
        
    return 0;
}