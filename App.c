#include "App.h"
#include "Slider.h"

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

   // GUI Creation

   SDL_Color borderColor;
   borderColor.r = 245;
   borderColor.g = 245;
   borderColor.b = 245;
   borderColor.a = 255;

   SDL_Color fillColor;
   fillColor.r = 120;
   fillColor.g = 120;
   fillColor.b = 120;
   fillColor.a = 255;

   SDL_Color hoverColor;
   hoverColor.r = 190;
   hoverColor.g = 190;
   hoverColor.b = 190;
   hoverColor.a = 255;

   SDL_Color pressColor;
   pressColor.r = 230;
   pressColor.g = 230;
   pressColor.b = 230;
   pressColor.a = 255;

   SDL_Color barColor;
   barColor.r = 250;
   barColor.g = 250;
   barColor.b = 250;
   barColor.a = 255;

   app->buttons[0] = CreateButton(800, 50, 430, 50, "BUTTON", borderColor, fillColor, hoverColor, pressColor);
   app->sliders[0] = CreateSlider(800, 150, 430, 20, 2, 100, &app->mult, barColor, fillColor, hoverColor, pressColor);
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

    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        DrawButton(app, &(app->buttons[i]));
    }

    for (int i = 0; i < SLIDER_COUNT; i++)
    {
        DrawSlider(app, &(app->sliders[i]));
    }
}