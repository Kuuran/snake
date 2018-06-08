#include "main.h"

void input(void) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    SDL_PumpEvents();
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        angle -= M_PI/7.0;
    } else if (state[SDL_SCANCODE_RIGHT]|| state[SDL_SCANCODE_D]) {
        angle+= M_PI/7.0;
    } else if (state[SDL_SCANCODE_ESCAPE]) {
        exit(0);
    }


    SDL_Event event;
    while (SDL_PollEvent(&event)) // Récupération des actions de l'utilisateur
    {
        switch(event.type)
        {
            case SDL_KEYUP: // Relâchement d'une touche
                if ( event.key.keysym.sym == SDLK_f ) // Touche f
                {
                    // Alterne du mode plein écran au mode fenêtré
                    if ( fullscreen == 0 )
                    {
                        fullscreen = 1;
                        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
                    }
                    else if ( fullscreen == 1 )
                    {
                        fullscreen = 0;
                        SDL_SetWindowFullscreen(window,0);
                    }
                }
                break;
        }
    }

    /* Ignore opposite direction */
    // INUTILE ?
    if (dir + old_dir != 5 || snake.len == 1) {
        old_dir = dir;
    } else {
        dir = old_dir;
    }
}

int update(void) {
    body = head;
    head.x += cos(angle) * SPEED_SCALE;
    head.y += sin(angle) * SPEED_SCALE;

    if (head.x < 0/*&& (angle <= M_PI/2 || angle >= -M_PI/2)*/) {
        head.x=MAX_X;
    }else if( head.x > MAX_X /*&& (angle >= M_PI/2 || angle <= -M_PI/2)*/){
    head.x=0;
    }else if( head.y < 0 /*&& (angle <= M_PI || angle >= 0)*/){
    head.y=MAX_Y;
    }else if( head.y > MAX_Y /*&& (angle >= M_PI || angle <= 0)*/){
    head.y=0;
    }
    // Detection des collisions
    for (int i = 0; i < snake.len-1; i++){
        if (head.x+0.5 <= snake.elems[i].x +1 && head.x+0.5 >= snake.elems[i].x && head.y-0.5 <= snake.elems[i].y && head.y-0.5 >= snake.elems[i].y -1){
            return 1;
        }
    }

    if (head.x+0.5 <= fruit.x +1 && head.x+0.5 >= fruit.x && head.y-0.5 <= fruit.y && head.y-0.5 >= fruit.y -1) { // head.x <= fruit.x +16 && head.x >= fruit.x -16
        next_fruit();
        eaten = 1;
        switch (snake.len) {
            case 10:
                *delay -= 2;
                printf("Level 2\n");
                break;
            case 20:
                *delay -= 2;

                load_level(SDL_LoadBMP("field2.bmp"));

                printf("Level 3\n");
                break;
            case 30:
                *delay /= 2;
                printf("Level 4\n");
                break;
            case 40:
                *delay /= 2;
                printf("Level 5\n");
                break;
        }
    } else if (head.x+0.5 <= bombs.x +1 && head.x+0.5 >= bombs.x && head.y-0.5 <= bombs.y && head.y-0.5 >= bombs.y -1) {

        bombed=1;
        if(snake.len==1){
            gameover();
        }
        next_bombs();
        pop_tail();
        pop_tail();

    }
        else{
        pop_tail();
        eaten = 0;
        bombed = 0;
    }


    push_head();
    return 0;
}

void pop_tail(void) {

    tail = snake.elems[snake.first];
    snake.first = (snake.first + 1) % QUEUE_SIZE;
    //snake.last = snake.last-1;

    snake.len--;
}

void push_head(void) {
    //TODO deplacement tous les 400 tiles
    snake.elems[snake.last] = head;
    snake.last = (snake.last + 1) % QUEUE_SIZE;


    //for(int i=0; i<QUEUE_SIZE-1; i++){

    //}

    snake.len++;
}

void gameover(void) {
    printf("Snake Length: %d\n", snake.len);
    printf("Game Over\n");
    exit(0);
}

void next_fruit(void) {

    mat[(int)fruit.x][(int)fruit.y]=0;

    do {
        fruit.x = ((int)fruit.x * 8 + 1) % (MAX_X + 1);
        fruit.y = ((int)fruit.y * 12 + 1) % (MAX_Y + 1);
    } while (mat[(int)fruit.x][(int)fruit.y]);
    mat[(int)fruit.x][(int)fruit.y]=1;
}

void next_bombs(){

    mat[(int)bombs.x][(int)bombs.y]=0;

    do{

        bombs.x = ((int)bombs.x * 4 + 1) % (MAX_X + 1);
        bombs.y = ((int)bombs.y * 11 +2) % (MAX_Y + 1);

    }while(mat[(int)bombs.x][(int)bombs.y]);
    mat[(int)bombs.x][(int)bombs.y]=1;
}
