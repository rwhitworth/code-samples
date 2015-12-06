#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <ctype.h> // tolower() for lc()
#include "CStrings.h"

int chomp(char *input, const char remove_char)
{
	if (!input)
		return 0;
	int slen = strlen(input);
	if (slen == 0)
		return 0;
	int result = 0;

	for (size_t i = slen - 1; i >= 0 ; i--)
	{
		if (input[i] == remove_char)
		{
			input[i] = 0;
			result++;
		}
		else
		{
			break;
		}
	}

	return result;
}
void chop(char *input)
{
	if (!input)
		return;
	int slen = strlen(input);
	if (slen == 0)
		return;
	input[slen-1] = 0;
}
char chr(const unsigned char input)
{
	char a = input;
	return a;
}
int hex(const char *input)
{
	int output = -1;
	sscanf(input, "%x", &output);
	return output;
}
int index(const char *input, const char *substr)
{
	//char *res = NULL;
	//if (!input)
	//	return -1;
	//if (!substr)
	//	return -1;
	//if (strlen(input) == 0 || strlen(substr) == 0)
	//{
	//	return -1;
	//}
	//res = strstr(input, substr);
	//if (!res)
	//	return -1;
	//return res - input;
	return index_pos(input, substr, 0);
}
int index_pos(const char* input, const char *substr, const int pos)
{
	char *res = NULL;
	if (!input)
		return -1;
	if (!substr)
		return -1;
	if (strlen(input) == 0 || strlen(substr) == 0)
	{
		return -1;
	}
	if (pos < 0)
		return -1;
	if (strlen(input) < pos)
		return -1;
	res = strstr(input + pos, substr);
	if (!res)
		return -1;
	return res - input;
}
char *lc(const char *input)
{
	if (!input)
		return NULL;
	int slen = strlen(input);
	if (slen == 0)
		return NULL;
	
	char *result = strdup(input);
	if (!result)
		return NULL;
	for (size_t i = 0; i < slen; i++)
	{
		result[i] = tolower(result[i]);
	}
	return result;
}