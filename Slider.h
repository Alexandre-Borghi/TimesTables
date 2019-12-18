#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SDL2/SDL.h>

typedef struct App App;

typedef struct SliderDouble
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
    
    double minVal;
    double maxVal;
    double* value;
} SliderDouble;

void CreateSliderDouble(
    SliderDouble* s,
    int x, int y, int w, int h, 
    double minVal_, double maxVal_, double* value_,
    SDL_Color barColor_,
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor
    );
void DrawSlider(App* app, SliderDouble* s);
void EventSlider (SliderDouble* s, SDL_Event* e);

#endif