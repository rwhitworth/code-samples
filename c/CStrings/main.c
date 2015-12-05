#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "CStrings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main()
{
	char *q = NULL;
	q = strdup("hello");
	chop(q);
	printf("%s", q);
	getchar();
	return;
}