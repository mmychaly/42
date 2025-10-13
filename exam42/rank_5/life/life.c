#include "life.h"

int init_game(t_game* game, char* argv[])
{
	game->w = atoi(argv[1]);
	game->h = atoi(argv[2]);
	game->it = atoi(argv[3]);
	game->alive = '0';
	game->dead = ' ';
	game->x = 0;
	game->y = 0;
	game->draw = 0;
	game->board = (char**)malloc(game->h * sizeof(char *));
	if (!(game->board))
		return -1;
	for (int i = 0; i < game->h; i++)
	{
		game->board[i] = (char *)malloc(game->w * sizeof(char));
		if (!(game->board[i]))
		{
			free_board(game);
			return -1;
		}
		for (int i_2 = 0; i_2 < game->w; i_2++)
		{
			game->board[i][i_2] = game->dead;
		}
	}
	return 0;
}

int count_neigboards(t_game* game, int i, int i_2)
{
	int count = 0;

	for (int ii = -1; ii < 2; ii++)
	{
		for (int ii_2 = -1; ii_2 < 2; ii_2++)
		{
			if (ii == 0 && ii_2 == 0)
				continue;
			int ni = i + ii;
			int ni_2 = i_2 +ii_2;
			if (ni >= 0 && ni_2 >= 0 && ni < game->h && ni_2 < game->w)
			{
				if (game->board[ni][ni_2] == game->alive)
					count++;
			} 
		}
	}
	return count;
}

int play(t_game* game)
{
	char** temp = (char**)malloc(game->h * sizeof(char*));
	if (!(temp))
		return -1;
	for (int i = 0; i < game->h; i++)
	{
		temp[i] = (char*)malloc(game->w * sizeof(char));
		if (!(temp[i]))
			return -1;
	}

	for (int i = 0; i < game->h; i++)
	{
		for(int i_2 = 0; i_2 < game->w; i_2++)
		{
			int neightboard = count_neigboards(game, i, i_2);
			if (game->board[i][i_2] == game->alive)
			{
				if (neightboard == 2 || neightboard == 3)
					temp[i][i_2] = game->alive;
				else
					temp[i][i_2] = game->dead;
			}
			else
			{
				if (neightboard == 3)
					temp[i][i_2] = game->alive;
				else	
					temp[i][i_2] = game->dead;
			}
		}
	}

	free_board(game);
	game->board = temp;
	return 0;
}

void fill_board(t_game* game)
{
	char buffer;
	int flag;

	while(read(STDIN_FILENO, &buffer, 1) == 1)
	{
		flag = 0;
		switch (buffer)
		{
			case 'w':
				if (game->y > 0)
				game->y--;
				break;
			case 's':
				if (game->y < (game->h - 1))
				game->y++;
				break;
			case 'a':
				if (game->x > 0)
				game->x--;
				break;
			case 'd':
				if (game->x < (game->w - 1))
				game->x++;
				break;
			case 'x':
				game->draw = !(game->draw);
				break;
			default:
				flag = 1;
				break;
		}
		if (game->draw && flag == 0)
		{
			if ((game->x >= 0) && (game->x < (game->w)) && (game->y >= 0) && (game->y < (game->h)))
				game->board[game->y][game->x] = game->alive;
		}
	}

}
void print_board(t_game* game)
{
	for (int i = 0; i < game->h; i++)
	{
		for (int i_2 = 0; i_2 < game->w; i_2++)
		{
			putchar(game->board[i][i_2]);
		}
		putchar('\n');
	}
}
void free_board(t_game* game)
{
	if (!(game->board))
	{
		for (int i = 0; i < game->h; i++)
		{
			if (!(game->board[i]))
				free(game->board[i]);
		}
		free(game->board);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 4)
		return 1;
	
	t_game game;

	if (init_game(&game, argv) == -1)
		return 1;

	fill_board(&game);

	for (int i = 0; i < game.it; i++)
	{
		if (play(&game) == -1)
		{
			free_board(&game);
			return 1;
		}
	}

	print_board(&game);
	free_board(&game);

	return 0;
}