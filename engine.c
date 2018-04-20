#include "main.h"

void input(void)

{

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    SDL_PumpEvents();

    if (state[SDL_SCANCODE_UP]) {

        dir = UP;

    } else if (state[SDL_SCANCODE_DOWN]) {

        dir = DOWN;

    } else if (state[SDL_SCANCODE_LEFT]) {

        dir = LEFT;

    } else if (state[SDL_SCANCODE_RIGHT]) {

        dir = RIGHT;

    } else if (state[SDL_SCANCODE_ESCAPE]) {

        exit(0);

    }

    /* Ignore opposite direction */

    if (dir + old_dir != 5 || snake.len == 1) {

        old_dir = dir;

    } else {

        dir = old_dir;

    }

}

int update(void)

{
    delay=16;

    body = head;

    switch (dir) {

        case UP:

            head.y = head.y - 1;

            break;

        case DOWN:

            head.y = head.y + 1;

            break;

        case LEFT:

            head.x = head.x - 1;

            break;

        case RIGHT:

            head.x = head.x + 1;

            break;

    }

    if (head.x < 0 || head.x > MAX_X || head.y < 0 || head.y > MAX_Y) {

        return 1;

    }

    if (mat[head.x][head.y]) {

        return 1;

    }

    if (head.x == fruit.x && head.y == fruit.y) {

        next_fruit();

        eaten = 1;

        switch (snake.len) {

            case 10:

                delay -= 4;

                printf("Level 2\n");

                break;

            case 20:

                delay -= 4;

                printf("Level 3\n");

                break;

            case 30:

                delay /= 2;

                printf("Level 4\n");

                break;

            case 40:

                delay /= 2;

                printf("Level 5\n");

                break;

        }

    } else {

        pop_tail();

        eaten = 0;

    }

    push_head();

    return 0;

}

void pop_tail(void)

{

    tail = snake.elems[snake.first];

    snake.first = (snake.first + 1) % QUEUE_SIZE;

    snake.len--;

    mat[tail.x][tail.y] = 0;

}

void push_head(void)

{

    snake.elems[snake.last] = head;

    snake.last = (snake.last + 1) % QUEUE_SIZE;

    snake.len++;

    mat[head.x][head.y] = 1;

}

void gameover(void)

{

    printf("Snake Length: %d\n", snake.len);

    printf("Game Over\n");

    exit(0);

}

void next_fruit(void)

{

    do {

        fruit.x = (fruit.x * 6 + 1) % (MAX_X + 1);

        fruit.y = (fruit.y * 16 + 1) % (MAX_Y + 1);

    } while (mat[fruit.x][fruit.y]);

}
