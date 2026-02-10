#include <stdio.h>

int lower(int c); // Prototipo añadido aquí

void main(){
    printf("El valor de 'A' en minuscula es '%c'\n", lower('A'));
    printf("El valor de 'W' en minuscula es '%c'\n", lower('W'));
}

int lower(int c){
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}