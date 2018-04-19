#ifndef ENGINE_H
#define ENGINE_H

#include "main.h"

char mat[MAX_X+1][MAX_Y+1];


int delay = 16;



void input(void);

int  update(void);

void pop_tail(void);

void push_head(void);

void gameover(void);

void next_fruit(void);

#endif //ENGINE_H
