#include <stdio.h>

int  rightrot(int x, int n);

int main()
{

	printf("%d\n", rightrot(15, 3));
	return 0;
}
 
 	int rightrot(int x, int n)
 	{
		int y, pos_izq;

		while (n > 0) {
			 y = x & ~(~0 << 1);
 			if (y == 1) {
 				pos_izq = 0;
 				while (!pos_izq) {
                                      y = y << 1;
                                      if ((y << 1) <= 0)
                                           pos_izq = 1;
                                }                                
                         }
                         x = x >> 1;
                         x = x | y;
                         --n;
                }
                return x;

        }