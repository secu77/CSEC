#include <stdio.h>

/* Multiple line
   comment, 
   why not
 */

int add_numbers(int a, int b)
{
	int sum;

	sum = a + b;

	return sum;
}

// One line comment

int main(int argc, char *argv[])
{
	int result;

	int(*myfunc_ptr)(int, int);

	myfunc_ptr = &add_numbers;

	result = myfunc_ptr(3, 7);

	printf("result = %d\n", result);

	return 0;
}
