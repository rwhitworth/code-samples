#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
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