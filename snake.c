#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 20
#define INITIAL_LENGTH 3

typedef struct Snake {
    int x[100], y[100];
    int length;
    int direction;
} Snake;

void init();
void draw_border();
void draw_snake(Snake *snake);
void move_snake(Snake *snake, int *food_x, int *food_y);
int collision(Snake *snake);
void generate_food(int *food_x, int *food_y, Snake *snake);
void game_over(int score);

int main() {
    Snake snake;
    int food_x, food_y;
    int ch;
    int score = 0;

    srand(time(NULL));
    init();

    snake.length = INITIAL_LENGTH;
    snake.x[0] = WIDTH / 4;
    snake.y[0] = HEIGHT / 2;

    for (int i = 1; i < snake.length; i++) {
        snake.x[i] = snake.x[i - 1] - 1;
        snake.y[i] = snake.y[0];
    }

    snake.direction = KEY_RIGHT;

    generate_food(&food_x, &food_y, &snake);

    while (1) {
        clear();
        draw_border();
        draw_snake(&snake);
        mvprintw(1, 1, "Score: %d", score);
        mvprintw(food_y, food_x, "*");

        refresh();

        ch = getch();
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT) {
            if ((snake.direction == KEY_UP && ch != KEY_DOWN) ||
                (snake.direction == KEY_DOWN && ch != KEY_UP) ||
                (snake.direction == KEY_LEFT && ch != KEY_RIGHT) ||
                (snake.direction == KEY_RIGHT && ch != KEY_LEFT)) {
                snake.direction = ch;
            }
        }

        move_snake(&snake, &food_x, &food_y);

        if (collision(&snake)) {
            game_over(score);
            break;
        }

        score = snake.length - INITIAL_LENGTH;

        usleep(500000);
    }

    endwin();
    return 0;
}

void init() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100);
}

void draw_border() {
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT, i, "#");
    }

    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH, "#");
    }
}

void draw_snake(Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        mvprintw(snake->y[i], snake->x[i], (i == 0) ? "O" : "o");
    }
}

void move_snake(Snake *snake, int *food_x, int *food_y) {
    int new_x = snake->x[0];
    int new_y = snake->y[0];

    switch (snake->direction) {
        case KEY_UP: new_y--; break;
        case KEY_DOWN: new_y++; break;
        case KEY_LEFT: new_x--; break;
        case KEY_RIGHT: new_x++; break;
    }

    for (int i = snake->length - 1; i > 0; i--) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }

    snake->x[0] = new_x;
    snake->y[0] = new_y;

    if (new_x == *food_x && new_y == *food_y) {
        snake->length++;
        generate_food(food_x, food_y, snake);
    }
}

int collision(Snake *snake) {
    if (snake->x[0] <= 0 || snake->x[0] >= WIDTH || snake->y[0] <= 0 || snake->y[0] >= HEIGHT) {
        return 1;
    }

    for (int i = 1; i < snake->length; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i]) {
            return 1;
        }
    }

    return 0;
}

void generate_food(int *food_x, int *food_y, Snake *snake) {
    int valid;
    do {
        valid = 1;
        *food_x = rand() % (WIDTH - 1) + 1;
        *food_y = rand() % (HEIGHT - 1) + 1;

        for (int i = 0; i < snake->length; i++) {
            if (snake->x[i] == *food_x && snake->y[i] == *food_y) {
                valid = 0;
                break;
            }
        }
    } while (!valid);
}

void game_over(int score) {
    clear();
    mvprintw(HEIGHT / 2, WIDTH / 4, "Game Over!");
    mvprintw(HEIGHT / 2 + 1, WIDTH / 4, "Final Score: %d", score);
    mvprintw(HEIGHT / 2 + 2, WIDTH / 4, "Press any key to exit...");
    refresh();
    getch();
}
