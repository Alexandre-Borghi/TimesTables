#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

typedef struct App App;

typedef struct Button
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

    void (*callback)(App*);

    // Text

    SDL_Texture* textTexture;
    SDL_Rect* textRect;
} Button;


void CreateButton (
    App* app,
    Button* button,
    int x_, int y_, int w_, int h_, 
    char* string_,
    SDL_Color borderColor_, 
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor,
    SDL_Color textColor_,
    void (callback_)(App*)
    );
void DrawButton (App* app, Button* button);
void EventButton (Button* button, SDL_Event* event);
void ChangeTextButton (App* app, Button* b, char* newText);
void DestroyButton (Button* button);

#endif