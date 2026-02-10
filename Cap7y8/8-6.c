#include <stdio.h>
#include "malloc_kr.h"

void *mi_calloc(unsigned n, unsigned size) {
    unsigned i, nb;
    char *p, *q;

    nb = n * size;
    if ((p = q = mi_malloc(nb)) != NULL) {
        for (i = 0; i < nb; i++)
            *p++ = 0;
    }
    return (void *) q;
}

int main() {
    printf("Probando calloc (8-6)...\n");
    int *nums = (int *) mi_calloc(5, sizeof(int));
    if (nums) {
        printf("nums[0] = %d (Debe ser 0)\n", nums[0]);
        mi_free(nums);
        printf("Memoria liberada.\n");
    }
    return 0;
}