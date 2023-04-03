#ifndef POST_CREATE_IMAGE_H
#define POST_CREATE_IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef CELL_SIZE
    #define CELL_SIZE 50
#endif

void add_note(SDL_Surface *res, int x, int y);

#endif
