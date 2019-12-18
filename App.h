#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

#include "Button.h"
#include "SliderDouble.h"

#define PI     3.141592653
#define TWO_PI 6.283185306

#define BUTTON_COUNT 1
#define SLIDER_COUNT 1

typedef struct App
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

    Button* buttons;
    SliderDouble* sliders;
} App;

void CreateApp (App* app, char* title, int wW, int wH, int fW, int fH, int nbPoints_, double mult_);
void DrawApp (App* app);
void DestroyApp (App* app);

#endif