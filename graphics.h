#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"

typedef struct tag_node node;

void init(void);

void render(void);

void draw_body(node elmt);

void draw_head(void);

void draw_fruit(void);

void draw_bombs();

void draw_mur();

void draw_metafruit();

void clear_tail(void);

void load_level(SDL_Surface* level_surface);

void load_apple(SDL_Surface* apple_surface);

void load_body(SDL_Surface* body_surface);

void load_head(SDL_Surface* head_surface);

void load_metafruit(SDL_Surface* banana_surface);

#endif //GRAPHICS_H
