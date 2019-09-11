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
	FILE* fp_1 = fopen(argv[2],"w");
	write_to_out_1(fp_1,list);
	FILE* fp_2 = fopen(argv[3], "w");
	Node* arr = write_to_out_2(fp_2,list);
	Tree* f_tree = get_the_tree(arr);
	FILE* fp_3 = fopen(argv[4], "w");
	if (fp_3 == NULL)
	{
		return EXIT_FAILURE;
	}
	write_to_out_3(f_tree,ls,fp_3);
	Free_tree(f_tree);
	free(list);
    fclose(fp);
	fclose(fp_1);
	fclose(fp_2);
	return EXIT_SUCCESS;
}
