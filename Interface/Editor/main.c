#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "postprocess.h"

int main(int argc, char **argv)
{
    if (argc != 2)
	errx(1, "You must put 2 arguments\n");

    SDL_Surface *image = postprocess(argv[1]);
    IMG_SavePNG(image, "partition.png");
    SDL_FreeSurface(image);
    SDL_Quit();
    
    return 0;
}
