#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PERMS 0666

struct _flags {
    unsigned int _READ  : 1;
    unsigned int _WRITE : 1;
    unsigned int _UNGET : 1;
    unsigned int _BIGBUF: 1;
    unsigned int _EOF   : 1;
    unsigned int _ERR   : 1;
};

typedef struct _iobuf {
    int  cnt;
    char *ptr;
    char *base;
    struct _flags flag;
    int  fd;
} MY_FILE;

// --- FUNCIONES QUE ESCRIBIMOS ANTES ---

int _flushbuf(int x, MY_FILE *fp) {
    int bufsize = (fp->flag._BIGBUF) ? 1024 : 1;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) return -1;
    } else {
        int n = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, n) != n) return -1;
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;
    return (unsigned char) (*fp->ptr++ = (char)x);
}

int mi_fflush(MY_FILE *fp) {
    if (fp->flag._WRITE && fp->base != NULL) {
        int n = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, n) != n) return -1;
        fp->ptr = fp->base;
        fp->cnt = 1024;
    }
    return 0;
}

MY_FILE *mi_fopen(char *name, char *mode) {
    int fd;
    MY_FILE *fp = (MY_FILE *) malloc(sizeof(MY_FILE));
    if (*mode == 'w') fd = creat(name, PERMS);
    else return NULL;
    
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag._WRITE = 1;
    fp->flag._BIGBUF = 1;
    return fp;
}

int mi_fclose(MY_FILE *fp) {
    mi_fflush(fp);
    close(fp->fd);
    free(fp->base);
    free(fp);
    return 0;
}

#define mi_putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), (p)))

// --- EL MAIN PARA EJECUTAR ---

int main() {
    MY_FILE *f = mi_fopen("prueba_8-3.txt", "w");
    
    if (f == NULL) {
        write(2, "Error al crear archivo\n", 23);
        return 1;
    }

    char *mensaje = "Hola! Este archivo fue escrito usando el ejercicio 8-3.\n";
    for (int i = 0; i < strlen(mensaje); i++) {
        mi_putc(mensaje[i], f);
    }

    mi_fclose(f);
    write(1, "Proceso terminado. Revisa el archivo 'prueba_8-3.txt'\n", 53);
    
    return 0;
}