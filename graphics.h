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

void clear_tail(void);

void load_level(SDL_Surface* level_surface);

#endif //GRAPHICS_H
