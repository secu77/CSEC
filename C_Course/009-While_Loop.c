#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 10;

	do {
		printf("i = %d\n", i);
		i++;
	} while (i < 15);

	return 0;
}
