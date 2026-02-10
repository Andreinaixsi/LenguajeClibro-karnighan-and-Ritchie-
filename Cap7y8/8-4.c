#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> 

#define BUFSIZE 1024
#define PERMS 0666

/* --- 1. ESTRUCTURAS --- */
/* Definimos los flags nosotros mismos */
struct _mis_flags {
    unsigned int _READ  : 1;
    unsigned int _WRITE : 1;
    unsigned int _UNGET : 1;
    unsigned int _BIGBUF: 1;
    unsigned int _EOF   : 1;
    unsigned int _ERR   : 1;
};

/* CORRECCIÓN: Cambiamos '_iobuf' a '_mi_iobuf' para no chocar con stdio.h */
typedef struct _mi_iobuf {
    int  cnt;          
    char *ptr;         
    char *base;        
    struct _mis_flags flag; /* Usamos nuestros flags */
    int  fd;           
} MY_FILE;

/* --- 2. FUNCIONES AUXILIARES --- */

int _fillbuf(MY_FILE *fp) {
    int bufsize;
    if (!fp->flag._READ || fp->flag._EOF || fp->flag._ERR) return -1;
    bufsize = (fp->flag._BIGBUF) ? BUFSIZE : 1;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) return -1;
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) fp->flag._EOF = 1;
        else fp->flag._ERR = 1;
        fp->cnt = 0;
        return -1;
    }
    return (unsigned char) *fp->ptr++;
}

MY_FILE *mi_fopen(char *name, char *mode) {
    int fd;
    MY_FILE *fp;
    if (*mode != 'r') return NULL; 
    
    /* Reservamos memoria para NUESTRA estructura */
    if ((fp = (MY_FILE *) malloc(sizeof(MY_FILE))) == NULL) return NULL;
    
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

#define mi_getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

/* --- 3. EJERCICIO 8-4: fseek --- */

int mi_fseek(MY_FILE *fp, long offset, int origin) {
    long rc = 0; 

    if (fp->flag._READ) {
        if (origin == 1) { 
            /* Si es relativo a la posición actual, restamos lo que queda en buffer */
            offset -= fp->cnt; 
        }
        fp->cnt = 0; 
        fp->ptr = fp->base; 
    } 
    /* Nota: La escritura no está implementada en este ejemplo de lectura */

    if (rc != -1) {
        rc = lseek(fp->fd, offset, origin);
    }
    
    return (rc == -1) ? -1 : 0;
}

/* --- 4. MAIN --- */
int main() {
    /* Crear archivo de prueba usando llamadas de sistema estándar para asegurar que existe */
    int fd = open("test_8-4.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error creando archivo");
        return 1;
    }
    write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    close(fd);

    /* Usar nuestra implementación */
    MY_FILE *fp = mi_fopen("test_8-4.txt", "r");
    if (fp == NULL) {
        printf("Error abriendo archivo con mi_fopen\n");
        return 1;
    }

    printf("Leyendo 3 caracteres:\n");
    printf("%c ", mi_getc(fp)); // A
    printf("%c ", mi_getc(fp)); // B
    printf("%c\n", mi_getc(fp)); // C
    
    printf("\n[fseek] Saltando 2 adelante (desde actual)...\n");
    mi_fseek(fp, 2L, 1); // Salta D, E -> F
    
    printf("Caracter actual: %c\n", mi_getc(fp)); // Debería ser F

    printf("\n[fseek] Volviendo al inicio (offset 0, origin 0)...\n");
    mi_fseek(fp, 0L, 0);
    
    printf("Caracter al inicio: %c\n", mi_getc(fp)); // A

    printf("\n[fseek] Al final - 1 (offset -1, origin 2)...\n");
    mi_fseek(fp, -1L, 2);
    
    printf("Ultimo caracter: %c\n", mi_getc(fp)); // Z

    /* Limpieza simple (en un programa real haríamos mi_fclose) */
    close(fp->fd);
    free(fp->base);
    free(fp);

    return 0;
}