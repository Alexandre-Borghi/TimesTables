#include <stdio.h>
#include <SDL2/SDL.h>

#include "Button.h"

const int WINDOWED_WIDTH= 1280;
const int WINDOWED_HEIGHT = 720;
const int FULLSCREEN_WIDTH = 1920;
const int FULLSCREEN_HEIGHT = 1080;


int nbPoints = 100;
float mult = 2;

double pi = 3.14159235;

double min(int a, int b)
{
    // Returns the smaller between a and b
    return a < b ? a : b;
}

void toggleFullscreen(SDL_Window* window)
{
    // https://stackoverflow.com/questions/30629106/sdl2-how-to-properly-toggle-fullscreen

    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    int isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
    // SDL_SetWindowSize(window, isFullscreen ? WINDOWED_WIDTH : FULLSCREEN_WIDTH, isFullscreen ? WINDOWED_HEIGHT : FULLSCREEN_HEIGHT);
    // SDL_ShowCursor(isFullscreen);
}


void draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    double xOff = 355;
    double yOff = 355;

    // int* w;
    // int* h;
    // SDL_GetRendererOutputSize(renderer, w, h);

    double r = 700 / 2;

    // Drawing the outer circle
    SDL_Point points[nbPoints];
    // memset(points, 0, nbPoints * sizeof(SDL_Point));

    for (int i = 0; i <= nbPoints; i++)
    {
        double theta = (pi * 2 / nbPoints) * i;

        SDL_Point temp;
        temp.x = r * cos(theta) + xOff;
        temp.y = r * sin(theta) + yOff;

        points[i] = temp;
    }

    // Adding the last point to close the circle
    points[nbPoints + 1] = points[0];

    SDL_RenderDrawLines(renderer, points, nbPoints + 1);

    for (int i = 0; i < nbPoints; i++)
    {
        double theta = (pi * 2 / nbPoints) * i;

        double x1 = r * cos(theta) + xOff;
        double y1 = r * sin(theta) + yOff;

        theta = (pi * 2 / nbPoints) * i * mult;

        double x2 = r * cos(theta) + xOff;
        double y2 = r * sin(theta) + yOff;

        SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }
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

    window = SDL_CreateWindow("Times Tables", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWED_WIDTH, WINDOWED_HEIGHT, SDL_WINDOW_SHOWN);

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

        mult += 0.0005;
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}