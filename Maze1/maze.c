#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include <stdbool.h>

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) {
	*a_num_rows = *a_num_cols = 0;
	fseek(fp,0L,SEEK_SET);
	int c = 0;
	int number = 0;
	while (true){
		c = fgetc(fp);
		if (feof(fp)){
			break;
		}
		if (c == '\n')
		{
			(*a_num_rows)++;
		}
		else
		{
			number++;
		}
	}
	*a_num_cols = number / *a_num_rows;
    return;

}

int find_opening_location(FILE * fp) {
	int c = 0;
	fseek(fp,0L,SEEK_SET);
	int open_location = 0;
	while (true){
		c = fgetc(fp);
		if (c != ' '){
			open_location++;
		}
		else
		{
			break;
		}
		
	}

	return open_location;
}

int count_path_locations(FILE * fp) {
	int c = 0;
	fseek(fp,0L,SEEK_SET);
	int count = 0;
	while (true){
		c = fgetc(fp);
		if (feof(fp))
		{
			break;
		}
		if (c == ' ')
		{
			count++;
		}
	}
	return count;
}	

char get_location_type(FILE * fp, int row, int col) {
	char c = '0';
	int number = 0;
	int row_n = 0;
	int col_n = 0;
	fseek(fp,0L,SEEK_SET);
	find_maze_dimensions(fp,&row_n,&col_n);
    number = row * col_n + col;
	fseek(fp,number,SEEK_SET);
    c = fgetc(fp);
	return c;
}

int represent_maze_in_one_line(char * filename, FILE * fp) {
	FILE * f_outp = fopen(filename, "w");
	char c = '0';
	int terms = 0;
	while (true){
		c = fgetc(fp);
		if (feof(fp)){
			break;
		}
		if (c != '\n')
		{
			fputc(c, f_outp);
			terms++;
		}
	}
	fclose(f_outp);

	return terms;
}
