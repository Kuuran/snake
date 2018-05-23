#ifndef ENGINE_H
#define ENGINE_H

int *delay;


SDL_Window *window;

void input(void);

int  update(void);

void pop_tail(void);

void push_head(void);

void gameover(void);

void next_fruit(void);

void next_bombs();

#endif //ENGINE_H
