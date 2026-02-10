#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define MAXBUF 100

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    char buf[MAXBUF];

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        p++;
        if (*p == '.') p++; // ignorar punto decimal opcional
        switch (*p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf("%s", sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}

int main() {
    minprintf("Entero: %d, Real: %f, Cadena: %s\n", 10, 3.1416, "Hola");
    return 0;
}