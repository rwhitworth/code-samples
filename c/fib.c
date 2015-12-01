#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#include <assert.h> // assert
#include <math.h> // sqrt and lround

int fib_r(int seq_num)
{
	// 0, 1, 1, 2, 3, 5, 8, etc
	if (seq_num <= 0)
		return 0;
	if (seq_num == 1)
		return 0;
	if (seq_num == 2)
		return 1;
	if (seq_num == 3)
		return 1;
	return (fib_r(seq_num - 1) + fib_r(seq_num - 2));
}
int fib_i(int seq_num)
{
	// 0, 1, 1, 2, 3, 5, 8, etc
	if (seq_num <= 0)
		return 0;
	if (seq_num == 1)
		return 0;
	if (seq_num == 2)
		return 1;
	if (seq_num == 3)
		return 1;

	int last1 = 0;
	int last2 = 1;
	int last3 = 1;
	int result = 0;
	for (int i = 3; i < seq_num; i++)
	{
		last1 = last2;
		last2 = last3;
		last3 = last1 + last2;
	}
	return last3;
}
int fib_a(int seq_num)
{
	if (seq_num <= 0)
		return 0;
	if (seq_num == 1)
		return 0;
	if (seq_num == 2)
		return 1;
	if (seq_num == 3)
		return 1;

	seq_num--;
	double sqrt5 = sqrt(5.0);
	// ( 1 / sq(5) ) * ( (1 + sq(5)) / 2 )^n - ( 1 / sq(5) ) * ( 1 - sq(5) ) / 2 )^n
	
	double i1 = 0.0;
	double i2 = 0.0;
	double i4 = 0.0;

	i1 = 1 / sqrt5;
	i2 = pow(((1 + sqrt5) / 2), seq_num);
	i4 = pow(((1 - sqrt5) / 2), seq_num);

	return lround((i1 * i2) - (i1 * i4));
}

void main()
{
	assert(fib_i(-1) == fib_r(-1));
	assert(fib_i(0) == fib_r(0));
	assert(fib_i(6) == fib_r(6));
	assert(fib_i(7) == fib_r(7));
	assert(fib_i(-1) == fib_a(-1));
	assert(fib_i(0) == fib_a(0));
	assert(fib_i(6) == fib_a(6));
	assert(fib_i(7) == fib_a(7));

	printf("1: %d\n", fib_a(1));
	printf("2: %d\n", fib_a(2));
	printf("3: %d\n", fib_a(3));
	printf("4: %d\n", fib_a(4));
	printf("5: %d\n", fib_a(5));
	printf("6: %d\n", fib_a(6));
	printf("7: %d\n", fib_a(7));
	printf("8: %d\n", fib_a(8));
	printf("9: %d\n", fib_a(9));
	printf("10: %d\n", fib_a(10));

	getchar();
	_CrtDumpMemoryLeaks();
	return;
}