#include <stdio.h>

#define TRUE 1
#define FALSE 0

/* Ejercicio 1-24: Escriba un programa para revisar los errores de sintaxis rudimentarios
 * de un programa en C, como paréntesis, llaves y corchetes no alineados. No olvide
 * las comillas ni los apóstrofos, las secuencias de escape y los comentarios.
 */

int main()
{
    int c; // Carácter actual leído
    int line = 1; // Contador de líneas
    
    // Banderas de estado
    int in_comment = FALSE;     // Dentro de un comentario /* ... */
    int in_line_comment = FALSE; // Dentro de un comentario de línea // ...
    int in_d_quotes = FALSE;    // Dentro de comillas dobles "..."
    int in_s_quote = FALSE;     // Dentro de apóstrofo simple '...'
    
    // Contadores de balance
    int p_count = 0; // Paréntesis ( )
    int b_count = 0; // Corchetes [ ]
    int c_count = 0; // Llaves { }
    
    // Bucle principal de lectura
    while ((c = getchar()) != EOF) {
        
        // 1. Contador de líneas
        if (c == '\n') {
            line++;
            in_line_comment = FALSE; // Los comentarios de línea terminan con \n
        }

        // 2. Manejo de estados especiales (comentarios, strings, caracteres)
        
        // --- Comentarios ---
        if (in_comment) {
            // Buscando el final del comentario de bloque: */
            if (c == '*' && getchar() == '/') {
                in_comment = FALSE;
            } else {
                // Volver a leer el caracter que se pudo haber consumido
                ungetc(c, stdin); 
            }
            continue; // Saltar todo lo demás dentro del comentario
        } 
        
        if (in_line_comment) {
            continue; // Saltar todo lo demás dentro del comentario de línea
        }
        
        // --- Strings y Caracteres ---
        
        // Si no estamos en un string o char, revisamos si entramos en uno
        if (!in_d_quotes && !in_s_quote) {
            if (c == '"') {
                in_d_quotes = TRUE;
                continue;
            } else if (c == '\'') {
                in_s_quote = TRUE;
                continue;
            }
        }
        
        // Si estamos en un string o char, manejamos secuencias de escape y salida
        if (in_d_quotes || in_s_quote) {
            if (c == '\\') {
                // Ignorar el siguiente caracter (secuencia de escape: \n, \t, \", \\, etc.)
                if (getchar() == EOF) {
                    fprintf(stderr, "Error en la línea %d: Secuencia de escape incompleta.\n", line);
                    break;
                }
            } else if (in_d_quotes && c == '"') {
                in_d_quotes = FALSE;
            } else if (in_s_quote && c == '\'') {
                in_s_quote = FALSE;
            }
            continue; // Saltar chequeo de balance dentro de strings/chars
        }
        
        // --- Detección de entrada a comentarios ---
        if (c == '/') {
            int next_c = getchar();
            if (next_c == '*') {
                in_comment = TRUE;
                continue;
            } else if (next_c == '/') {
                in_line_comment = TRUE;
                continue;
            } else {
                // Si no era un comentario, devolvemos el carácter que leímos de más
                ungetc(next_c, stdin); 
            }
        }
        
        // 3. Chequeo de balance de delimitadores
        
        switch (c) {
            case '(':
                p_count++;
                break;
            case ')':
                p_count--;
                if (p_count < 0) {
                    fprintf(stderr, "Error en la línea %d: Paréntesis ')' sin abrir.\n", line);
                    p_count = 0; // Resetear para encontrar más errores
                }
                break;
            case '[':
                b_count++;
                break;
            case ']':
                b_count--;
                if (b_count < 0) {
                    fprintf(stderr, "Error en la línea %d: Corchete ']' sin abrir.\n", line);
                    b_count = 0;
                }
                break;
            case '{':
                c_count++;
                break;
            case '}':
                c_count--;
                if (c_count < 0) {
                    fprintf(stderr, "Error en la línea %d: Llave '}' sin abrir.\n", line);
                    c_count = 0;
                }
                break;
        }
    }
    
    // 4. Chequeo final de balance
    
    if (in_comment) {
        fprintf(stderr, "Error: Comentario de bloque '/*' no cerrado al final del archivo.\n");
    }
    
    if (in_d_quotes) {
        fprintf(stderr, "Error: Comillas dobles '\"' no cerradas al final del archivo.\n");
    }
    
    if (in_s_quote) {
        fprintf(stderr, "Error: Apóstrofo simple '\\'' no cerrado al final del archivo.\n");
    }
    
    if (p_count != 0) {
        fprintf(stderr, "Error: Falta(n) %d paréntesis ')' al final del archivo.\n", p_count);
    }
    
    if (b_count != 0) {
        fprintf(stderr, "Error: Falta(n) %d corchete(s) ']' al final del archivo.\n", b_count);
    }
    
    if (c_count != 0) {
        fprintf(stderr, "Error: Falta(n) %d llave(s) '}' al final del archivo.\n", c_count);
    }
    
    if (p_count == 0 && b_count == 0 && c_count == 0 && !in_comment && !in_d_quotes && !in_s_quote) {
        printf("Revisión de sintaxis rudimentaria completa: No se encontraron errores de balance.\n");
    }
    
    return 0;
}