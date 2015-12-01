#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

typedef struct Books
{
	char title[50];
	char title2[5000];
	int count;
	struct Books *next;
} Books;



struct Books* add_node(Books *head, char title[50], int count)
{
	Books *a = malloc(sizeof(Books));
	if (a == NULL)
	{
		printf("error in add_node()\n");
		return head;
	}
	a->count = count;
	strcpy(a->title, title);
	a->next = head;
	return a;
}
struct Books* del_by_count(Books *head, int count)
{
	// empty list, return null (ie, return what was given)
	if (head == NULL)
	{
		return head;
	}
	
	// single node, and first node contains data
	if ((head->count == count) && (head->next == NULL))
	{
		free(head);
		head = NULL;
		return head;
	}

	// single node, and first node does not contain data
	if (!(head->count == count) && (head->next == NULL))
	{
		return head;
	}

	// create a new pointer for the list, that can be modified safely
	Books *a = head;

	// first node contains data
	if (head->count == count)
	{
		head = head->next;
		free(a);
		return head;
	}


	// assumptions at this point:
	//		List not empty
	//		List not single entry
	//		First node does not contain the entry
	//		'a' can be modified to point to node being investigated
	//
	// possible issues:
	//		'a' might need to be freed from this point forward

	while (a)
	{
		if (a->next->count == count)
		{
			// create temp pointer that can be free'd
			Books *temp = a->next;
			// update next to point to next->next, skipping over the soon to be removed node
			a->next = a->next->next;
			// reset variables.. just because
			temp->count = 0;
			strcpy(temp->title, "");
			// free the memory
			free(temp);
			break;
		}

		// advance one node
		a = a->next;
		if (!a->next) break;
	}

	return head;
}


int main2()
{
	Books *head = NULL;
	head = add_node(head, "Title of book 10", 10);
	head = add_node(head, "Title of book 10", 20);
	head = add_node(head, "Title of book 10", 30);
	head = add_node(head, "Title of book 10", 100);
	//for (int i = 0; i < 3; i++)
	//{
	//	head = add_node(head, "Title of book 100", 1000);
	//	head = del_by_count(head, 1000);
	//}

	head = del_by_count(head, 20);
	head = del_by_count(head, 100);
	head = del_by_count(head, 30);
	head = del_by_count(head, 10);


	_CrtDumpMemoryLeaks();
	printf("Done.\n");
	getchar();
	return 0;
}


int main()
{
	int q = 0;
	int w = 0;
	char str[100] = "10 20";
	int res = sscanf(str, "%x %x", &q, &w);

	printf("%x %x", q, w);
	getchar();
	return;
}