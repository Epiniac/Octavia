#include "postprocess.h"

void save_image(SDL_Renderer* prenderer, SDL_Window* pwindow)
{
    SDL_Surface* saveimage = SDL_CreateRGBSurface(0, 629, 645, 32, 0, 0, 0, 0);
    if (saveimage)
    {
	SDL_RenderReadPixels(prenderer, NULL, SDL_GetWindowPixelFormat(pwindow), saveimage->pixels, saveimage -> pitch);
	IMG_SavePNG(saveimage, "partition.png");
	SDL_FreeSurface(saveimage);
    }
}

int postprocess(char* p) 
{
    // Chargement du module video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
	return EXIT_FAILURE;
    }

    // Creation fenetre
    SDL_Window* pwindow = NULL;
    SDL_Renderer* prenderer = NULL;
    if (SDL_CreateWindowAndRenderer(629, 645, SDL_WINDOW_HIDDEN, &pwindow, &prenderer) < 0)
    {
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
	SDL_Quit();
	return EXIT_FAILURE;
    }
 
    // Chargement image 
    SDL_Surface* template = IMG_Load("empty.png");
    SDL_Texture* texturetemplate = SDL_CreateTextureFromSurface(prenderer, template); 
    SDL_FreeSurface(template);
    SDL_RenderCopy(prenderer, texturetemplate, NULL, NULL);
    SDL_Surface* croche;
    SDL_Texture* texturecroche;
 

    // Get melodie
    char* notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int* index = return_n(p); 
    size_t len = sizeof(index);
    printf("len = %ld\n", len);
    char* melodie[len];
    for (size_t i = 0; i < len; i++)
    {
	melodie[i] = notes[index[i]];
    }    
    

    // Ajout des notes    
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 0;
    src.h = 0;

    SDL_Rect dst;
    dst.x = 50;

    for (size_t i = 0; i < sizeof(melodie)/sizeof(melodie[0]); i++)
    {
	char* note = melodie[i];

    	if (strcmp(note, "C") == 0)
    	{
	    dst.y = 39;
	    dst.w = 19;
	    dst.h = 27;
	    croche = IMG_Load("croche.png");
    	}
	else if (strcmp(note, "C#") == 0)
	{
	    dst.y = 39;
	    dst.w = 27;
	    dst.h = 34;
	    croche = IMG_Load("croche#.png");
	}
    	else if (strcmp(note, "D") == 0)
    	{
	    dst.y = 36;
	    dst.w = 19;
	    dst.h = 27;
	    croche = IMG_Load("croche.png");
	}
	else if (strcmp(note, "D#") == 0)
	{
	    dst.y = 36;
	    dst.w = 27;
	    dst.h = 34;
	    croche = IMG_Load("croche#.png");
    	}
    	else if (strcmp(note, "E") == 0)
    	{
	    dst.y = 33;
	    dst.w = 19;
	    dst.h = 27;
	    croche = IMG_Load("croche.png");
    	}
    	else if (strcmp(note, "F") == 0)
    	{
	    dst.y = 29;
	    dst.w = 19;
	    dst.h = 27;
	    croche = IMG_Load("croche.png");
	}
	else if (strcmp(note, "F#") == 0)
	{
	    dst.y = 29;
	    dst.w = 27;
	    dst.h = 34;
	    croche = IMG_Load("croche#.png");
    	}
    	else if (strcmp(note, "G") == 0)
    	{
	    dst.y = 26;
	    dst.w = 19;
	    dst.h = 27;
	    croche = IMG_Load("croche.png");
	}
	else if (strcmp(note, "G#") == 0)
	{
	    dst.y = 26;
	    dst.w = 27;
	    dst.h = 34;
	    croche = IMG_Load("croche#.png");
    	}
    	else if (strcmp(note, "A") == 0)
    	{
	    dst.y = 22;
	    dst.w = 19;
	    dst.h = 27;
	    croche = IMG_Load("croche.png");
	}
	else if (strcmp(note, "A#") == 0)
	{
	    dst.y = 22;
	    dst.w = 27;
	    dst.h = 34;
	    croche = IMG_Load("croche#.png");
    	}
    	else if (strcmp(note, "B") == 0)
    	{
	    dst.y = 29;
	    dst.w = 19;
	    dst.h = 40;
	    croche = IMG_Load("croche_envers.png");
    	}
    
    	texturecroche = SDL_CreateTextureFromSurface(prenderer, croche);
    	SDL_FreeSurface(croche);
    	SDL_QueryTexture(texturecroche, NULL, NULL, &src.w, &src.h);
	
	SDL_RenderCopy(prenderer, texturecroche, &src, &dst);
	SDL_RenderPresent(prenderer);
	dst.x += 50;
    }

    // Sauvegarde en image png
    save_image(prenderer, pwindow);

    SDL_DestroyTexture(texturetemplate);
    SDL_DestroyTexture(texturecroche);
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}
