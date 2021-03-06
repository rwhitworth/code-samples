#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#define _CRT_NONSTDC_NO_DEPRECATE
	#include <crtdbg.h>	
	#define _CRTDBG_MAP_ALLOC
#endif
#include <stdio.h>
#include <string.h>
#include <ctype.h> // tolower() for lc()
#include <stdlib.h> // malloc() for q() and qq(), calloc() for reverse()
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
	if (strlen(input) < (unsigned int)pos)
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
	unsigned int slen = strlen(input);
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
int ord(const char input)
{
	return input;
}
char *_bookend(const char *input, const char *bookend)
{
	if (!input)
		return NULL;
	if (!bookend)
		return NULL;
	unsigned int slen = strlen(input);
	if (slen == 0)
		return NULL;
	char *result = malloc(sizeof(char) * slen + 3); // 3 == 2 new characters, plus zero EOL character
	if (!result)
		return NULL;
	result[0] = 0;
	strcat(result, bookend);
	strcat(result, input);
	strcat(result, bookend);
	return result;
}
char *q(const char *input)
{
	return _bookend(input, "'");
}
char *qq(const char *input)
{
	return _bookend(input, """");
}
char *reverse(const char *input)
{
	if (!input)
		return NULL;
	unsigned int slen = strlen(input);
	if (slen == 0)
		return NULL;
	// call calloc, so memory is zero filled
	char *result = calloc(1, sizeof(char) * slen + 1);
	if (!result)
		return NULL;
	for (size_t i = 0; i < slen; i++)
	{
		result[i] = input[slen - i - 1];
	}
	return result;
}
int rindex(const char *input, const char *substr)
{
	if (!input)
		return -1;
	if (!substr)
		return -1;
	int slen = strlen(input);
	if (slen == 0)
		return -1;
	int slen2 = strlen(substr);
	if (slen2 == 0)
		return -1;
	char *rev = reverse(input);
	if (!rev)
		return -1;
	char *rsubstr = reverse(substr);
	if (!rsubstr)
		return -1;
	int result = index(rev, rsubstr);
	free(rev);
	free(rsubstr);
	if (result < 0)
		return -1;
	return slen - result - slen2;
}
char *substr(const char *input, const int offset, const int length)
{
	if (!input)
		return NULL;
	if (offset < 0)
		return NULL;
	int slen = strlen(input);
	if (slen == 0)
		return NULL;
	if ((length <= 0) || (slen < offset + length))
		return NULL;

	char *result = malloc(sizeof(char) * (length + 1));

	if (!result)
		return NULL;
	
	result[length] = 0;
	for (size_t i = 0; i <= ((unsigned int)length - 1); i++)
	{
		result[i] = input[offset + i];
	}

	return result;
}
char *substr_replace(const char *input, const int offset, const int length, const char *replstr)
{
	if (!input)
		return NULL;
	if (!replstr)
		return NULL;
	int inlen = strlen(input);
	int relen = strlen(replstr);
	if ((inlen == 0) || (relen == 0))
		return NULL;
	if (offset < 0)
		return NULL;
	if (length < 0)
		return NULL;

	// TODO: correct RAM allocation.  Currently too large, so realloc() needed
	int msize = inlen + relen + 1;
	char *result = malloc(sizeof(char) * (inlen + relen + 1));
	if (!result)
		return NULL;
	result[0] = 0;
	char *firstpart = substr(input, 0, offset);
	if (!firstpart)
	{
		firstpart = malloc(sizeof(char) * 1);
		if (!firstpart)
		{
			// TODO: find better way to handle malloc() errors
			free(result);
			return NULL;
		}
		firstpart[0] = 0;
	}
	char *thirdpart = substr(input, offset + length, inlen - offset - length);
	if (!thirdpart)
	{
		thirdpart = malloc(sizeof(char) * 1);
		if (!thirdpart)
		{
			// TODO: find better way to handle malloc() errors
			free(firstpart);
			free(result);
			return NULL;
		}
		thirdpart[0] = 0;
	}
	strcat(result, firstpart);
	strcat(result, replstr);
	strcat(result, thirdpart);

	free(firstpart);
	free(thirdpart);

	result = realloc(result, strlen(result) + 1);

	return result;
}
char *uc(const char *input)
{
	if (!input)
		return NULL;
	unsigned int slen = strlen(input);
	if (slen == 0)
		return NULL;

	char *result = strdup(input);
	if (!result)
		return NULL;
	for (size_t i = 0; i < slen; i++)
	{
		result[i] = toupper(result[i]);
	}
	return result;
}