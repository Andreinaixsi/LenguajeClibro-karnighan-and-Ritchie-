#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int minscanf(char *fmt, ...) {
    va_list ap;
    char *p;
    int *ival, c;
    double *dval;
    char *sval, buf[100];
    int matched = 0;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (isspace(*p)) continue;
        if (*p != '%') {
            while (isspace(c = getchar()));
            if (c != *p) break;
            continue;
        }
        p++;
        switch (*p) {
            case 'd':
                ival = va_arg(ap, int *);
                if (scanf("%d", ival) == 1) matched++;
                break;
            case 'f':
                dval = va_arg(ap, double *);
                if (scanf("%lf", dval) == 1) matched++;
                break;
            case 's':
                sval = va_arg(ap, char *);
                if (scanf("%s", sval) == 1) matched++;
                break;
            default:
                break;
        }
    }
    va_end(ap);
    return matched;
}

int main() {
    int i;
    double d;
    char s[100];
    printf("Introduce un entero, un real y una cadena: ");
    int n = minscanf("%d %f %s", &i, &d, s);
    printf("Leidos %d valores: %d %f %s\n", n, i, d, s);
    return 0;
}