#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"

typedef node;
typedef queue;

SDL_Renderer* renderer = NULL;

SDL_Surface*  field_surface = NULL;

SDL_Surface*  fruit_surface = NULL;

SDL_Surface*  shead_surface = NULL;

SDL_Surface*  snake_surface = NULL;

SDL_Texture*  field_texture = NULL;

SDL_Texture*  fruit_texture = NULL;

SDL_Texture*  shead_texture = NULL;

SDL_Texture*  snake_texture = NULL;

void init(void);

void render(void);

void draw_body(void);

void draw_head(void);

void draw_fruit(void);

void clear_tail(void);

#endif //GRAPHICS_H
