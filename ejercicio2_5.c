#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
	char s1[] = "Murcielago contiene todas las vocales.";
	char s2[] = "aeiou";
	printf("Cadena 1 \'%s\', cadena 2 \'%s\'\n", s1, s2);
	printf("La primera coincidencia está en la posición \'%d\'\n", any(s1, s2));

	return 0;
}


int any(char s1[], char s2[])
{
	int i, j;

	for (j = 0; s1[j] != '\0'; ++j) {
		
		for (i = 0; s2[i] != '\0'; ++i) {
			
			if (s1[j] == s2[i]) {
				// Al encontrar la primera coincidencia, se devuelve el índice 'j' inmediatamente.
				return j; 
			}
		}
	}
	
	// Si los bucles terminan sin encontrar coincidencias.
	return -1;
}