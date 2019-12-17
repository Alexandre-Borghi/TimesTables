#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

struct Button
{
    // Geometry

    SDL_Rect rect;

    // Color

    SDL_Color borderColor;
    SDL_Color fillColor;
    SDL_Color hoverColor;
    SDL_Color pressColor;
    SDL_Color textColor;

    // Control

    int isHovered;
    int isPressed;
    int callCallback;

    // Text

    SDL_Texture* textTexture;
    SDL_Rect* textRect;
};

struct App;

void CreateButton (
    struct App* app,
    struct Button* button,
    int x_, int y_, int w_, int h_, 
    char* string_,
    SDL_Color borderColor_, 
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor,
    SDL_Color textColor_
    );
void DrawButton (struct App* app, struct Button* button);
void EventButton (struct Button* button, SDL_Event* event);
void ChangeTextButton (struct App* app, struct Button* b, char* newText);
void DestroyButton (struct Button* button);

#endif