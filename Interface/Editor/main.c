#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "postprocess.h"

int main()
{
    SDL_Surface *image = postprocess();
    IMG_SavePNG(image, "partition.png");
    SDL_FreeSurface(image);
    SDL_Quit();
    
    return 0;
}
