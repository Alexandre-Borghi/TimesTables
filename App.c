#include "App.h"

void CreateApp (struct App* app, int wW, int wH, int fW, int fH, int nbPoints_, double mult_)
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
}

int InitApp (struct App* app, const char* title)
{
    // SDL2 and Window intialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: Couldn't initialize SDL2\n");
        return 0;
    }

    app->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->windowedWidth, app->windowedHeight, SDL_WINDOW_SHOWN);

    if (app->window == NULL) 
    {
        printf("ERROR: Couldn't create the window");
        return 0;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, 0);
}

void DrawApp (struct App* app)
{
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 20);

    double xOff = 355;
    double yOff = 355;

    // int* w;
    // int* h;
    // SDL_GetRendererOutputSize(renderer, w, h);

    double r = 700 / 2;

    // Drawing the outer circle
    SDL_Point points[app->nbPoints];
    // memset(points, 0, nbPoints * sizeof(SDL_Point));

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

    for (int i = 0; i < app->nbPoints; i++)
    {
        double theta = (TWO_PI / app->nbPoints) * i;

        double x1 = r * cos(theta) + xOff;
        double y1 = r * sin(theta) + yOff;

        theta = (TWO_PI / app->nbPoints) * i * app->mult;

        double x2 = r * cos(theta) + xOff;
        double y2 = r * sin(theta) + yOff;

        SDL_RenderDrawLine(app->renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }
}