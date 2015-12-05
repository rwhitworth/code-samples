#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include "CStrings.h"

void chop(char *input)
{
	int slen = strlen(input);
	input[slen-1] = 0;
}