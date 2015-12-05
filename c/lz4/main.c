#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lz4.h"


void main()
{
	char *input = strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890AAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBB");
	char *output = malloc(sizeof(char) * strlen(input) + 1);

	int result = 0;
	result = LZ4_compress(input, output, strlen(input));
	printf("%d %d", strlen(input), result);
	getchar();

	return;
}