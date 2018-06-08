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

    node tmp = head;

    tmp.x += cos(angle) * SPEED_SCALE;
    tmp.y += sin(angle) * SPEED_SCALE;

    // Detection des collisions
    for (int i = 0; i < snake.len-1; i++){
        if (tmp.x+0.5 <= snake.elems[i].x +1 && tmp.x+0.5 >= snake.elems[i].x && tmp.y-0.5 <= snake.elems[i].y && tmp.y-0.5 >= snake.elems[i].y -1){
            return 1;
        }
    }

    if (tmp.x+0.5 <= fruit.x +1 && tmp.x+0.5 >= fruit.x && tmp.y-0.5 <= fruit.y && tmp.y-0.5 >= fruit.y -1) { // head.x <= fruit.x +16 && head.x >= fruit.x -16
        next_fruit();
        move(1,0);
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
    } else if (tmp.x+0.5 <= bombs.x +1 && tmp.x+0.5 >= bombs.x && tmp.y-0.5 <= bombs.y && tmp.y-0.5 >= bombs.y -1) {


        next_bombs();
        move(0,1);

    }
        else{
        move(0,0);
    }
    return 0;
}


void victory(){


}


void move(int eaten, int bombed){
    if(eaten == 1){
        snake.len ++;

            for(int i=snake.len-1; i>0; i--){
            snake.elems[i] = snake.elems[i-1];
        }
        snake.elems[0] = head;

        head.x += cos(angle) * SPEED_SCALE;
        head.y += sin(angle) * SPEED_SCALE;

    }else if(bombed == 1){
        snake.len --;
        if (snake.len == -1) gameover();

        for(int i=snake.len-1; i>0; i--){
            snake.elems[i] = snake.elems[i-1];
        }
        snake.elems[0] = head;

        head.x += cos(angle) * SPEED_SCALE;
        head.y += sin(angle) * SPEED_SCALE;

        //snake.elems[snake.len] = NULL;

    }else{
        for(int i=snake.len-1; i>0; i--){
            snake.elems[i] = snake.elems[i-1];
        }
        snake.elems[0] = head;

        head.x += cos(angle) * SPEED_SCALE;
        head.y += sin(angle) * SPEED_SCALE;
    }

    if (head.x < 0) {
        head.x=MAX_X;
    }else if( head.x > MAX_X){
    head.x=0;
    }else if( head.y < 0){
    head.y=MAX_Y;
    }else if( head.y > MAX_Y){
    head.y=0;
    }

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
