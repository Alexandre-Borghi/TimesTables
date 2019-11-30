#include "Button.h"

#include "App.h"

struct Button CreateButton (
    int x_, int y_, int w_, int h_, 
    char string_[50],
    SDL_Color borderColor_, 
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor_
    )
{
    struct Button t;
    t.rect.x = x_;
    t.rect.y = y_;
    t.rect.w = w_;
    t.rect.h = h_;

    t.borderColor = borderColor_;

    t.fillColor = fillColor_;
    t.hoverColor = hoverColor_;
    t.pressColor = pressColor_;

    t.isPressed = 0;

    strcpy(t.string, string_);

    return t;
}

void DrawButton (struct App* app, struct Button* button)
{
    // Callback function

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