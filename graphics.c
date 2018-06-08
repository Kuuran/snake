#include "main.h"


SDL_Renderer* renderer = NULL;

SDL_Surface*  field_surface = NULL;

SDL_Surface*  fruit_surface = NULL;

SDL_Surface*  shead_surface = NULL;

SDL_Surface*  snake_surface = NULL;

SDL_Surface*  bombs_surface = NULL;

SDL_Surface*  metafruit_surface = NULL;

SDL_Surface*  wall_surface = NULL;

SDL_Texture*  field_texture = NULL;

SDL_Texture*  fruit_texture = NULL;

SDL_Texture*  shead_texture = NULL;

SDL_Texture*  snake_texture = NULL;

SDL_Texture*  bombs_texture = NULL;

SDL_Texture*  metafruit_texture = NULL;

SDL_Texture*  wall_texture = NULL;



void init(void){

    int i, j,wind;

    window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());

}

    atexit(SDL_Quit);


    wind = SDL_CreateWindowAndRenderer(800, 576, 0, &window, &renderer);

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

    fruit_surface = SDL_LoadBMP("apple.bmp");
    for (int i=0; i<snake.len-1; i++){
        draw_body(snake.elems[i]);
    }

    if(fruit_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

     metafruit_surface = SDL_LoadBMP("metafruit3.bmp");
    if(metafruit_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    shead_surface = SDL_LoadBMP("head.bmp");

    if(shead_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    bombs_surface = SDL_LoadBMP("bomb.bmp");

     if(bombs_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

     wall_surface = SDL_LoadBMP("wall.bmp");

     if(wall_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    snake_surface = SDL_LoadBMP("snake.bmp");

    if(snake_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    field_surface = SDL_LoadBMP("field.bmp");

    if(field_surface==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    fruit_texture = SDL_CreateTextureFromSurface(renderer, fruit_surface);

    if(fruit_texture==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

    metafruit_texture = SDL_CreateTextureFromSurface(renderer, metafruit_surface);

    if(metafruit_texture==NULL)
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

    bombs_texture = SDL_CreateTextureFromSurface(renderer, bombs_surface);
    if(bombs_texture==NULL)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    }

     wall_texture = SDL_CreateTextureFromSurface(renderer, wall_surface);
    if(wall_texture==NULL)
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

    compteur_mur = 0;

    for(int i = 0; i<NB_MUR;i++){

        mur[i].x = 300;
        mur[i].y = 200;

    }

    // srand((unsigned) (NULL));

    fruit.x = /*rand() % 16 +*/ 4;

    fruit.y = /*rand() % 6 +*/ 5;

    head = fruit;

    if (head.x < (MAX_X / 2)) {

        dir = RIGHT;

    } else {

        dir = LEFT;

    }

    next_fruit();

    next_bombs();

    printf("Level 1\n");

}

void render(void){
    SDL_RenderClear(renderer);

    for (int i = 0; i <= MAX_X; i++) {

        for (int j = 0; j <= MAX_Y; j++) {

            tail.x = i;

            tail.y = j;

            clear_tail();

        }

    }

    if (snake.len > 0) {

        for (int i=0; i<snake.len; i++){
            draw_body(snake.elems[i]);
            }

    }

    draw_fruit();

    draw_bombs();

    draw_head();

    SDL_RenderPresent(renderer);

}

void draw_body(node elmt){

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = elmt.x * TILE_SIZE;

    rect.y = elmt.y * TILE_SIZE;

    SDL_RenderCopy(renderer, snake_texture, NULL, &rect);

}

void draw_head(void){

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = head.x * TILE_SIZE;

    rect.y = head.y * TILE_SIZE;

    SDL_RenderCopy(renderer, shead_texture, NULL, &rect);

}

void draw_fruit(void){

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = fruit.x * TILE_SIZE;

    rect.y = fruit.y * TILE_SIZE;

    SDL_RenderCopy(renderer, fruit_texture, NULL, &rect);

}

void draw_bombs(){

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = bombs.x * TILE_SIZE;

    rect.y = bombs.y * TILE_SIZE;

    SDL_RenderCopy(renderer, bombs_texture, NULL, &rect);
}

void draw_mur(){

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;


    for(int i = 0; i<NB_MUR;i++){


    rect.x = bombs.x * TILE_SIZE;

    rect.y = bombs.y * TILE_SIZE;

    SDL_RenderCopy(renderer, wall_texture, NULL, &rect);
    }
}

void draw_metafruit(){

    SDL_Rect rect;

    rect.h = TILE_SIZE;

    rect.w = TILE_SIZE;

    rect.x = metafruit.x * TILE_SIZE;

    rect.y = metafruit.y * TILE_SIZE;

    SDL_RenderCopy(renderer, metafruit_texture, NULL, &rect);


}

void clear_tail(void){
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

void load_level(SDL_Surface* level_surface){

    field_surface = level_surface;

     if(field_surface==NULL)
    {
        fprintf(stderr, "load level: %s\n", SDL_GetError());
    }

    field_texture = SDL_CreateTextureFromSurface(renderer, field_surface);

    if(field_texture==NULL)
    {
        fprintf(stderr, "load level: %s\n", SDL_GetError());
    }
}

void load_head(SDL_Surface* head_surface){

    shead_surface = head_surface;

     if(shead_surface==NULL)
    {
        fprintf(stderr, "load head: %s\n", SDL_GetError());
    }

    shead_texture = SDL_CreateTextureFromSurface(renderer, shead_surface);

    if(shead_texture==NULL)
    {
        fprintf(stderr, "load head: %s\n", SDL_GetError());
    }

}

void load_body(SDL_Surface* body_surface){

    snake_surface = body_surface;

    if(snake_surface==NULL)
    {
        fprintf(stderr, "load body: %s\n", SDL_GetError());
    }

    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);

    if(snake_texture==NULL)
    {
        fprintf(stderr, "load body: %s\n", SDL_GetError());
    }

}

void load_apple(SDL_Surface* apple_surface){

    fruit_surface = apple_surface;

    if(fruit_surface==NULL)
    {
        fprintf(stderr, "load apple: %s\n", SDL_GetError());
    }

    fruit_texture = SDL_CreateTextureFromSurface(renderer, fruit_surface);

    if(fruit_texture==NULL)
    {
        fprintf(stderr, "load apple: %s\n", SDL_GetError());
    }

}

void load_metafruit(SDL_Surface* banana_surface){

    metafruit_surface = banana_surface;

    if(metafruit_surface==NULL)
    {
        fprintf(stderr, "load meta: %s\n", SDL_GetError());
    }

    metafruit_texture = SDL_CreateTextureFromSurface(renderer, metafruit_surface);

    if(metafruit_texture==NULL)
    {
        fprintf(stderr, "load meta: %s\n", SDL_GetError());
    }
}
