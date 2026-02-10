#include <stdio.h>

#define MAXLINE 1000 /* maxima cantidad de caracteres */
#define TABWIDTH 4 /* ancho del tab */

int gettline(char line[], int maxline);
void detab(char to[], char from[]);

int main(void)
	{
		int len;
		char line[MAXLINE];
		char nline[MAXLINE];

		while ((len = gettline(line, MAXLINE)) > 0) {
			detab(nline, line);
			printf("%s", nline);
		}

		return 0;
	}


	int gettline(char s[], int lim)
	{
		int i, c;

		for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
			s[i] = c;
		if (c == '\n') {
			s[i] = c;
			++i;
		}
		s[i] = '\0';

		return i;
	}

	/* detab: reemplaza los tabs por caracteres de espacio con el mismo tamaño de tab */
	void detab(char to[], char from[])
	{
		int i, j, n;

		i = j = n = 0;
		while ((to[j] = from[i]) != '\0') {
		if (to[j] == '\t')
			for (n = 0; n < TABWIDTH; ++n, ++j)
				to[j] = ' ';
		else
			++j;
		++i;
	}
}