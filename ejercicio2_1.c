#include <stdio.h>
#include <limits.h>

int main(){
// Con signo
printf("Minimo signed char = %d\n", SCHAR_MIN);
printf("Maximo signed char = %d\n", SCHAR_MAX);
printf("Minimo signed short = %d\n", SHRT_MIN);
printf("Maximo signed short = %d\n", SHRT_MAX);

printf("Minimo signed int = %d\n", INT_MIN);
printf("Maximo signed int = %d\n", INT_MAX);
printf("Minimo signed long = %ld\n", LONG_MIN);
printf("Maximo signed long = %ld\n", LONG_MAX);
printf("\n");
// Sin signo
printf("unsigned char max = %u\n", UCHAR_MAX);
printf("unsigned short max = %u\n", USHRT_MAX);
printf("unsigned int max = %u\n", UINT_MAX);
printf("unsigned long max = %lu\n", ULONG_MAX);
}
