/*
 * game.h
 *
 * Richard Degenne - Adrien Deprez
 * 06/12/14
 *
 * Header for the game.c file.
 */

# ifndef _GAME_H
# define _GAME_H 1


// Includes
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>

// Defines and macros
# define X_SIZE 10
# define Y_SIZE 10
# define FLEET_SIZE 6

# define EMPTY_SQ '.'

# define max(a,b) (((a)>(b)) ? (a) : (b))
# define min(a,b) (((a)<(b)) ? (a) : (b))

// Typedefs and structs
typedef char grid[X_SIZE][Y_SIZE];
typedef struct coord {
	int x;
	int y;
} coord;
typedef struct boat {
	char name[30];
	int lenght;
	coord start, end;
} boat;

// Prototypes
void setup_fleet(boat[]);
void reset_grid(grid);
void select_boat_coord(boat*);
void place_boat(boat*, grid);
void print_grid(grid);

// Misc
void flush();


# endif // _GAME_H defined
