//
// Created by 24087 on 24-12-2.
//
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define GRID_SIZE 4
#include <stdbool.h>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

void init_game();
bool move(Direction direction);
bool check_game_over();
int get_score();
const int (*get_grid())[GRID_SIZE];

#endif // GAME_LOGIC_H
