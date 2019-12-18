#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "App.h"

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
    App* app = malloc(sizeof(App));

    CreateApp(app, "Times Tables Drawing", 1280, 720, 1280, 720, 100, 2);

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

                default:
                    break;
            }

            for (int i = 0; i < BUTTON_COUNT; i++)
            {
                EventButton(&app->buttons[i], &event);
            }

            for (int i = 0; i < SLIDER_DOUBLE_COUNT; i++)
            {
                EventSlider(&app->slidersDouble[i], &event);
            }
        }

        // Clearing window
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
        SDL_RenderClear(app->renderer);
        
        // Drawing
        DrawApp(app);
   
        // Updating the window
        SDL_RenderPresent(app->renderer);

        app->mult += app->speed;
    }

    DestroyApp(app);

    free(app);

    TTF_Quit();

    SDL_Quit();

	return 0;
}