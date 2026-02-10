#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int tabstart = 0;
int tabinterval = 8;

void parse_args(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            tabstart = atoi(argv[++i]);
        } else if (strcmp(argv[i], "+n") == 0 && i + 1 < argc) {
            tabinterval = atoi(argv[++i]);
        }
    }
}

int is_tabstop(int col) {
    if (col < tabstart) return 0;
    return ((col - tabstart) % tabinterval) == 0;
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    
    int c, col = 0, spaces = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            spaces++;
            col++;
        } else {
            if (spaces > 0) {
                int tab_pos = 0;
                while (spaces > 0) {
                    if (is_tabstop(col - spaces)) {
                        putchar('\t');
                        tab_pos = col - spaces;
                        while (tab_pos < col && !is_tabstop(tab_pos)) {
                            tab_pos++;
                        }
                        spaces -= (tab_pos - (col - spaces));
                    } else {
                        putchar(' ');
                        spaces--;
                    }
                }
            }
            putchar(c);
            if (c == '\n')
                col = 0;
            else
                col++;
            spaces = 0;
        }
    }
    return 0;
}