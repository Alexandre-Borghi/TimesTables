#include "Button.h"

#include "App.h"
#include "SDL2/SDL_ttf.h"

void CreateButton (
    struct App* app,
    struct Button* b,
    int x_, int y_, int w_, int h_, 
    char* string_,
    SDL_Color borderColor_, 
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor_,
    SDL_Color textColor_
    )
{
    // Geometry

    b->rect.x = x_;
    b->rect.y = y_;
    b->rect.w = w_;
    b->rect.h = h_;

    // Color

    b->borderColor = borderColor_;

    b->fillColor = fillColor_;
    b->hoverColor = hoverColor_;
    b->pressColor = pressColor_;

    // Control

    b->isPressed = 0;

    // Text

    TTF_Font* font = TTF_OpenFont("./font.ttf", 25);

    if (!font)
        printf("Error with font : %s\n", TTF_GetError());

    b->textColor = textColor_;
    SDL_Surface* surface = TTF_RenderText_Solid(font, string_, b->textColor);
    b->textTexture = SDL_CreateTextureFromSurface(app->renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    int texW = 0;
    int texH = 0;
    
    SDL_QueryTexture(b->textTexture, NULL, NULL, &texW, &texH);
    
    b->textRect = malloc(sizeof(SDL_Rect));
    b->textRect->w = texW;
    b->textRect->h = texH;
    b->textRect->x = b->rect.x + (b->rect.w / 2) - (b->textRect->w / 2);
    b->textRect->y = b->rect.y + (b->rect.h / 2) - (b->textRect->h / 2);
}

void DrawButton (struct App* app, struct Button* button)
{
    // TODO: Callback function

    if (button->callCallback == 1)
    {
        button->callCallback = 0;
        app->mult = 2;
    }

    // Drawing
    
    SDL_Color* bc = &(button->borderColor);
    SDL_Color* fc = &(button->fillColor);
    SDL_Color* hc = &(button->hoverColor);
    SDL_Color* pc = &(button->pressColor);

    if (button->isPressed == 1)
    {
        SDL_SetRenderDrawColor(app->renderer, pc->r, pc->g, pc->b, pc->a);
    }
    else if (button->isHovered == 1)
    {
        SDL_SetRenderDrawColor(app->renderer, pc->r, pc->g, pc->b, pc->a);
    }
    else
    {
        SDL_SetRenderDrawColor(app->renderer, fc->r, fc->g, fc->b, fc->a);   
    }
    
    SDL_RenderFillRect(app->renderer, &(button->rect));

    SDL_SetRenderDrawColor(app->renderer, bc->r, bc->g, bc->b, bc->a);
    SDL_RenderDrawRect(app->renderer, &(button->rect));

    // Drawing text

    SDL_RenderCopy(app->renderer, button->textTexture, NULL, button->textRect);
    SDL_RenderPresent(app->renderer);
}

static int IsPointInRect(Sint32 x, Sint32 y, SDL_Rect* rect)
{
    if (x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h)
        return 1;
    
    return 0;
}

void EventButton (struct Button* button, SDL_Event* e)
{
    // Button hovered

    if (e->type == SDL_MOUSEMOTION && IsPointInRect(e->motion.x, e->motion.y, &(button->rect)) == 1)
    {
        button->isHovered = 1;
    }
    else if (e->type == SDL_MOUSEMOTION)
    {
        button->isHovered = 0;
    }    

    // Button clicked

    if (e->type == SDL_MOUSEBUTTONDOWN && button->isHovered == 1)
    {
        button->isPressed = 1;
    }

    if (e->type == SDL_MOUSEBUTTONUP && button->isHovered == 1)
    {
        button->isPressed = 0;
        button->callCallback = 1;
    }
    else if (e->type == SDL_MOUSEBUTTONUP)
    {
        button->isPressed = 0;
    }
}

void ChangeTextButton (struct App* app, struct Button* b, char* newText)
{
    TTF_Font* font = TTF_OpenFont("./font.ttf", 25);

    if (!font)
        printf("Error with font : %s\n", TTF_GetError());

    SDL_Surface* surface = TTF_RenderText_Solid(font, newText, b->textColor);
    b->textTexture = SDL_CreateTextureFromSurface(app->renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    int texW = 0;
    int texH = 0;
    
    SDL_QueryTexture(b->textTexture, NULL, NULL, &texW, &texH);
    
    b->textRect = malloc(sizeof(SDL_Rect));
    b->textRect->w = texW;
    b->textRect->h = texH;
    b->textRect->x = b->rect.x + (b->rect.w / 2) - (b->textRect->w / 2);
    b->textRect->y = b->rect.y + (b->rect.h / 2) - (b->textRect->h / 2);
}

void DestroyButton (struct Button* button)
{
    SDL_DestroyTexture(button->textTexture);

    free(button->textRect);
}