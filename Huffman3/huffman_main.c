#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
	FILE* fp = fopen(argv[1],"r");
	if (fp == NULL)
	{
		return EXIT_FAILURE;
	}
	char ls[256] = {'\0'}; 
	long long *list = read_from_file(fp);
	Node* arr = get_list(list);
	Tree* f_tree = get_the_tree(arr);
	FILE* fp_1 = fopen(argv[2], "w");
	if (fp_1 == NULL)
	{
		return EXIT_FAILURE;
	}
	write_to_out_1(f_tree,ls,fp_1);
	FILE* fp_2 = fopen(argv[3],"w");
	if(fp_2 == NULL)
	{
		return EXIT_FAILURE;
	}
	add_zero(f_tree,fp_2);
	fclose(fp_2);
    fp_2 = fopen(argv[3],"r");
	FILE* fp_3 = fopen(argv[4],"w");
	if (fp_3 == NULL)
	{
		return EXIT_FAILURE;
	}
	write_to_out3(fp_2,fp_3);
	Free_tree(f_tree);
	free(list);
    fclose(fp);
	fclose(fp_1);
	fclose(fp_2);
	fclose(fp_3);
	return EXIT_SUCCESS;
}
