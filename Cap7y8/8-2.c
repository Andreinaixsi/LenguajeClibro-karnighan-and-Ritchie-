#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

/* Definición de la estructura FILE con campos de bits según el ejercicio 8-2 */
struct _flags {
    unsigned int _READ  : 1;
    unsigned int _WRITE : 1;
    unsigned int _UNGET : 1;
    unsigned int _BIGBUF: 1;
    unsigned int _EOF   : 1;
    unsigned int _ERR   : 1;
};

typedef struct _iobuf {
    int  cnt;          /* caracteres restantes en el búfer */
    char *ptr;         /* posición actual dentro del búfer */
    char *base;        /* dirección de inicio del búfer */
    struct _flags flag;/* banderas de estado */
    int  fd;           /* descriptor de archivo del sistema */
} MY_FILE;

/* Función para llenar el búfer cuando se queda vacío */
int _fillbuf(MY_FILE *fp) {
    int bufsize;

    if (!fp->flag._READ || fp->flag._EOF || fp->flag._ERR)
        return -1;

    bufsize = (fp->flag._BIGBUF) ? BUFSIZE : 1;

    if (fp->base == NULL) { /* ¿Aún no tenemos búfer? Creamos uno */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return -1;
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return -1;
    }

    return (unsigned char) *fp->ptr++;
}

/* Nuestro fopen personalizado */
MY_FILE *mi_fopen(char *name, char *mode) {
    int fd;
    MY_FILE *fp;

    if (*mode != 'r') return NULL; // Simplificado solo para lectura

    if ((fp = (MY_FILE *) malloc(sizeof(MY_FILE))) == NULL)
        return NULL;

    if ((fd = open(name, O_RDONLY, 0)) == -1) {
        free(fp);
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag._READ = 1;
    fp->flag._WRITE = 0;
    fp->flag._EOF = 0;
    fp->flag._ERR = 0;
    fp->flag._BIGBUF = 1;

    return fp;
}

/* Definición de la macro para leer carácter por carácter */
#define mi_getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

int main(int argc, char *argv[]) {
    int c;
    MY_FILE *fp;

    if (argc < 2) {
        write(1, "Uso: 8-2.exe archivo\n", 21);
        return 1;
    }

    if ((fp = mi_fopen(argv[1], "r")) == NULL) {
        write(2, "No se pudo abrir el archivo\n", 28);
        return 1;
    }

    // Leemos el archivo usando nuestra propia lógica de búfer
    while ((c = mi_getc(fp)) != -1) {
        char ch = (char)c;
        write(1, &ch, 1);
    }

    return 0;
}