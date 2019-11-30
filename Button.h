#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

struct Button
{
    SDL_Rect rect;
    SDL_Color borderColor;
    SDL_Color fillColor;
    SDL_Color hoverColor;
    SDL_Color pressColor;

    int isHovered;
    int isPressed;
    int callCallback;

    char string[50];
};

struct App;

struct Button CreateButton (
    int x_, int y_, int w_, int h_, 
    char string_[50],
    SDL_Color borderColor_, 
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor
    );
void DrawButton (struct App* app, struct Button* button);
void EventButton (struct Button* button, SDL_Event* event);

#endif