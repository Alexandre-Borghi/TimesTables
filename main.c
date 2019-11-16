#include <SDL2/SDL.h>
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int main (int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Surface* renderSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: Couldn't initialize SDL2\n");
        return -1;
    }

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );

    if (window == NULL)
    {
        printf("ERROR: Couldn't create the window");
        return -1;
    }

    renderSurface = SDL_GetWindowSurface(window);

    SDL_FillRect(renderSurface, NULL, SDL_MapRGB(renderSurface->format, 0xFF, 0xFF, 0xFF));
    
    SDL_UpdateWindowSurface(window);

    SDL_Delay(10000);

    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}