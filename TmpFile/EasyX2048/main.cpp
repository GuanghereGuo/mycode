#include <conio.h>
#include <easyx.h>
#include <stdio.h>

#include "game_draw.h"
#include "game_logic.h"

#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define ESC_KEY   27

void handle_input() {
    int key = _getch();
    switch (key) {
        case KEY_UP:
            move(LEFT);
        break;
        case KEY_DOWN:
            move(RIGHT);
        break;
        case KEY_LEFT:
            move(UP);
        break;
        case KEY_RIGHT:
            move(DOWN);
        break;
        case ESC_KEY:
            exit(0);
        break;
    }
}


int main() {
    init_window();
    BeginBatchDraw();
    init_game();

    while (true) {
        render_game();

        if (check_game_over()) {
            draw_game_over();
            break;
        }

        if (_kbhit()) {
            handle_input();
        }
    }

    getchar();
    EndBatchDraw();
    closegraph();
    return 0;
}

