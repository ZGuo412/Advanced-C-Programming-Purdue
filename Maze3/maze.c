#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze.h"
#include <string.h>

void _find_maze_dimensions(FILE * fp, int *n_row, int *n_col) 
{
	*n_row = *n_col = 0;
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
			(*n_row)++;
		}
		else
		{
			number++;
		}
	}
	*n_col = number / *n_row;
	return;

}
void free_maze(Maze* maze)
{
	for (int i = 0; i < maze->n_row;i++){
		free(maze->maze_array[i]);
	}
	free(maze->maze_array);
	free(maze);
	return;
}
Maze* malloc_maze(int n_row, int n_col)
{
	Maze* maze = malloc(sizeof(*maze));
	if (maze == NULL){
		return NULL;
	}
	maze->n_row = n_row;
	maze->n_col = n_col;
	maze->maze_array = malloc(sizeof(*maze->maze_array) * n_row);
	if (maze->maze_array == NULL){
		free(maze);
		return NULL;
	}
	for (int i = 0; i < n_row; i++){
		maze->maze_array[i] = malloc(sizeof(*maze->maze_array[i]) * n_col);
		if (maze->maze_array[i] == NULL){
			free_maze(maze);
			return NULL;
		}
	}
	return maze;
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
			new_maze->maze_array[count / col][count % col] = c;
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
	for (int i = 0; i < maze->n_row; i++)
	{
		for(int j = 0; j < maze->n_col; j++)
		{
			int maze_n = fputc(maze->maze_array[i][j],fp);
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


static int is_path(Maze *maze, int row, int col)
{
	if ((row >= 0) && (row < maze->n_row)) {
		if ((col >= 0) && (col < maze->n_col)) {
			return maze->maze_array[row][col] == PATH;
		}
	}
	return 0;
}
int _find_steps(int row, int col, Coord destination,int steps, Maze *save_maze, Maze *get_maze,int* s_dis,char* route,char* min_route)
{
	if( row != destination.row || col != destination.col)
	{
		int dist = INT_MAX;
		steps++;
		if (is_path(get_maze, row, col + 1) == 1 && save_maze->maze_array[row][col + 1] != 'X')
		{
			save_maze->maze_array[row][col + 1] = WALL;
			route[steps - 1] = 'E';
			int steps_r = _find_steps(row,col + 1,destination,steps,save_maze, get_maze,s_dis,route,min_route);
			dist = steps_r;
			save_maze->maze_array[row][col + 1] = PATH;
		}
		if(is_path(get_maze, row, col - 1) == 1 && save_maze->maze_array[row][col - 1] != 'X')
		{
			save_maze->maze_array[row][col - 1] = 'X';
			route[steps - 1] = 'W';
			int steps_l = _find_steps(row,col - 1,destination,steps,save_maze, get_maze,s_dis,route,min_route);
			if (steps_l < dist)
			{
				dist = steps_l;
			}
			save_maze->maze_array[row][col - 1] = PATH;

		}
		if(is_path(get_maze, row + 1, col) == 1 && save_maze->maze_array[row + 1][col] != 'X')
		{
			save_maze->maze_array[row + 1][col] = 'X';
			route[steps - 1] = 'S';
	        int steps_u = _find_steps(row + 1,col,destination,steps, save_maze,get_maze,s_dis,route,min_route);
			if (steps_u < dist)
			{
				dist = steps_u;
			}
			save_maze->maze_array[row + 1][col] = PATH;
		}
		if((is_path(get_maze, row - 1, col) == 1) && save_maze->maze_array[row - 1][col] != 'X')
		{
			save_maze->maze_array[row - 1][col] = 'X';
			route[steps - 1] = 'N';
			int steps_o = _find_steps(row - 1,col,destination,steps,save_maze, get_maze,s_dis,route,min_route);
			if (steps_o < dist)
			{
				dist = steps_o;
			}
			save_maze->maze_array[row - 1][col] = PATH;
		}
		return dist;
	}

	else
	{
	
		if (steps < *s_dis)
		{
			*s_dis = steps;
			route[steps] = '\0';
			memcpy(min_route,route,steps);
		}

		return steps;
	}
}

int dfs_shortest_path_directions(char *maze_file, char *directions_file,
		Coord source, Coord destination)
{
	int s_dis = INT_MAX;
	int steps = 0;
	int row = source.row;
	int col = source.col;
	FILE*fp = fopen(maze_file,"r");
	if (fp == NULL)
	{
		return -1;
	}
	Maze* get_maze = read_maze(fp);
	if (get_maze == NULL)
	{ 
		fclose(fp);
		return -1;
	}
	FILE* fp_w = fopen(directions_file,"w");
	if (fp_w == NULL)
	{
		return -1;
	}
	Maze *save_maze = read_maze(fp);
    save_maze->maze_array[row][col] = 'X';
	char* route = malloc(sizeof(*route) * get_maze->n_row * get_maze->n_col);
	for (int m = 0; m < get_maze->n_row * get_maze->n_col; m++)
	{
		route[m] = 'A';
	}

	char* min_route = malloc(sizeof(*min_route)* get_maze->n_row * get_maze->n_col);
	steps = _find_steps(row,col,destination,steps,save_maze,get_maze,&s_dis,route,min_route);
	fclose(fp);
	if (steps != 0)
	{
		for(int i = 0; i < steps; i++)
		{
			fputc(min_route[i],fp_w);
		}
	}
	fclose(fp_w);
	free(min_route);
	free_maze(save_maze);
	free_maze(get_maze);
	free(route);
	return steps;
}

int simulate_movement(char *maze_file, char *directions_file, char *visited_file,
		Coord source, Coord destination)
{
	int num = 0;
	int row = source.row;
	int col = source.col;
	int count = 0;
	FILE* fp_maze = fopen(maze_file,"r");
	if (fp_maze == NULL)
	{
		return -1;
	}
	Maze* new_maze = read_maze(fp_maze);
	if (new_maze == NULL)
	{
		fclose(fp_maze);
		return -1;
	}
	FILE* fp_dire = fopen(directions_file,"r");
	if (fp_dire == NULL)
	{
		return -1;
	}
	while(true)
	{
		int c = fgetc(fp_dire);
		if(feof(fp_dire))
		{
			break;
		}
		if (c != '\n')
		{
			count++;
		}	
	}

    if (source.row < 0 || source.row > new_maze->n_row)
	{
		fclose(fp_maze);
	    fclose(fp_dire);
		return -1;
	}
	if (source.col < 0 || source.col > new_maze->n_col)
	{
		fclose(fp_maze);
		fclose(fp_dire);
		return -1;
	}
   	char* dir = malloc(sizeof(*dir) * (count));
	for (int n = 0; n <count; n++)
	{
		dir[n] = 'a';
	}
	fseek(fp_dire,0L,SEEK_SET);
	while(true)
	{
		int c = fgetc(fp_dire);
		if(feof(fp_dire))
		{
			break;
		}
		if (c != '\n')
		{
            dir[num] = c;
			num++;
		}	
	}



	new_maze->maze_array[row][col] = '.';
    for (int j = 0; j < count; j++)
	{
		if (dir[j] == 'N')
		{
			new_maze->maze_array[row - 1][col] = '.';
			row = row -1;
		}
		if (dir[j] == 'S')
		{
			new_maze->maze_array[row + 1][col] = '.';
			row = row + 1;
		}
		if (dir[j] == 'W')
		{
			new_maze->maze_array[row][col - 1] = '.';
			col = col - 1;
		}
		if (dir[j] == 'E')
		{
			new_maze->maze_array[row][col + 1] = '.';
			col = col + 1;
		}
	}
    write_maze(visited_file,new_maze);
	if (row != destination.row || col != destination.col)
	{
		fclose(fp_maze);
		fclose(fp_dire);
		return -1;
	}
    free(dir);
	free_maze(new_maze);
    fclose(fp_maze);
    fclose(fp_dire);
	return count + 1;
}

