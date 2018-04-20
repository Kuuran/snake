#include "main.h"


SDL_Renderer* renderer = NULL;

SDL_Surface*  field_surface = NULL;

SDL_Surface*  fruit_surface = NULL;

SDL_Surface*  shead_surface = NULL;

SDL_Surface*  snake_surface = NULL;

SDL_Texture*  field_texture = NULL;

SDL_Texture*  fruit_texture = NULL;

SDL_Texture*  shead_texture = NULL;

SDL_Texture*  snake_texture = NULL;

void init(void)

{

    int i, j,wind;

    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());

    }

    atexit(SDL_Quit);

    wind = SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    //SDL_SetVideoMode(640,480,32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_RESIZABLE);

    if(wind!=0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    wind=SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(wind!=0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    fruit_surface = SDL_LoadBMP("apple.bmp.bmp");

    if(fruit_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    shead_surface = SDL_LoadBMP("head.bmp.bmp");

    if(shead_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    snake_surface = SDL_LoadBMP("snake.bmp.bmp");

    if(snake_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    field_surface = SDL_LoadBMP("field.bmp.bmp");

    if(field_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    fruit_texture = SDL_CreateTextureFromSurface(renderer, fruit_surface);

    if(fruit_texture==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    shead_texture = SDL_CreateTextureFromSurface(renderer, shead_surface);

    if(shead_texture==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);

    if(snake_texture==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    field_texture = SDL_CreateTextureFromSurface(renderer, field_surface);

    if(field_texture==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    for (i = 0; i <= MAX_X; i++) {

        for (j = 0; j <= MAX_Y; j++) {

            tail.x = i;

            tail.y = j;

            clear_tail();

        }

    }

    snake.first = 0;

    snake.last = 0;

    snake.len = 0;

    // srand((unsigned) (NULL));

    fruit.x = /*rand() % 16 +*/ 5;

    fruit.y = /*rand() % 6 +*/ 5;

    head = fruit;

    if (head.x < (MAX_X / 2)) {

        dir = RIGHT;

    } else {

        dir = LEFT;

    }

    push_head();

    next_fruit();

    eaten = 1;

    old_dir = 0;

    printf("Level 1\n");

}

void render(void)

{

    if (snake.len > 1) {

        draw_body();

    }

    if (eaten) {

        draw_fruit();

    } else {

        clear_tail();

    }

    draw_head();

    SDL_RenderPresent(renderer);

}

void draw_body(void)

{

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = body.x * TILE_SIZE;

    rect.y = body.y * TILE_SIZE;

    SDL_RenderCopy(renderer, snake_texture, NULL, &rect);

}

void draw_head(void)

{

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = head.x * TILE_SIZE;

    rect.y = head.y * TILE_SIZE;

    SDL_RenderCopy(renderer, shead_texture, NULL, &rect);

}

void draw_fruit(void)

{

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = fruit.x * TILE_SIZE;

    rect.y = fruit.y * TILE_SIZE;

    SDL_RenderCopy(renderer, fruit_texture, NULL, &rect);

}

void clear_tail(void)

{
    int erreur;

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = tail.x * TILE_SIZE;

    rect.y = tail.y * TILE_SIZE;

    erreur=SDL_RenderCopy(renderer, field_texture, NULL, &rect);

    if(erreur!=0)
    {
        fprintf(stderr, "SDL_RenderCopy: %s\n", SDL_GetError());
    }

    /* SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

     SDL_RenderFillRect(renderer, &rect); */

}
