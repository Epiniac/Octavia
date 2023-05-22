#include "create_image.h"

void add_note(SDL_Surface *res, int x, int y)
{
    SDL_Color note_color = {0, 0, 0, 255};
    if (TTF_Init() < 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    TTF_Font *font = TTF_OpenFont("ArchivoNarrow-Regular.ttf", CELL_SIZE);
    if (font == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);

    SDL_Surface* letter = TTF_RenderText_Solid(font, ".", note_color);

    TTF_CloseFont(font);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = CELL_SIZE;
    rect.h = CELL_SIZE;

    SDL_BlitSurface(letter, NULL, res, &rect);

    SDL_FreeSurface(letter);
}
