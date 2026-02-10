#include <stdio.h>

#define MAXLINE 1000

int main(void){
	int i, c;
	char line[MAXLINE];
	for(i =0; ((i < MAXLINE-1) + ((c = getchar())!= '\n') + (c !=
		 EOF)) == 3; ++i)
			putchar(c);
			putchar('\n');
			return 0;
}