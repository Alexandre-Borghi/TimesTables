#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SDL2/SDL.h>

typedef struct App App;

typedef struct SliderInt
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

    int xOffsetWhenGrabbed;
    
    int minVal;
    int maxVal;
    int* value;
} SliderInt;

void CreateSliderInt(
    SliderInt* s,
    int x, int y, int w, int h, 
    int minVal_, int maxVal_, int* value_,
    SDL_Color barColor_,
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor
    );
void DrawSliderInt (App* app, SliderInt* s);
void EventSliderInt (SliderInt* s, SDL_Event* e);

#endif