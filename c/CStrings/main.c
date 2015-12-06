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
	// multi letter word, single letter search
	assert(index("hello123", "h") == 0);
	assert(index("hello123", "e") == 1);
	assert(index("hello123", "l") == 2);
	assert(index("hello123", "o") == 4);
	assert(index("hello123", "3") == 7);
	assert(index("hello123", "4") == -1);

	// multi letter word, single letter search
	assert(index("hello123", "h") == 0);
	assert(index("hello123", "e") == 1);
	assert(index("hello123", "l") == 2);
	assert(index("hello123", "o") == 4);
	assert(index("hello123", "3") == 7);
	assert(index("hello123", "4") == -1);

	// multi letter word, multi letter search
	assert(index("hello123", "he") == 0);
	assert(index("hello123", "ll") == 2);
	assert(index("hello123", "lo") == 3);
	assert(index("hello123", "23") == 6);

	// negative tests
	assert(index("hello123", "Z") == -1);
	assert(index("hello123", "ZZ") == -1);
	assert(index("hello123", NULL) == -1);
	assert(index(NULL, "4") == -1);
	assert(index("", "1") == -1);
	assert(index("1", "") == -1);
}
void test_index_pos()
{
	// multi letter word, single letter search, start at zero
	assert(index_pos("hello123", "h", 0) == 0);
	assert(index_pos("hello123", "e", 0) == 1);
	assert(index_pos("hello123", "l", 0) == 2);
	assert(index_pos("hello123", "o", 0) == 4);
	assert(index_pos("hello123", "3", 0) == 7);
	assert(index_pos("hello123", "4", 0) == -1);

	// multi letter word, single letter search, start middle
	assert(index_pos("hello123", "h", 2) == -1);
	assert(index_pos("hello123", "e", 2) == -1);
	assert(index_pos("hello123", "l", 2) == 2);
	assert(index_pos("hello123", "o", 2) == 4);
	assert(index_pos("hello123", "3", 2) == 7);
	assert(index_pos("hello123", "4", 2) == -1);

	// multi letter word, single letter search, start at last
	assert(index_pos("hello123", "h", 7) == -1);
	assert(index_pos("hello123", "e", 7) == -1);
	assert(index_pos("hello123", "l", 7) == -1);
	assert(index_pos("hello123", "o", 7) == -1);
	assert(index_pos("hello123", "3", 7) == 7);
	assert(index_pos("hello123", "4", 7) == -1);

	// multi letter word, multi letter search
	assert(index_pos("hello123", "he", 0) == 0);
	assert(index_pos("hello123", "he", 1) == -1);
	assert(index_pos("hello123", "ll", 0) == 2);
	assert(index_pos("hello123", "ll", 1) == 2);
	assert(index_pos("hello123", "ll", 2) == 2);
	assert(index_pos("hello123", "ll", 3) == -1);

	// negative tests
	assert(index_pos("hello123", "h", 100) == -1);
	assert(index_pos("hello123", NULL, 0) == -1);
	assert(index_pos(NULL, "4", 0) == -1);
	assert(index_pos("hello123", "h", -1) == -1);
}
void test_lc()
{
	char *q = NULL;

	q = lc("HELLO");
	assert(strcmp(q, "hello") == 0);
	free(q);

	q = lc("HELLO123");
	assert(strcmp(q, "hello123") == 0);
	free(q);

	q = lc("hello");
	assert(strcmp(q, "hello") == 0);
	free(q);

	q = lc(NULL);
	assert(q == NULL);
	free(q);

	q = lc("");
	assert(q == NULL);
	free(q);
}

void main()
{
	test_chop();
	test_chomp();
	test_chr();
	test_hex();
	test_index();
	test_index_pos();
	test_lc();



	printf("Success is likely.\n");
	getchar();
	return;
}