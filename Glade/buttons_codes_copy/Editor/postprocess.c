#include <stdlib.h>
#include <stdio.h>
#include "postprocess.h"
#include "../V2/detect.h"

SDL_Surface *postprocess(char* p) 
{
	
    SDL_Surface* temp = IMG_Load(TEMPLATE);
    SDL_Surface* result = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGB888 , 0);
    SDL_FreeSurface(temp);

    char* notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int n = return_n(p);
    char* note = notes[n];

    // x et y inverse
    // 50
    // do : x = 40 y = 16
    // re : x = 40 y = 12
    // mi : x = 40 y = 8
    // fa : y = 5
    // sol : y = 1
    // la : y = -3
    // si : y = -7 
    
    printf("Starting now...\n");
    int x = 40;
    int y;
    if (strcmp(note, "C") == 0 || strcmp(note, "C#") == 0)
	y = 16;
    else if (strcmp(note, "D") == 0 || strcmp(note, "D#") == 0)
	y = 12;
    else if (strcmp(note, "E") == 0)
	y = 8;
    else if (strcmp(note, "F") == 0 || strcmp(note, "F#") == 0)
	y = 5;
    else if (strcmp(note, "G") == 0  || strcmp(note, "G#") == 0 )
	y = 1;
    else if (strcmp(note, "A") == 0  || strcmp(note, "A") == 0 )
	y = -3;
    else if (strcmp(note, "B") == 0 )
	y = -7;

    add_note(result, x, y);

    printf("I guess you note is: %s\n", note);

    printf("Done !\n");
    return result;
}

