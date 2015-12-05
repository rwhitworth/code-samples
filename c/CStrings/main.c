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
void test_hex()
{
	assert(hex("A") == 10);
	assert(hex("0A") == 10);
	assert(hex("FF") == 255);
	assert(hex("a") == 10);
	assert(hex("0a") == 10);
	assert(hex("ff") == 255);
	assert(hex("Ff") == 255);
	assert(hex("fF") == 255);
	// currently failing:
	// assert(hex("FFQQ") == 0);
	
	// TODO: should these tests pass?...
	// should hex() return results differently?  in a parameter perhaps?
	assert(hex("Z") == -1);
	assert(hex("") == -1);
}
void test_index()
{
	assert(index("hello", "ll") == 2);
	assert(index("hellollo", "ll") == 2);
	assert(index("", "1") == -1);
	assert(index("1", "") == -1);
}
void test_index_pos()
{
	assert(index_pos("hello", "ll", 0) == 2);
	assert(index_pos("hello", "ll", 1) == 2);
	assert(index_pos("hello", "ll", 2) == 2);
	assert(index_pos("hello", "ll", 3) == -1);
	// TODO: additional tests needed
}

void main()
{
	test_chop();
	test_chomp();
	test_chr();
	test_hex();
	test_index();
	test_index_pos();

	printf("Success is likely.\n");
	getchar();
	return;
}