#ifndef LIFE_HPP
#define LIFE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_game
{

	int w;
	int h;
	int it;
	char alive;
	char dead;
	int x;
	int y;
	int draw;
	char** board;

} t_game;

int init_game(t_game* game, char* argv[]);
int play(t_game* game);
void fill_board(t_game* game);
void print_board(t_game* game);
void free_board(t_game* game);

#endif