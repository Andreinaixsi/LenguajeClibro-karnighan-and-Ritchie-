#include <stdio.h>
#define MAXLINE 30

int gettline(char line[], int maxline);
void invertir(char line[]);

int main(){

			char line[MAXLINE];

			while(gettline(line, MAXLINE) > 0) {
				invertir(line);
				printf("%s\n", line);
			  }
			return 0;
			}

			void invertir(char s[]){
			     int i, j;
			     char mantener;
			     i = 0;
			     while(s[i] != '\0')
				  ++i;

			     j = i - 1;

			     for (i = 0; i < j; ++i){
				  mantener = s[i];
				  s[i] = s[j];
				  s[j] = mantener;
				  --j;
			}
		}

		int gettline(char s[], int lim){
		    int i, c;

		    for (i = 0; (c=getchar()) != EOF && c != '\n' &&
			 i < lim - 1; ++i){
			    s[i] = c;
			}
			if (c == '\n'){
			    s[i] = '\n';
			    i++;
		}
		s[i] = '\0';

		return i;
}