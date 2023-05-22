#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include "create_image.h"
#include "../V2/detect.h"
#include <SDL2/SDL_image.h>
 

#include <string.h>
#include <stdbool.h>
#include <err.h>
#include <SDL2/SDL.h>


#define TEMPLATE "empty.png"

SDL_Surface *postprocess(char* p);
int return_n(char* p);

#endif


