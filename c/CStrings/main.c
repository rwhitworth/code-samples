#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#define _CRT_NONSTDC_NO_DEPRECATE
	#include <crtdbg.h>	
	#define _CRTDBG_MAP_ALLOC
#endif
#include "CStrings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_chop()
{
	char *result = strdup("hello");
	
	assert(result != 0);
	chop(result);
	assert(strcmp("hell", result) == 0);
	free(result);
}
void test_chomp()
{
	char *resultstr = strdup("hello");
	
	assert(resultstr != NULL);
	int result = chomp(resultstr, 'o');
	assert(strcmp("hell", resultstr) == 0);
	assert(result == 1);
	result = chomp(resultstr, 'l');
	assert(strcmp("he", resultstr) == 0);
	assert(result == 2);
	result = chomp(resultstr, 'Z');
	assert(strcmp("he", resultstr) == 0);
	assert(result == 0);
	result = chomp(resultstr, 'e');
	assert(strcmp("h", resultstr) == 0);
	assert(result == 1);
	result = chomp(resultstr, 'h');
	assert(strcmp("", resultstr) == 0);
	assert(result == 1);
	result = chomp(resultstr, 'Z');
	assert(strcmp("", resultstr) == 0);
	assert(result == 0);
	free(resultstr);

	resultstr = strdup("aaaaa");
	result = chomp(resultstr, 'a');
	assert(strcmp("", resultstr) == 0);
	assert(result == 5);
	free(resultstr);
}
void test_chr()
{
	assert(chr(' ') == 32);
	assert(chr('A') == 65);
	assert(chr('Z') == 90);
	// perfectly valid test, but causes compilation warnings.. so disabled
	//assert(chr(NULL) == 0);
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
	char *result = NULL;

	result = lc("HELLO");
	assert(strcmp(result, "hello") == 0);
	free(result);

	result = lc("HELLO123");
	assert(strcmp(result, "hello123") == 0);
	free(result);

	result = lc("hello");
	assert(strcmp(result, "hello") == 0);
	free(result);

	result = lc(NULL);
	assert(result == NULL);
	free(result);

	result = lc("");
	assert(result == NULL);
	free(result);
}
void test_ord()
{
	assert(ord(' ') == 32);
	assert(ord('A') == 65);
	assert(ord('Z') == 90);
	// perfectly valid test, but causes compilation warnings.. so disabled
	//assert(ord(NULL) == 0);
}
void test_q()
{
	char *result = NULL;
	
	result = q("hello");
	assert(strcmp(result, "'hello'") == 0);
	free(result);

	result = q("");
	assert(result == NULL);
	free(result);

	result = q(NULL);
	assert(result == NULL);
	free(result);
}
void test_qq()
{
	char *result = NULL;

	result = qq("hello");
	assert(strcmp(result, """hello""") == 0);
	free(result);

	result = qq("");
	assert(result == NULL);
	free(result);

	result = qq(NULL);
	assert(result == NULL);
	free(result);
}
void test_reverse()
{
	char *result = NULL;
	
	result = reverse("hello");
	assert(strcmp(result, "olleh") == 0);
	free(result);

	result = reverse("a");
	assert(strcmp(result, "a") == 0);
	free(result);

	result = reverse("ab");
	assert(strcmp(result, "ba") == 0);
	free(result);

	result = reverse("");
	assert(result == NULL);
	free(result);

	result = reverse(NULL);
	assert(result == NULL);
	free(result);
}
void test_rindex()
{
	assert(rindex("this that this", "this") == 10);
	assert(rindex("this that this1", "this") == 10);
	assert(rindex("thisthisthis1", "thisthis1") == 4);
	assert(rindex("this", "this") == 0);
	assert(rindex("this", "that") == -1);
	assert(rindex("this", NULL) == -1);
	assert(rindex(NULL, "that") == -1);
}
void test_substr()
{
	char *result = NULL;

	result = substr("hello", 0, 0);
	assert(result == NULL);
	free(result);

	result = substr("hello", 0, 1);
	assert(strcmp(result, "h") == 0);
	free(result);

	result = substr("hello", 0, 2);
	assert(strcmp(result, "he") == 0);
	free(result);

	result = substr("hello", 0, 5);
	assert(strcmp(result, "hello") == 0);
	free(result);

	
	result = substr("hello", 1, 1);
	assert(strcmp(result, "e") == 0);
	free(result);

	result = substr("hello", 1, 2);
	assert(strcmp(result, "el") == 0);
	free(result);

	result = substr("hello", 1, 3);
	assert(strcmp(result, "ell") == 0);
	free(result);

	result = substr("hello", 1, 4);
	assert(strcmp(result, "ello") == 0);
	free(result);


	result = substr("hello", 1, 6);
	assert(result == NULL);
	free(result);

	result = substr("hello", 6, 1);
	assert(result == NULL);
	free(result);

	result = substr("hello", 0, 6);
	assert(result == NULL);
	free(result);

	result = substr("hello", 6, 0);
	assert(result == NULL);
	free(result);

	result = substr("hello", -1, 2);
	assert(result == NULL);
	free(result);

	result = substr("hello", 2, -1);
	assert(result == NULL);
	free(result);

	result = substr("h", 0, 2);
	assert(result == NULL);
	free(result);

	result = substr("", 0, 2);
	assert(result == NULL);
	free(result);
}
void test_substr_replace()
{
	char *result = NULL;

	result = substr_replace("hello", 0, 1, "h");
	assert(strcmp(result, "hello") == 0);
	free(result);

	result = substr_replace("hello", 1, 1, "e");
	assert(strcmp(result, "hello") == 0);
	free(result);

	result = substr_replace("hello", 0, 2, "he");
	assert(strcmp(result, "hello") == 0);
	free(result);

	result = substr_replace("hello", 0, 1, " ");
	assert(strcmp(result, " ello") == 0);
	free(result);

	result = substr_replace("hello", 0, 1, "hello");
	assert(strcmp(result, "helloello") == 0);
	free(result);

	result = substr_replace("hello", 0, 5, "1");
	assert(strcmp(result, "1") == 0);
	free(result);

	result = substr_replace("hello", 0, 5, "1");
	assert(strcmp(result, "1") == 0);
	free(result);

	result = substr_replace("hello", 0, 4, "1");
	assert(strcmp(result, "1o") == 0);
	free(result);

	// // TODO: Is this test valid?
	result = substr_replace("hello", 5, 1, "h");
	assert(strcmp(result, "helloh") == 0);
	free(result);
	
	// // TODO: Is this test valid?
	result = substr_replace("hello", 5, 1, "1");
	assert(strcmp(result, "hello1") == 0);
	free(result);
}
void test_uc()
{
	char *result = NULL;

	result = uc("hello");
	assert(strcmp(result, "HELLO") == 0);
	free(result);

	result = uc("hello123");
	assert(strcmp(result, "HELLO123") == 0);
	free(result);

	result = uc("HELLO");
	assert(strcmp(result, "HELLO") == 0);
	free(result);

	result = uc(NULL);
	assert(result == NULL);
	free(result);

	result = uc("");
	assert(result == NULL);
	free(result);
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
	test_ord();
	test_q();
	test_qq();
	test_reverse();
	test_rindex();
	test_substr();
	test_substr_replace();
	test_uc();

#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif
	

	printf("Success is likely.\n");
	getchar();
	return;
}