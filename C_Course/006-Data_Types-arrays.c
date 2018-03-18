#include <stdio.h>

int main(int argv, char *argc[])
{
	int a[4];
	int b[4] = {54, 354, 2, 7829};

	a[0] = 78;
	a[1] = 89768;
	a[2] = 379;
	a[3] = 4;

	printf("array a = %d, %d, %d, %d\n", a[0], a[1], a[2], a[3]);
	printf("array b = %d, %d, %d, %d\n", b[0], b[1], b[2], b[3]);

	return 0;
}
