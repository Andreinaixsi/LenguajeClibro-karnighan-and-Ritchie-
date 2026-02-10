#ifndef MALLOC_KR_H
#define MALLOC_KR_H

#include <stddef.h>

typedef long Align;

union header {
    struct {
        union header *ptr; 
        unsigned size;     
    } s;
    Align x;               
};

typedef union header Header;

void *mi_malloc(unsigned nbytes);
void mi_free(void *ap);

#endif