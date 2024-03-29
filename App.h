#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

#include "Button.h"
#include "SliderDouble.h"
#include "SliderInt.h"

#define PI     3.141592653
#define TWO_PI 6.283185306

#define BUTTON_COUNT 1
#define SLIDER_DOUBLE_COUNT 2
#define SLIDER_INT_COUNT 4

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
    double speed;
    int isPaused;

    int linesRed; // Must use ints with sliders
    int linesGreen;
    int linesBlue;

    // GUI Variables

    Button* buttons;
    SliderDouble* slidersDouble;
    SliderInt* slidersInt;

    // These are textures for the texts, their name is what is written on them

    SDL_Texture* titleTexture;
    SDL_Rect titleRect;

    SDL_Texture* speedTexture;
    SDL_Rect speedRect;

    SDL_Texture* multiplierTexture;
    SDL_Rect multiplierRect;

    SDL_Texture* nbPointsTexture;
    SDL_Rect nbPointsRect;

    SDL_Texture* colorTexture;
    SDL_Rect colorRect;

    SDL_Texture* redTexture;
    SDL_Rect redRect;

    SDL_Texture* blueTexture;
    SDL_Rect blueRect;

    SDL_Texture* greenTexture;
    SDL_Rect greenRect;
} App;

void CreateApp (App* app, char* title, int wW, int wH, int fW, int fH, int nbPoints_, double mult_);
void DrawApp (App* app);
void DestroyApp (App* app);

#endif