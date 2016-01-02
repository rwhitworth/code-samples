#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#define _CRT_NONSTDC_NO_DEPRECATE
	#include <crtdbg.h>	
	#define _CRTDBG_MAP_ALLOC
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rle.h"

int main()
{
	char *input = NULL;
	char *dd = NULL;
	char *ee = NULL;

	input = malloc(1024);
	
	
	input[0] = 0;
	strcpy(input, "AAAAAAAAAABBBBBBBBBBBBBBBCCC"); // 10A15B3C
	
	dd = rle_enc(input);	
	assert(dd != NULL);
	ee = rle_dec(dd);
	assert(ee != NULL);
	assert(strcmp(dd, "10A15B3C") == 0);
	assert(strcmp(ee, input) == 0);

	free(dd);
	free(ee);



	input[0] = 0;
	strcpy(input, "ZAAAAAAAAAABBBBBBBBBBBBBBBCCC"); // Z10A15B3C

	dd = rle_enc(input);
	assert(dd != NULL);
	ee = rle_dec(dd);
	assert(ee != NULL);
	assert(strcmp(dd, "Z10A15B3C") == 0);
	assert(strcmp(ee, input) == 0);

	free(dd);
	free(ee);




	input[0] = 0;
	strcpy(input, "Z"); // Z

	dd = rle_enc(input);
	assert(dd != NULL);
	ee = rle_dec(dd);
	assert(ee != NULL);
	assert(strcmp(dd, "Z") == 0);
	assert(strcmp(ee, input) == 0);

	free(dd);
	free(ee);



	input[0] = 0;
	strcpy(input, "ZZ"); // 2Z

	dd = rle_enc(input);
	assert(dd != NULL);
	ee = rle_dec(dd);
	assert(ee != NULL);
	assert(strcmp(dd, "2Z") == 0);
	assert(strcmp(ee, input) == 0);

	free(dd);
	free(ee);



	input[0] = 0;
	strcpy(input, "ZZA"); // 2ZA

	dd = rle_enc(input);
	assert(dd != NULL);
	ee = rle_dec(dd);
	assert(ee != NULL);
	assert(strcmp(dd, "2ZA") == 0);
	assert(strcmp(ee, input) == 0);

	free(dd);
	free(ee);



	free(input);

	printf("Success is likely.\n");
	getchar();
	return 0;
}
