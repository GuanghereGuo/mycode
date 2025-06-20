//
// Created by 24087 on 24-12-2.
//
#include "game_logic.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 4
#define NEW_TILE_CHANCE 90 // 90%概率生成2，10%概率生成4

static int grid[GRID_SIZE][GRID_SIZE];
static int score = 0;

static void add_random_tile() {
    int empty_positions[GRID_SIZE * GRID_SIZE][2];
    int count = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                empty_positions[count][0] = i;
                empty_positions[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int rand_index = rand() % count;
        int value = (rand() % 100) < NEW_TILE_CHANCE ? 2 : 4;
        grid[empty_positions[rand_index][0]][empty_positions[rand_index][1]] = value;
    }
}

static void rotate_grid() {
    int temp[GRID_SIZE][GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            temp[i][j] = grid[GRID_SIZE - j - 1][i];
        }
    }
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = temp[i][j];
        }
    }
}

static bool slide_and_merge_row(int row[GRID_SIZE]) {
    bool changed = false;
    int temp[GRID_SIZE] = {0};
    int index = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        if (row[i] != 0) {
            if (index > 0 && temp[index - 1] == row[i]) {
                temp[index - 1] *= 2;
                score += temp[index - 1];
                row[i] = 0;
                changed = true;
            } else {
                temp[index++] = row[i];
                if (index - 1 != i) {
                    changed = true;
                }
            }
        }
    }
    for (int i = 0; i < GRID_SIZE; i++) {
        row[i] = temp[i];
    }
    return changed;
}

bool move(Direction direction) {
    bool changed = false;

    if (direction == LEFT) {
        for (int i = 0; i < GRID_SIZE; i++) {
            if (slide_and_merge_row(grid[i])) {
                changed = true;
            }
        }
    } else if (direction == RIGHT) {
        for (int i = 0; i < GRID_SIZE; i++) {
            int temp[GRID_SIZE];
            for (int j = 0; j < GRID_SIZE; j++) {
                temp[j] = grid[i][GRID_SIZE - j - 1];
            }
            if (slide_and_merge_row(temp)) {
                changed = true;
            }
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][GRID_SIZE - j - 1] = temp[j];
            }
        }
    } else if (direction == UP) {
        rotate_grid();
        rotate_grid();
        rotate_grid();
        changed = move(LEFT);
        rotate_grid();
    } else if (direction == DOWN) {
        rotate_grid();
        changed = move(LEFT);
        rotate_grid();
        rotate_grid();
        rotate_grid();
    }

    if (changed) {
        add_random_tile();
    }
    return changed;
}

bool check_game_over() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                return false;
            }
            if (j + 1 < GRID_SIZE && grid[i][j] == grid[i][j + 1]) {
                return false;
            }
            if (i + 1 < GRID_SIZE && grid[i][j] == grid[i + 1][j]) {
                return false;
            }
        }
    }
    return true;
}

int get_score() {
    return score;
}

const int (*get_grid())[GRID_SIZE] {
    return grid;
}

void init_game() {
    srand((unsigned int)time(NULL));
    score = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
    add_random_tile();
    add_random_tile();
}
