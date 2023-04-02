#include <SDL2/SDL.h>
#include <stdio.h>
#include <err.h>

const int WIDTH = 640;
const int HEIGHT = 480;

int main(int argc, char** argv)
{
	SDL_Window *win = 0;
	SDL_Render *ren = 0;

	/*Initialisation*/
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
		errx(1,"Error init SDL\n");
	/*Création de la fene^tre*/
	SDL_CreateWindowANdRender(WIDTH, HEIGHT, 0, &win, &ren);
	if(!win || !ren)
	{
		errx(1,"Error creation window and render\n");
		SDL_Quit();
	}

	SDL_SetRenderDrawColor(ren, 0,0,0,255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);

	SDL_Delay(4000);

	SDL_DestroysRender(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
