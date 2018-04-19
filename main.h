#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <SDL2/SDL.h>

#include "graphics.h"

#include "engine.h"



#define QUEUE_SIZE 400

#define LEFT  1

#define UP    2

#define DOWN  3

#define RIGHT 4

#define MAX_X 24

#define MAX_Y 14

#define TILE_SIZE 32


typedef struct tag_node {

    char x;

    char y;

} node;


typedef struct tag_queue {

    int first;

    int last;

    int len;

    node elems[QUEUE_SIZE];

} queue;


char dir;

char old_dir;

char eaten;



node body;

node head;

node tail;

node fruit;


queue snake;


#endif //MAIN_H
