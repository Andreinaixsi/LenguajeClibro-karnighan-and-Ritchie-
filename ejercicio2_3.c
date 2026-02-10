#include <stdio.h>
#define SI 1
#define NO 0
int htoi(char s[]);

int main(){
	char s[] = "0Xa1A";
	char f[] = "0XFF";
	printf("%s a decimal es %d\n", s, htoi(s));
		printf("%s a decimal es %d\n", f, htoi(f));
		return 0;
	}
	int htoi(char s[]){
		int digHexa, i, enHexa, n;
		i = 0;
		if (s[i] == '0'){
			++i;
			if(s[i] == 'x' || s[i] == 'X')
				++i;
		}
		n = 0;
		enHexa = SI;
		for( ; enHexa == SI; ++i){
			if(s[i] >= '0' && s[i] <= '9')
				digHexa = s[i] - '0';
			else if(s[i] >= 'a' && s[i] <= 'f')
				digHexa = s[i] - 'a' + 10;
			else if(s[i] >= 'A' && s[i] <= 'F')
				digHexa = s[i] - 'A' + 10;
			else
				enHexa = NO;
			if(enHexa == SI)
				n = 16 * n + digHexa;
		}
		return n;
}