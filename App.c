#include "App.h"
#include "Slider.h"
#include <SDL2/SDL_ttf.h>

void CreateApp (App* app, char* title, int wW, int wH, int fW, int fH, int nbPoints_, double mult_)
{
    /*
    This function helps to create an App struct

    App* app : Pointer to the struct to initialize

    int wW : The width of the window when in windowed mode
    int wH : The height of the window when in windowed mode
    int fW : The width of the window when in fullscreen mode
    int fH : The height of the window when in fullscreen mode

    int nbPoints_ : The number of points on the circle
    int mult_ : Number used to draw the pattern
    */

    app->windowedWidth = wW;
    app->windowedHeight = wH;
    app->fullscreenWidth = fW;
    app->fullscreenHeight = fH;

    app->nbPoints = nbPoints_;
    app->mult = mult_;

    // SDL2 and Window intialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: Couldn't initialize SDL2\n");
        return;
    }

    app->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->windowedWidth, app->windowedHeight, SDL_WINDOW_SHOWN);

    if (app->window == NULL) 
    {
        printf("ERROR: Couldn't create the window");
        return;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, 0);

    // SDL_ttf initialization

    if (TTF_Init() < 0)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    // GUI Creation

    SDL_Color borderColor = { 245, 245, 245, 255 };
    SDL_Color fillColor = { 120, 120, 120, 255 };
    SDL_Color hoverColor = { 190, 190, 190, 255 };
    SDL_Color pressColor = { 230, 230, 230, 255 };
    SDL_Color barColor = { 250, 250, 250, 255 };
    SDL_Color textColor = { 0, 0, 0, 255 };

    app->buttons = calloc(BUTTON_COUNT, sizeof(Button));
    app->sliders = calloc(SLIDER_COUNT, sizeof(Slider));

    CreateButton(app, &app->buttons[0], 800, 50, 430, 50, "Reset", borderColor, fillColor, hoverColor, pressColor, textColor);
    CreateSlider(&app->sliders[0], 800, 150, 430, 20, 2, 100, &app->mult, barColor, fillColor, hoverColor, pressColor);
}

void DrawApp (App* app)
{
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 20);

    double xOff = 355;
    double yOff = 355;

    double r = 700 / 2;

    // Drawing the outer circle
    SDL_Point points[app->nbPoints];

    for (int i = 0; i <= app->nbPoints; i++)
    {
        double theta = (TWO_PI / app->nbPoints) * i;

        SDL_Point temp;
        temp.x = r * cos(theta) + xOff;
        temp.y = r * sin(theta) + yOff;

        points[i] = temp;
    }

    // Adding the last point to close the circle
    points[app->nbPoints + 1] = points[0];

    SDL_RenderDrawLines(app->renderer, points, app->nbPoints + 1);

    // Drawing the lines inside the circle
    for (int i = 0; i < app->nbPoints; i++)
    {
        double theta = (TWO_PI / app->nbPoints) * i;

        double x1 = r * cos(theta) + xOff;
        double y1 = r * sin(theta) + yOff;

        theta = (TWO_PI / app->nbPoints) * i * app->mult;

        double x2 = r * cos(theta) + xOff;
        double y2 = r * sin(theta) + yOff;

        SDL_RenderDrawLine(app->renderer, x1, y1, x2, y2);
    }


    // GUI Drawing

    for (int i = 0; i < SLIDER_COUNT; i++)
    {
        DrawSlider(app, &(app->sliders[i]));
    }

    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        DrawButton(app, &(app->buttons[i]));
    }
}

void DestroyApp (App* app)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        DestroyButton(&(app->buttons[i]));
    }

    free(app->buttons);

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}