#include "postprocess.h"

SDL_Surface *postprocess(char* p) 
{
    SDL_Surface* temp = IMG_Load(TEMPLATE);
    SDL_Surface* result = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGB888 , 0);
    SDL_FreeSurface(temp);

    char* notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int n = return_n(p);
    char note = *notes[n];

    // x et y inverse
    // 50
    // do : x = 40 y = 16
    // re : x = 40 y = 12
    // mi : x = 40 y = 8
    // fa : y = 5
    // sol : y = 1
    // la : y = -3
    // si : y = -7 
    
    int x = 40;
    int y;
    if (note == 'C' || note == "C#")
	y = 16;
    else if (note == "D" || note == "D#")
	y = 12;
    else if (note == "E")
	y = 8;
    else if (note == "F" || note == "F#")
	y = 5;
    else if (note == "G" || note == "G#")
	y = 1;
    else if (note == "A" || note == "A#")
	y = -3;
    else if (note == "B")
	y = -7;

    add_note(result, x, y);
    
    return result;
}

