#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <SDL2/SDL.h>

#include <math.h>

#include "engine.h"

#include "graphics.h"


#define QUEUE_SIZE 400

#define LEFT  1

#define UP    2

#define DOWN  3

#define RIGHT 4

#define MAX_X 49

#define MAX_Y 37

#define TILE_SIZE 16

#define SPEED_SCALE 1

#define NB_MUR 10


typedef struct tag_node {

    double x;

    double y;

} node;


typedef struct tag_queue {

    int first;

    int last;

    int len;

    node elems[QUEUE_SIZE];

} queue;


char dir;

double angle;

char old_dir;

char eaten;

char bombed;

char mat[MAX_X+1][MAX_Y+1];

node mur[NB_MUR];

int compteur_mur;


node body;

node head;

node tail;

node fruit;

node bombs;




queue snake;

#endif //MAIN_H
