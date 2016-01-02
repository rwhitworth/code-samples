#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#define _CRT_NONSTDC_NO_DEPRECATE
	#include <crtdbg.h>	
	#define _CRTDBG_MAP_ALLOC
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rle.h"

char* rle_enc(const char *input)
{
	int length = strlen(input);
	char previous = input[0];
	int counter = 0;
	// length + 2, because:
	// +1 needed for trailing zero on string
	// +1 needed for single character inputs
	char *output = malloc(sizeof(char) * (length + 2));
	if (!output)
		return NULL;
	output[0] = 0;
	char tempstr[rle_encode_memory_multipler];

	for (int i = 0; i < length; i++)
	{
		if (input[i] == previous)
		{
			counter++;
		}
		else
		{
			if (counter > 1)
			{
				sprintf(tempstr, "%d", counter);
				strcat(output, tempstr);
				sprintf(tempstr, "%c", previous);
				strcat(output, tempstr);
				counter = 1;
			}
			else
			{
				sprintf(tempstr, "%c", previous);
				strcat(output, tempstr);
				counter = 1;
			}
		}
		previous = input[i];
	}

	if (counter != 0)
	{
		// If strlen(input) == 1, then no number of characters required as output
		// If counter == 1, then no number of characers required as output
		if ((length != 1) && (counter != 1))
		{
			sprintf(tempstr, "%d", counter);
			strcat(output, tempstr);
		}
		sprintf(tempstr, "%c", previous);
		strcat(output, tempstr);
		counter = 1;
	}

	// TODO: This realloc causes a free() to have a chance of causing issues.
	// Avoid the realloc at this time.  
	// A max of (strlen(input) - strlen(output) + 1) bytes of RAM are wasted.
	// realloc(output, strlen(output) + 1);
	return output;
}
char* rle_dec(const char *input)
{
	// TODO: Guess required memory more effectively
	int output_size = strlen(input) * rle_decode_memory_multipler;
	char *output = malloc(output_size);
	if (!output)
		return NULL;
	char *tempinput = malloc(strlen(input) + 1);
	if (!tempinput)
	{
		free(output);
		return NULL;
	}
	memcpy(tempinput, input, strlen(input) + 1);
	char tempstr[2];
	char tempstra[rle_decode_memory_multipler];
	int tempint = 0;
	int result = 0;
	output[0] = 0;
	tempstr[1] = 0;
	tempstr[0] = 0;

	while (strlen(tempinput) > 0)
	{
		// TODO: Handle memory management better
		if ((int)strlen(output) > (output_size - 2))
		{
			realloc(output, output_size * 2);
			output_size *= 2;
		}

		result = sscanf(tempinput, "%d", &tempint);

		if (result == 1)
		{
			result = sscanf(tempinput, "%d%c", &tempint, &tempstr);
			for (int i = 0; i < tempint; i++)
			{
				strcat(output, tempstr);
			}
			result = sprintf(tempstra, "%d%c", tempint, tempstr[0]);
			memcpy(tempinput, tempinput + result, strlen(tempinput) - result + 1);
		}
		else
		{
			result = sscanf(tempinput, "%c", &tempstr);
			if (result == 1)
			{
				strcat(output, tempstr);
				result = sprintf(tempstra, "%c", tempstr[0]);
				memcpy(tempinput, tempinput + result, strlen(tempinput) - result + 1);
			}
			else
			{
				printf("ERROR in dec() - %d\n", result);
				free(tempinput);
				return output;
			}
		}
	}

	free(tempinput);
	realloc(output, strlen(output) + 1);
	return output;
}