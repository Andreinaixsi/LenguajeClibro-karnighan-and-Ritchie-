#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    int lines[100];
    int line_count;
    struct tnode *left;
    struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);

int main() {
    struct tnode *root = NULL;
    char word[MAXWORD];
    int line_num = 1;
    int c;

    while ((c = getword(word, MAXWORD)) != EOF) {
        if (isalpha(word[0]) && strcmp(word, "int") != 0 && strcmp(word, "char") != 0) {
            root = addtree(root, word, line_num);
        }
        if (c == '\n') {
            line_num++;
        }
    }

    treeprint(root);
    return 0;
}



struct tnode *addtree(struct tnode *p, char *w, int line) {
    int cond;

    if (p == NULL) {
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w); 
        p->count = 1;
        p->lines[0] = line;
        p->line_count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        if (p->line_count < 100 && p->lines[p->line_count - 1] != line) {
            p->lines[p->line_count++] = line;
        }
    } else if (cond < 0) {
        p->left = addtree(p->left, w, line);
    } else {
        p->right = addtree(p->right, w, line);
    }
    return p;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%10s: ", p->word);
        for (int i = 0; i < p->line_count; i++) {
            printf("%d%s", p->lines[i], (i == p->line_count - 1) ? "" : ", ");
        }
        printf("\n");
        treeprint(p->right);
    }
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar()) && c != '\n');

    if (c != EOF) *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    }
    *w = '\0';
    return word[0];
}