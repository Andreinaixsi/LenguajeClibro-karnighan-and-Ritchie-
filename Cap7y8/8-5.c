#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <time.h>

void fsize(char *);

int main(int argc, char **argv) {
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

void fsize(char *name) {
    struct stat stbuf;
    struct dirent *dp;
    DIR *dfd;
    char buf[1024];

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: no se puede acceder a %s\n", name);
        return;
    }

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        /* Es un directorio: listar su contenido */
        if ((dfd = opendir(name)) == NULL) {
            fprintf(stderr, "fsize: no se puede abrir %s\n", name);
            return;
        }
        while ((dp = readdir(dfd)) != NULL) {
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
                continue;
            
            // Construir la ruta: nombre/archivo
            snprintf(buf, sizeof(buf), "%s/%s", name, dp->d_name);
            fsize(buf);
        }
        closedir(dfd);
    } else {
        /* Ejercicio 8-5: Imprimir información extendida (Inodo) */
        
        // Formatear la fecha de modificación
        char date[20];
        strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&stbuf.st_mtime));

        printf("%10ld bytes | Modificado: %s | Permisos: %o | %s\n", 
            (long)stbuf.st_size, 
            date,
            stbuf.st_mode & 0777, 
            name);
    }
}