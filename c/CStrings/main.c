#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "CStrings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_chop()
{
	char *q = strdup("hello");
	assert(q != 0);
	chop(q);
	assert(strcmp("hell", q) == 0);
	free(q);
}
void test_chomp()
{
	char *q = strdup("hello");
	assert(q != 0);
	int result = chomp(q, 'o');
	assert(strcmp("hell", q) == 0);
	assert(result == 1);
	result = chomp(q, 'l');
	assert(strcmp("he", q) == 0);
	assert(result == 2);
	result = chomp(q, 'Z');
	assert(strcmp("he", q) == 0);
	assert(result == 0);
	result = chomp(q, 'e');
	assert(strcmp("h", q) == 0);
	assert(result == 1);
	result = chomp(q, 'h');
	assert(strcmp("", q) == 0);
	assert(result == 1);
	result = chomp(q, 'Z');
	assert(strcmp("", q) == 0);
	assert(result == 0);
	free(q);

	q = strdup("aaaaa");
	result = chomp(q, 'a');
	assert(strcmp("", q) == 0);
	assert(result == 5);
	free(q);
}
void test_chr()
{
	const int A_int = 65;
	const char A_char = 'A';
	assert(chr(A_int) == A_char);
}

void main()
{
	test_chop();
	test_chomp();
	test_chr();

	printf("Success is likely.\n");
	getchar();
	return;
}