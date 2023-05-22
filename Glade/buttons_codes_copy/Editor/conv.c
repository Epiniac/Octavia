#include "conv.h"

void conv(char *path)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Surface *image = postprocess(path);
    printf("EST PASSER PAR LA! \n");
    IMG_SavePNG(image, "partition.png");
    printf("EST PASSER PAR LA!  2\n");
    SDL_FreeSurface(image);
    printf("EST PASSER PAR LA! 3 \n");
    SDL_Quit();
    printf("EST PASSER PAR LA! fino\n");
}
