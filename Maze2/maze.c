#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include <stdbool.h>

void _find_maze_dimensions(FILE * fp, int *a_num_rows, int * a_num_cols) 
{
	*a_num_rows = *a_num_cols = 0;
	fseek(fp,0L,SEEK_SET);
	int c = 0;
	int number = 0;
	while (true)
	{
		c = fgetc(fp);
		if (feof(fp))
		{
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

Maze* malloc_maze(int num_rows, int num_cols)
{
	Maze* maze = malloc(sizeof(*maze));
	if (maze == NULL){
		return NULL;
	}
    maze->num_rows = num_rows;
    maze->num_cols = num_cols;
	maze->cells = malloc(sizeof(*maze->cells) * num_rows);
	if (maze->cells == NULL){
		free(maze);
		return NULL;
	}
	for (int i = 0; i < num_rows; i++){
	    maze->cells[i] = malloc(sizeof(*maze->cells[i]) * num_cols);
	    if (maze->cells[i] == NULL){
		    free_maze(maze);
    		return NULL;
		}
	}
	return maze;
}

void free_maze(Maze* maze)
{
    for (int i = 0; i < maze->num_rows;i++){
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
	return;
}

Maze* read_maze(FILE *fp)
{  
	int row = 0;
	int col = 0;
	int count = 0;
	_find_maze_dimensions(fp,&row,&col);
    Maze* new_maze = malloc_maze(row,col);
	fseek(fp,0l,SEEK_SET);
	while(true)
	{
	    int c = fgetc(fp);
		if(feof(fp))
		{
			break;
		}
		if (c != '\n')
	    {
			new_maze->cells[count / col][count % col] = c;
	        count++;
		}

	}
	return new_maze;
}


bool write_maze(const char* filename, const Maze* maze)
{
    FILE *fp = fopen(filename,"w");
	if (fp == NULL)
	{
       return false;
	}
    fseek(fp,0L,SEEK_SET);
	for (int i = 0; i < maze->num_rows; i++)
	{
		for(int j = 0; j < maze->num_cols; j++)
		{
 	        int maze_n = fputc(maze->cells[i][j],fp);
	        if (maze_n == EOF)
			{
				fclose(fp);
				return false;
			}
		}
		fputc('\n',fp);
    }
	fclose(fp);
	return true;
}


Maze* make_taller(const Maze* orig)
{  
	Maze* taller_maze = malloc_maze(2 * orig->num_rows - 1, orig->num_cols);
    for(int i = 0; i < orig->num_rows;i++)
	{
		for(int j = 0; j < orig->num_cols; j++)
		{
			taller_maze->cells[i][j] = orig->cells[i][j];
			taller_maze->cells[2 * orig->num_rows - 2 - i][j] = orig->cells[i][j];
		}
	}
	return taller_maze;
}

Maze* make_wider(const Maze* orig)
{
	Maze* wider_maze = malloc_maze(orig->num_rows, 2 * orig->num_cols - 1);
	for (int i = 0; i < orig->num_rows; i++)
	{
		for(int j = 0; j < orig->num_cols; j++)
		{
			wider_maze->cells[i][j] = orig->cells[i][j];
			wider_maze->cells[i][2 * orig->num_cols - 2 - j] = orig->cells[i][j];
		}
	}
	int count = 0;
	int m_col = orig->num_cols - 1;
	int m_row = orig->num_rows / 2;
	wider_maze->cells[m_row][m_col - count] = PATH;
	while (true)
	{
		if (wider_maze->cells[m_row][m_col - count - 1] == PATH)
		{
			break;
		}
        if (wider_maze->cells[m_row + 1][m_col - 1 - count] == PATH)
		{
			break;
		}
		if (wider_maze->cells[m_row - 1][m_col - 1 - count] == PATH)
		{
			break;
		}
		wider_maze->cells[m_row][m_col - count - 1] = PATH;
		wider_maze->cells[m_row][m_col + count + 1] = PATH;
		count++;
	}
	
	return wider_maze;
}




