#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> // En Windows podrías necesitar <io.h>
#include <stdarg.h>
#include <stdlib.h>

void error(char *fmt, ...);
void filecopy(int ifd, int ofd);

int main(int argc, char *argv[]) {
    int fd;

    if (argc == 1) { // Si no hay argumentos, copia la entrada estándar
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                error("8-1: no se puede abrir %s", *argv);
            } else {
                filecopy(fd, 1); // 1 es la salida estándar (pantalla)
                close(fd);
            }
        }
    }
    return 0;
}

/* filecopy: copia el archivo ifd al archivo ofd */
void filecopy(int ifd, int ofd) {
    char buf[BUFSIZ];
    int n;

    while ((n = read(ifd, buf, BUFSIZ)) > 0) {
        if (write(ofd, buf, n) != n) {
            error("8-1: error de escritura");
        }
    }
}

void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}