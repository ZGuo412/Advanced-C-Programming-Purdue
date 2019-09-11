#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int main(int argc, char* argv[]) 
{
	int f_steps = 0;
	if (argc < 2) 
	{
		return EXIT_FAILURE;
	}

	if (strcmp("-s", argv[1]) == 0) {
		if (argc != 9) { 
			return EXIT_FAILURE; 
		}
		for ( int i = 5; i < 9;i++)
		{
			if (atoi(argv[i]) == 0 && strcmp(argv[i],"0"))
			{
				return EXIT_FAILURE;
			}
		}
		Coord source ={
			.row = atoi(argv[5]),
			.col = atoi(argv[6])
		};
		Coord destination ={
			.row = atoi(argv[7]),
			.col = atoi(argv[8])
		};

		int step_count = simulate_movement(argv[2], argv[3], argv[4],source,destination);
		printf("%d\n", step_count); 
	} 
	else if (strcmp("-m", argv[1]) == 0) {
		if (argc != 8) { 
			return EXIT_FAILURE; 
		}
		for ( int i = 4; i < 8;i++)
		{
			if (atoi(argv[i]) == 0 && strcmp(argv[i],"0"))
			{
				return EXIT_FAILURE;
			}
		}
		Coord source ={
			.row = atoi(argv[4]),
			.col = atoi(argv[5])
		};
		Coord destination ={
			.row = atoi(argv[6]),
			.col = atoi(argv[7])
		};
		f_steps = dfs_shortest_path_directions(argv[2],argv[3],source,destination);
        printf("%d\n", f_steps);
	}
	else {
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
