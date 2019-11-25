#include <stdio.h>
#include <SDL2/SDL.h>

#include "App.h"

#include "Button.h"

void toggleFullscreen (SDL_Window* window)
{
    // https://stackoverflow.com/questions/30629106/sdl2-how-to-properly-toggle-fullscreen

    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    int isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
    // SDL_SetWindowSize(window, isFullscreen ? WINDOWED_WIDTH : FULLSCREEN_WIDTH, isFullscreen ? WINDOWED_HEIGHT : FULLSCREEN_HEIGHT);
    // SDL_ShowCursor(isFullscreen);
}


int main (int argc, char* args[])
{
    struct App* app = malloc(sizeof(struct App));
    CreateApp(app, 1280, 720, 1280, 720, 100, 2);
    InitApp(app, "Times Tables Drawing");

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
                    if (event.key.keysym.sym == SDLK_F1) toggleFullscreen(app->window); break;
                    break;

                default:
                    break;
            }
        }

        // Clearing window
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
        SDL_RenderClear(app->renderer);
        
        // Drawing
        DrawApp(app);

        // Updating the window
        SDL_RenderPresent(app->renderer);

        app->mult += 0.0005;
    }

    SDL_DestroyWindow(app->window);

    SDL_Quit();

	return 0;
}