#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "maze.h"
void _print_maze(Maze* maze)
{
	for (int i = 0; i < maze->num_rows; i++)
	{
		for (int j = 0; j < maze->num_cols;j++)
		{
			fputc(maze->cells[i][j],stdout);
		}
		fputc('\n',stdout);
	}
	return;
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen("test.txt","r");
	if(fp == NULL)
	{
		return EXIT_FAILURE;
	}
    
	Maze* get_maze = read_maze(fp);
	_print_maze(get_maze);
	write_maze("test_w.txt", get_maze);
    Maze* taller_maze = make_taller(get_maze);	
	_print_maze(taller_maze);
	write_maze("test_t.txt", taller_maze);
	Maze* wider_maze = make_wider(get_maze);
	_print_maze(wider_maze);
	write_maze("test_w.txt", wider_maze);
	free_maze(get_maze);
	free_maze(taller_maze);
	free_maze(wider_maze);
    fclose(fp);
	return EXIT_SUCCESS;
}

