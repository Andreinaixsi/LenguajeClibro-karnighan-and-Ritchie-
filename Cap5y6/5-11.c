#include <stdio.h>
#include <stdlib.h>

#define MAX_TABS 100
#define DEFAULT_TAB 8

int tabs[MAX_TABS];
int tab_count = 0;

void settabs(int argc, char *argv[]) {
    tab_count = 0;
    if (argc <= 1) {
        tabs[tab_count++] = DEFAULT_TAB;
    } else {
        while (--argc > 0) {
            tabs[tab_count++] = atoi(*++argv);
        }
    }
}

int nexttab(int col) {
    static int tab_index = 0;
    if (tab_count == 0) {
        return DEFAULT_TAB - (col % DEFAULT_TAB);
    }
    if (tab_index >= tab_count) {
        tab_index = 0;
    }
    int next = tabs[tab_index];
    if (col >= next) {
        tab_index++;
        if (tab_index >= tab_count) {
            tab_index = 0;
        }
        next = tabs[tab_index];
    }
    return next - col;
}

int main(int argc, char *argv[]) {
    settabs(argc, argv);
    
    int c, col = 0, spaces;
    
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            spaces = nexttab(col);
            while (spaces-- > 0) {
                putchar(' ');
                col++;
            }
        } else {
            putchar(c);
            if (c == '\n')
                col = 0;
            else
                col++;
        }
    }
    return 0;
}