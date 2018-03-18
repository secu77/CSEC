#include <stdio.h>

int main(int argc, char *argv[])
{
	int myint;
	char mychar;
	float myfloat;
	long int mylongint;
	double mydouble, mysumdb;

	myint = 32;
	mychar = 'd';
	myfloat = 67.89;

	printf("size of myint = %lu\n", sizeof(myint));
	printf("size of int = %lu\n\n", sizeof(int));
	
	printf("size of mychar = %lu\n", sizeof(mychar));
	printf("size of char = %lu\n\n", sizeof(char));

	printf("size of mylong = %lu\n", sizeof(myfloat));
	printf("size of long = %lu\n\n", sizeof(float));

	printf("size of double = %lu\n", sizeof(double));
	printf("size of mydouble = %lu\n", sizeof(mydouble));

	return 0;
}
