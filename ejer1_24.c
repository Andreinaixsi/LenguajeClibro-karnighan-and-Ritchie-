#include <stdio.h>

#define TRUE 1
#define FALSE 0

/* Versión Simplificada: Prioriza la claridad sobre la robustez completa.
 * Chequea balance de () [] {} y maneja rudimentariamente comentarios y strings.
 */

int main()
{
    int c;
    int line = 1;

    // Banderas de estado
    int in_comment = FALSE;
    int in_d_quotes = FALSE;

    // Contadores de balance específicos (más fácil de rastrear que un solo contador total)
    int p_count = 0; // ( )
    int b_count = 0; // [ ]
    int c_count = 0; // { }

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            line++;
        }

        // 1. Manejo de Strings ("...")
        if (in_d_quotes) {
            if (c == '\\') {
                // Ignorar el siguiente caracter (secuencia de escape)
                if (getchar() == EOF) break;
            } else if (c == '"') {
                in_d_quotes = FALSE;
            }
            continue; // Saltar chequeo de balance y comentarios dentro del string
        } else if (c == '"') {
            in_d_quotes = TRUE;
            continue;
        }

        // 2. Manejo de Comentarios (Bloque /* */)
        if (in_comment) {
            if (c == '*' && getchar() == '/') {
                in_comment = FALSE;
            } else {
                // Devolver el carácter que pudo haber sido consumido por getchar()
                ungetc(c, stdin);
            }
            continue; // Saltar chequeo de balance dentro del comentario
        } else if (c == '/') {
            int next_c = getchar();
            if (next_c == '*') {
                in_comment = TRUE;
                continue;
            } else if (next_c == '/') {
                // Comentario de línea, ignorar hasta el salto de línea
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                if (c == '\n') line++;
                continue;
            } else {
                ungetc(next_c, stdin); // Si no era comentario, devolver el carácter
            }
        }
        
        // 3. Chequeo de Balance
        switch (c) {
            case '(': p_count++; break;
            case ')': p_count--; break;
            case '[': b_count++; break;
            case ']': b_count--; break;
            case '{': c_count++; break;
            case '}': c_count--; break;
        }
        
        // 4. Reporte de errores inmediatos (cierre sin apertura)
        if (p_count < 0) {
            fprintf(stderr, "Error en línea %d: Paréntesis ')' sin abrir.\n", line);
            p_count = 0;
        }
        if (b_count < 0) {
            fprintf(stderr, "Error en línea %d: Corchete ']' sin abrir.\n", line);
            b_count = 0;
        }
        if (c_count < 0) {
            fprintf(stderr, "Error en línea %d: Llave '}' sin abrir.\n", line);
            c_count = 0;
        }
    }

    // 5. Reporte de errores finales (apertura sin cierre)
    if (p_count > 0 || b_count > 0 || c_count > 0) {
        fprintf(stderr, "\n--- Errores de Balance Finales ---\n");
        if (p_count > 0) fprintf(stderr, "Falta(n) %d paréntesis(s) de cierre.\n", p_count);
        if (b_count > 0) fprintf(stderr, "Falta(n) %d corchete(s) de cierre.\n", b_count);
        if (c_count > 0) fprintf(stderr, "Falta(n) %d llave(s) de cierre.\n", c_count);
    } else if (in_comment) {
        fprintf(stderr, "Error: Comentario de bloque '/*' no cerrado.\n");
    } else if (in_d_quotes) {
        fprintf(stderr, "Error: Comillas dobles '\"' no cerradas.\n");
    } else if (p_count == 0 && b_count == 0 && c_count == 0) {
        printf("Revisión rudimentaria: No se encontraron errores de balance obvios.\n");
    }

    return 0;
}