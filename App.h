#ifndef APP_H
#define APP_H

#include "SDL2/SDL.h"

struct App
{
    // SDL Variables

    SDL_Window* window;
    SDL_Renderer* renderer;

    // Window variables

    int windowedWidth;
    int windowedHeight;
    int fullscreenWidth;
    int fullscreenHeight;

    // Drawing variables

    int nbPoints; // Number of points on the circle
    double mult;
};

#define PI     3.141592653
#define TWO_PI 6.283185306

void CreateApp (struct App* app, int wW, int wH, int fW, int fH, int nbPoints_, double mult_);
int InitApp (struct App* app, const char* title);
void DrawApp (struct App* app);

#endif