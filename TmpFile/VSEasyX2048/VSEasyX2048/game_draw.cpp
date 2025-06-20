//
// Created by 24087 on 24-12-2.
//
#define _CRT_SECURE_NO_WARNINGS

#include "game_draw.h"

#include <conio.h>
#include <easyx.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>

#include "game_logic.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define CELL_SIZE (WINDOW_WIDTH / GRID_SIZE)

static int background_color = RGB(187, 173, 160);
static int tile_colors[16] = {
    RGB(204, 192, 179),  // 2
    RGB(238, 228, 218),  // 4
    RGB(241, 177, 121),  // 8
    RGB(244, 123, 94),   // 16
    RGB(243, 94, 42),    // 32
    RGB(255, 59, 0),     // 64
    RGB(255, 255, 0),    // 128
    RGB(153, 255, 0),    // 256
    RGB(0, 255, 255),    // 512
    RGB(0, 102, 204),    // 1024
    RGB(0, 51, 102),     // 2048
    RGB(0, 0, 0),        // 超过2048 (可设定为黑色)
};

void init_window() {
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    setbkcolor(background_color);
    cleardevice();
}

static void draw_tile(int x, int y, int value) {
    int tile_color = (value == 0) ? background_color : tile_colors[(int)log2(value) - 1];
    setfillcolor(tile_color);
    fillrectangle(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);

    if (value != 0) {
        char value_str[5];
        sprintf(value_str, "%d", value);
        settextstyle(24, 0, "Arial");
        settextcolor(RGB(255, 255, 255));
        int text_width = textwidth(value_str);
        int text_height = textheight(value_str);
        int text_x = x * CELL_SIZE + (CELL_SIZE - text_width) / 2;
        int text_y = y * CELL_SIZE + (CELL_SIZE - text_height) / 2;
        outtextxy(text_x, text_y, value_str);
    }
}

void draw_grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            draw_tile(i, j, get_grid()[i][j]);
        }
    }
}

void draw_score() {
    char score_str[20];
    sprintf(score_str, "Score: %d", get_score());
    settextstyle(24, 0, "Arial");
    settextcolor(RGB(255, 255, 255));
    outtextxy(10, 10, score_str);
}

void draw_game_over() {
    settextstyle(40, 0, "Arial");
    settextcolor(RGB(255, 0, 0));
    outtextxy(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, "Game Over!");
}

void draw_win() {
    settextstyle(40, 0, "Arial");
    settextcolor(RGB(0, 255, 0));
    outtextxy(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, "You Win!");
}

void render_game() {
    cleardevice();    // 清空屏幕
    draw_grid();      // 绘制棋盘
    draw_score();     // 绘制分数

    if (check_game_over()) {
        draw_game_over();
    }

    if (get_score() >= 2038) {
        draw_win();
    }

    FlushBatchDraw(); // 刷新图形界面
}
