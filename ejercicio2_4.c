#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(){
	char s1[] = "Murcielago contiene todas las vocales.";
	char s2[] = "aeiou";
	printf("Oración inicial \'%s\', letras a quitar \'%s\'\n", s1, s2);
	squeeze(s1, s2);
		printf("%s\n", s1);

		return 0;
	}

	/* squeeze: borra los caracteres que coinciden de s1 y s2 */
	void squeeze(char s1[], char s2[]) {
		int i, j, k;

		for (k = 0; s2[k] != '\0'; k++) {
			for (i = j = 0; s1[i] != '\0'; i++)
				if (s1[i] != s2[k])
					s1[j++] = s1[i];
			s1[j] = '\0';
		}

}