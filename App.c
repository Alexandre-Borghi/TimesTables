#include "App.h"
#include "SliderDouble.h"
#include <SDL2/SDL_ttf.h>

void resetMultApp (App* app)
{
    app->mult = 2.;
}

void togglePause (App* app)
{
    app->isPaused = !app->isPaused;
}

static SDL_Texture* textureFromText (App* app, char* text, int fontSize, SDL_Color textColor)
{
    TTF_Font* font = TTF_OpenFont("./font.ttf", fontSize);

    if (!font)
        printf("Error with font : %s\n", TTF_GetError());

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(app->renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    return textTexture;
}

static SDL_Rect getTextureRect (SDL_Texture* texture, int x, int y)
{
    int texW = 0;
    int texH = 0;
    
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    
    SDL_Rect textRect;
    textRect.w = texW;
    textRect.h = texH;
    textRect.x = x;
    textRect.y = y;

    return textRect;
}

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
    app->speed = 0.0005;
    app->isPaused = 0;

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

    SDL_Color black = { 0, 0, 0, 255 };
    SDL_Color white = { 255, 255, 255, 255 };

    SDL_Color borderColor = { 245, 245, 245, 255 };
    SDL_Color fillColor = { 120, 120, 120, 255 };
    SDL_Color hoverColor = { 190, 190, 190, 255 };
    SDL_Color pressColor = { 230, 230, 230, 255 };
    SDL_Color barColor = { 250, 250, 250, 255 };

    app->buttons = calloc(BUTTON_COUNT, sizeof(Button));
    app->slidersDouble = calloc(SLIDER_DOUBLE_COUNT, sizeof(SliderDouble));
    app->slidersInt = calloc(SLIDER_INT_COUNT, sizeof(SliderInt));

    app->titleTexture = textureFromText(app, "Times Tables Drawing", 40, white);
    app->titleRect = getTextureRect(app->titleTexture, 750, 25);

    app->speedTexture = textureFromText(app, "Speed", 30, white);
    app->speedRect = getTextureRect(app->speedTexture, app->titleRect.x,
        app->titleRect.y + app->titleRect.h + 20);
    
    app->multiplierTexture = textureFromText(app, "Multiplier", 30, white);
    app->multiplierRect = getTextureRect(app->multiplierTexture, app->titleRect.x,
        app->speedRect.y + app->speedRect.h + 20);
    
    app->nbPointsTexture = textureFromText(app, "Number of points", 25, white);
    app->nbPointsRect = getTextureRect(app->nbPointsTexture, app->titleRect.x,
        app->multiplierRect.y + app->multiplierRect.h + 20);
    
    CreateSliderDouble(&app->slidersDouble[0], app->speedRect.x + app->speedRect.w + 20,
    (app->speedRect.y + app->speedRect.h / 2) - 10,
    app->windowedWidth - 20 - (app->speedRect.x + app->speedRect.w + 20), 20, -0.001, 0.001, &app->speed, barColor, fillColor, hoverColor, pressColor);

    CreateSliderDouble(&app->slidersDouble[1], app->multiplierRect.x + app->multiplierRect.w + 20,
    (app->multiplierRect.y + app->multiplierRect.h / 2) - 10,
    app->windowedWidth - 20 - (app->multiplierRect.x + app->multiplierRect.w + 20), 20, 0, app->nbPoints, &app->mult, barColor, fillColor, hoverColor, pressColor);
    
    CreateSliderInt(&app->slidersInt[0], app->nbPointsRect.x + app->nbPointsRect.w + 20,
    (app->nbPointsRect.y + app->nbPointsRect.h / 2) - 10,
    app->windowedWidth - 20 - (app->nbPointsRect.x + app->nbPointsRect.w + 20), 20, 0, 1000, &app->nbPoints, barColor, fillColor, hoverColor, pressColor);

    CreateButton(app, &app->buttons[0], app->titleRect.x, app->nbPointsRect.y + app->nbPointsRect.h + 20,
    app->windowedWidth - 20 - app->titleRect.x, 50, "Pause/Play", borderColor, fillColor, hoverColor, pressColor, black, &togglePause);
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

    for (int i = 0; i < SLIDER_DOUBLE_COUNT; i++)
    {
        DrawSliderDouble(app, &app->slidersDouble[i]);
    }

    for (int i = 0; i < SLIDER_INT_COUNT; i++)
    {
        DrawSliderInt(app, &app->slidersInt[i]);
    }

    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        DrawButton(app, &app->buttons[i]);
    }

    SDL_RenderCopy(app->renderer, app->titleTexture, NULL, &app->titleRect);
    SDL_RenderCopy(app->renderer, app->speedTexture, NULL, &app->speedRect);
    SDL_RenderCopy(app->renderer, app->multiplierTexture, NULL, &app->multiplierRect);
    SDL_RenderCopy(app->renderer, app->nbPointsTexture, NULL, &app->nbPointsRect);
}

void DestroyApp (App* app)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        DestroyButton(&(app->buttons[i]));
    }

    free(app->buttons);

    SDL_DestroyTexture(app->titleTexture);
    SDL_DestroyTexture(app->speedTexture);
    SDL_DestroyTexture(app->multiplierTexture);

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}