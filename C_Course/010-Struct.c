#include <stdio.h>

union UData {
   int i;
   float f;
   char str[8];
};

int main(int argc, char *argv[])
{
	struct {
		int a;
		float b;
		int c;
	} myst;
	union UData udata;
	
	myst.a = 4;
	myst.b = 3.37;
	myst.c = 8;

	printf("a = %d, b=%f, c = %d\n", myst.a, myst.b, myst.c);

	return 0;
}
