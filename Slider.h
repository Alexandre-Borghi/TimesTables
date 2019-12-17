#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SDL2/SDL.h>

typedef struct App App;

typedef struct Slider
{
    SDL_Color barColor;
    SDL_Color handleColor;
    SDL_Color hoverColor;
    SDL_Color pressColor;

    SDL_Rect bar;
    SDL_Rect handle;

    int isHovered;
    int isPressed;
    int callCallback;
    
    float minVal;
    float maxVal;
    double* value;
} Slider;

void CreateSlider(
    Slider* s,
    int x, int y, int w, int h, 
    float minVal_, float maxVal_, double* value_,
    SDL_Color barColor_,
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor
    );
void DrawSlider(App* app, Slider* s);
void EventSlider (Slider* s, SDL_Event* e);

#endif