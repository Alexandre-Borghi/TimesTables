#include <SDL2/SDL.h>
#include <stdio.h>

int windowedWidth = 1280;
int windowedHeight = 720;
int fullscreenWidth = 1920;
int fullscreenHeight = 1080;


void draw(SDL_Renderer* renderer)
{
    
}


void toggleFullscreen(SDL_Window* window)
{
    // https://stackoverflow.com/questions/30629106/sdl2-how-to-properly-toggle-fullscreen

    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    int isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
    SDL_SetWindowSize(window, isFullscreen ? windowedWidth : fullscreenWidth, isFullscreen ? windowedHeight : fullscreenHeight);
    // SDL_ShowCursor(isFullscreen);
}


int main (int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // SDL2 and Window intialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: Couldn't initialize SDL2\n");
        return 0;
    }

    window = SDL_CreateWindow("Times Tables", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowedWidth, windowedHeight, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("ERROR: Couldn't create the window");
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    int quit = 0;

    while (!quit)
    {
        // Event handling
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_F1) toggleFullscreen(window); break;
                    break;

                default:
                    break;
            }
        }

        // Clearing window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Drawing
        draw(renderer);

        // Updating the window
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}