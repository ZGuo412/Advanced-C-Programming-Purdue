#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
void print_int(const void* a)
{
	printf("%d", *(int*)a);
	return;
}
int cmp_fn(const void*p1, const void* p2)
{
	return *(const int*)p1 - *(const int*)p2;
}   
int main(int argc, char*argv[])
{
	Node *list = NULL;
	for (int i = 0; i < 10; i++)
	{
	  	int*  arr = malloc(sizeof(*arr));
		*arr = i; 
		stack_push(&list,(const void*)(arr));
		print_node(list, print_int);
	}
	Node* last = remove_last_node(&list);
    print_node(last,print_int);
	print_node(list,print_int);
	Node *pq = NULL;
	for (int j = 0; j < 10; j++)
	{
		int *a = malloc(sizeof(*a));
		*a = j;
		pq_enqueue(&pq,(const void*)a,cmp_fn);
		print_node(pq,print_int);
	}
	for (int j = 0; j< 10; j++)
	{
		Node* d_pq = pq_dequeue(&pq);
		print_node(d_pq,print_int);
	    print_node(pq,print_int);
		destroy_node(d_pq,free);		
	}

    destroy_node(list, free);
	destroy_node(last,free);
	return EXIT_SUCCESS;
}
