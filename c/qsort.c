#include <stdlib.h>
#include <stdio.h>

int ryan_sort(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

void main()
{
	srand(1);
	int *arr = malloc(sizeof(int) * 10);
	
	printf("Before sort:\n");
	for (size_t i = 0; i < 10; i++)
	{
		arr[i] = rand();
		printf("%d\n", arr[i]);
	}

	qsort(arr, 10, sizeof(int), ryan_sort);

	printf("After sort:\n");
	for (size_t i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	getchar();
}