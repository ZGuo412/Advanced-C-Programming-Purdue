#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
int main(int argc, char **argv)
{
	int row = 0;
	int col = 0;
	FILE *fp = fopen("filename","r");
	find_maze_dimensions(fp,&row,&col);
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j<col; j++)
		{
			fprintf(stderr,"%c",get_location_type(fp,i,j));
		}
		fprintf(stderr,"\n");
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
