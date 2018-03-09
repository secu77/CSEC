#include <stdio.h>

int main(int argc, char *argv[])
{
	int num1;
	int num2;
	int num3;
	char mychar;

	num1 = 13;
	num2 = 7;

	printf("Value of \"num1\" = %d\nValue of \"num2\" = %d\n", num1, num2);

	num3 = num1 + num2;
	printf("Result of vars \"num1\" + \"num2\" = %d\n", num3);

	mychar = 'x';
	printf("Value of character variable \"mychar\" = %c\n", mychar);
	printf("Value of character variable \"mychar\" in ASCII = %d\n", mychar);

	return 0;
}
