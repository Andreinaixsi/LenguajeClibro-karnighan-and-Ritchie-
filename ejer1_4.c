#include <stdio.h>
 /* imprime la tabla Fahrenheit-Celsius
 para fahr = 0, 20, ..., 300*/
int main(){
 // declaraciones
 float fahr, celsius;
 int lower, upper, step;
 // inicialización de variables
 lower = 0;
 upper = 300;
 step = 20;
 celsius = lower;
 // encabezado
 printf("Tabla de Temperaturas\n");
 printf("Celsius\t\tFahrenheit\n");
 // realiza la operación e impresión de celsius a farenheit
 while (celsius <= upper) {
 fahr = (celsius*1.80) + 32.0;
 printf("%3.0f\t\t%6.0f\n", celsius, fahr);
 celsius = celsius + step;
 }
 return 0;
 }