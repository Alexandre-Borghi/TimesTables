#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

#include "Button.h"
#include "Slider.h"

#define PI     3.141592653
#define TWO_PI 6.283185306

#define BUTTON_COUNT 1
#define SLIDER_COUNT 1

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

    // GUI Variables

    struct Button* buttons;
    struct Slider sliders[SLIDER_COUNT];
};

void CreateApp (struct App* app, char* title, int wW, int wH, int fW, int fH, int nbPoints_, double mult_);
void DrawApp (struct App* app);
void DestroyApp (struct App* app);

#endif