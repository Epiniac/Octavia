#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void save_image(SDL_Renderer* prenderer, SDL_Window* pwindow);
int postprocess(char* p);
int return_n(char* p);

#endif


