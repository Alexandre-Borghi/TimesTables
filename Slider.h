#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SDL2/SDL.h>

struct App;

struct Slider
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
};

struct Slider CreateSlider(int x, int y, int w, int h, 
    float minVal_, float maxVal_, double* value_,
    SDL_Color barColor_,
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor
    );
void DrawSlider(struct App* app, struct Slider* slider);
void EventSlider (struct Slider* slider, SDL_Event* e);

#endif